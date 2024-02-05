#include "List/include/List.h"

#include <stdlib.h>

Node* newNode(int x) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->value = x;
    root->n = root->p = NULL;
    return root;
}

Node* addLastNode(Node* root, int x) {
    root->n = newNode(x);
    root->n->p = root;
    return root->n;
}

Node* addFirstNode(Node* root, int x) {
    root->p = newNode(x);
    root->p->n = root;
    return root->p;
}

Node* addNode(Node* root, int x) {
    Node* temp = newNode(x);
    temp->n = root->n;
    if (root->n != NULL) {
        temp->n->p = temp;
    }
    root->n = temp;
    temp->p = root;

    return temp;
}

int deleteNode(Node* root) {
    int s = 0;
    if (root->n != NULL && root->p != NULL) {
        if (root->p == NULL)  // ilk eleman sa
        {
            root->n->p = NULL;
            s = 2;
        } else if (root->p != NULL) {
            if (root->n == NULL)  // son elemansa
            {
                s = 3;
                root->p->n = NULL;
            } else if (root->n != NULL) {
                s = 1;
                root->p->n = root->n;
                root->n->p = root->p;
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
    while (temp->n != NULL) {
        temp = temp->n;
    }
    return temp;
}

Node* getFirstNode(Node* temp) {
    while (temp->p != NULL) {
        temp = temp->p;
    }
    return temp;
}

Node* pushNode(Node* root, int x) {
    root = getLastNode(root);
    return addLastNode(root, x);
}
