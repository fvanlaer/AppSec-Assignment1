#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 45
#define HASH_SIZE 2000
#define MAX_MISSPELLED 1000

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

typedef node* hashmap_t;

int hash_function(const char* word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++){
        sum += word[i];
    }

    int bucket = sum % HASH_SIZE;
    return bucket;
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
    // Initialize hashtable
    for (int i = 0; i < HASH_SIZE; i++){
        hashtable[i] = NULL;
    }

    // Open dictionary file
    FILE* fp = fopen(dictionary_file, "r");
    if (fp == null){
        printf("Unable to load dictionary file\n");
        return false;
    }

    // Variable to temporarily store each word from dictionary
    char temp[LENGHT + 1];

    // Read each word of dictionary    
    while (fscanf(fp, "%s", temp)==1){
        // Create new node
        node* new_node = malloc(sizeof(node);
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
    
    return true;
}

int check_word(const char* word, hashmap_t hashtable[])
{
}

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[])
{
}

int main()
{

}
