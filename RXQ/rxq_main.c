#include <stdio.h>
#include <limits.h>
#include "Segment.h"

int main() {
    int size = 12;
    int array[12] = {3, 6, 4, 8, 5, 2, 9, 4, 5, 2, 0, 1};

    struct SegTree* table = TreeCtor(array, size, INT_MAX, F);

    for (int L = 0; L < size; ++L)
        {
        for (int i = 0; i < L; i++) printf("\t");
        for (int R = L + 1; R < size + 1; ++R)
            {
            printf("%d\t", RXQ(table, L, R));
            }
        printf("\n");
        }
    TreeDtor(table);
    }

