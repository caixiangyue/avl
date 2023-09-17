#ifndef AVL_H
#define AVL_H

typedef struct AvlTree {
    struct AvlTree *left;
    struct AvlTree *right;
    int key;
    int height;
}AvlTree;




#endif //AVL_H
