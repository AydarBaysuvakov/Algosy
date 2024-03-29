#include <stdio.h>
#include "Splay.h"

int main() {
    struct SplayTreeNode* root = NULL;

    Add(&root, 12);
    Add(&root, 26);
    Add(&root, 59);
    Add(&root, 5);
    Add(&root, 99);
    Add(&root, 82);
    Find(&root, 26);
    SplayTreeDump(root, "splay.dot");

    Clear(root);
    }
