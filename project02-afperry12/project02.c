
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)
#define MAX_PASSWORD_LEN 64

//hash strings
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

//substitute string for l33t version then then copy value to variable from main
void L33tAdder(char* passwordBeforeL33t, char* passwordAfterL33t) {
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
		strcpy(passwordAfterL33t, updatePassword);
}

//add 1 to end of string then copy value to variable from main
void Plus1Adder(char* passwordBeforePlus1, char* passwordAfterPlus1) {
	char plus1Password[strlen(passwordBeforePlus1)+1];
	strcpy(plus1Password, passwordBeforePlus1);
	strcat(plus1Password, "1");
	strcpy(passwordAfterPlus1,plus1Password);
}

//create a struct that holds the password, hash, and the next node
struct entry {
	char password[MAX_PASSWORD_LEN + 1];
	char hash[DIG_STR_LEN + 1];
	struct entry *next;
};

//function for inserting a new node into the list starting at specific head
//utilize double pointer for head to always update values on the original
//head created in main and so we do not need to return a new head everytime
void InsertIntoLinkedList(struct entry **head, char* password, char* hash) {
	struct entry *current = malloc(sizeof(struct entry));
	//if malloc fails, then return
	if(!current) {
		printf("malloc failed\n");
		return;
	}
	//copy relevant values to variables in newly created node instance
	strncpy(current->password, password, MAX_PASSWORD_LEN+1);
	strncpy(current->hash, hash,MAX_PASSWORD_LEN+1);
	current->next = NULL;
	//keep track of current compare node and previous compare node
	//so we know where to insert node in certain circumstances
	struct entry *compare = malloc(sizeof(struct entry));
	struct entry *prevCompare = malloc(sizeof(struct entry));
	//assign the compare variable to head if it is not null,
	//otherwise do not do anything because a NULL head is handled in while
	//statement below
	if((*head)!=NULL) {
		compare=(*head);
	}
	int i = 0;
	int j = 0;
	//using a while statement to continuously traverse down nodes until
	//knowing where we need to insert
	while(true) {
		//if head is null then set head to the node being inserted since it is
		//the first node in list
		if(!(*head)) {
			(*head) = current;
			break;
		} 
		//first, if hash in list is the same as the new hash, break
		//because no duplicates allowed
		if(strcmp((compare->hash),(current->hash)) == 0) {
			break;
		}
		//if the hash in list is less than the new hash, then
		//if there is no next node in list, insert new node
		//else if the head's next value is null, set head's next
		//variable to new node
		//else simply move down the list to compare the new hash
		//with the next node to find a hash that is greater
		if( (compare->hash)[i] < (current->hash)[i] ) {
			if(compare->next != NULL) {
				prevCompare = compare;
				compare = compare->next;
				i=0;	
				j++;
			} else {
			if((*head)->next == NULL) {
				(*head)->next = current;
				break;
			} else {
				compare->next = current;
				break;
				}
			}
		}
		//check if chars at position i are equal
		//if they are equal, then increment i to check next place value
		else if( (compare->hash)[i] == (current->hash)[i] ) {
			i++;
		} 
		//finally, check if the char at i in the hash of the node already 
		//in the list is greater than char i in new node's hash
		//if it is, then
		//check if it is the head's hash that is greater than the new hash
		//if it is the head's hash value, then make the new node become the head
		//if it is not the head's hash value, simply insert the new node before the
		//node currently being compared with
		else if( (compare->hash)[i] > (current->hash)[i] ) {
		if(j==0) {
				current->next = (*head);
				(*head) = current;
			} else {
				prevCompare->next = current;
				current->next = compare;
			}
			break;
		}	
	};
};

//print out linked list
void PrintLinkedList(FILE *saveFile, struct entry **node, bool verbose) {
	//handle verbose separately
	if(verbose) {
		printf("%s %.05s...\n",(*node)->password,(*node)->hash);
	} else {
	fwrite((*node)->hash, sizeof(char),strlen((*node)->hash), saveFile);
	fwrite(",", sizeof(char),sizeof(",")-1, saveFile);
	fwrite((*node)->password, sizeof(char),strlen((*node)->password), saveFile);
	fwrite("\n", sizeof(char),sizeof("\n")-1, saveFile);
	}

	//stopping condition
	if((*node)->next==NULL) {
	} else {
		PrintLinkedList(saveFile, &(*node)->next, verbose);
	};
};

//calculate length of linked list
int LinkedListLength(struct entry **head, int length) {
	if((*head)->next != NULL) {
		return LinkedListLength(&(*head)->next, length+1);
	}
	return length+1;
};



int main(int argc, char **argv) {
	//check for correct arguments
	if( ! access(argv[1],F_OK) && (argc >= 3 && argc <= 4)) {
	} else {
		return -1;
	}

	bool verbose = false;
	//check for verbose arg
	if(argc == 4) {
	if(strcmp(argv[3],"-v") == 0) {
		verbose = true;
	}
	}
	//open files with r and w
	FILE *fp = fopen(argv[1],"r");
	FILE *saveFile = fopen(argv[2],"w");
	if(fp) {
		char password[MAX_PASSWORD_LEN+1];
		//create head variable
		struct entry *head = NULL;
		//do the following process for every line in file
		while(fgets(password, sizeof(password), fp)) {
		if(password[strlen(password)-1]=='\n') {
			password[strlen(password)-1]='\0';
		}
	
		char hashOfCleartext[DIG_STR_LEN];
		sha256(hashOfCleartext, password);

		// insert basic password and hash as taken from file and handle verbose if needed
		InsertIntoLinkedList(&head, password, hashOfCleartext);
		if(verbose) {
			printf("inserting: %s\n",password);
			// take & of *head because this = **head, so changes persist after method
			PrintLinkedList(fp, &head, verbose);
			printf("\n");
		}

		char l33tPassword[MAX_PASSWORD_LEN+1];
		L33tAdder(password, l33tPassword);
		
		char hashOfL33t[DIG_STR_LEN];
		sha256(hashOfL33t, l33tPassword);
		if(l33tPassword!=NULL){
		// insert l33t version of password and hash as taken from file and handle verbose if needed
		InsertIntoLinkedList(&head, l33tPassword, hashOfL33t);
		}
		if(verbose) {
				printf("inserting: %s\n",l33tPassword);
				PrintLinkedList(fp, &head, verbose);
				printf("\n");
		}

		char plus1Password[MAX_PASSWORD_LEN+1];
		Plus1Adder(password, plus1Password);
		
		char hashOfPlus1[DIG_STR_LEN];
		sha256(hashOfPlus1, plus1Password);
		// insert plus1 version of password and hash as taken from file and handle verbose if needed
		InsertIntoLinkedList(&head, plus1Password, hashOfPlus1);
		if(verbose) {
				printf("inserting: %s\n",plus1Password);
				PrintLinkedList(fp, &head, verbose);
				printf("\n");
		}
		
	}
	// get list length to fprintf to file and print all passwords and hashes from list in order
	int listLength = LinkedListLength(&head, 0);
	fprintf(saveFile,"%d",listLength);
	fwrite("\n", sizeof(char),sizeof("\n")-1, saveFile);
	PrintLinkedList(saveFile, &head, false);
	fclose(saveFile);
	}
	return 0;
}
