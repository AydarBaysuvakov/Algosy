#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Splay.h"

void Add(struct SplayTreeNode** root, int key)
    {
    struct SplayTreeNode *tree1, *tree2;
    Split(root, key, &tree1, &tree2);

    struct SplayTreeNode *node = (struct SplayTreeNode*) calloc(1, sizeof(struct SplayTreeNode));
    node->key = key;
    node->left  = tree1;
    node->right = tree2;
    node->parent = NULL;

    if (tree1) tree1->parent = node;
    if (tree2) tree2->parent = node;
    *root = node;
    }

void Remove(struct SplayTreeNode** root, int key)
    {
    struct SplayTreeNode* x = Find(root, key);
    if (!x) return;
    *root = Merge(x->left, x->right);
    free(x);
    }

void Splay(struct SplayTreeNode* node, struct SplayTreeNode** root)
    {
    while (node != *root)
        {
        if (node == node->parent->left)
            {
            if (!Grandpa(node))
                RightRotate(node->parent, root);
            else if (node->parent == Grandpa(node)->left)
                {
                RightRotate(Grandpa(node), root);
                RightRotate(node->parent, root);
                }
            else
                {
                RightRotate(node->parent, root);
                LeftRotate(node->parent, root);
                }
            }
        else
            {
            if (!Grandpa(node))
                LeftRotate(node->parent, root);
            else if (node->parent == Grandpa(node)->right)
                {
                LeftRotate(Grandpa(node), root);
                LeftRotate(node->parent, root);
                }
            else
                {
                LeftRotate(node->parent, root);
                RightRotate(node->parent, root);
                }
            }
        }
    }

void LeftRotate(struct SplayTreeNode* node, struct SplayTreeNode** root)
    {
    struct SplayTreeNode* parent = node->parent;
    struct SplayTreeNode* right  = node->right;
    struct SplayTreeNode* t2     = right->left;

    if (parent)
        {
        if (parent->left == node)
            parent->left = right;
        else
            parent->right = right;
        }
    else
        *root = right;

    right->left   = node;
    node->right   = t2;
    node->parent  = right;
    right->parent = parent;

    if (node->right)
        node->right->parent = node;
    }

void RightRotate(struct SplayTreeNode* node, struct SplayTreeNode** root)
    {
    struct SplayTreeNode* parent = node->parent;
    struct SplayTreeNode* left   = node->left;
    struct SplayTreeNode* t2     = left->right;

    if (parent)
        {
        if (parent->left == node)
            parent->left = left;
        else
            parent->right = left;
        }
    else
        *root = left;

    left->right   = node;
    node->left    = t2;
    node->parent  = left;
    left->parent  = parent;

    if (node->left)
        node->left->parent = node;
    }

struct SplayTreeNode* Merge(struct SplayTreeNode* tree1, struct SplayTreeNode* tree2)
    {
    struct SplayTreeNode* max = MaxElem(tree1);
    Splay(max, &tree1);
    tree1->right = tree2;
    tree2->parent = tree1;
    return tree1;
    }

void Split(struct SplayTreeNode** root, int key, struct SplayTreeNode** tree1, struct SplayTreeNode** tree2)
    {
    if (!(*root))
        return;
    else if (!(*root)->left && !(*root)->right)
        {
        *tree2 = NULL;
        *tree1 = *root;
        return;
        }
    else
        {
        if (MaxElem(*root)->key < key)
            {
            Splay(MaxElem(*root), root);
            *tree2 = NULL;
            *tree1 = *root;
            return;
            }
        else if (MinElem(*root)->key > key)
            {
            Splay(MinElem(*root), root);
            *tree1 = NULL;
            *tree2 = *root;
            return;
            }
        struct SplayTreeNode* node = Find(root, key);
        while (!node)
            {
            key += 1;
            node = Find(root, key);
            }
        *tree1 = (*root)->left;
        (*tree1)->parent = NULL;
        *tree2 = *root;
        (*tree2)->left = NULL;
        }
    }

struct SplayTreeNode* MaxElem(struct SplayTreeNode* node)
    {
    while (node->right) node = node->right;
    return node;
    }

struct SplayTreeNode* MinElem(struct SplayTreeNode* node)
    {
    while (node->left) node = node->left;
    return node;
    }

struct SplayTreeNode* Find(struct SplayTreeNode** root, int key)
    {
    struct SplayTreeNode* node = Search(*root, key);
    if (!node) return NULL;
    Splay(node, root);
    return *root;
    }

struct SplayTreeNode* Search(struct SplayTreeNode* node, int key)
    {
    if (!node)            return NULL;
    if (node->key == key) return node;
    if (node->key >  key) return Search(node->left,  key);
    if (node->key <  key) return Search(node->right, key);
    }

struct SplayTreeNode* Grandpa(struct SplayTreeNode* node)
    {
    struct SplayTreeNode* parent = node->parent;
    if (parent && parent->parent)
        return parent->parent;
    return NULL;
    }

void Clear(struct SplayTreeNode* node)
    {
    if (!node) return;
    if (node->left)  Clear(node->left);
    if (node->right) Clear(node->right);
    free(node);
    }

void SplayTreeDump(struct SplayTreeNode* node, const char* file)
    {
    assert(node != NULL);
    assert(file != NULL);

    FILE *fp = fopen(file, "w");

    fprintf(fp,                 "digraph MyTree\n{\n"
                                "\tbgcolor = darkgreen;\n"
                                "\tgraph [splines = splines];\n"
                                "\tnode  [width = 2, style = filled, color = wheat];\n"
                                "\tedge  [color = darkgreen, fontsize = 15];\n\n"
                                "\tsubgraph cluster0\n    {\n"
                                "\t\tbgcolor = yellowgreen;"
                                "\t\theight  = 20"
                                "\t\tstyle   = filled;\n");

    SplayNodeDump(node, fp);

    fprintf(fp, "\t}\n}\n");
    fclose(fp);
    }

void SplayNodeDump(struct SplayTreeNode* node, FILE *fp)
    {
    fprintf(fp,  "\t\t%ld [shape=oval, height = 1, label = \"%d\"];\n", node, node->key);

    if (node->left)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node->left);
        SplayNodeDump(node->left, fp);
        }

    if (node->right)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = cyan];\n", node, node->right);
        SplayNodeDump(node->right, fp);
        }
    }
