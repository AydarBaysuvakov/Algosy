#ifndef AVL_H
#define AVL_H

struct AvlTreeNode
    {
    int key;
    int height;
    struct AvlTreeNode* left;
    struct AvlTreeNode* right;
    };

void RightRotate(struct AvlTreeNode** node);
void LeftRotate(struct AvlTreeNode** node);

void Insert(struct AvlTreeNode** node, int key);
void Delete(struct AvlTreeNode** root, int key);
void Clear(struct AvlTreeNode* node);
struct AvlTreeNode* Find(struct AvlTreeNode* node, int key);

int max(int a, int b);
int Height(struct AvlTreeNode* node);
int Balance(struct AvlTreeNode* node);

struct AvlTreeNode* minValueNode(struct AvlTreeNode* node);

void AvlTreeDump(struct AvlTreeNode* node, const char* file);
void AvlNodeDump(struct AvlTreeNode* node, FILE *fp);

#endif //AVL_H
