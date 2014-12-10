#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"
#define STR_LEN 100 // define possible length of string entered in for file_name
/* declarations of functions that must defined in lc4_loader.c */

FILE* get_file() 
{
	FILE *src_file;
	char file_name[STR_LEN];

	printf("Please enter the name of the file to open: \n");
	scanf("%s", file_name);

	src_file = fopen(file_name, "rb"); // open user-inputted file name in read-binary mode

	if (src_file == NULL) { // check to make sure that user inputted existent file name that could be opened
		fprintf(stderr, "File does not exist.\n"); // print error if fopen was unsuccessful
		return NULL; // return 0 if fopen was unsuccessful
	}
	return src_file ; // return pointer to file contents
};

int parse_file (FILE* my_obj_file, Row** memory) {

	int byte_read_1, byte_read_2; // will be used to parse file by reading bytes sequentially
	short unsigned int address; 
	short unsigned int contents;
	char * label;
	int wordcount; // used to set range of loops when scanning the words following a header

	if (my_obj_file == NULL) { // if file couldn't be opened, print error message and return 1
		fprintf(stderr, "File does not exist.\n");
		return 1;
	}
	
	do{
		byte_read_1 = fgetc(my_obj_file); // these two lines scan two bytes to detect the presence of labels
		byte_read_2 = fgetc(my_obj_file); 

		if (byte_read_1 == EOF || byte_read_2 == EOF) break; // check that not at the end of file; break if EOF

		address = (fgetc(my_obj_file) << 8) + fgetc(my_obj_file); // store two bytes following header as a short unsigned int address variable

        wordcount = (fgetc(my_obj_file) << 8) + fgetc(my_obj_file); // store two bytes following address as a short unsigned int wordcount variable

		if (byte_read_1 == 202 && byte_read_2 == 222){  // when header == CA D3
            for (int i = 0; i < wordcount; i++){ // loop through wordcount# of words following the wordcount
        		contents = (fgetc(my_obj_file) << 8) + fgetc(my_obj_file); // store two bytes as a short unsigned int contents
            	*memory = add_to_list(*memory, address + i, contents); // add a node to the list with these contents/address
            }
		}

		else if (byte_read_1 == 218 && byte_read_2 == 218){  // when header == DA DA
            for (int i = 0; i < wordcount; i++){ // loop through wordcount# of words following the wordcount
        		contents = (fgetc(my_obj_file) << 8) + fgetc(my_obj_file); // store two bytes as a short unsigned int contents
            	*memory = add_to_list(*memory, address + i, contents); // add a node to the list with these contents/address
            }
		}
		
		else if (byte_read_1 == 195 && byte_read_2 == 183){ // when header == C3 B7

			label = (char *) malloc(wordcount + 2); // allocate space for store of label to be read from file
			for (int i = 0; i < wordcount; i++){ // loop through contents following C3 B7 header to extract label
				label[i] = fgetc(my_obj_file); // store label chars in string
			}
			label[wordcount] = '\0'; // add null char to end of string

			Row* labeledNode = search_address(*memory, address); // search for existing node with specified address

			if (labeledNode != NULL) labeledNode -> label = label; // updates node if address exists
			else { // adds new Row node to list if not already existing
				add_to_list(*memory, address, 0); // add to list a node with contents 0 
				labeledNode = search_address(*memory, address); // search for node with specified address
				if (labeledNode -> label == NULL) labeledNode -> label = label; // update that specific node if no previous label exists
			}
		} 
	} while(1); // will continue until loop breaks when EOF

	if (fclose(my_obj_file) == 0) return 0; // test to make sure that file closes properly
	else {
		return 2; // if does not close correctly, return
	}
};
