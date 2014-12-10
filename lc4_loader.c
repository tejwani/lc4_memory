#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic LC4's program & data memory */

int main () {
	/**
	 * main() holds the linked list &
	 * only calls functions in other files 
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	Row* memory = NULL;
	int testFunction;

	
	/* step 2: call function: get_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	FILE *file = get_file();
	if (file == NULL) return 1;
	
	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	testFunction = parse_file(file, &memory);
	if (testFunction == 2) {
		delete_list(memory);
		return 2;
	}
	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
	reverse_assemble(memory);
	if (reverse_assemble(memory) == 3) { // checks for errors (invalid assembly for subpcodes corresponding to opcode 0001)
		print_list(memory); // prints list up to error and terminates
		delete_list(memory);
		return 3;
	}


	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
	print_list(memory);


	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
	delete_list(memory);



	/* only return 0 if everything works properly */
	return 0 ;
}
