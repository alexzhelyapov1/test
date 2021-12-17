#include <stdio.h>
#include <stdlib.h>

typedef int Data;
struct Node {
    Data val;
    struct Node* next; //head pref
    int switcher;
};
struct List {
    struct Node* head;
    int size;
    struct Node* last;
};


void list_delete_el (struct List * list, int x){
    if (list == NULL){
        return;
    }
    struct Node * temp = list -> head;
    while (temp != NULL){
        if (temp -> val == x){
            temp -> switcher = 0;
        }
        temp = temp -> next;
    }
}

struct List* list_create (void) {
    struct List* list = (struct List*) calloc (1, sizeof (struct List));
    list -> head = NULL;
    list -> last = NULL;
    return list;
}

struct Node* node_create (Data val) {
    struct Node* node = (struct Node*) calloc (1, sizeof (struct Node));
    node -> val = val;
    node -> next = NULL;
    node -> switcher = 1;
    return node;
}

void list_add_first (struct List* list, Data x) {
    if (!list) {
        return;
    }
    struct Node* temp_node = list -> head;
    if (list -> head) {
        list -> head = node_create (x);
        list -> head -> next = temp_node;
    }
    else {
        list -> head = node_create (x);
        list -> last = list -> head;
    }
}

void list_add_last (struct List* list, Data x) {
    if (!list) {
        return;
    }   
    struct Node* last = list -> last;
    if (!last) {
        list_add_first (list, x);
        return;
    }
    last -> next = node_create (x);
    list -> last = last -> next;
}

struct Node* semi_last_node (struct List* list) {
    if (!list) {
        return NULL;
    }
    struct Node* node = list -> head;
    if (node -> next == NULL) {
        return NULL;
    }
    while (node -> next -> next){
        node = node -> next;
    }
    return node;
}

Data list_remove_first (struct List* list) {
    Data x = list -> head -> val;
    struct Node* temp = list -> head;
    list -> head = list -> head -> next;
    free (temp);
    return x;
}

Data list_remove_last (struct List* list) {
    if (!list) {
        return 1331;
    }
    struct Node* semi_last = semi_last_node (list);

    Data x = 0;
    if (semi_last) {
        x = semi_last -> next -> val;
        free (semi_last -> next);
        semi_last -> next = NULL;
        list -> last = semi_last;
    } 
    else {
        x = list -> head -> val;
        free (list -> head);
        list -> head = NULL;
        list -> last = NULL;
    }
    return x;
}

Data list_get_first (struct List* list) {
    return list -> head -> val;
}

Data list_get_last (struct List* list) {
    return list -> last -> val;
}


void list_print (struct List* list) {
    if (!list || !list -> head) {
        printf ("Empty list");
    }
    struct Node* node = list -> head;
    while (node) {
        printf ("%d ", node -> val);
        node = node -> next;
    }
    printf ("\n");
}

int list_size (struct List* list) {
    int size = 0;
    if (!list) {
        return 0;
    }
    struct Node* node = list -> head;
    while (node) {
        size += 1;
        node = node -> next;
    }
    return size;
}

void list_clear_node (struct Node* node) {
    if (!node) {
        return;
    }
    list_clear_node (node -> next);
    free (node);
}

void list_clear (struct List* list) {
    if (!list) {
        return;
    }
    list_clear_node (list -> head);
    list -> head = NULL;
}

void list_destroy (struct List * list) {
    if (!list) {
        return;
    }
    list_clear_node (list -> head);
    list -> head = NULL;
    free (list);
}

int main (int argc, char * argv[]) {
    struct List * a = list_create();
    FILE * input = fopen ("input.txt", "r");
    int x;
    fscanf (input, "%d", &x);
    while (x != -1){
        list_add_last (a, x);
        fscanf (input, "%d", &x);
    }
    fscanf (input, "%d", &x);
    while (x != -1){
        list_delete_el (a, x);
        fscanf (input, "%d", &x);
    }
    fclose (input);
    FILE * out = fopen ("output.txt", "w");
    struct Node * temp = a -> head;
    while (temp != NULL){
        if (temp -> switcher == 1){
             fprintf (out, "%d ", temp -> val);
         }
        temp = temp -> next;
    }
    fclose (out);
    return 0;
}