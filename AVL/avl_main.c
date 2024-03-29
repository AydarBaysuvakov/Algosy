#include <stdio.h>
#include "AVL.h"

int main()
    {
    struct AvlTreeNode* root = NULL;

    Insert(&root, 1);
    Insert(&root, 2);
    Insert(&root, 3);
    Insert(&root, 4);
    Insert(&root, 5);
    Insert(&root, 6);
    Insert(&root, 7);
    Insert(&root, 8);
    Insert(&root, 9);
    Insert(&root, 10);
    Insert(&root, 11);
    Insert(&root, 12);
    Insert(&root, 13);
    Insert(&root, 14);
    Insert(&root, 15);
    Insert(&root, 16);
    Delete(&root, 8);
    Delete(&root, 5);
    Delete(&root, 13);
    AvlTreeDump(root, "avl.dot");

    Clear(root);
    }
