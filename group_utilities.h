#ifndef GROUP_UTILITIES_H
#define GROUP_UTILITIES_H

#include <sys/types.h>
#include <stdbool.h>

struct group{
	char *gr_name; 	 // Pointer to a string containing the name of the group
	char *gr_passwd; // Pointer to a string containing the group's password
	gid_t gr_gid; 	 // The group's numerical ID (gid)
	char **gr_mem; 	 // Pointer to an array of strings, each containing a member's username
};

struct group *getgrnam(char *name);
struct group *getgrgid(char *id);
bool myprint(char *string);
char* readLineName(int fd, char *name);
char* readLineId(int fd, char *id);
bool findLineName(char *line, char *name);
bool findLineId(char *line, char *id);
struct group *newGroup(char *name, char *passwd, gid_t id, char **mems, int count);

#endif



