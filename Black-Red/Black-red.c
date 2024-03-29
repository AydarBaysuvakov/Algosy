#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Black-red.h"

void Insert(struct BRTreeNode** root, int key)
    {
    struct BRTreeNode** node = NewNode(root, key);
    if (node) Balance(node, root);
    }

struct BRTreeNode** NewNode(struct BRTreeNode** node, int key)
    {
    if (*node == NULL)
        {
        *node = (struct BRTreeNode*) calloc(1, sizeof(struct BRTreeNode));
        (*node)->key = key;
        (*node)->color = RED;
        (*node)->left  = NULL;
        (*node)->right = NULL;
        (*node)->parent = NULL;
        return node;
        }
    else if (key  > (*node)->key)
        {
        struct BRTreeNode** tmp = NewNode(&((*node)->right), key);
        (*node)->right->parent = *node;
        return tmp;
        }
    else if (key  < (*node)->key)
        {
        struct BRTreeNode** tmp = NewNode(&((*node)->left), key);
        (*node)->left->parent = *node;
        return tmp;
        }
    else if (key == (*node)->key)
        {
        printf("Key already in tree: %d\n", key);
        return NULL;
        }
    }


void Balance(struct BRTreeNode** node, struct BRTreeNode** root)
    {
    struct BRTreeNode* parent = (*node)->parent;
    struct BRTreeNode* uncle = Uncle(*node);
    struct BRTreeNode* grandpa = Grandpa(*node);
    struct BRTreeNode* tmp = *node;

    // Корень
    if (*node == *root)
        {
        (*node)->color = BLACK;
        return;
        }
    // Черный отец
    else if ((*node)->parent->color == BLACK)
        return;
    // Красные отец и дядя
    else if (uncle && uncle->color == RED)
        {
        (*node)->parent->color = BLACK;
        uncle->color = BLACK;
        grandpa->color = RED;
        Balance(&grandpa, root);
        return;
        }
    // Красный отец и черный дядя
    if (parent->right == *node && parent == grandpa->left)
        {
        tmp = parent;
        LeftRotate(&parent, root);
        }
    else if (parent->left == *node && parent == grandpa->right)
        {
        tmp = parent;
        RightRotate(&parent, root);
        }

    grandpa = Grandpa(tmp);
    parent  = tmp->parent;
    parent->color = BLACK;
    grandpa->color = RED;

    if (tmp == parent->left)
        RightRotate(&grandpa, root);
    else
        LeftRotate(&grandpa, root);
    }

void LeftRotate(struct BRTreeNode** node, struct BRTreeNode** root)
    {
    struct BRTreeNode* right = (*node)->right;

    if (*node == *root)
        *root = right;

    right->parent = (*node)->parent;
    (*node)->parent = right;
    if (right->left)
        right->left->parent = *node;

    (*node)->right = right->left;
    right->left = *node;
    if (right->parent)
        if (right->parent->left == *node)
            right->parent->left = right;
        else
            right->parent->right = right;
    *node = right;
    }

void RightRotate(struct BRTreeNode** node, struct BRTreeNode** root)
    {
    struct BRTreeNode* left = (*node)->left;

    if (*node == *root)
        *root = left;

    left->parent = (*node)->parent;
    (*node)->parent = left;
    if (left->right)
        left->right->parent = *node;

    (*node)->left = left->right;
    left->right = *node;
    if (left->parent)
        if (left->parent->right == *node)
            left->parent->right = left;
        else
            left->parent->left = left;
    *node = left;
    }

void Delete(struct BRTreeNode** root, int key)
    {
    struct BRTreeNode* node = *root ? Find(*root, key) : NULL;

    if (!node) {
        return;
    }

    // Корень
    if (!node->parent && !node->left && !node->right) {
        free(*root);
        *root = NULL;
        return;
    }

    // Отец двух детей
    if (node->left && node->right)  {
        struct BRTreeNode* removed = minValueNode(node);
        node->key = removed->key;
        node = removed;
    }

    struct BRTreeNode* child = node->left ? node->left : node->right;
    if (!child)
        {
        if (node->color == BLACK)
            {
            Delete1(&node, root);
            }

        struct BRTreeNode* parent = node->parent;

        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
        }
    else
        {
        struct BRTreeNode* parent = node->parent;
        child->parent = parent;

        if (parent)
            {
            if (node == parent->left)
                parent->left = child;
            else
                parent->right = child;
            }
        else
            *root = child;

        if (node->color == BLACK)
            {
            if (child->color == RED)
                child->color = BLACK;
            else
                Delete1(&child, root);
            }
        }
    }

void Delete1(struct BRTreeNode** Node, struct BRTreeNode** root)
    {
    if ((*Node)->parent)
        {
        struct BRTreeNode* node = *Node;
        struct BRTreeNode* sibling = Sibling(node);
        struct BRTreeNode* parent = node->parent;
        Color sbcol = sibling ? sibling->color : BLACK;

        if (sbcol == RED)
            {
            parent->color = RED;
            sibling->color = BLACK;

            if (node == parent->left)
                LeftRotate(&parent, root);
            else
                RightRotate(&parent, root);
            }

        sibling = Sibling(node);
        parent = node->parent;
        sbcol = sibling ? sibling->color : BLACK;
        Color slcol = sibling && sibling->left ? sibling->left->color : BLACK;
        Color srcol = sibling && sibling->right ? sibling->right->color : BLACK;

        if (sbcol == BLACK && slcol == BLACK && srcol == BLACK)
            {
            if (parent->color == BLACK)
                {
                if (sibling) sibling->color = RED;
                Delete1(&parent, root);
                }
            else if (parent->color == RED)
                {
                if (sibling) sibling->color = RED;
                parent->color = BLACK;
                }
            }
        else
            {
            if (sbcol == BLACK)
                {
                if (node == parent->left && srcol == BLACK && slcol == RED)
                    {
                    sibling->color = RED;
                    sibling->left->color = BLACK;
                    RightRotate(&sibling, root);
                    }
                else if (node == parent->right && slcol == BLACK && srcol == RED)
                    {
                    sibling->color = RED;
                    sibling->right->color = BLACK;
                    LeftRotate(&sibling, root);
                    }
                }

            sibling = Sibling(node);
            parent = node->parent;
            sibling->color = parent->color;
            parent->color = BLACK;

            if (node == parent->left)
                {
                if (sibling->right)
                    sibling->right->color = BLACK;
                LeftRotate(&parent, root);
                }
            else
                {
                if (sibling->left)
                    sibling->left->color = BLACK;
                RightRotate(&parent, root);
                }
            }
        }
    }


struct BRTreeNode* Find(struct BRTreeNode* node, int key)
    {
    if (!node)            return NULL;
    if (node->key == key) return node;
    if (node->key >  key) return Find(node->left,  key);
    if (node->key <  key) return Find(node->right, key);
    }

void Clear(struct BRTreeNode* node)
    {
    if (!node) return;
    if (node->left)  Clear(node->left);
    if (node->right) Clear(node->right);
    free(node);
    }

struct BRTreeNode* minValueNode(struct BRTreeNode* node) {
    while (node->left)
        node = node->left;

    return node;
}


struct BRTreeNode* Grandpa(struct BRTreeNode* node)
    {
    struct BRTreeNode* parent = node->parent;
    if (parent && parent->parent)
        return parent->parent;
    return NULL;
    }

struct BRTreeNode* Uncle(struct BRTreeNode* node)
    {
    struct BRTreeNode* grandpa = Grandpa(node);
    if (grandpa)
        {
        if (grandpa->left == node->parent)
            return grandpa->right;
        return grandpa->left;
        }
    return NULL;
    }

struct BRTreeNode* Sibling(struct BRTreeNode* node)
    {
    if (!node->parent) {
        return NULL;
    }

    struct BRTreeNode* parent = node->parent;
    if (node == parent->left)
        return parent->right;
    else
        return parent->left;
    }

void BRTreeDump(struct BRTreeNode* node, const char* file)
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

    BRNodeDump(node, fp);
    //fprintf(fp,  "\t\t0 [shape=oval, color=black, height = 1, fontcolor=white, label = \"NULL\"];\n");

    fprintf(fp, "\t}\n}\n");
    fclose(fp);
    }

void BRNodeDump(struct BRTreeNode* node, FILE *fp)
    {
    if (node->color == RED)
        fprintf(fp,  "\t\t%ld [shape=oval, color=red, height = 1, label = \"%d\"];\n", node, node->key);
    if (node->color == BLACK)
        fprintf(fp,  "\t\t%ld [shape=oval, color=black, height = 1, fontcolor=white, label = \"%d\"];\n", node, node->key);

    if (node->left)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node->left);
        BRNodeDump(node->left, fp);
        }
    //else
        //{
        //fprintf(fp,  "\t\t%ld [shape=oval, color=black, height = 1, fontcolor=white, label = \"NULL\"];\n", node+1);
        //fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node+1);
        //}

    if (node->right)
        {
        fprintf(fp, "\t\t%ld -> %ld [color = cyan];\n", node, node->right);
        BRNodeDump(node->right, fp);
        }
    //else
      //  {
        //fprintf(fp,  "\t\t%ld [shape=oval, color=black, height = 1, fontcolor=white, label = \"NULL\"];\n", node + 2);
        //fprintf(fp, "\t\t%ld -> %ld [color = red];\n", node, node+2);
        //}
    }
