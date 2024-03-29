#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AVL.h"

void Insert(struct AvlTreeNode** node, int key)
    {
    // Непосредственно вставка нового узла
    if (*node == NULL)
        {
        *node = (struct AvlTreeNode*) calloc(1, sizeof(struct AvlTreeNode));
        (*node)->key = key;
        (*node)->height = 1;
        (*node)->left  = NULL;
        (*node)->right = NULL;
        return;
        }
    else if (key  > (*node)->key)
        {
        Insert(&((*node)->right), key);
        }
    else if (key  < (*node)->key)
        {
        Insert(&((*node)->left), key);
        }
    else if (key == (*node)->key)
        {
        printf("Key already in tree: %d\n", key);
        return;
        }

    // Балансировка
    (*node)->height = max(Height((*node)->left), Height((*node)->right)) + 1;
    int balance = Balance(*node);

    if (balance > 1 && key < (*node)->left->key)
        RightRotate(node);
    if (balance < -1 && key > (*node)->right->key)
        LeftRotate(node);
    if (balance > 1 && key > (*node)->left->key)
        {
        LeftRotate(&((*node)->left));
        RightRotate(node);
        }
    if (balance < -1 && key < (*node)->right->key)
        {
        RightRotate(&((*node)->right));
        LeftRotate(node);
        }
    }

void RightRotate(struct AvlTreeNode** node)
    {
    assert(node != NULL);

    struct AvlTreeNode *root = (*node)->left;
    struct AvlTreeNode *T2   = root->right;

    root->right    = *node;
    (*node)->left  = T2;

    (*node)->height = max(Height((*node)->left), Height((*node)->right)) + 1;
    root->height    = max(Height(root->left), Height(root->right)) + 1;

    *node = root;
    }

void LeftRotate(struct AvlTreeNode** node)
    {
    assert(node != NULL);

    struct AvlTreeNode *root = (*node)->right;
    struct AvlTreeNode *T2   = root->left;

    root->left  = *node;
    (*node)->right = T2;

    (*node)->height = max(Height((*node)->left), Height((*node)->right)) + 1;
    root->height = max(Height(root->left), Height(root->right)) + 1;

    *node = root;
    }

void Delete(struct AvlTreeNode** root, int key)
    {
    if (*root == NULL)
        return;

    if (key < (*root)->key)
        Delete(&((*root)->left), key);
    else if (key > (*root)->key)
        Delete(&((*root)->right), key);
    else
        {
        if ((*root)->left && (*root)->right)
            {
            struct AvlTreeNode* temp = minValueNode((*root)->right);
            (*root)->key = temp->key;
            Delete(&((*root)->right), temp->key);
            }
        else if (!((*root)->left || (*root)->right))
            {
            free(*root);
            *root = NULL;
            return;
            }
        else
            {
            *root = (*root)->left ? (*root)->left : (*root)->right;
            }
        }

    if (*root == NULL)
        return;

    (*root)->height = max(Height((*root)->left), Height((*root)->right)) + 1;
    int balance = Balance(*root);

    if (balance > 1 && Balance((*root)->left) >= 0)
        RightRotate(root);
    if (balance > 1 && Balance((*root)->left) < 0)
        {
        LeftRotate(&((*root)->left));
        RightRotate(root);
        }
    if (balance < -1 && Balance((*root)->right) <= 0)
    {
        LeftRotate(root);
    }
    if (balance < -1 && Balance((*root)->right) > 0)
        {
        RightRotate(&((*root)->right));
        LeftRotate(root);
        }
    }

void Clear(struct AvlTreeNode* node)
    {
    if (!node) return;
    if (node->left)  Clear(node->left);
    if (node->right) Clear(node->right);
    free(node);
    }


struct AvlTreeNode* Find(struct AvlTreeNode* node, int key)
    {
    if (!node)            return NULL;
    if (node->key == key) return node;
    if (node->key >  key) return Find(node->left,  key);
    if (node->key <  key) return Find(node->right, key);
    }

int max(int a, int b) {
    return (a > b) ? a : b;
}

int Height(struct AvlTreeNode* node) {
    if (!node)
        return 0;
    return node->height;
}

int Balance(struct AvlTreeNode* node) {
    if (!node)
        return 0;
    return Height(node->left) - Height(node->right);
}

struct AvlTreeNode* minValueNode(struct AvlTreeNode* node) {
    while (node->left)
        node = node->left;

    return node;
}

void AvlTreeDump(struct AvlTreeNode* node, const char* file)
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

    AvlNodeDump(node, fp);

    fprintf(fp, "\t}\n}\n");
    fclose(fp);
    }

void AvlNodeDump(struct AvlTreeNode* node, FILE *fp)
    {
    fprintf(fp,  "\t\t%ld [shape=oval, height = 1, label = \"%d\"];\n", node, node->key);

    if (node->left)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node->left);
        AvlNodeDump(node->left, fp);
        }

    if (node->right)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = cyan];\n", node, node->right);
        AvlNodeDump(node->right, fp);
        }
    }
