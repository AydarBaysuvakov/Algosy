#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Fanvic.h"

struct BinIndexed* TreeCtor(int* array, int size)
    {
    assert(array);

    //printf("\n");
    struct BinIndexed *table = (struct BinIndexed*) calloc(1, sizeof(struct BinIndexed));

    table->array = array;
    table->size = size;
    table->tree = (int*) calloc(size, sizeof(int));

    for (int i = 0; i < size; ++i)
        Modify(table, i, array[i]);

    return table;
    }

void TreeDtor(struct BinIndexed* table)
    {
    free(table->tree);
    free(table);
    }

void Modify(struct BinIndexed* table, int index, int value)
    {
    while (index < table->size)
        {
        table->tree[index] += value;
        index = index | (index + 1);
        }
    }

void Set(struct BinIndexed* table, int index, int value)
    {
    int difference = value - table->array[index];
    table->array[index] = value;
    Modify(table, index, difference);
    }

int RSQ(const struct BinIndexed* table, int L, int R)
    {
    assert(table);
    return Sum(table, R) - Sum(table, L - 1);
    }

int Sum(const struct BinIndexed* table, int index)
    {
    assert(table);
    int res = 0;

    while (index >= 0)
        {
        res += table->tree[index];
        index = index & (index + 1);
        --index;
        }

    return res;
    }
