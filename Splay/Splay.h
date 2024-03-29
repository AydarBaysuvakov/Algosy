#ifndef SPLAY_H
#define SPLAY_H

struct SplayTreeNode {
    int key;
    struct SplayTreeNode* left;
    struct SplayTreeNode* right;
    struct SplayTreeNode* parent;
};

void Add(struct SplayTreeNode** root, int key);
void Remove(struct SplayTreeNode** root, int key);

void Splay(struct SplayTreeNode* node, struct SplayTreeNode** root);

void LeftRotate(struct SplayTreeNode* node, struct SplayTreeNode** root);
void RightRotate(struct SplayTreeNode* node, struct SplayTreeNode** root);

struct SplayTreeNode* Merge(struct SplayTreeNode* tree1, struct SplayTreeNode* tree2);
void Split(struct SplayTreeNode** root, int key, struct SplayTreeNode** tree1, struct SplayTreeNode** tree2);

struct SplayTreeNode* MaxElem(struct SplayTreeNode* node);
struct SplayTreeNode* MinElem(struct SplayTreeNode* node);

struct SplayTreeNode* Find(struct SplayTreeNode** root, int key);
struct SplayTreeNode* Search(struct SplayTreeNode* node, int key);

struct SplayTreeNode* Grandpa(struct SplayTreeNode* node);

void Clear(struct SplayTreeNode* node);

void SplayTreeDump(struct SplayTreeNode* node, const char* file);
void SplayNodeDump(struct SplayTreeNode* node, FILE *fp);

#endif //SPLAY_H
