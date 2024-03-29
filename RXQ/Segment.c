#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Segment.h"

struct SegTree* TreeCtor(int* array, int size, int neutral, int (*func)())
    {
    assert(array);

    //printf("\n");
    struct SegTree *table = (struct SegTree*) calloc(1, sizeof(struct SegTree));

    table->buf_size = (1 << (Log(size - 1) + 2)) - 1;
    table->tree = (int*) calloc(table->buf_size, sizeof(int));

    table->array_size = (1 << (Log(size - 1) + 1));
    table->array = table->tree + table->array_size - 1;

    int i = 0;
    for (; i < size; ++i)
        table->array[i] = array[i];
    for (; i < table->array_size; ++i)
        table->array[i] = neutral;

    table->neutral = neutral;
    table->func = func;

    for (i = table->array_size - 2; i >= 0; --i)
        table->tree[i] = func(table->tree[2 * i + 1], table->tree[2 * i + 2]);

    return table;
    }

void TreeDtor(struct SegTree* table)
    {
    free(table->tree);
    free(table);
    }

void Update(struct SegTree* table, int index, int value)
    {
    update(table, 0, index, value, 0, table->array_size);
    }

void update(struct SegTree* table, int vertex, int index, int value, int il, int ir)
    {
    if (!(il <= index && index < ir))
        return;
    if (vertex == index + table->array_size - 1)
        {
        table->tree[vertex] = value;
        return;
        }
    int im = (il + ir) / 2;
    update(table, 2 * vertex + 1, index, value, il, im);
    update(table, 2 * vertex + 2, index, value, im, ir);
    table->tree[vertex] = table->func(table->tree[2 * vertex + 1], table->tree[2 * vertex + 2]);
    }

int RXQ(const struct SegTree* table, int L, int R)
    {
    assert(table);
    return compute(table, 0, L, R, 0, table->array_size);
    }

int compute(const struct SegTree* table, int vertex, int L, int R, int il, int ir)
    {
    if (ir <= L || R <= il)
        return table->neutral;
    if (L <= il && ir <= R)
        {
        return table->tree[vertex];
        }
    int im = (il + ir) / 2;
    int a = compute(table, 2 * vertex + 1, L, R, il, im);
    int b = compute(table, 2 * vertex + 2, L, R, im, ir);
    return table->func(a, b);
    }

int F(int a, int b)
    {
    return a < b ? a : b;
    }

int Log(int x)
    {
    int log = 0;
    for (; x; x = x >> 1, ++log);
    return --log;
    }
