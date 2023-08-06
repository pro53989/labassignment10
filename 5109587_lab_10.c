#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int count;
};

struct Trie* createTrieNode() {
    struct Trie* node = (struct Trie*) malloc(sizeof(struct Trie));
    node->isEndOfWord = false;
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Function to insert a word into the trie
void insert(struct Trie** ppTrie, char* word) {
    struct Trie* curr = *ppTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            curr->children[index] = createTrieNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
    curr->count++;
}

// Function to find the number of occurrences of a word in the trie
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    struct Trie* curr = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            return 0;
        curr = curr->children[index];
    }
    return (curr != NULL && curr->isEndOfWord) ? curr->count : 0;
}

// Function to deallocate memory used by the trie
struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
}

int main(void) {
    // Create the root node of the trie
    struct Trie* trie = createTrieNode();

    int numWords;
    printf("Enter the number of words in the dictionary: ");
    scanf("%d", &numWords);
    getchar();

    // Insert words into the trie
    printf("Enter the words in the dictionary:\n");
    for (int i = 0; i < numWords; i++) {
        char word[50];
        fgets(word, 50, stdin);
        word[strcspn(word, "\n")] = '\0'; // Remove the newline character from the input
        insert(&trie, word);
    }

    // Words to search for in the trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));

    // Deallocate memory used by the trie
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
