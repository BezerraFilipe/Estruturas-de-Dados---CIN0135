#include <stdlib.h>
#include <stdio.h>


struct Node{
    int val;
    struct Node *next;
};

typedef struct Node Node;

Node *create_node(int value){ // valor do nó criado
    Node *node = malloc(sizeof(Node));
    node->val = value;
    node->next = NULL;
    return node;
}

Node *create_list(){
    Node *head = create_node(-1);
    return head;
}

void append(Node *head, int val) { // ponteiro para primeiro elemento da lista, valor a ser adicionado
    Node *addedNode = create_node(val);
    Node *cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }
    cur->next = addedNode;
    
}

void print_list(Node *head){
    int i = -1;
    Node *cur = head;
    while (cur != NULL){
        printf("list[%d] = %d\n", i, cur->val);
        cur = cur->next;
        i++;
    }
    
}

void insert_pos(Node *head, unsigned int pos, int val){
    Node *addedNode = create_node(val);

     // Caso especial: Inserção na posição 0
    if (pos == 0) {
        addedNode->next = head->next;
        head->next = addedNode;
        return;
    }
    
    int i = 0;
    Node *cur = head->next;
    while (i <( pos -1) && cur->next != NULL){
        cur = cur->next;
        i++;
    }
    addedNode->next = cur->next;
    cur->next = addedNode;

    
}

int main(){
    
    Node *list = create_list();
    
    append(list, 2);
    append(list, 3);
    append(list, 5);
    append(list, 7);
    printf("1: \n");
    printf("\n");
    print_list(list);

    insert_pos(list,0, 0);
    printf("2: \n");
    printf("\n");
    print_list(list);

    insert_pos(list,3,12);
    printf("3: \n");
    printf("\n");
    print_list(list);

    insert_pos(list,5,9);
    printf("4: \n");
    printf("\n");
    print_list(list);


    return 0;
}



/*

find_val
find_pos
insert_pos
*/