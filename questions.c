#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "questions.h"

Node * get_list_from_file (char *input_file_name) {
	Node * head = NULL;

	FILE *input_file;
	input_file = fopen(input_file_name, "r");
    //read lines and add to the list
	if (input_file != NULL) {
		char line[MAX_LINE];
		Node *cur;

		head = malloc(sizeof(Node));
		fgets(line, MAX_LINE - 1, input_file);
		line[strcspn(line, "\r\n")] = '\0';
		head->str = malloc(MAX_LINE * sizeof(char));
		strcpy(head->str, line);
		head->next = NULL;
		
		cur = head;

	    while(fgets(line, MAX_LINE - 1, input_file) != NULL) {

			line[strcspn(line, "\r\n")] = '\0';
			cur->next = malloc(sizeof(Node));
			cur = cur->next;
			cur->str = malloc(MAX_LINE * sizeof(char));
			cur->next = NULL;
			strcpy(cur->str, line);
	
		}
	}
	fclose(input_file);
	return head;
}

void print_list (Node *head) {
	
	Node *cur;
	cur = head;
	while (cur != NULL) {
		printf("%s\n", cur->str);
		cur = cur->next;
	}
}

void free_list (Node *head) {

	Node *cur;
	Node *temp;
	cur = head->next;
	free(head->str);
	free(head);
	while (cur != NULL) {
		temp = cur->next;
		free(cur->str);
		free(cur);
		cur = temp;
	}
}