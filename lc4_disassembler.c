#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"
#include <string.h>

int reverse_assemble (Row* memory) 
{
	short unsigned int opcode = 0b0001; // opcode for ADD, MUL, SUB, DIV, ADD IMM
	short unsigned int subopcode;
	short unsigned int immediateBit;
	short unsigned int immediateValue;
	short unsigned int Rd; // value of destination register
	short unsigned int Rs; // value of first source register
	short unsigned int Rt; // value of second source register
	char assembly[15]; // assembly instruction cannot exceed 15 chars, so put limit and declare
	int str_len; // used to concatenate componenents of assembly code by appending to end of str

	
	Row * temp = search_opcode(memory, opcode);

	while (temp != NULL) { // only gets in here if temp is storing the pointer to node in linked list with opcode 0001

		immediateBit = (((temp -> contents) & 0x20) >> 5); //0x20 corresponds to 0000000000100000 bitmask; shift to trim subsequent 0s
		immediateValue = ((temp -> contents) & 0x1F); //0x1F corresponds to the 0000000000011111 bitmask 
		subopcode = (((temp -> contents) & 0x38) >> 3); // 0x38 corresponds to 0000000000111000 bitmask ; shift to 3 trim subsequent 0s
		Rd = (((temp -> contents) & 0xE00) >> 9); // 0xE00 corresponds to 0000111000000000000 bitmask; shift 9 to trim subsequent 0s
		Rs = (((temp -> contents) & 0x1C0) >> 6); // 0x1C0 corresponds to 0000000111000000000 bitmask; shift 6 to trim subsequent 0s
		Rt = ((temp -> contents) & 0x7); // 0x7 corresponds to 0000000000000000111 bitmask

		
		if (immediateBit == 1){ // for add immediate operation
					strcpy(assembly, "ADD R");

					str_len = (strlen(assembly)); // get length of str so far 
					assembly[str_len] = (char)(((int)'0') + Rd); //  append character representation of Rd to end of assembly str
					assembly[str_len + 1] = '\0'; // add null char to keep track of str_len

					strcat(assembly, " R"); // append "R" to end of assembly str
					str_len = (strlen(assembly)); // get length of str so far 
					assembly[str_len] = (char)(((int)'0') + Rs); //  append character representation of Rs to end of assembly str
					assembly[str_len + 1] = '\0'; // add null char to keep track of str_len

					strcat(assembly, " #"); // append "#" to end of assembly str to represent addition of immediate value
					str_len = (strlen(assembly)); // get length of str so far 
					assembly[str_len] = (char)(((int)'0') + immediateValue); //  append character representation of immediate value to end of assembly str
					assembly[str_len + 1] = '\0'; // add null char to keep track of str_len


					temp -> assembly = malloc(strlen(assembly) + 1); // allocate memory in temp -> assembly to hold assembly string
					strcpy(temp -> assembly, assembly); // copy assembly string into temp -> assembly
		}
		else{
			switch(subopcode){

				case 0b000: // addition assembly command
					strcpy(assembly, "ADD R");

					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rd);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rs);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R"); // append "R" to end of assembly str
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rt); //  append character representation of Rt to end of assembly str
					assembly[str_len + 1] = '\0';


					temp -> assembly = malloc(strlen(assembly) + 1);
					strcpy(temp -> assembly, assembly);
					
					break;
				
				case 0b001: // multiplication assembly command
					strcpy(assembly, "MUL R");

					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rd);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rs);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rt);
					assembly[str_len + 1] = '\0';


					temp -> assembly = malloc(strlen(assembly) + 1);
					strcpy(temp -> assembly, assembly);
					
					break;
				
				case 0b010: // subtraction assembly command
					strcpy(assembly, "SUB R");

					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rd);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rs);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rt);
					assembly[str_len + 1] = '\0';


					temp -> assembly = malloc(strlen(assembly) + 1);
					strcpy(temp -> assembly, assembly);
					
					break;
				
				case 0b011: // division assembly command
					strcpy(assembly, "DIV R");

					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rd);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rs);
					assembly[str_len + 1] = '\0';

					strcat(assembly, " R");
					str_len = (strlen(assembly));
					assembly[str_len] = (char)(((int)'0') + Rt);
					assembly[str_len + 1] = '\0';


					temp -> assembly = malloc(strlen(assembly) + 1);
					strcpy(temp -> assembly, assembly);					
					break;

				default:
					printf("nothing done\n");
					break;
			}
		}
		temp = search_opcode(temp, opcode); // look for next node in linked list with opcode 0001
	}
	
	return 0 ;
}
