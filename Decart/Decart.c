#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Decart.h"

void Insert(struct DTreeNode** root, struct Node elem)
    {
    struct DTreeNode* node = (struct DTreeNode*) calloc(1, sizeof(struct DTreeNode));
    node->key = elem.key;
    node->priority = elem.priority;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    struct DTreeNode *t1, *t2;
    Split(*root, elem.key, &t1, &t2);
    *root = Merge(Merge(t1, node), t2);
    }

void Remove(struct DTreeNode** root, int key)
    {
    struct DTreeNode *t1, *t2, *x;
    Split(*root, key, &t1, &t2);

    if (!t2) return;

    x = t2;
    while (x->left) x = x->left;
    if (x->parent) x->parent->left = x->right;
    else t2 = x->right;
    if (x->right) x->right->parent = x->parent;

    free(x);
    *root = Merge(t1, t2);
    }

struct DTreeNode* BuildTree(struct Node* array, int size)
    {
    qsort(array, size, sizeof(struct Node), Compare);

    if (size == 0) return NULL;

    struct DTreeNode* root = (struct DTreeNode*) calloc(1, sizeof(struct DTreeNode));
    root->key = array->key;
    root->priority = array->priority;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;

    struct DTreeNode* last = root;

    for (int i = 1; i < size; ++i)
        {
        struct DTreeNode* node = (struct DTreeNode*) calloc(1, sizeof(struct DTreeNode));
        node->key = array[i].key;
        node->priority = array[i].priority;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;

        if (node->priority < last->priority)
            {
            last->right = node;
            node->parent = last;
            }
        else
            {
            while (last && last->priority < node->priority) last = last->parent;
            if (last)
                {
                node->left = last->right;
                node->parent = last;
                if (last->right) last->right->parent = node;
                last->right = node;
                }
            else
                {
                node->left = root;
                node->parent = NULL;
                root->parent = node;
                root = node;
                }
            }
        last = node;
        }

    return root;
    }

void Split(struct DTreeNode* root, int key, struct DTreeNode** tree1, struct DTreeNode** tree2)
    {
    if (!root)
        {
        *tree1 = NULL;
        *tree2 = NULL;
        return;
        }
    if (key > root->key)
        {
        struct DTreeNode *t1, *t2;
        Split(root->right, key, &t1, &t2);

        if (t1) t1->parent = root;
        *tree1 = root;
        (*tree1)->right = t1;

        if (t2) t2->parent = NULL;
        *tree2 = t2;
        }
    else
        {
        struct DTreeNode *t1, *t2;
        Split(root->left, key, &t1, &t2);

        if (t2) t2->parent = root;
        *tree2 = root;
        (*tree2)->left = t2;

        if (t1) t1->parent = NULL;
        *tree1 = t1;
        }
    }

struct DTreeNode* Merge(struct DTreeNode* tree1, struct DTreeNode* tree2)
    {
    if (!tree1) return tree2;
    if (!tree2) return tree1;
    if (tree1->priority > tree2->priority)
        {
        tree1->right = Merge(tree1->right, tree2);
        if (tree1->right) tree1->right->parent = tree1;
        return tree1;
        }
    else
        {
        tree2->left = Merge(tree2->left, tree1);
        if (tree2->left) tree2->left->parent = tree2;
        return tree2;
        }
    return NULL;
    }

struct DTreeNode* Find(struct DTreeNode* node, int key)
    {
    if (!node)            return NULL;
    if (node->key == key) return node;
    if (node->key >  key) return Find(node->left,  key);
    if (node->key <  key) return Find(node->right, key);
    }

void Clear(struct DTreeNode* node)
    {
    if (!node) return;
    if (node->left)  Clear(node->left);
    if (node->right) Clear(node->right);
    free(node);
    }

int Compare(const void* a, const void* b)
    {
    struct Node arg1 = *(struct Node*)a;
    struct Node arg2 = *(struct Node*)b;
    return arg1.key - arg2.key;
    }

void DTreeDump(struct DTreeNode* node, const char* file)
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

    DNodeDump(node, fp);

    fprintf(fp, "\t}\n}\n");
    fclose(fp);
    }

void DNodeDump(struct DTreeNode* node, FILE *fp)
    {
    fprintf(fp,  "\t\t%ld [shape=oval, height = 1, label = \"%d, %d\"];\n", node, node->key, node->priority);

    if (node->left)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node->left);
        DNodeDump(node->left, fp);
        }

    if (node->right)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = cyan];\n", node, node->right);
        DNodeDump(node->right, fp);
        }
    }
