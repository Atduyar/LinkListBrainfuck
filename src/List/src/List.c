#include "List/include/List.h"

#include <stdlib.h>

Node* newNode(int x) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->value = x;
    root->next = root->prev = NULL;
    return root;
}

Node* addLastNode(Node* root, int x) {
    root->next = newNode(x);
    root->next->prev = root;
    return root->next;
}

Node* addFirstNode(Node* root, int x) {
    root->prev = newNode(x);
    root->prev->next = root;
    return root->prev;
}

Node* addNode(Node* root, int x) {
    Node* temp = newNode(x);
    temp->next = root->next;
    if (root->next != NULL) {
        temp->next->prev = temp;
    }
    root->next = temp;
    temp->prev = root;

    return temp;
}

int deleteNode(Node* root) {
    int s = 0;
    if (root->next != NULL && root->prev != NULL) {
        if (root->prev == NULL)  // ilk eleman sa
        {
            root->next->prev = NULL;
            s = 2;
        } else if (root->prev != NULL) {
            if (root->next == NULL)  // son elemansa
            {
                s = 3;
                root->prev->next = NULL;
            } else if (root->next != NULL) {
                s = 1;
                root->prev->next = root->next;
                root->next->prev = root->prev;
            }
        }
    } else {  // tek elemansa
        s = 0;
    }
    free(root);
    return s;
}

///////////////

Node* getLastNode(Node* temp) {
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

Node* getFirstNode(Node* temp) {
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    return temp;
}

Node* pushNode(Node* root, int x) {
    root = getLastNode(root);
    return addLastNode(root, x);
}
