#ifndef tree_h
#define tree_h

#include <stdlib.h>
#include <stdio.h>
#include "Person.h"

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_RT(a, b) ((a) > (b))

typedef struct Tree {
    int data;
    Person _person;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
} Tree;

Tree *getTreeNode(int value);

Tree* insert(Tree *root,int value);

Tree* findMax(Tree *root);

Tree* findMin(Tree* root);

Tree* deleteNode(Tree* root, int value);

void printOneNode(Tree* root, int value);

void printNode(Tree *current);

void preOrderTravers(Tree* root);

Tree* editNode(Tree* root, int value);

void RigthRotation(Tree **root);

void LeftRotation(Tree **root);

#endif