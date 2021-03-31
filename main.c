/*
    Name  : Tushar Chakradhar Pathade
    MIS   : 111903114
    Batch : S2
    Div   : 2
*/

#include<stdio.h>
#include<ctype.h>
#include "calc.h"

int z;
int precedence(int c){
    if(c == '+'-'0')
        return 10;
    else if(c == '-'-'0')
        return 10;
    else if(c == '*'-'0')
        return 20;
    else if(c == '/'-'0')
        return 20;
    else if(c == '%'-'0')
        return 20;
    else if(c == '^'-'0')
        return 30;
    else if(c == '('-'0')
        return 5;
    return 0;
}


int main() {
    NUM in, post, s;
    init(&in);
    init(&post);
    init(&s);
    int num1, x;

    printf("Enter a expression : ");
    while(1){
        num1 = fgetc(stdin);
        append(&in, num1-'0');
        if(num1 == '\n')
            break;
    }

   // traverse(in);
    // handling of '+' sign if it is there at the start of the input.
    if(in->data == '+'-'0')
        in = in->next;

    // handling of '-' sign if it is there at the start of the input.
    if(in->data == '-'-'0'){
        in = in->next;
        z = -4;
    }

    // handling of initial spaces before sign or digit.
    while(in->data == ' '- '0')
        in = in->next;


    if(in->data == 'o'-'0'){
        int t;
        if(in->next->data == 'b'-'0') in = in->next;
        else {printf("BadInputError : 'b' is expected after 'o' in line 1\n"); return 0;}

        if(in->next->data == '='-'0') in = in->next;
        else {printf("SyntaxError : '=' operator is  expected after 'b' in line 1\n"); return 0;}

        if(in->next->data == 2) {in = in->next; t = 2;}
        else if(in->next->data == 8) {in = in->next; t= 8;}
        else {printf("BadInputError : base is expected either 2 or 8\n"); return 0;}

        if(in->next->data == ';'-'0') in = in->next;
        else {printf("SyntaxError : ';' is expected after 2\n"); return 0;}


        if(in->next->data == ' '-'0') in = in->next;
        else {printf("SyntaxError : space expected after ';'\n"); return 0;}

        if(isDigit(in->next->data) && in->next->data != -2){
            in = in->next;
            node *p = in;
            NUM num = NULL;
            while(1){
                append(&num, p->data);
               // traverse(num);
                p = p->next;
                if(p->data == '\n'-'0')
                    break;
                if(!isDigit(p->data) || p->data == -2){
                    printf("SyntaxError : integers expected. '%c' is not an integer\n", p->data+'0');
                    return 0;
                }
            }
            NUM res = NULL;
            if(t == 2) res = DecimaToBinary(&num);
            if(t == 8) res = DecimaToOctal(&num);
            printf("output : ");
            traverse_expr(res);
            return 0;
        }
        else {printf("SyntaxError : integers expected. '%c' is not an integer\n", in->next->data+'0'); return 0;}
    }

    // encountering error if first character of input is other than '+' or spaces.
    if((!isDigit(in->data) || in->data == -2) && in->data != '-'-'0'){
        printf("SyntaxError : ");
        printf("oparand is expected before '%c' in line 1\n", in->data+'0');
        return 0;
    }

    int c;
    while(in->data != '\n'-'0'){
        c = in->data;

        if((c+'0' <= 90 && c+'0' >= 65) || (c+'0' <= 122 && c+'0' >= 97)){
           printf("BadInputError : ");
           printf("alphabetical character are not expected\n");
           return 0;
        }
        // if there is more than one space
        if(c == ' '-'0' && (in->next->data == c || in->prev->data == c)){
            printf("SpaceError : ");
            printf("At most one space is expected between operator and operand.\n");
            return 0;
        }

        // if there is no operator between two operand.
        if(c == ' '-'0' && (isDigit(in->next->data) && isDigit(in->prev->data))){
            printf("SyntaxError : ");
            printf("operator is expected between two operand.\n");
            return 0;
        }

        if(isDigit(c)){
            append(&post, c) ;
            if(!isDigit(in->next->data) &&  in->next->data != '.'-'0')
                append(&post, ' '-'0');
            if(in->next->data == '('-'0' || (in->next->data == ' '-'0' && in->next->next->data == '('-'0')){
                printf("SyntaxError : ");
                printf("operator is expected between %d and '(' in line 1\n", c);
                return 0;
            }
        }
        else if( c == '('-'0'){
            if(isOpr(in->next->data) || (in->next->data == ' '-'0' && isOpr(in->next->next->data))){
                printf("SyntaxError : ");
                printf("operand is expected after %dth '(' in line 1\n", x);
                return 0;
            }
            append(&s,'('-'0');
            x++;
        }
        else if(c == ')' - '0'){
            if(isOpr(in->prev->data) || (in->next->data == ' '-'0' && isOpr(in->prev->prev->data))){
                printf("SyntaxError : \n");
                printf("operand is expected before ')' in line 1\n");
                return 0;
            }
            while(s && peek(s)!= '('-'0'){
                append(&post, pop(&s));
                append(&post, ' '-'0');
            }
            if(peek(s) == '('-'0')
                pop(&s);
            x--;
        }
        else if(c == '>'-'0' || c == '<'-'0' || c == '='-'0' || c == '!'-'0'){
            if((c == '>'-'0' && in->next->data == '=' - '0')){
                c = -400;
                in = in->next;
            }
            if((c == '<'-'0' && in->next->data == '=' - '0')){
                c = -500;
                in = in->next;
            }
            if((c == '!'-'0' && in->next->data == '=' - '0')){
                c = -600;
                in = in->next;
            }
            if((c == '='-'0' && in->next->data == '=' - '0')){
                c = -100;
                in = in->next;
            }
            if(in->next->next->data == '='-'0'){
                printf("SyntaxError : Unexpected space between %c and '=' operator\n", c+'0');
                return 0;
            }
            if(!s)
                append(&s, c);
            else {
                while(s && precedence(peek(s)) >= precedence(c)){
                    append(&post, pop(&s));
                    append(&post, ' '-'0');
                }
                append(&s, c);
            }
        }
        else if(c == '&'-'0' || c == '|'-'0'){
            if((c == '&'-'0'  &&  in->next->data == c)){
                c = -700;
                in = in->next;
            }
            else if((c == '|'-'0'  &&  in->next->data == c)){
                c = -800;
                in = in->next;
            }
            else if(c == '&'-'0'  ||  c == '|'-'0'){
                printf("BadInputError : %c is not defined\n", c+'0');
                return 0;
            }
            if(!s)
                append(&s, c);
            else {
                while(s && precedence(peek(s)) >= precedence(c)){
                    append(&post, pop(&s));
                    append(&post, ' '-'0');
                }
                append(&s, c);
            }
        }
        else if(c == '%'-'0') append(&s, -200);
        else if(c == '^'-'0') append(&s, -300);

        else {
            if( c == '+'-'0' || c =='-'-'0' || c == '*'-'0' || c == '/'-'0') {
                // if there is no operand between two operator.
                if(isOpr(in->next->data) || (in->next->data == ' '-'0' && isOpr(in->next->next->data))){
                    printf("SyntaxError : ");
                    printf("operand is expected after '%c' in line 1\n", c+'0');
                    return 0;
                }
                if(!s)
                    append(&s, c);
                else {
                    while(s && precedence(peek(s)) >= precedence(c)){
                        append(&post, pop(&s));
                        append(&post, ' '-'0');
                    }
                    append(&s, c);
                }
            }
        }
        in = in->next;
    }

    if(x != 0){
        printf("ParanthesesError : \n");
        if(x > 0)
            printf("%d ')' parantheses missing in line 1\n", x);
        if(x < 0)
            printf("%d '(' parantheses missing in line 1\n", -x);
        return 0;
    }

    while(s){
        append(&post, pop(&s));
        append(&post, ' '-'0');
    }
    pop_last(&post);
    append(&post, '#'-'0');   // appending '#' as end of input detection

    evaluatePostfix(&post);

    return 0;
}


