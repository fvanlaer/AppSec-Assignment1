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

//    int counter = 0;

    hashmap_t hashtable[HASH_SIZE];

    char* misspelled[MAX_MISSPELLED];

    bool dict_read = load_dictionary("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\wordlist.txt", hashtable);

//    fputs(dict_read ? "true" : "false", stdout);
//
//    for (int i = 0 ; i < HASH_SIZE; i++){
//        counter = printList(hashtable[i], counter);
//    }
//
//    printf("\n %d", counter);
//
//    bool success = check_word("Remember", hashtable);
//
//    fputs(success ? "true" : "false", stdout);

    FILE* fp = fopen("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\test1.txt", "r");
    if (fp == NULL){
        printf("Unable to load text file\n");
    }

    int num_misspelled = check_words(fp, hashtable, misspelled);

    printf("%d \n", num_misspelled);

    fclose(fp);

    free_memory(hashtable);

    return 0;
}