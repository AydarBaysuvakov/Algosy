#include <stdio.h>
#include "Decart.h"

int main() {
    struct Node array[] = {{83, 11}, {18, 8},  {25, 64}, {77, 33}, {44, 3},  {75, 55}, {86, 53},
                           {17, 87}, {57, 36}, {23, 84}, {69, 27}, {13, 47}, {7, 94},  {80, 21},
                           {32, 37}, {98, 88}, {19, 31}, {78, 72}, {24, 82}, {35, 41}};
    struct DTreeNode* root = BuildTree(array, 20);

    struct Node node = {50, 100};
    Insert(&root, node);
    Remove(&root, 85);

    DTreeDump(root, "decart.dot");

    Clear(root);
    }
