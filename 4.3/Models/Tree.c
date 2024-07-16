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


Tree* deletePerson(Tree* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (CMP_RT(root->data, value)) {
        root->left = deletePerson(root->left, value);
        return root;
    } else if (CMP_LT(root->data, value)) {
        root->right = deletePerson(root->right, value);
        return root;
    } else {
        if (root->left && root->right) {
            Tree* locMax = findMax(root->left);
            root->data = locMax->data;
            root->left = deletePerson(root->left, locMax->data); 
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
    printf("%d\n", current->data);
    printf("----------\n");
    printPerson(current->_person);
    printf("----------\n");
}