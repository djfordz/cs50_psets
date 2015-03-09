/**
*
* Linked List Practice
*
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int		data;
	struct node* next;
} node;

struct node* BuildOneTwoThree() {
	node* head = malloc(sizeof(node)), second = malloc(sizeof(node)), third = malloc(sizeof(node));

	head->data = 1;
	head->next = second;

	second = head + 1;

	third = second + 1;

	return head;
}


int Length(struct node* head) {
	node* current = head;
	int count = 0;

	while(current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

int main(int argc, char** argv) {

}

void LengthTest() {
	node* myList = BuildOneTwoThree();

	int len = Length(myList);
}

void LinkTest() {
	node* head = BuildOneTwoThree();
	node* newNode;

	newNode = malloc(sizeof(node));
	newNode->data = 1;

	head = newNode;
}
 
void Push(struct node** headRef, int data) {
	node* newNode = malloc(sizeof(node));

	newNode->data = data;
	newNode->next = *headRef;

	*headRef = newNode;
}

void PushTest() {
	node* head = BuildOneTwoThree();

	Push(&head, 1);
	Push(&head, 13);
}

int Length(node* head) {
	int count = 0;
	node* current = head;

	while(current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

struct node* AddAtHead() {
	node* head = NULL;
	int i;

	for(i = 1; i < 6; i++)
		Push(&head, i);

	return head;
}

struct node* BuildWithSpecialCase() {
	node* head = NULL;
	node* tail;
	int i;

	Push(&head, 1);
	tail = head;

	for(i = 2; i < 6; i++) {
		Push(&(tail->next), i);
		tail = tail->next;
	}

	return head;
}

struct node* BuildWithDummyNode() {
	node dummy;
	node* tail = &dummy;

	int i;

	dummy.next = NULL;

	for(i = 1; i < 6; i++) {
		Push(&(tail->next), i);
		tail = tail->next;
	}

	return dummy.next;
}