#pragma once

typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} Node;

Node* newNode(int x);

Node* addLastNode(Node* root, int x);

Node* addFirstNode(Node* root, int x);

Node* addNode(Node* root, int x);

int deleteNode(Node* root);

Node* getLastNode(Node* temp);

Node* getFirstNode(Node* temp);

Node* pushNode(Node* root, int x);
