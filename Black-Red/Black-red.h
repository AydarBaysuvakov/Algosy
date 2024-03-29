#ifndef BR_H
#define BR_H

typedef enum { RED, BLACK } Color;

struct BRTreeNode {
    int key;
    Color color;
    struct BRTreeNode* left;
    struct BRTreeNode* right;
    struct BRTreeNode* parent;
};


void Insert(struct BRTreeNode** root, int key);
struct BRTreeNode** NewNode(struct BRTreeNode** node, int key);
void Balance(struct BRTreeNode** node, struct BRTreeNode** root);

void LeftRotate(struct BRTreeNode** node, struct BRTreeNode** root);
void RightRotate(struct BRTreeNode** node, struct BRTreeNode** root);

struct BRTreeNode* Find(struct BRTreeNode* node, int key);
void Clear(struct BRTreeNode* node);

void Delete(struct BRTreeNode** root, int key);
void Delete1(struct BRTreeNode** Node, struct BRTreeNode** root);
struct BRTreeNode* minValueNode(struct BRTreeNode* node);

struct BRTreeNode* Grandpa(struct BRTreeNode* node);
struct BRTreeNode* Uncle(struct BRTreeNode* node);
struct BRTreeNode* Sibling(struct BRTreeNode* node);

void BRTreeDump(struct BRTreeNode* node, const char* file);
void BRNodeDump(struct BRTreeNode* node, FILE *fp);
#endif //BR_H
