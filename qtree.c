#include "qtree.h"

QNode *add_next_level (QNode *current, Node *list_node) {
	int str_len;
	
	str_len = strlen (list_node->str);
	current = (QNode *) calloc (1, sizeof(QNode));

	current->question =  (char *) calloc (str_len +1, sizeof(char ));
	strncpy ( current->question, list_node->str, str_len );
	current->question [str_len] = '\0';  
	current->node_type = REGULAR;
	
	if (list_node->next == NULL) {
		current->node_type = LEAF;
		return current;
	}
	
	current->children[0].qchild = add_next_level ( current->children[0].qchild, list_node->next);
	current->children[1].qchild = add_next_level ( current->children[1].qchild, list_node->next);

	return current;
}

void print_qtree (QNode *parent, int level) {
	int i;
	for (i=0; i<level; i++)
		printf("\t");
	
	printf ("%s type:%d\n", parent->question, parent->node_type);
	if(parent->node_type == REGULAR) {
		print_qtree (parent->children[0].qchild, level+1);
		print_qtree (parent->children[1].qchild, level+1);
	}
	else { //leaf node
		for (i=0; i<(level+1); i++)
			printf("\t");
		print_users (parent->children[0].fchild);
		for (i=0; i<(level+1); i++)
			printf("\t");
		print_users (parent->children[1].fchild);
	}
}

void print_users (Node *parent) {
	if (parent == NULL)
		printf("NULL\n");
	else {
		printf("%s, ", parent->str);
		while (parent->next != NULL) {
			parent = parent->next;
			printf("%s, ", parent->str);
		}
		printf ("\n");
	}
}



QNode *add_new_user(QNode *cur, char *answer_str, char *user) {
	int answer;
	if(answer_str[0] == '0')
		answer = 0;
	else
		answer = 1;
	if(cur->node_type == LEAF) {
		Node *newUser = malloc(sizeof(Node));
        newUser->str = malloc(129 * sizeof(char));
        strncpy(newUser->str, user, 128);
        newUser->next = cur->children[answer].fchild;
        cur->children[answer].fchild = newUser;
	} else {
		cur = cur->children[answer].qchild;
	}

	return cur;
}

Node *search_user(QNode *parent, char *username) {
	Node *friends = NULL;
	if (parent->node_type == LEAF) {
		friends = parent->children[0].fchild;
		Node *current = friends;
		while (current != NULL) {
			if (!strcmp(current->str, username)) return friends;
			current = current->next;
		}
		friends = parent->children[1].fchild;
		current = friends;
		while (current != NULL) {
			if (!strcmp(current->str, username)) return friends;
			current = current->next;
		}
		return friends;
	} else {
		friends = search_user(parent->children[0].qchild, username);
		if (friends != NULL) return friends;
		else return search_user(parent->children[1].qchild, username);
	}
}

void free_qtree (QNode *parent) {
	if(parent->node_type == REGULAR) {
		QNode *child0 = parent->children[0].qchild;
		QNode *child1 = parent->children[1].qchild;
		free(parent->question);
		free(parent);
		free_qtree(child0);
		free_qtree(child1);
	}
	else { //leaf node
		Node *child0 = parent->children[0].fchild;
		Node *child1 = parent->children[1].fchild;
		free(parent->question);
		free(parent);
		if (child0 != NULL) free_list(child0);
		if (child1 != NULL) free_list(child1);
	}
}

