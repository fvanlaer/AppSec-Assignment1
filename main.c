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

    printf("FIRST TEST:\n");
    printf("Loading dictionary file...\n");

    bool dict_read = load_dictionary("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\wordlist.txt", hashtable);

    if (dict_read == true){
        printf("The dictionary was properly loaded.\n");
    }
    else{
        printf("ERROR! The program will terminate now.\n");
        return 0;
    }
//
//    for (int i = 0 ; i < HASH_SIZE; i++){
//        counter = printList(hashtable[i], counter);
//    }
//
//    printf("\n %d", counter);
//
    printf("SECOND TEST\n");
    printf("Checking specific word...\n");

    bool is_word = check_word("1234", hashtable);

    if (is_word == true){
        printf("The selected word is spelled correctly.\n");
    }

    else{
        printf("This word is not spelled correctly.\n");
    }

    printf("THIRD TEST\n");
    printf("Checking spelling in specific file...\n");

    FILE* fp = fopen("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\test1.txt", "r");
    if (fp == NULL){
        printf("Unable to load text file\n");
    }

    int num_misspelled = check_words(fp, hashtable, misspelled);

    printf("There are %d misspelled words in the selected file.\n", num_misspelled);

    fclose(fp);

    printf("END OF PROGRAM\n");
    printf("Freeing allocated memory...\n");

    bool success = free_memory(hashtable);
    if (success == true){
        printf("All the allocated memory was properly freed. The operation is a SUCCESS!\n");
    }
    else{
        printf("ERROR! The allocated memory could not be freed.\n");
    }

    return 0;
}