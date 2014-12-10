#ifndef LC4_MEMORY_H
#define LC4_MEMORY_H

/*
 * definition of linked list node 
 */ 

typedef struct row_of_memory Row;

struct row_of_memory {
	short unsigned int address ;
	char * label ;
	short unsigned int contents ;
	char * assembly;
	Row *next;
} ;

/*
 * declaration of linked list helper functions 
 */

Row* add_to_list    (Row* head, 
				      short unsigned int address, 
				      short unsigned int contents) ;

Row* search_address (Row* head, 
				      short unsigned int address ) ;

Row* search_opcode  (Row* head, 
				      short unsigned int opcode  ) ;

void print_list (Row* head ) ;

Row* delete_list    (Row* head ) ; 
/* struct row_of_memory* delete_list    (struct row_of_memory* head ) ; */

#endif
