#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spell.c"

int printList(node* n, int counter){
    while (n != NULL) {
        counter++;
        printf(" %s \n", n->word);
        n = n->next;
    }
    return counter;
}

int main(){

    printf("WELCOME TO SPELL CHECK\n");

    int counter = 0;

    hashmap_t hashtable[HASH_SIZE];

    bool dict_read = load_dictionary("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\wordlist.txt", hashtable);

//    fputs(dict_read ? "true" : "false", stdout);
//
//    for (int i = 0 ; i < HASH_SIZE; i++){
//        counter = printList(hashtable[i], counter);
//    }
//
//    printf("\n %d", counter);

    bool success = check_word("autHentICated", hashtable);

    fputs(success ? "true" : "false", stdout);

    return 0;
}