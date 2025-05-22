#include "../include/Globals.h"

node_t* CreateNode(char* word, const int length, const node_t* next)
{
    if (!word)
    {
        fprintf(stderr, "CreateNode() error: no word given\n");
        return NULL;
    }

    node_t* new_node = (node_t*) calloc(1, sizeof(node_t));

    if (!new_node)
    {
        fprintf(stderr, "CreateNode() error: unable to calloc memory for new_node\n");
        return NULL;
    }

    new_node->word = (char*) calloc(length, sizeof(char));

    if (!(new_node->word))
    {
        fprintf(stderr, "CreateNode() error: unable to calloc memory for the word"
                        "(length = %d)\n", length);
        return NULL;
    }

    new_node->next = next;

    return new_node;
}

int ListDtor(node_t* node)
{
    if (!node) return OK;

    ListDtor(node->next);

    free(node);

    return OK;
}
