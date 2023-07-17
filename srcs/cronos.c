#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <time.h>

void rockthehash(char *string, char *hash)
{
	EVP_MD_CTX *mdctx;
	unsigned int md5_digest_len = EVP_MD_size(EVP_md5());
	unsigned char *md5;

	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

	EVP_DigestUpdate(mdctx, string, strlen(string));

	md5 = (unsigned char *)OPENSSL_malloc(md5_digest_len);
	EVP_DigestFinal_ex(mdctx, md5, &md5_digest_len);
	EVP_MD_CTX_free(mdctx);
	for (int i = 0; i < EVP_MD_size(EVP_md5()); i++)
		sprintf(hash + 2 * i, "%02x", md5[i]);
}

int main(int argc, char *argv[]) {
    clock_t start, end;
    double 	cpu_time;

	if(argc < 3)
	{
		printf("Usage : cronos <md5 hash> <wordlist>\n");
		printf("Error : Not enough args\n");
		return 1;
	}
	start = clock();
    char md5_hash[2*EVP_MD_size(EVP_md5())+1];
	FILE *rockyoufile;
	rockyoufile = fopen(argv[2], "r");
	if (!rockyoufile)
	{
		printf("Usage : cronos <md5 hash> <wordlist>\n");
		printf("Error : file not found\n");
		return 2;
	}
	char line[255];
	printf("\033[0;31mCronos \e[0mis cracking the hash...\n");
	while(fgets(line, sizeof(line), rockyoufile))
	{
		line[strcspn(line, "\n")] = 0;
		rockthehash(line, md5_hash);
		if(memcmp(argv[1], md5_hash, 16) == 0)
		{
			end = clock();
			cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("\r\e[0mResult   :\033[0;34m %s\n", line);
			printf("\e[0mFound in : %f\n", cpu_time);
			return 0;
		}
	}
	end = clock();
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\rNothing was found, try another wordlist\n");
	printf("Time taken : %f\n", cpu_time);
	return 0;
}
