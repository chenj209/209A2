#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"questions.h"

//typedef struct interests {
//	char *topic;
//	struct interests *next;
//} Interests;

Interests *lineReader(FILE *input) {
	Interests *head = NULL;
	int start = 0;
	char line[30];
	Interests *cur;

	while(fgets(line, 29, input) != NULL) {
		line[strcspn(line, "\r\n")] = '\0';

		if(!start) { //create the head of the list before start.
			head = malloc(sizeof(Interests));
			head->topic = malloc(30 * sizeof(char));
			head->next = NULL;
			strcpy(head->topic, line);
			cur = head;
			start = 1;
		} else { //extent the list will list exists.
			cur->next = malloc(sizeof(Interests));
			cur = cur->next;
			cur->topic = malloc(30 * sizeof(char));
			cur->next = NULL;
			strcpy(cur->topic, line);
		}
	}

	return head;
}
