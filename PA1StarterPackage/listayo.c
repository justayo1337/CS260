// PROGRAMMING ASSIGNMENT I STARTER CODE
/*In order to complete this assignment, you need to complete the function defintions in the section commented FUNCTION DEFINITIONS.
When you implement a function, make sure that you uncomment its provided function call from main so that your program can utilize it.*/

// HEADER FILES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CONSTANT DECLARATIONS

#define INITIAL_SIZE 2

// STRUCT DECLARATIONS

typedef struct entry
{
	char* name;
	char* lastname;
	float height;
	int age;
} Entry;

typedef struct list 
{
	int capacity;
	int size;
	Entry** data;
} List;

// FUNCTION DEFINTIONS
/* The function declarations have been given to you which should make the parameters and the return value for each function obvious.
The initializeEntry, freeEntry, printList, and printEntry function have been coded to start you off.*/

// Returns a pointer to an Entry struct initialized with the specified values for each of the 4 members of the struct (NO NEED TO CHANGE).
Entry* initializeEntry(char* name, char* lastname, float height, int age)
{
	Entry* newEntry = malloc(sizeof(Entry));
	
	newEntry -> name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(newEntry -> name, name);
	
	newEntry -> lastname = malloc(sizeof(char) * (strlen(lastname) + 1));
	strcpy(newEntry -> lastname, lastname);
	
	newEntry -> height = height;
	
	newEntry -> age = age;
	
	return newEntry;
}

// Given a pointer to an Entry struct, this function frees the memory allocated for that Entry struct (NO NEED TO CHANGE).
void freeEntry(Entry* entry)
{
	if (entry != NULL)
	{
		free(entry -> name);
		free(entry -> lastname);
		free(entry);
	}
}

List* initializeList(){
   List* reqlist = malloc(sizeof(List));
	reqlist -> size = 0;
	reqlist -> capacity = INITIAL_SIZE;
	reqlist -> data = malloc(reqlist->capacity * sizeof(Entry) );
}

void deleteList(List* myList){ 
	for (int i = 0; i< myList->size ; i++){
		if (myList->data[i] != NULL){
		freeEntry(myList->data[i]);	
		}
	}
	free(myList -> data);
	free(myList);
	}

void doubleCapacity(List* myList)
{
	myList->capacity *= 2;
	Entry** newloc = malloc(myList->capacity * sizeof(Entry));
	for ( int i = 0 ; i < myList->size; i++){
		newloc[i] = myList -> data[i];
	}
	free(myList->data);
	myList->data = newloc;
	//printf("test: %s\n",myList->data[myList->size-2] ->name );
	newloc = NULL;
};

void halveCapacity(List* myList){

	myList->capacity /= 2;
	Entry** newloc = malloc(myList->capacity * sizeof(Entry));
	for ( int i = 0 ; i< myList->size; i++){
		newloc[i] = myList->data[i];
	}
	free(myList->data);
	myList->data = newloc;
	newloc = NULL;

	};

void insertToHead(List* myList, char* name, char* lastname, float height, int age)

{
	if (myList->size != 0 ){
		if (myList->size == myList->capacity)
		{
			doubleCapacity(myList);
	}
		for (int i = myList->size - 1;i >= 0; --i){
			myList->data[i+1] = myList->data[i];
			myList->data[i] = NULL;

		 }
		}
   Entry* newEntry = initializeEntry(name,lastname,height,age);
	myList->data[0] = newEntry;
	myList->size++;
	//printf("Name: %s size:%d\n", myList->data[myList->size - 1] ->name, myList->size);

}
void insertToTail(List* myList, char* name, char* lastname, float height, int age)
{
	//printf("tails size:%d\n",  myList->size);

	if (myList->size == myList->capacity)
	{
			
			doubleCapacity(myList);
	}
	
	Entry* newEntry = initializeEntry(name,lastname,height,age);
	myList->data[myList->size] = newEntry;

	myList->size++;
		//printf("Name: %s size:%d\n", myList->data[myList->size - 2] ->name, myList->size);

}


void insertToPosition(List* myList, int position, char* name, char* lastname, float height, int age)
{
   if (position > myList->size){
		printf("Invalid Insert! Position: %d\n", position);
	}else{
	if (myList->size == myList->capacity)
		{
			doubleCapacity(myList);
	}

	for (int i = myList->size - 1;i >= position; --i){
			myList->data[i+1] = myList->data[i];
			myList->data[i] = NULL;

		 }
		
   Entry* newEntry = initializeEntry(name,lastname,height,age);
	myList->data[position] = newEntry;
	myList->size++;
}
}

int findPosition(List* myList, char* name){
	int pos = -1;
	for (int i = 0;i < myList->size; i++ ){
		if (strcmp(myList-> data[i] -> name, name) == 0){
			pos = i;
			return pos;
		}
	}
	return pos;
}

void deleteFromHead(List* myList){

	if (myList->size !=0){
	freeEntry(myList->data[0]);
	if (myList->size > 1) 
	{
	for (int i = 0;i < myList->size ; i++)
	{
			myList->data[i] = myList->data[i+1];
			myList->data[i+1] = NULL;	 
}
}	
	--myList->size;
	if (myList->size < 0.5 * myList->capacity ){
		halveCapacity(myList);
	}
}

}

void deleteFromTail(List* myList){
if (myList->size !=0){
	freeEntry(myList->data[myList->size - 1]);
}
	--myList->size;
	if (myList->size < 0.5 * myList->capacity ){
		halveCapacity(myList);
	}
}



void deleteFromPosition(List* myList, int position){
	if (myList->size !=0 && position < myList->size){
		freeEntry(myList->data[position]);
		if (myList->size > 1) 
		{
		for (int i = position;i < myList->size ; i++)
			{
			myList->data[i] = myList->data[i+1];
			myList->data[i+1] = NULL;	 
			}
		}	
	--myList->size;
	if (myList->size < 0.5 * myList->capacity ){
		halveCapacity(myList);
		}
}
};

// Given a pointer to a List struct, this function prints each Entry in that list (NO NEED TO CHANGE).
void printList(List* myList)
{
	if (myList -> size == 0)
	{
		printf("List is empty!\n");
	}
	else
	{
		for (int i = 0; i < myList -> size; i++)
		{
			printf("[%d]\t%s\t%s\t%0.2f\t%d\n", i, myList -> data[i] -> name, myList -> data[i] -> lastname, myList -> data[i] -> height, myList -> data[i] -> age);
		}
	}
}

// Given a pointer to a List struct, this function prints out the size and capacity of that List (NO NEED TO CHANGE).
void printListInfo(List* myList)
{
	printf("size:%d, capacity:%d\n", myList -> size, myList -> capacity);
}

int main(int argc, char** argv) 
{
	FILE* fp = fopen(argv[1], "r");
	char* line = NULL;
	size_t lineBuffSize = 0;
	ssize_t lineSize;
	
	if (fp == NULL)
	{
		fprintf(stderr, "Error opening file\n");
		return -1;
	}
	
	List* myList;
	// Uncomment the following function call when you implement the initializeList() function
	myList = initializeList(); 
	
	while ((lineSize = getline(&line, &lineBuffSize, fp)) != -1)
	{
		char* token;
		const char delimiter[2] = " ";
		
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}

		token = strtok(line, delimiter);
					
		if (strcmp(token, "insertToHead") == 0)
		{
			char* name;
			char* lastname;
			float height;
			int age;
			
			name = strtok(NULL, delimiter);
			lastname = strtok(NULL, delimiter);
			height = atof(strtok(NULL, delimiter));
			age = atoi(strtok(NULL, delimiter));
			// Uncomment the following insertToHead function call when you have implemented it
			insertToHead(myList, name, lastname, height, age);
		}
		else if (strcmp(token, "insertToTail") == 0)
		{
			char* name;
			char* lastname;
			float height;
			int age;
			
			name = strtok(NULL, delimiter);
			lastname = strtok(NULL, delimiter);
			height = atof(strtok(NULL, delimiter));
			age = atoi(strtok(NULL, delimiter));
			// Uncomment the following insertToTail function call when you have implemented it
			insertToTail(myList, name, lastname, height, age);
		}
		else if (strcmp(token, "insertToPosition") == 0)
		{
			char* name;
			char* lastname;
			float height;
			int age;
			int position;
			
			position = atoi(strtok(NULL, delimiter));
			name = strtok(NULL, delimiter);
			lastname = strtok(NULL, delimiter);
			height = atof(strtok(NULL, delimiter));
			age = atoi(strtok(NULL, delimiter));
			// Uncomment the following insertToPosition function call when you have implemented it
			 insertToPosition(myList, position, name, lastname, height, age);
		}
		else if (strcmp(token, "findPosition") == 0)
		{
			char* name;
			
			name = strtok(NULL, delimiter);
			// Uncomment the following printf statement using the return value from a findPosition function call when you have implemented the function
			printf("%d\n", findPosition(myList, name));
		}
		else if (strcmp(token, "deleteFromHead") == 0)
		{
			// Uncomment the following deleteFromHead function call when you have implemented it
			deleteFromHead(myList);
		}
		else if (strcmp(token, "deleteFromTail") == 0)
		{
			// Uncomment the following insertToHead function call when you have implemented it
			 deleteFromTail(myList);
		}
		else if (strcmp(token, "deleteFromPosition") == 0)
		{
			int position;
			
			position = atoi(strtok(NULL, delimiter));
			
			// Uncomment the following deleteFromPosition function call when you have implemented it
			 deleteFromPosition(myList, position);
		}
		else if (strcmp(token, "printList") == 0)
		{
			printList(myList);
		}
		else if(strcmp(token, "printListInfo") == 0)
		{
			printListInfo(myList);
		}
		else if (strcmp(token, "deleteList") == 0)
		{
			// Uncomment the following deleteList function call when you have implemented it
			 deleteList(myList);
			 myList = NULL;
		}
		else
		{
			printf("Invalid command: <%s>\n", token);
		}
	}

	 //free(myList); 	
	 //myList = NULL;
    //printf("%p\n", myList);
	//freeing all the memory used f

	//free buff
	free(line);
	
	fclose(fp);
	if (myList != NULL) {
	   deleteList(myList);
		myList = NULL;
	}
	return 0;
} 
