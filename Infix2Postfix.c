
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include "calc.h"


/* ------- traverse_expr -------- */
void traverse_expr(NUM l){
    node *p;
    p = l;

    while(p){
        if(p->data == '.'-'0')
            printf(".");
        else if(p->data == '+'-'0')
            printf("+");
        else if(p->data == '-'-'0')
            printf("-");
        else if(p->data == '*'-'0')
            printf("*");
        else if(p->data == -1)
            printf("-");
        else if(p->data == '/'-'0')
            printf("/");
        else if(p->data == '('-'0')
            printf("(");
        else if(p->data == ')'-'0')
            printf(")");
        else if(p->data == '>'-'0')
            printf(">");
        else if(p->data == '<'-'0')
            printf("<");
        else if(p->data == -100)
            printf("==");
        else if(p->data == -200)
            printf("%c", '%');
        else if(p->data == -300)
            printf("^");
        else if(p->data == -400)
            printf(">=");
        else if(p->data == -500)
            printf("<=");
        else if(p->data == -600)
            printf("!=");
        else if(p->data == -700)
            printf("&&");
        else if(p->data == -800)
            printf("||");
        else if(p->data == ' '-'0')
            printf(" ");
        else if(p->data == '\n'-'0'  ||  p->data == '#'-'0')
            break;
        else
            printf("%d", p->data);
        p = p->next;
        if(p == l)
            break;
    }
    printf("\n");
    return;
}



/* ------- pop --------- */
int pop(NUM *l){
    if(*l == NULL) return INT_MIN;
    node *p = *l;
    int ele;
    ele = p->data;
    if(p->prev == p){
        *l = NULL;
        free(p);
        return ele;
    }
    node *last = p->prev;
    ele = last->data;
    p->prev = last->prev;
    last->prev->next = p;
    free(last);
    return ele;
}


void push_list(NUM *soln, NUM *l){
    node *p = *l;
    while(1){
        append(soln, p->data);
        if(p->next == *l)
            break;
        p = p->next;
    }
    destroy(l);
    p = NULL;

    return;
}

/* ------- peek --------- */
int peek(NUM l){
    int ele = INT_MIN;
    if(l == NULL)
        return ele;
    ele = l->prev->data;
    return ele;
}


/* --------- isdigit -------- */
int isDigit(int d){
    if(d == 1 || d == 2 || d == 3 || d == 4 || d == 5 || d == 6 || d == 7 || d == 8 || d == 9 || d == 0 || d == -2)
        return 1;
    else
        return 0;
}

/* ------ isOpr ------- */
int isOpr(int d){
    if(d == '+'-'0' || d == '-'-'0' || d == '*'-'0' || d == '/'-'0')
        return 1;
    else
        return 0;
}
