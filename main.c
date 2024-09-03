/* gcc -std=c99 -Wall -Wextra main.c group_utilities.c group_utilities.h mystring.c mystring.h */

#include <stdio.h>
#include <stdlib.h>
#include "group_utilities.h"
#include "mystring.h"

#define BUF_SIZE    (8096)
#define check_error(cond, msg)\
	do{\
		if(!(cond)){\
			perror(msg);\
			fprintf(stderr,"%s:%d\n",__FILE__,__LINE__);\
			exit(EXIT_FAILURE);\
		}\
	}while(0)


int main(int argc, char **argv) {
	check_error(argc == 3, "args");

	// Get group by name
	struct group *gr1 = getgrnam(argv[1]);
	check_error(gr1!=NULL,"getgrnam");

	// Print group details for the first group
	myprint("\nName = ");
	myprint(gr1->gr_name);
	myprint("\nPassword = ");
	myprint(gr1->gr_passwd);
	myprint("\nId = ");
	char gid1[3];
	tostring(gid1,gr1->gr_gid);
	myprint(gid1);
	myprint("\nMembers = \n");
	if(gr1->gr_mem !=NULL)
		for(int i=0; gr1->gr_mem[i]!= NULL; i++){
			myprint(gr1->gr_mem[i]);
			myprint("\n");
			
		}
	free(gr1);

	// Get group by gid
	struct group *gr2 = getgrgid(argv[2]);
	check_error(gr2!=NULL,"getgrgid");

	// Print group details for the second group
	myprint("\nName = ");
	myprint(gr2->gr_name);
	myprint("\nPassword = ");
	myprint(gr2->gr_passwd);
	myprint("\nId = ");
	char gid2[3];
	tostring(gid2,gr2->gr_gid);
	myprint(gid2);
	myprint("\nMembers = \n");
	if(gr2->gr_mem !=NULL)
		for(int i=0; gr2->gr_mem[i]!= NULL; i++){
			myprint(gr2->gr_mem[i]);
			myprint("\n");		
		}
	
	
	free(gr2);

	return 0;
}


