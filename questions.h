#include<stdio.h>

#ifndef HEADER_FICHIERS
#define HEADER_FICHIERS

typedef struct interests {
	char *topic;
	struct interests *next;
} Interests;

#endif

Interests *lineReader(FILE *);
