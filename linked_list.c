//the goal of this function is to read an input file to created a sorted link list, which is printed when all entries are made
//only function missing the freeing all allocated memory when finished

#include <stdio.h>
#include <stdlib.h>

//creating a node struct
typedef struct Node Node;
struct Node {
	int data;
	Node* next;
};


//takes front of LL and new node as parameters
Node* insert(Node*front, Node* new) {
	Node* frontHold = front;
	Node* ptr = front;
	Node* prev = NULL;
	//checking if new node needs to be added to front
	if(new->data < ptr->data) {
		new->next = ptr;
		return new;
	}
	prev = ptr;
	ptr = ptr->next;
	//traverse list to find where new node belongs
	while(ptr) {
		if(new->data < ptr->data) {
			prev->next = new;
			new->next = ptr;
			return frontHold;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	//case where new node is the largest, added to end
	prev->next = new;
	return frontHold;
}


//takes the element to be removed as an int, the front of the LL and the number 
//of insertions as parameters
Node* delete(int n, Node* front, int* i) {
	Node* frontHold = front;
	Node* ptr = front;
	Node* prev = NULL;
	if(front == NULL) {
		return NULL;
	}
	//check if front needs to be removed
	if(ptr->data == n) {
		ptr = ptr->next;
		*i = *i-1;
		return ptr;
	}
	prev = ptr;
	ptr = ptr->next;
	//traverse to find element to delete
	while(ptr) {
		if(ptr->data == n) {
			prev->next = ptr->next;
			ptr = prev->next;
			*i = *i-1;
			return frontHold;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return frontHold;
}


//front as a parameter, and print all elements once
void printUniques(Node* front) {
	Node* ptr = front;
	Node* prev;
	//print first element always, also avoid tab at end
	printf("%d", ptr->data);
	prev = ptr;
	ptr = ptr->next;
	//traverse
	while(ptr) {
		//make sure to not reprint duplicates
		if(ptr->data != prev->data) {
			//avoid extra tab
			printf("\t%d", ptr->data);
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

//reads file
int main(int argc, char** argv) {
	//checks to assure valid number of arguments
	if(argc <= 1) {
		printf("error\n");
		return 0;
	}
	//file pointer
	char* path = argv[1];
	FILE* filePtr;
	filePtr = fopen(path, "r");
	//checks for nullity of file pointer
	if(filePtr == NULL) {
		printf("0\n");
		return 0;
	}
	//initializing all necessary variables
	int inserts = 0;
	char c;
	int n;
	int* cnt = &inserts;
	Node* front = NULL;
	Node* tnode = NULL;
	Node* cptr = malloc(sizeof(Node));
	//scanning entire file, until end, to create each node and either inser
	//t when coming across 'i' and delete for 'd'
	while(fscanf(filePtr, "%c\t%d\n", &c, &n) == 2) {
		tnode = malloc(sizeof(Node));
		tnode->data = n;
 		tnode->next = NULL;
		if(c == 'i') {
			//first element
			if(front == NULL) {
				cptr->next = NULL;
				cptr->data = n;
				front = cptr;
				inserts++;
			//all other elements
			}else {	
				front = insert(front, tnode);
				inserts++;	
			}
		}		
		if(c == 'd') {
			front = delete(n, front, cnt);
		}		
	}	
	//close file	
	fclose(filePtr);
	printf("%d\n", inserts);
	if(inserts > 0) {
		printUniques(front);
	}	
	printf("\n");
	return 0;
}		
		








