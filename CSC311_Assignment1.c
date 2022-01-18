#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//structure to hold node data
struct node{
	int data;
	struct node* next;
};

//structure to keep track of head, tail, and length of linked lists
struct linkedList{
	struct node* head;
	struct node* tail;
	int length;
};


/*
* Creates an empty node with an integer e as the data.
*/
struct node* createNode(int e){
	struct node* newNode = (struct node *)malloc(sizeof(struct node));
	newNode->data=e;
	newNode->next=NULL;
	return newNode;
} //end of createNode


/*
* Checks if a linked list is empty. Returns true or false.
*/
bool checkEmpty(struct linkedList* list){
	bool empty;
	if (list->length==0)
		empty = true;
	else
		empty = false;
	return empty;
} // end of checkEmpty

void emptyRemoveError(struct linkedList* list){
	if (checkEmpty(list))
		printf("ERROR: There is nothing in the list!\n\n");
	else
		printf("Removed node\n\n");
}// end of emptyRemoveError



/*
* Adds a node to the start of a linked list. Takes a linked list pointer and an
* integer as inputs.
*/
void addFirst(struct linkedList *list, int data){
	struct node *new_node = createNode(data);
	if(checkEmpty(list))
		list->tail = new_node;

	//adds the new node at start of linked list
	new_node->next = list->head;
	list->head = new_node;
	list->length++;
}

/*
* Adds a node to the end of a linked list. Takes a linked list pointer and an
* integer as inputs.
*/
void addLast(struct linkedList *list, int data){
	struct node *new_node = createNode(data);
	if(checkEmpty(list)){
		//initializing list
		list->head = new_node;
		list->tail = new_node;
	}
	else{
		//adds new node at the end of linked list
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->length++;
}



/*
* Adds a node to a specified position in the linked list. Takes a linked list pointer,
* an integer for data, and an integer for positition as inputs.
*/
void add(struct linkedList* list, int e, int pos){

        //if the position we're adding is at (or past) the end of the linked list, call addLast
        if (list->length <= pos) 
        	addLast(list, e);
        else if(pos==0) 
        	addFirst(list, e);
        else {
		struct node *newNode = createNode(e);	
		struct node* currentNode = list->head;

		//iterate until the node before the position we want to insert at
		for(int i=0; i<pos-1; i++){
		        currentNode = currentNode->next;
		}//end for
		
		//adds a new node after the node at pos
		newNode->next = currentNode->next;
		currentNode->next = newNode;
		
		list->length ++;
        }
}//end of add



/*
* Prints a linked list. Takes a linked list pointer as an input.
*/
void printList(struct linkedList* list){

        struct node* currentNode = list->head;

        //for each node in the list, print the data, then move to the next node
        for(int i=0; i<list->length; i++){
                printf("|%d|->", currentNode->data);
                currentNode = currentNode->next;
        } //end for
        printf("NULL\n\n");

}//end of printList



/* Searches a singly linked list with the desired key
* if there is no linked list associated with the key
* it will return NULL
*/
struct node * searchList(struct linkedList* list, int key) {

	//Initializes Variables
	struct node* current = list->head;
	struct node* correctnode = NULL;

	//Checks key exists within List to return it otherwise return NULL

	while (current != NULL && correctnode == NULL){
		if (current->data == key) {
			correctnode = current;
		}
		current = current->next;
	}
	return correctnode;
}



/*
* Removes the first node of a linked list. Takes a linked list pointer as an input.
*/
struct node* removeFirst(struct linkedList* list) {
	struct node* tempnode = list->head;
	// checks if the list is not NULL
	if (!checkEmpty(list)){
		tempnode = list->head;
		list->head = list->head->next;
		if (list->length==1)
			list->tail=NULL;

		list->length--;
	}
	return tempnode;

}



/*
* Removes the last node of a linked list. Takes a linked list pointer as an input.
*/
struct node* removeLast(struct linkedList* list){
	struct node* last = list->tail;
	struct node* current = list->head;
	
	//linked list is longer than one node
	if (list->length > 1){
		while (current->next != list->tail){
			current = current->next;
		}
		//sets second to last node as tail and sets next as null
		current->next = NULL;
		list->tail=current;
		list->length--;
	}
	//if linked list has one node
	else if (list->length == 1){
		removeFirst(list);
	}	
	return last;
} // end of removeLast




/*
* Merges two sorted linked lists. Takes two linked lists pointers as inputs.
*/
struct linkedList* mergeSortedLists(struct linkedList* list1, struct linkedList* list2){
	//create new list to return
	
	struct linkedList* result = (struct linkedList *)malloc(sizeof(struct linkedList));
	result->head=NULL;
	result->tail=NULL;
	result->length=0;

	
	//set up traversal of nodes
	struct node* current1 = list1->head;
	struct node* current2 = list2->head;
	
	//loop through both lists
	while (current1 != NULL && current2 != NULL){
		if (current2->data < current1->data){
			addLast(result, current2->data);
			current2 = current2->next;
		} else {
			addLast(result, current1->data);
			current1=current1->next;
		}
	}
	
	//loop through rest of list1
	while (current1 != NULL){
		addLast(result, current1->data);
		current1=current1->next;
	}
	
	//loop through rest of list2
	while (current2 != NULL){
		addLast(result, current2->data);
		current2=current2->next;
	}
	
	return result;
}// end of mergeSortedLists



/*
* Contains user interface.
*/
int main(){

	struct linkedList* list1 = (struct linkedList *)malloc(sizeof(struct linkedList));
	list1->head=NULL;
	list1->tail=NULL;
	list1->length=0;

	//user interface
	int userChoice = 9;
	int num;
	int position;
	
	while (userChoice != 0){
		printf("0: quit\n1: addFirst\n2: addLast\n3: add\n4: printList\n5: searchList\n6: removeFirst\n7: removeLast\nEnter Choice: ");
		fflush(stdout);
		scanf("%d", &userChoice);

		switch (userChoice){
			// quits program
			case 0:
				printf("Quitting Program...\n\n");
				break;
			//calls addFirst function
			case 1:
				printf("Enter the integer to be added to the linked list: ");
				scanf("%d", &num);
				addFirst(list1, num);
				printf("Success\n\n");
				break;
			//calls addLast function
			case 2:				
				printf("Enter the integer to be added to the linked list: ");
				scanf("%d", &num);
				addLast(list1, num);
				printf("Success\n\n");
				break;
			//calls add function
			case 3:
				printf("Enter the integer to be added to the linked list: ");
				scanf("%d", &num);
				printf("Enter the position: ");
				scanf("%d", &position);
				add(list1, num, position);
				printf("Success\n\n");
				break;
			//calls printList function
			case 4:
				printList(list1);
				break;
			//calls searchList function
			case 5:
				printf("Enter the integer to be searched for: ");
				scanf("%d", &num);
				if (searchList(list1, num) != NULL)
					printf("Node exists\n\n");
				else
					printf("Node does not exist\n\n");
				break;
			//calls removeFirst function
			case 6:
				emptyRemoveError(list1);
				free(removeFirst(list1));
				break;
			//calls removeLast function
			case 7:
				emptyRemoveError(list1);
				free(removeLast(list1));
				break;
			//Gives an error message if input is invalid.
			default:
				printf("Invalid input. Please enter an integer between 0-7\n\n");
				break;
		}// end of switch statement
	}// end of user interface	
}// end of main








