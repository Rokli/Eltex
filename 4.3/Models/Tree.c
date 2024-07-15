#include "Tree.h"

Tree* getFreeTree(int value, Tree *parent) {
    Tree* tmp = (Tree*) malloc(sizeof(Tree));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insert(Tree **head, int value) {
    Tree *tmp = NULL;
    Tree *ins = NULL;
    if (*head == NULL) {
        *head = getFreeTree(value, NULL);
        return;
    }
     
    tmp = *head;
    while (tmp) {
        if (CMP_GT(value, tmp->data)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeTree(value, tmp);
                return;
            }
        } else if (CMP_LT(value, tmp->data)) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeTree(value, tmp);
                return;
            }
        } else {
            exit(2);
        }
    }
}

Tree* getMinTree(Tree *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

Tree* getMaxTree(Tree *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

Tree *getTreeByValue(Tree *root, int value) {
    while (root) {
        if (CMP_GT(root->data, value)) {
            root = root->left;
            continue;
        } else if (CMP_LT(root->data, value)) {
            root = root->right;
            continue;
        } else {
            return root;
        }
    }
    return NULL;
}

void removeTreeByPtr(Tree *target) {
    if (target->left && target->right) {
        Tree *localMax = getMaxTree(target->left);
        target->data = localMax->data;
        removeTreeByPtr(localMax);
        return;
    } else if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        } else {
            target->parent->right = target->left;
        }
    } else if (target->right) {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        } else {
            target->parent->left = target->right;
        }
    } else {
        if (target == target->parent->left) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }
    }
    free(target);
}

void deleteValue(Tree *root, int value) {
    Tree *target = getTreeByValue(root, value);
    removeTreeByPtr(target);
}

void printTree(Tree *root, const char *dir, int level){
    if (root) {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}