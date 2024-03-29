#ifndef DEC_H
#define DEC_H

struct Node
    {
    int key;
    int priority;
    };

struct DTreeNode
    {
    int key;
    int priority;
    struct DTreeNode* left;
    struct DTreeNode* right;
    struct DTreeNode* parent;
    };

void Insert(struct DTreeNode** root, struct Node elem);
void Remove(struct DTreeNode** root, int key);

struct DTreeNode* BuildTree(struct Node* array, int size);

void Split(struct DTreeNode* root, int key, struct DTreeNode** tree1, struct DTreeNode** tree2);
struct DTreeNode* Merge(struct DTreeNode* tree1, struct DTreeNode* tree2);

int Compare(const void* a, const void* b);

struct DTreeNode* Find(struct DTreeNode* node, int key);
void Clear(struct DTreeNode* node);

void DTreeDump(struct DTreeNode* node, const char* file);
void DNodeDump(struct DTreeNode* node, FILE *fp);

#endif //DEC_H
