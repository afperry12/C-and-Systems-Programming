
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)
#define LEN 64

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

// structure for password and hash that will be saved and pulled from file
struct PasswordDictionary {
	char hash[LEN+1];
	char password[LEN+1];
};

// add the Password Dictionary containing the password and hash to file
void AddToFile(FILE* fp, char* cleartextPassword) {
	char hashOfCleartext[DIG_STR_LEN];
	sha256(hashOfCleartext, cleartextPassword);
	
	struct PasswordDictionary pd;
	
	memset(&pd, 0, sizeof(struct PasswordDictionary));

	strncpy(pd.hash, hashOfCleartext, LEN);
	strncpy(pd.password, cleartextPassword, LEN);
	
	fwrite(&pd, sizeof(struct PasswordDictionary), 1, fp);
}

// read each password and hash in file and if it matches inputted hash, print cleartext
void ReadFromFile(FILE* fp, char* hash) {

	struct PasswordDictionary pd;
		
	memset(&pd, 0, sizeof(struct PasswordDictionary));
	bool notFound = true;
	while(fread(&pd, sizeof(struct PasswordDictionary), 1, fp)==1) {

	if(strcmp(pd.hash,hash)==0) {
		printf("%s\n", pd.password);
		notFound = false;
	}
	
	}
	if(notFound == true) {
		printf("not found\n");
	}
}

// convert a password to its l33t version and call function to add it to file
void L33tAdder(FILE* fp, char* passwordBeforeL33t) {
char updatePassword[strlen(passwordBeforeL33t)+1];
	strcpy(updatePassword, passwordBeforeL33t);
	for(int j = 0; j<strlen(updatePassword);j++) {
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
			
	if(strcmp(passwordBeforeL33t, updatePassword)!=0) {
		AddToFile(fp, updatePassword);
	}
}

// add a 1 to the end of the word and add it to file through AddToFile function
void Plus1Adder(FILE* fp, char* passwordBeforePlus1) {
	char plus1Password[strlen(passwordBeforePlus1)+1];
	strcpy(plus1Password, passwordBeforePlus1);
	strcat(plus1Password, "1");
	AddToFile(fp, plus1Password);
}



int main(int argc, char **argv) {
	// if only 1 argument then create Dictionary.txt if it does not exist. If it already exists, print it exists.
	if(argc==1) {
	if(!access("Dictionary.txt",F_OK)) {
		printf("dictionary exists\n");
	} else {
		FILE *fp = fopen("Dictionary.txt","a");

		for(int i = 0; i<10000; i++) {
		AddToFile(fp, passwords[i]);
		L33tAdder(fp, passwords[i]);
		Plus1Adder(fp, passwords[i]);
		}
		
		printf("dictionary built\n");
		fclose(fp);
	}
	}

	// if 2 arguments and the file exists then ReadFromFile the password that is associated with given hash (second argument passed through)
	if(argc==2) {
	FILE *fp = fopen("Dictionary.txt","r");
	if(fp!=NULL) {
	char* hash = argv[1];
	ReadFromFile(fp, hash);
	fclose(fp);
	} else {
		printf("file does not exist\n");
	}
	}
	return 0;
}
