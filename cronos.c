#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <time.h>

void rockthehash(char *string, char *hash) {
    int i;
    char unsigned md5[MD5_DIGEST_LENGTH] = {0};

    MD5((const unsigned char *)string, strlen(string), md5);

    for (i=0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + 2*i, "%02x", md5[i]);
    }
}

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("Usage : cronos <wordlist> <md5 hash>\n");
		return 0;
	}
	clock_t start, end;
	double cpu_time;
	start = clock();
    char md5_hash[2*MD5_DIGEST_LENGTH+1] = "";
	FILE *rockyoufile;
	rockyoufile = fopen(argv[1], "r");
	char line[255];
	printf("Cronos is cracking the hash...\n");
	while(fgets(line, sizeof(line), rockyoufile)){ 
		line[strcspn(line, "\n")] = 0;
		rockthehash(line, md5_hash);
		if(memcmp(argv[2], md5_hash, 16) == 0) {
			end = clock();
			cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("\rResult : %s\n", line);
			printf("Found in : %f\n", cpu_time);
			return 0;
		}
	}
	end = clock();
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Nothing was found, try another wordlist\n");
	printf("Time taken : %f\n", cpu_time);
	return 0;
}
