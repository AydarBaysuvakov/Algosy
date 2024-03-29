#include <stdio.h>
#include "Fanvic.h"

int main() {
    int size = 12;
    int array[12] = {3, 6, 4, 8, 5, 2, 9, 4, 5, 2, 0, 1};


    struct BinIndexed* table = TreeCtor(array, size);

    for (int L = 0; L < size; ++L)
        {
        for (int i = 0; i < L; i++) printf("\t");
        for (int R = L; R < size; ++R)
            {
            printf("%d\t", RSQ(table, L, R));
            }
        printf("\n");
        }
    TreeDtor(table);
    }

