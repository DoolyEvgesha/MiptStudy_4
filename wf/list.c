#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "dictionary.h"
#include "list.h"

void push(struct Node** head_ref, wrd * new_data)
{
    struct Node* new_node   = (struct Node*)malloc(sizeof(struct Node));

    new_node->data          = new_data;
    new_node->next          = (*head_ref);
    new_node->prev          = NULL;

    if ((*head_ref) != NULL)
        (*head_ref)->prev   = new_node;

    (*head_ref)             = new_node;
}

void insertAfter(struct Node* prev_node, wrd * new_data)
{
    if (prev_node == NULL) {
        fprintf(stderr,"the given previous node cannot be NULL");
        return;
    }

    struct Node* new_node   = (struct Node*)malloc(sizeof(struct Node));

    new_node->data          = new_data;
    new_node->next          = prev_node->next;
    prev_node->next         = new_node;
    new_node->prev          = prev_node;

    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

void insertBefore(struct Node** head_ref, struct Node* next_node, wrd * new_data)
{
    if (next_node == NULL) {
        fprintf(stderr, "the given next node cannot be NULL\n");
        //printf("the given next node cannot be NULL\n");
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data      = new_data;
    new_node->prev      = next_node->prev;
    next_node->prev     = new_node;
    new_node->next      = next_node;

    if (new_node->prev != NULL)
        new_node->prev->next    = new_node;
    else
        (*head_ref)             = new_node;

}

void append(struct Node** head_ref, wrd * new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last   = *head_ref;

    new_node->data      = new_data;
    new_node->next      = NULL;

    if (*head_ref == NULL) {
        new_node->prev  = NULL;
        *head_ref       = new_node;
        return;
    }
    while (last->next != NULL)
        last            = last->next;

    last->next          = new_node;
    new_node->prev      = last;

    return;
}

void print_list(struct Node *node)
{
    printf("\ncount = %d\n", node->count);

    struct Node* last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL) {
        printf(" %s ", node->data->w);
        last    = node;
        node    = node->next;
    }

    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf(" %s ", last->data->w);
        last    = last->prev;
    }
}

int list_size(dict_fn * d)
{
    dct * v = d->dct;
    return v->count;
}

void list_dict(dict_fn * d, char * w)
{
    dct * node = d->dct;

    if(node.count == 0)
    {
        push(&node, w);
        return;
    }

    for(int i = 0; i < node->count + 1; i++)
    {
        if(strcmp(w, node->w->w) == 0)
        {
            node->w[i].num++;
            return;
        }
    }

    push(&node, w);
    node->count++;
    node->w->num++;
}


dict_fn * list_create()
{
    dict_fn * d       = malloc(sizeof(dict_fn));
    Node    * n       = calloc(1, sizeof(Node));

    d->dict           = list_dict;
    d->print_dict     = print_list; //incompatible types
    d->size           = list_size;

    d->dct            = n;

    return d;
};