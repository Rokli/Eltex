#include "Tree.h"


Tree *getTreeNode(int value) {

    Person person = CreatePerson();
    Tree* tmp = (Tree*) malloc(sizeof(Tree));

    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->_person = person;

    return tmp;
}

Tree* insert(Tree *root,int value) {

    if (root == NULL) {
        return getTreeNode(value);
    }
    if (CMP_RT(root->data, value)) {
        root->left = insert(root->left, value);
        return root;
    } else if (CMP_LT(root->data, value)) {
        root->right = insert(root->right, value);
        return root;
    } else {
        exit(3);
    }

}

Tree* editNode(Tree* root, int value){
    if (!root) {
        return NULL;
    }
    if (CMP_RT(root->data, value)) {
        editNode(root->left, value);
    } else if (CMP_LT(root->data, value)) {
        editNode(root->right, value);
    } else {
        root->_person = EditPerson(root->_person);
        return root;
    }
}

void printOneNode(Tree* root, int value){
    if (!root) {
        return;
    }
    if (CMP_RT(root->data, value)) {
        editNode(root->left, value);
    } else if (CMP_LT(root->data, value)) {
        editNode(root->right, value);
    } else {
        printNode(root);
        return;
    }
}

Tree* findMax(Tree *root) {
    if (root == NULL) {
        exit(4);
    }
    if (root->right) {
        return findMax(root->right);
    }
    return root;
}
 
Tree* findMin(Tree* root) {
    if (root == NULL) {
        exit(3);
    }
    if (root->left) {
        return findMin(root->left);
    }
    return root;
}

Tree* deleteNode(Tree* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (CMP_RT(root->data, value)) {
        root->left = deleteNode(root->left, value);
        return root;
    } else if (CMP_LT(root->data, value)) {
        root->right = deleteNode(root->right, value);
        return root;
    } else {
        if (root->left && root->right) {
            Tree* locMax = findMax(root->left);
            root->data = locMax->data;
            root->left = deleteNode(root->left, locMax->data); 
            return root;
        } else if (root->left) {
            Tree *tmp = root->left;
            free(root);
            return tmp;
        } else if (root->right) {
            Tree *tmp = root->right;
            free(root);
            return tmp;
        } else {
            free(root);
            return NULL;
        }
         
    }
}

void preOrderTravers(Tree* root) {
    if (root) {
        printNode(root);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

void printNode(Tree *current) {
    printf("----------\n");
    printf("ID:%d\n", current->data);
    printPerson(current->_person);
    printf("----------\n");
}

void LeftRotation(Tree **root) {
    Tree *parent = NULL,
         *C = NULL,
         *a = NULL, 
         *b = NULL;
 
    a = (*root);
    parent = a->parent;
    b = a->right;
    if (b == NULL) {
        return;
    }
    C = b->left;
 
    b->left = a;
    a->right = C;
    if (C) {
        C->parent = a;
    }
    b->parent = parent;
    if (parent) {
        if (parent->left == a) {
            parent->left = b;
        } else {
            parent->right = b;
        }
    }
    a->parent = b;
    if (!parent) {
        *root = (*root)->parent;
    }
}
 
void RigthRotation(Tree **root) {
    Tree *parent = NULL,
         *C = NULL,
         *a = NULL, 
         *b = NULL;
 
    b = (*root);
    parent = b->parent;
    a = b->left;
    if (a == NULL) {
        return;
    }
    C = a->right;
 
    a->right = b;
    b->left = C;
    if (C) {
        C->parent = b;
    }
    a->parent = parent;
    if (parent) {
        if (parent->left == b) {
            parent->left = a;
        } else {
            parent->right = a;
        }
    }
    b->parent = a;
 
    *root = (*root)->parent;
}

