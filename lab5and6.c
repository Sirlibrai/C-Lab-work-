#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10
#define MAX_NAME_LENGTH 50
#define MAX_DOORS 4

struct room{char * name;struct door * doors[MAX_DOORS];int dp;};
struct door{char * name;struct room * room;};
struct room * rooms[MAX];

int rp;

int main(int argc,char ** argv){
	if(argc != 2){
		printf("Usage: explore filename\n");
		exit(0);
	}

	FILE * source = fopen(argv[1],"r");
	if(source==NULL){
		printf("File not found.\n");
		exit(0);	
	}

	readRooms(source);
	fclose(source);
	connect();

	struct room * current = rooms[0];
	int input = -1;
	while(input != 0){
	        printf("\n");
		showRoom(current);
		printf("Enter door number, or Enter 0 to quit > ");
		scanf("%d",&input);
		if(input>=(current->dp+1) || input<0)
			printf("Please Enter a Valid Room Number\n");
		else if(input>0)
			current = current->doors[input-1]->room;
	}
	printf("\nGoodbye\n");
}

struct door * newDoor(char * name){
	struct door * x;
	x = (struct door *)malloc(sizeof(struct door *));
	x->name=(char*)malloc(MAX_NAME_LENGTH*sizeof(char));
	x->name = name;
	x-> room = NULL;
	return x;
}

struct room * newRoom(char * name){
	struct room * z;
	z = (struct room *)malloc(sizeof(struct room *));
	z->name = (char*)malloc(MAX_NAME_LENGTH*sizeof(char));
	z->name = name;
	z->dp = 0;
	return z;
}

showRoom(struct room * room){
	printf("%s\n",room->name);
	int i;
	for(i = 0;i<room->dp;i++)
		printf("%d.%s\n",i+1,room->doors[i]->name);
}

char * readLine(FILE * filepath){
	char line[MAX_NAME_LENGTH];
	char current = getc(filepath);
	if(current==EOF)
		return NULL;
	int i;

	for(i =0;current!='\n';i++){
		line[i] = current;
		current = getc(filepath);		
	}

	while(current != '\n')
		current = getc(filepath);

	line[i] = '\0';
	char * value = malloc((i+1)*sizeof(char));
	int j;

	for(j=0;j<=i;j++)
		value[j]=line[j];
	return value;
}

readRooms(FILE * filepath){
	char * line = readLine(filepath);
	rp = 0;
	while(line!=NULL){
		if(rp==MAX){
			printf("Error: room limit reached\n");
			exit(0);		
		}
		rooms[rp] = newRoom(line);
		line = readLine(filepath);
		while(strcmp(line,"*")!=0){
			if(rooms[rp]->dp==MAX_DOORS){
				printf("Error: door limit reached\n");
				exit(0);			
			}

			rooms[rp]->doors[rooms[rp]->dp] = newDoor(line);
			rooms[rp]->dp++;
			line = readLine(filepath);
		}
		rp++;
		line = readLine(filepath);	
	}	
}

showRooms(){
	int i;
	for(i=0;i<rp;i++)
		showRoom(rooms[i]);
}

connect(){
	int i, j, x;
	for(i=0;i<rp;i++){
		for(j=0;j<rooms[i]->dp;j++){
			for(x=0;x<rp;x++){
				if(strcmp(rooms[x]->name,rooms[i]->doors[j]->name)==0)
					rooms[i]->doors[j]->room = rooms[x];
			}
		}
	}
}
