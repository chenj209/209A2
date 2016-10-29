#include<stdio.h>
#include<stdlib.h>
#include "questions.h"

int main() {
	FILE *input;
	Interests *list;
	int index = 0;

	input = fopen("./test.txt", "r");
	list = lineReader(input);

	while(list != NULL) {
		printf("%s\n", list->topic);
		list = list->next;
	}

	return 0;
}
