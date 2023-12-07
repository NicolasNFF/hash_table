#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

struct HashNode
{
    char *key;
    int value;
    struct HashNode *next;
};

struct HashNode *table[TABLE_SIZE] = {NULL};

int hash(char *key)
{
    int hash = 0;
    while (*key)
    {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

void insert(char *key, int value)
{
    int index = hash(key);
    struct HashNode *newNode = malloc(sizeof(struct HashNode));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
}

int search(char *key)
{
    int index = hash(key);
    struct HashNode *current = table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void removeElement(char *key)
{
    int index = hash(key);
    struct HashNode *current = table[index];
    struct HashNode *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            printf("Elemento com chave '%s' removido.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Elemento com chave '%s' nao encontrado.\n", key);
}

void listAllElements()
{
    printf("Elementos na tabela hash:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct HashNode *current = table[i];
        while (current != NULL)
        {
            printf("Chave: %s, Valor: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}

int main()
{
    insert("apple", 42);
    insert("banana", 17);
    insert("cherry", 73);

    printf("Value for 'apple': %d\n", search("apple"));
    printf("Value for 'banana': %d\n", search("banana"));
    printf("Value for 'cherry': %d\n", search("cherry"));

    printf("\n");

    removeElement("banana");
    listAllElements();

    return 0;
}
