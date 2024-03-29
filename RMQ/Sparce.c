#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Sparce.h"

struct SparceTable* SparceTableCtor(int* array, int size, int mode)
    {
    assert(array);
    printf("\n");
    struct SparceTable *table = (struct SparceTable*) calloc(1, sizeof(struct SparceTable));

    int height = Log(size) + 1;
    table->buf_size = size * height;
    table->arr_size = size;
    table->mode = mode;

    table->buf = (int*) calloc(table->buf_size, sizeof(int));
    table->array = table->buf;

    Copy(array, table->array, size);
    for (int k = 1; k <= height; ++k)
        {
        for (int i = 0; i < size; ++i)
            {
            if (mode == MIN && table->buf[(k - 1) * size + i] < table->buf[(k - 1) * size + i + (1 << (k - 1))])
                table->buf[k * size + i] = table->buf[(k - 1) * size + i];
            else
                table->buf[k * size + i] = table->buf[(k - 1) * size + i + (1 << (k - 1))];
            }
        }

    return table;
    }

void SparceTableDtor(struct SparceTable* table)
    {
    free(table->buf);
    free(table);
    }

int RMQ(const struct SparceTable* table, int L, int R)
    {
    assert(table);

    int k = Log(R - L);
    int s = table->arr_size;
    if (table->mode == MIN)
        return table->buf[k * s + L] < table->buf[k * s + R - (1 << k)] ? table->buf[k * s + L] : table->buf[k * s + R - (1 << k)];
    if (table->mode == MAX)
        return table->buf[k * s + L] > table->buf[k * s + R - (1 << k)] ? table->buf[k * s + L] : table->buf[k * s + R - (1 << k)];
    return 0;
    }

int Log(int x)
    {
    int log = 0;
    for (; x; x = x >> 1, ++log);
    return --log;
    }

void Copy(int *src, int *dest, int size)
    {
    assert(src);
    assert(dest);
    for (int i = 0; i < size; i++) *(dest++) = *(src++);
    }
