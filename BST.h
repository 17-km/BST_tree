#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

// wezel drzewa
struct node
{
    // wartosc wezla
    int key;
    // wskazniki do lewego i prawego dziecka
    struct node *left, *right;
};

struct node *createNode(int number);

void display(struct node *parentNode, int level);

struct node *insertNode(struct node *parentNode, int number);

char isNodeInTree(struct node *parentNode, int number);

struct node *minimumNode(struct node *parentNode);

struct node *maximumNode(struct node *parentNode);

void minimumValue(struct node *parentNode);

void maximumValue(struct node *parentNode);

struct node *deleteNode(struct node *parentNode, int number, char side);

struct node *deleteLowerThan(struct node *parentNode, int number);

struct node *deleteHigherThan(struct node *parentNode, int number);

#endif // BST_H


