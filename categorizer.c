#include "qtree.h"
#include <ctype.h>

void print_greetings();

int quit(char *input, int len) {
	return (len <= 3) && ((input[0] == 'q') || (input[0] == 'Q'));
}

int main (int argc, char **argv) {
	// Add print greetings
	print_greetings();
	QNode *root = NULL;	
	char answer[MAX_LINE];	
	char name[MAX_LINE];
	

	Node * interests = NULL;

	if (argc < 2) {
        printf ("To run the program ./categorizer <name of input file>\n");
        return 1;
    }
	
    interests = get_list_from_file ( argv[1]);
	
    if (interests == NULL)
        return 1;

	root = add_next_level (root,  interests);

	free_list (interests);

	//main application loop
	char buffer[MAX_LINE];
	printf("What is your name?\n");
	while (fgets(buffer, MAX_LINE - 1, stdin) != NULL) {
		buffer[strcspn(buffer, "\r\n")] = '\0';
		int len = strlen(buffer);

		// break conditon
		if(quit(buffer, len))
			break;

		// reading username
		if (len < 8 || len >= 128) {
			printf("Invalid username length, try again\n");
			printf("What is your name?\n");
			continue;
		}
		//valid lenth of username.

		//check if input contains invalid char.
		int invalid_string = 0;
		for (int i = 0; i < len; i++) {
			if (!(isalpha(buffer[i]) 
				|| (('0' <= buffer[i]) && (buffer[i] <= '9')))) {
				// username invaild, try again.
				invalid_string = 1;
			}
		}
		if (invalid_string) {
			printf("Username contains invalid string, try again\n");
			printf("What is your name?\n");
			continue;
		}

		// Username valid, checking if username exists.
		strncpy(name, buffer, MAX_LINE - 1);
		Node *friends = search_user(root, name);
		if(friends != NULL) {
			print_users(friends);
			continue;
		}

		//Username doesn't exist, adding new user.
		int q = 0;
		QNode *cur = root;
		printf("Do you like %s?\n", cur->question);
		int end_of_question = 0;
		while(fgets(buffer, MAX_LINE - 1, stdin) != NULL) {
			buffer[strcspn(buffer, "\r\n")] = '\0';
			len = strlen(buffer);
			strncpy(answer, buffer, MAX_LINE - 1);

			//User quit the program.
			if(quit(answer, len)) {
				q = 1;
				break;
			}

			//Check if answer is valid.
			if(len > 3) {
				printf("Invalid length, try again\n");
				printf("Do you like %s?\n", cur->question);
				continue;
			}
			//Continue with 'Yes'.
			if(answer[0] == 'y' || answer[0] == 'Y') {
				cur = add_new_user(cur, "1", name);
			} else if(answer[0] == 'n' || answer[0] == 'N') { 
			//Continue with 'No'.
				cur = add_new_user(cur, "0", name);
			} else { //Invalid answer, repeat question again.
				printf("Invalid answer\n");
				printf("Do you like %s?\n", cur->question);
				continue;
			}

			//Check if it is the last question.
			if(cur->node_type == LEAF) {
				if(end_of_question == 1) 
					break;
				else
					end_of_question = 1;
			}
			//Next question.
			printf("Do you like %s?\n", cur->question);
		}

		//Check if user quit.
		if(q) break;

		//Show the users in the same group.
		if(answer[0] == 'y' || answer[0] == 'Y')
			print_users(cur->children[1].fchild);
		else
			print_users(cur->children[0].fchild);
		printf("What is your name?\n");

	}
    //end of main loop - the user tyoped "q".
    print_qtree (root, 0);
    free_qtree(root);
	return 0;
}

void print_greetings () {
	printf ("----------------------------------------------\n");
	printf ("Friend recommender system. Find people who are just like you!\n");
	printf ("CSC209 fall 2016 team. All rights reserved\n");
	printf ("----------------------------------------------\n");
}