/*
*     Author : Tushar Chakradhar Pathade    
*     Source : https://github.com/pathadeTush
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int data;
    struct node *next, *prev;
} node;

typedef node *NUM;

void init(NUM *l);

void append(NUM *l, int d);

void traverse(NUM l);

int search(NUM l, int num);

void insert_At(NUM *l, int posn, int num);

void Remove(NUM *l, int num);

void pop_last(NUM *l);

void pop_first(NUM *l);

void reverse(NUM *l);

void destroy(NUM *l);