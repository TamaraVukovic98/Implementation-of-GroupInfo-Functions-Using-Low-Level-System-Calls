#include "group_utilities.h"
#include "mystring.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE    (8096)
#define check_error(cond, msg)\
	do{\
		if(!(cond)){\
			perror(msg);\
			fprintf(stderr,"%s:%d\n",__FILE__,__LINE__);\
			exit(EXIT_FAILURE);\
		}\
	}while(0)

/* Function myprint uses the `write` system call to output the given string to the standard output (stdout).
 * It returns `true` if the printing operation was successful, or `false` if an error occurred. */
bool myprint(char *string){
	if(write(STDOUT_FILENO,string, mystrlen(string))<0)
		return false;
	return true;
}

/* Function getgrnam searches for a group by name in the `/etc/group` file and 
 * returns a struct group representing it. */
struct group *getgrnam( char *name){
	int fd = open("/etc/group", O_RDONLY);
	check_error(fd != -1, "open");

    	char *line = NULL;
	
	line = readLineName(fd,name);
	if (line == NULL){	
		return NULL;
	}
	char *token = NULL;
	int position = mystrrchr(line,':');
	int len = mystrlen(line);
	
	token = mystrtok(line,":");
	char *pswd = mystrtok(NULL,":");
	int id = atoi(mystrtok(NULL,":"));
	char *memstring = mystrtok(NULL,":");
	
	
	if(position+1 == len){
		char **mems=NULL;
		struct group *gr = newGroup(name,pswd,id,mems,0);
		return gr;
	}else{
		//char *memstring = mystrtok(NULL,":");
		char **mems =(char**)malloc(2*sizeof(char*));
		token = mystrtok(memstring,",");
		
		mems[0] = token;
		
		int i =1;
		while(token != NULL && mystrlen(token)>0)
        	{
                	token = mystrtok(NULL,",");
                	mems[i] = token;
                	i++;			
        	}
 
		struct group *gr = newGroup(name,pswd,id,mems,i-1);
		free(mems);
		
		return gr;
	}
}

/* Funtion getgrgid searches for a group by gid in the `/etc/group` file and 
 * returns a struct group representing it. */
struct group *getgrgid( char *id){
	int fd = open("/etc/group", O_RDONLY);
	check_error(fd != -1, "open");

    	char *line = NULL;
	
	line = readLineId(fd,id);
	if (line == NULL)
		return NULL;
	char *token = NULL;
	
	int position = mystrrchr(line,':');
	int len = mystrlen(line);
	
	char *name = mystrtok(line,":");
	char *pswd = mystrtok(NULL,":");
	int gid = atoi(mystrtok(NULL,":"));
	char *memstring = mystrtok(NULL,":");
	
	if(position+1 == len){
		char **mems=NULL;
		struct group *gr = newGroup(name,pswd,gid,mems,0);
		return gr;
	}else{
		
		char **mems =(char**)malloc(2*sizeof(char*));
		
		token = mystrtok(memstring,",");	
		mems[0] = token;	
		int i =1;
		while(token != NULL && mystrlen(token)>0)
        	{
			printf("Token no. : %s \n",token);
                	token = mystrtok(NULL,",");
                	mems[i] = token;
                	i++;
                	
			
        	}
        	struct group *gr = newGroup(name,pswd,gid,mems,i-1);
		free(mems);
		return gr;
	}	
}

/*  Function newGroup allocates and initializes a new group structure.
 * 
 *  name: Name of the group.
 *  passwd: Password of the group.
 *  id: Gid of the group.
 *  mems: Array of member usernames.
 *  count: Number of members.
 * 
 *  returns: A pointer to the newly created struct group. */
struct group *newGroup(char *name, char *passwd,gid_t id, char **mems, int count){
	errno = 0;

	struct group *new = malloc(sizeof(struct group));
	if(errno!=0)
		return NULL;
	new->gr_gid =id ;
	
	new->gr_name = malloc(mystrlen(name)+1);
	mystrcpy(new->gr_name, name);
	
	new->gr_passwd = malloc(mystrlen(passwd)+1);
	mystrcpy(new->gr_passwd, passwd);
	
	if(mems==NULL){
		new->gr_mem=NULL;
	}else{
		errno = 0;
		new->gr_mem = (char**)malloc(count*sizeof(char*));
		
		if(errno != 0){
    			return NULL;
   		}
		for(int i=0; i<count; i++){
			errno = 0;
			new->gr_mem[i] = (char*)malloc(mystrlen(mems[i])*sizeof(char));
			if(errno!=0){
				free(new->gr_mem);
				return NULL;
			}
			mystrcpy(new->gr_mem[i],mems[i]);
		
		}
	}
    	return new;
}

/*  Function readLineName reads lines from the file descriptor `fd` and looks for the line
 *  containing the group name `name`.
 *  returns: The line containing the group name, or NULL if not found */
char* readLineName(int fd, char *name){
	
	char buffer[BUF_SIZE];
   	int readBytes = 0;
	
	char *token;
	int ind =1;
	while((readBytes = read(fd, buffer, BUF_SIZE))>0){
		token = mystrtok(buffer,"\n");
		while(token != NULL && ind==1 && mystrlen(token)>0){

                	if(findLineName(token,name)){
				
				ind=0;
				close(fd);
				return token;
			}
			token = mystrtok(NULL,"\n");
			
        	}
   	}
   	if(readBytes==0){
		
		close(fd);
		return NULL;
	}
	check_error(readBytes != -1, "read");
	close(fd);
    	
	return NULL;
	
}

/*  Function readLineId reads lines from the file descriptor `fd` and looks for the line
 *  containing the group gid `id`.
 *  returns: The line containing the group gid, or NULL if not found. */
char* readLineId(int fd, char *id){
	
	char buffer[BUF_SIZE];
   	int readBytes = 0;
	
	char *token;
	int ind =1;
	while((readBytes = read(fd, buffer, BUF_SIZE))>0){
		token = mystrtok(buffer,"\n");
		while(token != NULL && ind==1 && mystrlen(token)>0)
        	{
                	
                	if(findLineId(token,id)){

				ind=0;
				close(fd);
				return token;
			}
			token = mystrtok(NULL,"\n");
			
        	}
   	}
   	if(readBytes==0){
		close(fd);
		return NULL;
	}
	
	check_error(readBytes != -1, "read");
	close(fd);
    	
	return NULL;	
}

/* Function findLineName checks if the given line starts with the group name `name`. */
bool findLineName(char *line, char *name){	
	if(prefix(line,name)){
		return true;
	}
	return false;
}

/* Function findLineId checks if the given line contains the group gid `id`. */
bool findLineId(char *line, char *id){	
	if(infix(line,id)>0){
		return true;
	}
	return false;
}
