#ifndef QTREE_H
#define QTREE_H
#include "questions.h"

typedef enum {
    REGULAR, LEAF
} NodeType;

union Child {
	struct str_node *fchild;
	struct QNode *qchild;
} Child;

typedef struct QNode {
	char *question;
	NodeType node_type;
	union Child children[2];
} QNode;

QNode *add_next_level (QNode *current, Node * list_node);
QNode *add_new_user(QNode *cur, char *answer, char *user);

void print_qtree (QNode *parent, int level);
void print_users (Node *parent);

void free_qtree(QNode *root);
Node *search_user(QNode *root, char *username);

#endif