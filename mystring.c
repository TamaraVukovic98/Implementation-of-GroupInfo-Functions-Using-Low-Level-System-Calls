#include "mystring.h"
#include <stdbool.h>
#include <stdio.h>

// Function mystrlen calculates and returns the length of a string `s`.
int mystrlen(char *s){
	int i;
	for(i=0; *(s+i); i++);
	return i;
}

/* Function mystrcmp compares two strings `s` and `t` character by character:
	returns 0 if the strings are identical,
	a positive value if `s` is lexicographically greater than `t`,
	a negative value if `s` is lexicographically less than `t`. */
int mystrcmp(char *s, char *t){
	int i;
	for(i=0; *(s+i)==*(t+i); i++) {
		if(*(s+i) == '\0') {
			return 0;
		}
	}
	return *(s+i)-*(t+i);	
}
  
/* Function prefix checks if the string `prefix` is a prefix of the string `s`:
	returns 1 if `prefix` matches the beginning of `s`, 
	returns 0 if `prefix` is not a prefix of `s`. */
int prefix(char *s, char *prefix){
	int i;
	int len_prefix = mystrlen(prefix);
	int len_s = mystrlen(s);
	if(len_prefix <= len_s){
		for(i=0; i<len_prefix; i++) {
			if(*(prefix+i) != *(s+i)) {
				return 0;
			}
		}
		return 1;
	} 
	else {
		return 0;
	}
}

/* Function infix checks if the string `infix` is a substring of the string `s`:
    returns the starting index of `infix` within `s` if found,
    returns -1 if `infix` is not found within `s`.*/
int infix(char *s, char *infix){
	int i,j;
	int len_infix = mystrlen(infix);
	int len_s = mystrlen(s);
	bool isPresent = false; // Flag to indicate if infix is found
	for (i=0; i < len_s - len_infix; i++){
		isPresent = true;
		
		for(j=0; j<len_infix; j++){

			if(*(infix+j) != *(s+j+i)){			
				isPresent = false;
				break;
			}
		}

		if (isPresent) {
         		return i;
       	}
	}
	
	if (isPresent) {
		return i;
	}
	else {
		return -1;
	}
}

/* Function tostring takes an integer `num` and converts it to a string, 
   storing the result in the character array `str[]`.*/
void tostring(char str[], int num){
    int i, rem, len = 0, n;
 
	if (num == 0) { // Handle the case where num is 0
    	str[0] = '0';
    	str[1] = '\0';
    	return;
	}

	n = num;
	// Calculate the length of the number by counting digits
    while (n != 0) {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++) {
        rem = num % 10; // Get the last digit
        num = num / 10;	// Remove the last digit from the number
        str[len - (i + 1)] = rem + '0'; // Store the digit as a character
    }
    str[len] = '\0';
}


/*
int infixmod(char *s, char *infix){
	int i,j;
	int len_infix = mystrlen(infix);
	int len_s = mystrlen(s);
	bool isPresent = false;
	for (i=0; i<len_s;i++){
		isPresent = false;
		if(*infix == *(s+i) && mystrlen(infix)==1)
			return i;
		else if(*infix == *(s+i) && *(infix+1)!=*(s+i+1))
			return -1;
		else if(*infix == *(s+i) && *(infix+1)==*(s+i+1) && *(infix+2)!=*(s+i+2))
			return -1;
		for(j=0; j<len_infix; j++){
			if(*(infix+j) != *(s+j+i)){
				
				isPresent = false;
				break;
			}
			isPresent = true;
		}
		if (isPresent) {
         		break;
       		}
	}
	
	if (isPresent) {
		return j+i;
	}
	else 
		return -1;
}*/

// Function mystrchr finds the first occurrence of a character `c` in the string `s`
int mystrchr(char *s, char c){
	int i; 
	
	for(i=0; *(s+i); i++)
		if(*(s+i) == c)
			return i; // Return the index if a match is found
	return -1; // Character not found
}

// Function mystrrchr finds the last occurrence of a character `c` in a string `s`.
int mystrrchr(char *s, char c) {
    int i;
    int len = mystrlen(s);  // Length of the string, excluding null terminator

    for (i = len - 1; i >= 0; i--) {  // Start from the last character
        if (*(s + i) == c)
            return i; // Return the index if a match is found
    }
    return -1;  // Character not found
}

// Function mystrcat appends the string `append` to the end of the string `s`.
char* mystrcat(char *s, const char *append){
	char *save = s; // Save the starting address of the destination string

	for (; *s; ++s); // Move the pointer `s` to the end of the existing string
	while ((*s++ = *append++) != '\0'); // Append each character from `append` to the end of `s`

	return save;
}

// Function mystrcpy copies the string `from` to the destination buffer `to`.
char* mystrcpy(char *to, const char *from){
	char *save = to; // Save the starting address of the destination buffer

	for (; (*to = *from) != '\0'; ++from, ++to); // Copy characters from `from` to `to` including the null terminator

	return save; // Return the pointer to the beginning of the destination buffer
}


/* Function mystrtok is designed to tokenize a string based on a delimiter. 
   It splits the string into tokens separated by the delimiter and returns one token at a time. 
   The function uses a static pointer to keep track of the current position in the string between calls. */
char* mystrtok(char *string, char *delim){
	static char *remember = NULL; // Static pointer to keep track of the current position
	int string_length = 0;
	int i= 0;
	int search_hit=0;

	// Return NULL if delimiter is NULL
	if(delim == NULL)
                return NULL;

	// Handle the case where `string` is NULL and `remember` is also NULL
	if((string == NULL) && (remember == NULL))
                return NULL;

	// If `string` is NULL, use the saved position from the previous call
	if(string == NULL)
                string = remember;

	string_length = mystrlen(string) + 1; // Calculate the length of the string including null terminator

	// Find the first occurrence of the delimiter
	for(i=0; i<string_length; i++){
		if(string[i] == delim[0]){
			search_hit = 1 ;
			break;
		}
	}
	// If delimiter is not found, return the whole string
	if(search_hit != 1){
		remember = NULL;
			return string;
	}
	string[i] = '\0'; // Null-terminate the token

	// Set `remember` to the next token's starting position
	if((string+i+1) != NULL)
		remember = string + i + 1;
	else
		remember = NULL;

	return string;
}
