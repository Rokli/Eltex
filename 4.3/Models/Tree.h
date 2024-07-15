#ifndef tree_h
#define tree_h

#include <stdlib.h>
#include <stdio.h>

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))
 
typedef struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
} Tree;

Tree* getFreeTree(int value, Tree *parent);

void insert(Tree **head, int value);

Tree* getMinTree(Tree *root);

Tree* getMaxTree(Tree *root);

Tree *getTreeByValue(Tree *root, int value);

void removeTreeByPtr(Tree *target);

void deleteValue(Tree *root, int value);

void printTree(Tree *root, const char *dir, int level);

#endif