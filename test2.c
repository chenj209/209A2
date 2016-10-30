#include "qtree.h"

int main (int argc, char ** argv) {
    QNode *root = NULL;
	Node *q_list;
    
    if (argc < 2) {
        printf ("To run the program ./test2 <name of input file>\n");
        return 1;
    }
    
    q_list = get_list_from_file (argv[1]);
    
    if (q_list == NULL) {
        printf ("The list is empty\n");
        return 1;
    }
    
    //that is only the first test to test creation of the question tree
    root = add_next_level (root, q_list);
	print_qtree (root, 0);
    
    
    //your tests here

    // test add_new_user.
    char *username = argv[2];
    char **answers = &(argv[3]);
    int ans_len = argc - 3;
    //check the length of questions
    int q_len = 0;
    Node *q_counter = q_list;
    while (q_counter != NULL) {
        q_counter = q_counter->next;
        q_len++;
    }

    if (q_len != ans_len) 
        printf("\n\nAnswer length does not equal question length.\n\n");
    else {
        QNode *cur = add_new_user(root, answers[0], username);
        for (int i = 1; i < ans_len; i++) {
            cur = add_new_user(cur, answers[i], username);
            // if (i == ans_len - 1) {
            //     add_new_user(cur, answers[i], "Kinder");
            // }
        }
    }
    printf("Adding user: %s\n", username);
    print_qtree(root, 0);
    //done testing add_new_user.

    //testing search friends
    Node *friends = search_user(root, username);
    printf("These are friends of %s: \n", username);
    print_users(friends);
    //done testing search friends.


    free_list(q_list);
    free_qtree(root);
    
    return 0;
}