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

int numberOfOccurances(struct Trie* pTrie, char* word) {
    struct Trie* curr = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            return 0;
        curr = curr->children[index];
    }
    return (curr != NULL && curr->isEndOfWord) ? curr->count : 0;
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie* trie = createTrieNode();

    int numWords;
    printf("Enter the number of words in the dictionary: ");
    scanf("%d", &numWords);
    getchar();

    printf("Enter the words in the dictionary:\n");
    for (int i = 0; i < numWords; i++) {
        char word[50];
        fgets(word, 50, stdin);
        word[strcspn(word, "\n")] = '\0';
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
