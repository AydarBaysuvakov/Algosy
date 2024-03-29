#ifndef RSQ_H
#define RSQ_H

struct BinIndexed
    {
    int* array;
    int* tree;
    int size;
    };

struct BinIndexed* TreeCtor(int* array, int size);
void TreeDtor(struct BinIndexed* table);

void Modify(struct BinIndexed* table, int index, int value);
void Set(struct BinIndexed* table, int index, int value);

int RSQ(const struct BinIndexed* table, int L, int R);
int Sum(const struct BinIndexed* table, int index);

#endif //RSQ_H
