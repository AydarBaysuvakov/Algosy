#include <stdio.h>
#include "Sparce.h"

int main() {
    int size = 12;
    int array[12] = {3, 6, 4, 8, 5, 2, 9, 4, 5, 2, 0, 1};

    struct SparceTable* table = SparceTableCtor(array, size, MIN);
    for (int L = 0; L < size; ++L)
        {
        for (int i = 0; i < L; i++) printf("  ");
        for (int R = L + 1; R < size + 1; ++R)
            {
            printf("%d ", RMQ(table, L, R));
            }
        putchar('\n');
        }
    SparceTableDtor(table);
    }
