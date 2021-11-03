#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

void rockthehash(char *string, char *hash) {
	int i;
	char unsigned md5[MD5_DIGEST_LENGTH] = {0};

	MD5((const unsigned char *)string, strlen(string), md5);

	for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(hash + 2 * i, "%02x", md5[i]);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage : cronos <wordlist> <md5 hash>\n");
		return 0;
	}

	char md5_hash[2 * MD5_DIGEST_LENGTH + 1] = "";
	FILE *rockyoufile;
	FILE *reverserockyoufile;
	rockyoufile = fopen(argv[1], "r");
	reverserockyoufile = fopen(argv[1], "r");
	char line[255];
	char reverseline[255];
	int i = 0;
	printf("Cronos is cracking the hash...\n");
	while (fgets(line, sizeof(line), rockyoufile)) {
		fseek(reverserockyoufile, -i, SEEK_END);
		fgets(reverseline, sizeof(reverseline), reverserockyoufile);
		line[strcspn(line, "\n")] = 0;
		reverseline[strcspn(line, "\n")] = 0;
		i++;
		/**
		rockthehash(line, md5_hash);
		if (memcmp(argv[2], md5_hash, 16) == 0) {
			printf("\rResult : %s\n", line);
			return 0;
		}
		**/
		rockthehash(reverseline, md5_hash);
		if (memcmp(argv[2], md5_hash, 16) == 0) {
			printf("\rResult : %s\n", line);
			return 0;
		}
	}
	printf("Nothing was find, try another wordlist\n");
	return 0;
}
