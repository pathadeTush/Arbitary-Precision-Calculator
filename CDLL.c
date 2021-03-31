#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "calc.h"



void init(NUM *l){
    *l = NULL;
    return;
}


void append(NUM *l, int d){
    node* nn = (node *)malloc(sizeof(node));
    if(nn){
    nn->data = d;
    nn->next = nn;
    nn->prev = nn;
    }
    else
        return;
    if(*l == NULL){
        *l = nn;
        return;
    }
    node *first, *last;
    first = *l;
    last = first->prev;
    first->prev = nn;
    last->next = nn;
    nn->next = first;
    nn->prev = last;
    return;
}

void traverse(NUM l){
    printf("[ ");
    node *p;
    p = l;
    while(p){
        if(p->data == -2)
            printf(". ");
        else
            printf("%d ", p->data);
        p = p->next;
        if(p == l)
            break;
    }
    printf("]\n");
    return;
}


/* -------- search ---------- */
int search(NUM l, int num){
    node *p;
    p = l;
    while(p){
        if(p->data == num)
            return 1;
        if(p->next == l)
            break;
        p = p->next;
    }
    return 0;
}


/* ---------- isert_At --------- */
void insert_At(NUM *l, int posn, int num){
    int i = 1;
    node *p = NULL, *newnode;
    newnode = (node *)malloc(sizeof(node));
    if(newnode){
        newnode->data = num;
        newnode->prev = newnode;
        newnode->next = newnode;
    }
    else return;
    p = *l;
    while(1){
        if(i == posn && p == *l){  // First node
            *l = newnode;
            newnode->next = p;
            newnode->prev = p->prev;
            p->prev->next = newnode;
            p->prev = newnode;
            return;
        }
        else if(i == posn){  // intermediate node
            newnode->prev = p->prev;
            newnode->next = p;
            p->prev->next = newnode;
            p->prev = newnode;
            return;
        }
        i++;
        p = p->next;
    }
}



/* ------- Remove --------- */    /* remove is keyword */
void Remove(NUM *l, int num){
    node *p;
    p = *l;
    while(p){
     if(p->prev == p && p->data == num){  // only one node
        free(p);
        *l = NULL;
        return;
     }
     else if(p->data == num){
        if(p == *l)
            *l = p->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        free(p);
        return;
     }
     if(p->next == *l)
        break;
     p = p->next;
    }
    return;
}


/* ------- pop_last --------- */
void pop_last(NUM *l){
    if(*l == NULL) return;
    node *p = *l;
    if(p->prev == p){
        *l = NULL;
        free(p);
        return;
    }
    node *last = p->prev;
    p->prev = last->prev;
    last->prev->next = p;
    free(last);
    return;
}


/* ------- pop_first --------- */
void pop_first(NUM *l){
    if(*l == NULL) return;
    node *p = *l;
    if(p->prev == p){
        *l = NULL;
        free(p);
        return;
    }
    p->next->prev = p->prev;
    p->prev->next = p->next;
    *l = p->next;
    free(p);
    return;
}



/* -------- reverse -------- */
void reverse(NUM *l){    // here l is used for pointing to the nodes (like head pointer)
    node *p = *l, *first;
    first = p;
    *l = NULL;
    while(p){
        p = p->prev;
        append(l, p->data);
        if(p == first)
            break;
    }
    return;
}

/* ------- deleting whole list (not done) -------- */

void destroy(NUM *l){
    node *p = *l;
    *l = NULL;
    while(p){
        if(p->prev == p)
            break;
        node *q = p;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p = p->next;
        free(q);
    }
    free(p);
    return;
}

