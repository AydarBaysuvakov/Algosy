#ifndef RMQ_H
#define RMQ_H

enum MODE
    {
    MIN = 0,
    MAX = 1
    };

struct SparceTable
    {
    int* array;
    int arr_size;
    int* buf;
    int buf_size;
    int mode;
    };


struct SparceTable* SparceTableCtor(int* array, int size, int mode);
void SparceTableDtor(struct SparceTable* table);
int RMQ(const struct SparceTable* table, int L, int R);
int Log(int x);
void Copy(int *src, int *dest, int size);

#endif //RMQ_H
