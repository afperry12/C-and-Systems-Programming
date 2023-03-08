
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

void sha256(char *dest, char *src) {
    // zero out the sha256 context
    struct sha256_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));

    // zero out the binary version of the hash digest
    unsigned char dig_bin[DIG_BIN_LEN];
    memset(dig_bin, 0, DIG_BIN_LEN);

    // zero out the string version of the hash digest
    memset(dest, 0, DIG_STR_LEN);

    // compute the binary hash digest
    __sha256_init_ctx(&ctx);
    __sha256_process_bytes(src, strlen(src), &ctx);
    __sha256_finish_ctx(&ctx, dig_bin);

    // convert it into a string of hexadecimal digits
    for (int i = 0; i < DIG_BIN_LEN; i++) {
        snprintf(dest, 3, "%02x", dig_bin[i]);
        dest += 2;
    }
}

// check if the inputted hash matches the hash of the clear text passwords stored in passwords.c file
bool PasswordsMatchChecker(char* hash,char* cleartextPassword) {
	char hashOfCleartext[DIG_STR_LEN];
	sha256(hashOfCleartext, cleartextPassword);
	if(!strcmp(hash, hashOfCleartext)) {
		printf("%s\n", cleartextPassword);
		return true;
	} else {
		return false;
			}
}

// convert a password to its l33t version and compare it to the original hash
bool L33tChecker(char* hash, char* passwordBeforeL33t) {
char updatePassword[strlen(passwordBeforeL33t)+1];
	strcpy(updatePassword, passwordBeforeL33t);
	for(int j = 0; j<strlen(passwordBeforeL33t);j++) {
		switch (updatePassword[j]) {
			case 'o':
				updatePassword[j] = '0';
				break;
			case 'e':
				updatePassword[j] = '3';
				break;
			case 'i':
				updatePassword[j] = '!';
				break;
			case 'a':
				updatePassword[j] = '@';
				break;
			case 'h':
				updatePassword[j] = '#';
				break;
			case 's':
				updatePassword[j] = '$';
				break;
			case 't':
				updatePassword[j] = '+';
				break;
			default:
				break;
		}
	}
	return PasswordsMatchChecker(hash, updatePassword);	
}

// add a 1 to the end of the word and run PasswordsMatchChecker to see if the new word's hash matches the original hash
bool PasswordPlus1Checker(char* hash, char* passwordBeforePlus1) {
	char plus1Password[strlen(passwordBeforePlus1)+1];
	strcpy(plus1Password, passwordBeforePlus1);
	strcat(plus1Password, "1");
	return PasswordsMatchChecker(hash, plus1Password);
}

int main(int argc, char **argv) {
	//invalid # of arguments
	if(argc != 2) {
		//add error statement invalid arguments???
		exit(0);
	}

	//Get hash from arguments
	char argHashedPassword[DIG_STR_LEN];
	strcpy(argHashedPassword, argv[1]);
	

	for(int i = 0; i<10000; i++) {
		bool passwordFound = PasswordsMatchChecker(argHashedPassword, passwords[i]);

		if(passwordFound) {
			exit(0);
		}

		bool passwordFoundL33t = L33tChecker(argHashedPassword, passwords[i]);

		if(passwordFoundL33t) {
			exit(0);
		}

		bool passwordFoundPlus1 = PasswordPlus1Checker(argHashedPassword, passwords[i]);

		if(passwordFoundPlus1) {
			exit(0);
		}
	}
	printf("not found\n");
	return 0;
}
