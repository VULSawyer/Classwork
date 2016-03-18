/*	this is  an application that puts newline strings into a linked list
*	It has a short form and long form getopt argument count to set how 
*	many strings are listed.
*	It prints the value of this count in the prompt and then the strings*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/*Linked list object*/
typedef struct s_word_object word_object;
struct s_word_object {
	char *word;
	word_object *next;
	};			/*this is not a function, so ends with ;*/
static word_object *list_head;

/*Add object to list*/
static void add_to_list(char *word) {
	word_object *last_object;
	if (list_head == NULL) {
		last_object = malloc(sizeof(word_object));
		list_head = last_object;
	}
	else{
		last_object = list_head;
		while (last_object->next) last_object = last_object->next;
		last_object->next = malloc(sizeof(word_object));
		last_object = last_object->next;
	}
	last_object->word = strdup(word);	/*duplicate string command*/
	last_object->next = NULL;
}

/*Print and free objects*/
void print_and_free(void) {
	word_object *current_object;
	word_object *old_object;
	current_object = list_head;
	while(1)	{
		printf("%s\n", current_object ->word);
		free(current_object->word);
		old_object = current_object;
		if (current_object ->next) {
			current_object = current_object ->next;
			free(old_object);
		}
		else	{
			free (old_object);
			break;
		}
	}	
}
													
/*main program*/
/*Modified to accept a number of strings and print them all out on new lines
*---number of strings can be invoked on command line*/
int main(int argc, char **argv)	{
	char input_word[256];	/*sets max string lngth*/
	int retval;		/*return value variable*/
	int option_index = 0;	/*index begins 0*/
	int count = 2;		/*initial value of number of strings*/
	static struct option long_option[] = {
		{"count",  required_argument, 0, 'c'},	/*form of struct option array*/
		{0,         0,                 0,  0 }	/*terminate array*/
	};
	while (1) {
		retval = getopt_long(argc, argv, "c:", long_option, &option_index);
		if (retval == -1) break;

	/*Check count*/
		switch (retval) {
			case'c':
			count = atoi(optarg);	/*read num of str invoked on command line*/
			break;
		}
	}
	fprintf(stderr, "Accepting %i input strings\n", count); /*output count value*/
	
	while (scanf("%256s", input_word) != EOF) {	
		add_to_list(input_word);
		if(!--count) break;		/*condition is zero value*/
		}
	
	/*print and free objects*/
	print_and_free();
	return 0;
}
