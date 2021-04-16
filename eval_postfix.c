/*
*     Author : Tushar Chakradhar Pathade    
*     Source : https://github.com/pathadeTush
*/



#include "eval_postfix.h"


extern int z;
// The evaluatePostfix function takes  postfix expression from main function.
// And handels the token and evaluate it.
void evaluatePostfix(NUM *post){
    NUM soln;
    init(&soln);
    node *p = *post;

    while(p->data != '#'-'0'){ // 35 = '#' EOL (Assumed)
        if(isDigit(p->data)){
            append(&soln, p->data);
        }
        else if(p->data == ' '-'0')
            append(&soln, p->data);
        else{
            NUM num1, num2;
            init(&num1);
            init(&num2);
            init_num(&soln, &num1);
            init_num(&soln, &num2);

            if(z == -4 && p->data == '+'-'0'){
                p->data = '-'-'0';
                z = -2;
            }
            if(z == -4 && p->data == '-'-'0'){
                p->data = '+'-'0';
                z = -4;
            }
            switch (p->data){
                case '+'-'0':{
                    NUM res = Add(&num1, &num2);
                    push_list(&soln, &res);
                    break;

                }
                case '-'-'0':{
                    NUM res = NULL;
                    if(z == -2)
                        res = Subtract(&num1, &num2);
                    else
                        res = Subtract(&num2, &num1);
                    if((res)->data == -1){
                        pop_first(&res);
                        z = -4;
                    }
                    else
                        z = 0;
                    push_list(&soln, &res);
                    break;

                }
                case '*'-'0':{
                    NUM res = Mult(&num1, &num2);
                    push_list(&soln, &res);
                    break;

                }
                case '/'-'0':{
                    if(isZero(num1)){
                        printf("Error : DivideByZeroError\n");
                        printf("Can't divide by 0\n");
                        return;
                    }
                    NUM res = Div(&num2, &num1);
                    push_list(&soln, &res);
                    break;
                }
                case '>'-'0':{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == -2) printf("1");
                    else printf("0");
                    return;

                }
                case '<'-'0':{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == -1) printf("1");
                    else printf("0");
                    return;

                }
                case -100:{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == 0) printf("1");
                    else printf("0");
                    return;

                }
                case -200:{
                    NUM res = Modulo(&num2, &num1);
                    push_list(&soln, &res);
                    break;

                }
                case -300:{
                    eq_num(&num1, &num2);
                    NUM res = Power(&num2, &num1);
                    push_list(&soln, &res);
                    break;

                }
                case -400:{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == -1) printf("0");
                    else printf("1");
                    return;

                }
                case -500:{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == -2) printf("0");
                    else printf("1");
                    return;

                }
                case -600:{
                    eq_num(&num1, &num2);
                    int y = greator(num1, num2);
                    if(y == 0) printf("0");
                    else printf("1");
                    return;

                }
                case -700:{
                    eq_num(&num1, &num2);
                    if(isZero(num1) || isZero(num2)) printf("0");
                    else printf("1");
                    return;

                }
                case -800:{
                    eq_num(&num1, &num2);
                    if(isZero(num1) && isZero(num2)) printf("0");
                    else printf("1");
                    return;

                }
            }
        }
        p = p->next;
    }
    if(z)
        insert_At(&soln, 1, -1);
    printf("\nOutput : ");
    traverse_expr(soln);
}




/* -------- init_num ----------- */
void init_num(NUM *soln, NUM *l){
    pop_last(soln);
    node *p = *soln;
    p = p->prev;

    while(p->data != ' '-'0'){
        append(l, p->data);
        if(p->prev == p){
            *soln = NULL;
            break;
        }

        p->next->prev = p->prev;
        p->prev->next = p->next;
        node *q = p;

        p = p->prev;
        free(q);
    }
    reverse(l);

    return;
}


