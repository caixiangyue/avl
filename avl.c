#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define MAX(a, b) (a)>(b)?a:b

int
avl_get_height(AvlTree *root) {
    if (!root) return 0;
    if (root->left && root->right){
        return MAX(root->left->height, root->right->height)+1;
    } else if(root->left) {
        return root->left->height+1;
    } else if (root->right) {
        return root->right->height+1;
    }

    return MAX(avl_get_height(root->left), avl_get_height(root->right)) + 1;
}

int avl_get_balance_factor(AvlTree *root) {
    if (!root) return 0;
    return avl_get_height(root->left) - avl_get_height(root->right);

}

AvlTree*
avl_rr(AvlTree* tree) {
    AvlTree* left = tree->left;
    tree->left = left->right;
    left->right = tree;

    left->height = MAX(avl_get_height(left->left), avl_get_height(left->right)) + 1;
    tree->height = MAX(avl_get_height(tree->left), avl_get_height(tree->right)) + 1;
    return left;
}

AvlTree*
avl_rl(AvlTree* tree) {
    AvlTree* right = tree->right;
    tree->right = right->left;
    right->left = tree;
    right->height = MAX(avl_get_height(right->left), avl_get_height(right->right)) + 1;
    tree->height = MAX(avl_get_height(tree->left), avl_get_height(tree->right)) + 1;
    return right;
}

AvlTree*
avl_rebalance(AvlTree *tree) {
    int factor = avl_get_balance_factor(tree);

    if (factor > 1 && avl_get_balance_factor(tree->left) > 0) {
        return avl_rr(tree);
    } else if (factor > 1 && avl_get_balance_factor(tree->left) <= 0) {
        tree->left = avl_rl(tree->left);
        return avl_rr(tree);
    } else if (factor < -1 && avl_get_balance_factor(tree->right) <= 0) {
        return avl_rl(tree);
    } else if (factor < -1 && avl_get_balance_factor(tree->right) > 0) {
        tree->right = avl_rr(tree->right);
        return avl_rl(tree);
    } else {
        tree->height = avl_get_height(tree);
        return tree;
    }
}

AvlTree*
avl_insert(AvlTree *tree, int key) {
    if (!tree) {
        tree = malloc(sizeof(AvlTree));
        tree->left = NULL;
        tree->right = NULL;
        tree->height = 1;
        tree->key = key;
    } else if (tree->key == key) {
        return tree;
    } else {
        if (tree->key < key) { 
            tree->right = avl_insert(tree->right, key);
        }
        else {
            tree->left = avl_insert(tree->left, key);
        }
    }
    return avl_rebalance(tree);
}

int
avl_search(AvlTree* tree, int val) {
    if (!tree) return -1;
    if (val == tree->key) {
        return 1;
    }
    else if (tree->key < val) {
        return avl_search(tree->right, val);
    }
    else {
        return avl_search(tree->left, val);
    }
}

void
avl_travel(AvlTree* tree, int key, int dir) {
    if(!tree) return;
    if (dir == 0) {
        printf("tree is root: %d, height:%d\n", tree->key, tree->height);
    } else if (dir == -1) {
        // printf("%d is %d left child:%d\n", tree->key, key, tree->height);
    } else {
        // printf("%d is %d right child:%d\n", tree->key, key, tree->height);
    }

    avl_travel(tree->left, tree->key, -1);
    avl_travel(tree->right, tree->key, 1);
}


#ifdef DEBUG

int main()
{
    AvlTree *tree = NULL;
    for (int i=0; i<1000000; i++) {
        tree = avl_insert(tree, i);
    }
    avl_travel(tree,0,0);
    int ret = avl_search(tree, 31);
    if (ret == 1) {
        printf("found\n");
    } else {
        printf("not found\n");
    }
    return 0;
}


#endif //DEBUG
