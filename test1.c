#include<stdio.h>
#include<stdlib.h>
#include "questions.h"

int main(int argc, char const *argv[]) {
	FILE *input;
	Interests *list;

	input = fopen(argv[1], "r");
	list = lineReader(input);

	while(list != NULL) {
		printf("%s\n", list->topic);
		list = list->next;
	}

	return 0;
}
