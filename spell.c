// Francois VAN LAER
// N14816307
// New York University
// CS 9163 - Application Security

#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 45
#define HASH_SIZE 2000
#define MAX_MISSPELLED 1000

typedef struct node{
    char word[LENGTH + 1];
    struct node* next;
}
node;

typedef node* hashmap_t;

int hash_function(const char* word)
{
    int sum = 0;
    int word_length = (int) strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }

    int bucket = sum % HASH_SIZE;
    return bucket;
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
    // Initialize / Reset hashtable
    for (int i = 0; i < HASH_SIZE; i++){
        hashtable[i] = NULL;
    }
    
    // Open dictionary file
    FILE* fp = fopen(dictionary_file, "r");
    if (fp == NULL){
        printf("Unable to load dictionary file\n");
        return false;
    }

    // Variable to temporarily store each word from dictionary
    char temp[LENGTH + 1];

    // Read each word of dictionary    
    while (fscanf(fp, "%s", temp) > 0){
        // Create new node
        hashmap_t new_node = malloc(sizeof(node));
        new_node->next = NULL;
        // Copy word from 'temp' to 'new_node'
        strcpy(new_node->word, temp);
        // Set bucket for new word
        int bucket = hash_function(new_node->word);
        if (hashtable[bucket] == NULL){
            hashtable[bucket] = new_node;
        }
        else{
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
    }

    // Close dictionary file
    fclose(fp);

    // The dictionary is loaded into the hashtable
    return true;
}

bool check_word(const char* word, hashmap_t hashtable[]){

    // Check whether the "word" is all digit
    bool all_digits = true;
    for (int i = 0; i < strlen(word); i++){
        if (!isdigit(word[i])){
            all_digits = false;
        }
    }
    if (all_digits == true){
        return true;
    }

    int bucket = hash_function(word);
    hashmap_t cursor = hashtable[bucket];

    while(cursor != NULL){
        if(strcmp(word, cursor->word) == 0){
            return true;
        }
        cursor = cursor->next;
    }

    // Lowercase the words
    char lower_word[strlen(word)];
    for (int i = 0; i < (int) strlen(word); i++){
        lower_word[i] = tolower( word[i]);
    }
    lower_word[strlen(word)] = '\0';

    // New bucket value for new word
    bucket = hash_function(lower_word);
    cursor = hashtable[bucket];

    while(cursor != NULL){
        if (strcmp(lower_word, cursor->word) == 0){
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]){
    int num_misspelled = 0;
    char* token;

    // Search the end of file and calculate total number of characters
    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    // Reset file pointer
    fseek(fp, 0L, SEEK_SET);

    // Buffer to store file
    char temp[file_size + 1];

    // Reading file
    while (fgets(temp, (int) file_size + 1, fp)){
        token = strtok(temp, " ");
        while (token != NULL) {
            // Case with new line
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = 0;
            }
            // Punctuation detected at the beginning of "word"
            if (ispunct(token[0])){
                token++;
            }
            // Punctuation detected at the end of "word"
            if (ispunct(token[strlen(token) - 1])){
                token[strlen(token) - 1] = 0;
            }
            // Comparing the current word to the dictionary hashtable
            if (check_word(token, hashtable) == false){
                misspelled[num_misspelled] = token;
                num_misspelled++;
            }
            token = strtok(NULL, " ");
        }
    }
    return num_misspelled;
}

bool free_memory(hashmap_t hashtable[]){
    for (int i = 0; i < HASH_SIZE; i++){
        node* pointer = hashtable[i];
        while (pointer != NULL){
            node* temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    return true;
}