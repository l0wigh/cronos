#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

void rockthehash(char *string, char *hash) {
	int i;
	char unsigned md5[MD5_DIGEST_LENGTH] = {0};

	MD5((const unsigned char *)string, strlen(string), md5);

	for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(hash + 2 * i, "%02x", md5[i]);
	}
}

int main(int argc, char *argv[]) {
	pthread_t thread_id;
	if (argc < 3) {
		printf("Usage : cronos <wordlist> <md5 hash>\n");
		return 0;
	}
	char md5_hash[2 * MD5_DIGEST_LENGTH + 1] = "";
	if (memcmp(argv[2], "-b", 2) == 0) {
		printf("Not implamented right now, use a wordlist\n");
		return 0;
	}
	else {
		FILE *rockyoufile;
		rockyoufile = fopen(argv[1], "r");
		char line[255];
		printf("Cronos is cracking the hash...\n");
		while (fgets(line, sizeof(line), rockyoufile)) {
			line[strcspn(line, "\n")] = 0;
			pthread_create(&thread_id, NULL, rockthehash, (line, md5_hash));
			if (memcmp(argv[2], md5_hash, 16) == 0) {
				printf("\rResult : %s\n", line);
				return 0;
			}
		}
	}
	printf("Nothing was find, try another wordlist\n");
	return 0;
}
