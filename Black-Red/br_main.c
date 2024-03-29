#include <stdio.h>
#include "Black-red.h"

int main() {
    struct BRTreeNode* root = NULL;

    Insert(&root, 12);
    Insert(&root, 26);
    Insert(&root, 59);
    Insert(&root, 5);
    Insert(&root, 99);
    Insert(&root, 82);
    Insert(&root, 81);
    Insert(&root, 56);
    Insert(&root, 39);
    Insert(&root, 83);
    Insert(&root, 11);
    Insert(&root, 18);
    Insert(&root, 25);
    Delete(&root, 11);
    Delete(&root, 59);
    Delete(&root, 56);
    Delete(&root, 82);
    BRTreeDump(root, "br.dot");


    Clear(root);
    }
