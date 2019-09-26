#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spell.c"

int main(){

    printf("WELCOME TO OUR SPELL CHECK\n");

    hashmap_t hashtable[HASH_SIZE];

    bool dict_read = load_dictionary("C:\\Users\\Francois\\CLionProjects\\Application Security\\AppSec-Assignment1\\wordlist.txt", hashtable);

    fputs(dict_read ? "true" : "false", stdout);

    return 0;
}