#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * initialFirst(char *first, char *stringToLookFor) {
		first = strstr(first, stringToLookFor);
		if(first == NULL) {
			printf("0\n");
			exit(0);
		}
		return first;
}

void nextIterations(char *next, char *stringToLookFor) {
		int count = 1;
		// while there is another instance of the substring in the main string, continue
		while(next != NULL) {
			// return next instance of substring by getting the main string starting at the first pointer location of the last instance of the substring
			// and adding the length of the substring to get the correct starting location after the most recent instance of the substring and traversing
			// until the next instance or setting next to null if no other instances found
			next = strstr(next + strlen(stringToLookFor), stringToLookFor);
		// only increase count if next is not null	
		if(next!=NULL) {
				count++;
			}
		}

		printf("%d\n",count);
		exit(0);
}

// main function takes in string to scan and string to search for
int main(int argc, char **argv) {
	// if there are not three arguments, exit
	if (argc != 3) {
		printf("invalid arguments\n");
		exit(1);
	}
	// return the pointer value of the first char in the chars that match the substring to look for if it exists
	char* first = initialFirst(argv[1],argv[2]);

	// printf("%p\n", first);
	// printf("%c\n", *first+1);

	// send the pointer value for the first character found in the string that matches the substring and the original substring to search for
	nextIterations(first, argv[2]);
		
	return 0;
}
