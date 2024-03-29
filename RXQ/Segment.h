#ifndef RXQ_H
#define RXQ_H

struct SegTree
    {
    int* tree;
    int buf_size;

    int* array;
    int array_size;

    int neutral;
    int (*func)();
    };

struct SegTree* TreeCtor(int* array, int size, int neutral, int (*func)());
void TreeDtor(struct SegTree* table);

void Update(struct SegTree* table, int index, int value);
void update(struct SegTree* table, int vertex, int index, int value, int il, int ir);

int RXQ(const struct SegTree* table, int L, int R);
int compute(const struct SegTree* table, int vertex, int L, int R, int il, int ir);

int F(int a, int b);
int Log(int x);

#endif //RXQ_H
