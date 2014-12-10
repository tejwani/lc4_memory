#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"
// #include "lc4_memory.h"

Row* add_to_list    (Row* head, 
				      short unsigned int address, 
				      short unsigned int contents) 
{
	/* takes in head pointer to a linked list: head
	   creates a new node with address & contents passed in
	   adds node to end of linked list pointed to by head
	   if list is empty, new node is now head
	   always returns head pointer */
	   
	/* add node to the end of linked list pointed to by "head"
	   if list doesn't exist, create 1st node */

	/* allocate memory for a single node */
	Row *newRow = (Row *) malloc(sizeof(Row));

	if (newRow == NULL) {  // in case malloc() could not allocate memory for the new node
		printf("Error: could not allocate memory.\n");
		return head;
	}

	/* populate fields in newly allocated node w/ address&contents */
	newRow -> address = address;
	newRow -> contents = contents;
	newRow -> label = NULL; // initialize to NULL to prevent conditional jumps based on uninitialised values
	newRow -> assembly = NULL; // initialize to NULL to prevent conditional jumps based on uninitialised values
	newRow -> next = NULL; // initialize to NULL to prevent conditional jumps based on uninitialised values

	/* if head==NULL, node created is the new head of the list! */

	if (head == NULL) {
		head = newRow; // make head newRow if it does not exist
		return head;

	} else { /* otherwise, traverse linked list and add new node in right order */
		
		Row *traverseList = head; //  set traverseList as temporary variable with which we can traverse linked list
		Row *nodeExists = search_address(traverseList, address); // need to check if address node already exists 
		int i = 0;

		if (nodeExists != NULL) nodeExists -> contents = contents; // update node's contents if the node with specified address already exists 
		else{  // gets into here only if a node with given address doesn't already exist

			if (address < head -> address) { 
				newRow -> next = head;
				head = newRow;
			}

			nodeExists = traverseList -> next;  // nodeExists will track current node; traverseList will track previous node
			do {
				if (traverseList -> next == NULL){ // check if at end of linked list
					traverseList -> next = newRow; // add newRow to the end of the linked list
					break;
				}
				if (address < nodeExists -> address) { // check to make sure that new nodes are added in ascending order of address
					traverseList -> next = newRow; // add the newNode before node with address field greater than address
					newRow -> next = nodeExists; // connect newly-inserted node to next nodes
					break;
				} 
				nodeExists = nodeExists -> next; // continue to increment if address to be added is higher than address at location in list
				traverseList = traverseList -> next; // keep traversing through linked list until end or until address to be added is lower than address at current
			} while (1);
		}
	}

	/* always return pointer to head of linked list */
	return head ;   
}

Row* search_address (Row* head, 
				      short unsigned int address ) 
{
	/* traverse linked list, searching each node for "address"  */
	Row * temp = head; // set temporary variable with which we can search through list
	while (temp != NULL){
	 	if (temp -> address == address){ // if the node's address matches given address, return pointer to that node;
	 		return temp; /* return pointer to node in list that matches */
	 	}
	 	else {
	 		temp = temp -> next; // continue to next node in linked list
	 	}
	 }
	 
	return NULL ; /* return NULL if list is empty or if "address" isn't found */
}

Row* search_opcode  (Row* head, 
				      short unsigned int opcode) 
{
	Row * temp = head;
	short unsigned int nodeOpcode;

	/* traverse linked list until node is found with matching opcode
	AND "assembly" field of node is empty */

	while (temp != NULL) {
		nodeOpcode = (((temp -> contents) & 0xF000) >> 12);  // 0xF000 corresponds to 1111000000000000 bitmask; shift to isolate opcode bits
		if (nodeOpcode == opcode && temp -> assembly == NULL) return temp; // return pointer to node if the opcode matches 0001 and the node's assembly field is empty
		temp = temp -> next; /* return pointer to node in list that matches */
	}
	 
	return NULL ; /* return NULL if list is empty or if no matching nodes */
}

void print_list (Row* head ) 
{
	char * label;
	char * assembly;
	short unsigned int address;

	if (head == NULL) return; /* make sure head isn't NULL */
	printf("%25s %24s %24s %20s\n", "<label>", "<address>", "<contents>", "<assembly>");/* print out a banner */
	
	Row * temp = head;

	 while (temp != NULL){ /* traverse linked list, print contents of each node */	
		
		if (temp -> label == NULL) label = ""; // populate the label field with an empty string if the field is null for printing purposes
		else {
			label = temp -> label; // or else, leave as it its
		}

		if (temp -> assembly == NULL) assembly = "";  // populate the label field with an empty string if the field is null for printing purposes
		else {
			assembly = temp -> assembly; // or else, leave as it its
		}

		printf("%25s %16s %04x %20s %04x %20s\n", label, "", // print well-aligned columns with the necessary fields
			temp -> address, "", temp -> contents, assembly);

		if (temp -> next == NULL) return; //print up to last node in linked list
		temp = temp -> next;
	}

	return ;
}

Row* delete_list   (Row* head ) 
{
	/* delete entire list node by node */
	Row *temp = head;

	while (head){
		temp = head; // store current pointer to node to allow for temporary overwriting
		head = head -> next; // move one spot down the line
		free(temp -> label); // free label field of node in linked list
		free(temp -> assembly); // free assembly field of node in linked list
		free(temp);
	}

	return NULL ;
}
