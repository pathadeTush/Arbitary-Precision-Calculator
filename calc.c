/*
*     Author : Tushar Chakradhar Pathade    
*     Source : https://github.com/pathadeTush
*/

#include "calc.h"

/* ------ isZero ------- */
int isZero(NUM l)
{
    int k = 1;
    node *p;
    p = l;
    while (1)
    {
        if (isDigit(p->data) && p->data != -2 && p->data != 0)
        {
            k = 0;
            break;
        }
        if (p->next == l)
            break;
        p = p->next;
    }
    return k;
}

/* ------- Greatest Number list between two number list ------- */
int greator(NUM l1, NUM l2)
{
    int n;
    node *p, *q;
    p = l1;
    q = l2;
    while (1)
    {
        if (p->data > q->data)
        {
            n = -1;
            break;
        }
        else if (q->data > p->data)
        {
            n = -2;
            break;
        }
        else if (p->data == -2 || p->next == l1)
        {
            n = 0;
            break;
        }
        p = p->next;
        q = q->next;
    }
    return n;
}

/* ------- Greatest decimal part of Number list between two number list ------- */
int fgreator(NUM l1, NUM l2)
{
    int n;
    node *p, *q;
    p = l1;
    q = l2;

    while (p->data != -2)
    {
        p = p->next;
    }
    while (q->data != -2)
    {
        q = q->next;
    }

    p = p->next;
    q = q->next;

    while (1)
    {
        if (p->data > q->data)
        {
            n = -1;
            break;
        }
        else if (q->data > p->data)
        {
            n = -2;
            break;
        }
        else if (p->next == l1)
        {
            n = 0;
            break;
        }
        p = p->next;
        q = q->next;
    }
    return n;
}

//  Function to make length of two number list same
/* -------- eq_num ----------- */
void eq_num(NUM *l1, NUM *l2)
{
    node *p, *q, *last1, *last2;
    p = *l1;
    q = *l2;
    last1 = p->prev;
    last2 = q->prev;

    // if numbers contains decimal point
    if (search(*l1, -2) || search(*l2, -2))
    {
        // appending '.' if one list not contained.
        if (!search(*l1, -2))
            append(l1, -2);
        else if (!search(*l2, -2))
            append(l2, -2);
        node *f1 = NULL, *f2 = NULL;
        p = *l1;
        q = *l2;
        last1 = p->prev;
        last2 = q->prev;

        while (p->data != -2)
        {
            p = p->next;
        }
        while (q->data != -2)
        {
            q = q->next;
        }

        f1 = p;
        f2 = q;

        while (p != last1 && q != last2)
        {
            p = p->next;
            q = q->next;
        }

        if (p == last1 && q != last2)
        {
            // appending zero to num1 as length of num1 is less than num2
            while (1)
            {
                append(l1, 0);
                q = q->next;
                if (q == last2)
                    break;
            }
        }
        else if (q == last2 && p != last1)
        {
            // appending zero to num2 as length of num2 is less than num1
            while (1)
            {
                append(l2, 0);
                p = p->next;
                if (p == last1)
                    break;
            }
        }
        p = f1->prev;
        q = f2->prev;

        while (p != *l1 && q != *l2)
        {
            p = p->prev;
            q = q->prev;
        }
        if (p == *l1 && q == *l2)
            return;
        else if (p == *l1)
        {
            reverse(l1);
            while (1)
            {
                append(l1, 0);
                q = q->prev;
                if (q == *l2)
                    break;
            }
            reverse(l1);
        }
        else if (q == *l2)
        {
            reverse(l2);
            while (1)
            {
                append(l2, 0);
                p = p->prev;
                if (p == *l1)
                    break;
            }
            reverse(l2);
        }
        return;
    }

    // if numbers contains intgers only
    else
    {
        while (p != last1 && q != last2)
        {
            p = p->next;
            q = q->next;
        }
        if (p == last1 && q == last2)
            return;
        else if (p == last1)
        {
            reverse(l1);
            while (1)
            {
                append(l1, 0);
                q = q->next;
                if (q == last2)
                    break;
            }
            reverse(l1);
        }
        else if (q == last2)
        {
            reverse(l2);
            while (1)
            {
                append(l2, 0);
                p = p->next;
                if (p == last1)
                    break;
            }
            reverse(l2);
        }
        return;
    }
}

/* ----------- Add ------------ */
NUM Add(NUM *l1, NUM *l2)
{
    NUM L3;
    init(&L3);
    int carry = 0, sum, k;
    node *last1, *last2;
    eq_num(l1, l2);

    last1 = *l1;
    last2 = *l2;
    last1 = last1->prev;
    last2 = last2->prev;
    if (search(*l1, -2))
    {
        while (last1->data != -2)
        {
            sum = last1->data + last2->data + carry;
            carry = 0;
            if (sum >= 10)
            {
                k = sum % 10;
                append(&L3, k);
                carry = (sum - k) / 10;
            }
            else
                append(&L3, sum);
            last1 = last1->prev;
            last2 = last2->prev;
        }
        last1 = last1->prev;
        last2 = last2->prev;
        append(&L3, -2);
    }
    while (1)
    {
        sum = last1->data + last2->data + carry;
        carry = 0;
        if (sum >= 10)
        {
            k = sum % 10;
            append(&L3, k);
            carry = (sum - k) / 10;
        }
        else
            append(&L3, sum);
        if (last1 == *l1)
            break;
        last1 = last1->prev;
        last2 = last2->prev;
    }

    if (carry == 1)
        append(&L3, 1);
    reverse(&L3);

    return L3;
}

/* ---------- Subtract ------------ */
NUM Subtract(NUM *l1, NUM *l2)
{

    eq_num(l1, l2);
    NUM L3;
    init(&L3);
    int borrow = 0, sub, k, gtr = 0;
    gtr = greator(*l1, *l2);

    node *last1, *last2;
    last1 = *l1;
    last2 = *l2;
    if (search(*l1, -2))
    {
        int n, r = 0;
        n = fgreator(*l1, *l2);
        // if num2 > num1 and fnum1 > fnum2
        if (n == -1 && gtr == -2)
        {
            node *p = *l1, *q = *l2, *nn1, *nn2;
            while (p->data != -2)
            {
                p = p->next;
            }
            while (q->data != -2)
            {
                q = q->next;
            }

            nn1 = (node *)malloc(sizeof(node));
            nn1->data = 0;
            nn1->prev = p;
            nn1->next = p->next;
            p->next->prev = nn1;
            p->next = nn1;

            nn2 = (node *)malloc(sizeof(node));
            nn2->data = 1;
            nn2->prev = q;
            nn2->next = q->next;
            q->next->prev = nn2;
            q->next = nn2;

            r = 1;
            n = -2;
        }
        // if num1 > num2 and fnum2 > fnum1
        if (n == -2 && gtr == -1)
        {
            node *p = *l1, *q = *l2, *nn1, *nn2;
            while (p->data != -2)
            {
                p = p->next;
            }
            while (q->data != -2)
            {
                q = q->next;
            }

            nn1 = (node *)malloc(sizeof(node));
            nn1->data = 1;
            nn1->prev = p;
            nn1->next = p->next;
            p->next->prev = nn1;
            p->next = nn1;

            nn2 = (node *)malloc(sizeof(node));
            nn2->data = 0;
            nn2->prev = q;
            nn2->next = q->next;
            q->next->prev = nn2;
            q->next = nn2;
            r = 1;
            n = -1;
        }

        last1 = last1->prev;
        last2 = last2->prev;
        // if fl1 > fl2 and l1 > l2
        if (n == -1)
        {
            while (last1->data != -2)
            {
                sub = last1->data - last2->data + borrow;
                borrow = 0;
                if (sub < 0)
                {
                    k = sub + 10;
                    append(&L3, k);
                    borrow = -1;
                }
                else
                    append(&L3, sub);
                last1 = last1->prev;
                last2 = last2->prev;
            }
        }

        // if l2 > l1  and fl2 > fl1
        if (n == -2)
        {
            while (last1->data != -2)
            {
                sub = last2->data - last1->data + borrow;
                borrow = 0;
                if (sub < 0)
                {
                    k = sub + 10;
                    append(&L3, k);
                    borrow = -1;
                }
                else
                    append(&L3, sub);
                last1 = last1->prev;
                last2 = last2->prev;
            }
            k = -2;
        }
        else if (n == 0)
            append(&L3, 0);
        if (r == 1)
        {
            // traverse(L3);
            pop_last(&L3);
            borrow = -1;
        }
        append(&L3, -2);
    }

    last1 = last1->prev;
    last2 = last2->prev;

    if (gtr == -1)
    {
        while (1)
        {
            sub = last1->data - last2->data + borrow;
            borrow = 0;
            if (sub < 0)
            {
                k = sub + 10;
                append(&L3, k);
                borrow = -1;
            }
            else
                append(&L3, sub);
            if (last1 == *l1)
                break;
            last1 = last1->prev;
            last2 = last2->prev;
        }
    }
    else if (gtr == -2)
    {
        while (1)
        {
            sub = last2->data - last1->data + borrow;
            borrow = 0;
            if (sub < 0)
            {
                k = sub + 10;
                append(&L3, k);
                borrow = -1;
            }
            else
                append(&L3, sub);
            if (last1 == *l1)
                break;
            last1 = last1->prev;
            last2 = last2->prev;
        }
        append(&L3, -1);
    }
    else if (gtr == 0)
    {
        append(&L3, 0);
        if (k == -2)
            append(&L3, -1);
    }
    reverse(&L3);
    return L3;
}

/* --------- mult ----------- */
NUM Mult(NUM *l1, NUM *l2)
{
    NUM L3, s, t;
    init(&L3);
    init(&t);

    eq_num(l1, l2);
    int gtr, ele, prod, carry = 0, k;
    node *f = NULL, *last1, *last2;
    last1 = (*l1)->prev;
    last2 = (*l2)->prev;

    gtr = greator(*l1, *l2);

    // if numbers are having decimal points
    if (search(*l1, -2))
    {
        if (gtr == -1)
        {
            while (last1->data != -2)
            {
                last1 = last1->prev;
            }
            f = last1->next;
        }
        else
        {
            while (last2->data != -2)
            {
                last2 = last2->prev;
            }
            f = last2->next;
        }
        Remove(l1, -2);
        Remove(l2, -2);
    }

    if (gtr == -1)
    {
        while (1)
        {
            if ((*l2)->data == 0)
            {
                pop_first(l2);
                if (*l2 == NULL)
                {
                    append(&L3, 0);
                    return L3;
                }
            }
            else
                break;
        }

        while (1)
        {
            init(&s);
            last1 = (*l1)->prev;
            ele = last2->data;

            while (1)
            {
                prod = ele * (last1->data) + carry;
                carry = 0;
                if (prod >= 10)
                {
                    k = prod % 10;
                    append(&s, k);
                    carry = (prod - k) / 10;
                }
                else
                    append(&s, prod);

                if (last1->prev == (*l1)->prev)
                    break;
                last1 = last1->prev;
            }
            if (carry != 0)
            {
                append(&s, carry);
                carry = 0;
            }
            reverse(&s);

            append(&t, 1);
            node *r = t;
            while (r->next != t)
            {
                append(&s, 0);
                r = r->next;
            }
            if (L3 != NULL)
                L3 = Add(&L3, &s);
            else
                L3 = s;
            if (last2->prev == (*l2)->prev)
                break;
            last2 = last2->prev;
        }
    }
    else if (gtr == -2 || gtr == 0)
    {
        while (1)
        {
            if ((*l1)->data == 0)
            {
                pop_first(l1);
                if (*l1 == NULL)
                {
                    append(&L3, 0);
                    return L3;
                }
            }
            else
                break;
        }

        while (1)
        {
            init(&s);
            last2 = (*l2)->prev;
            ele = last1->data;
            while (1)
            {
                prod = ele * (last2->data) + carry;
                carry = 0;
                if (prod >= 10)
                {
                    k = prod % 10;
                    append(&s, k);
                    carry = (prod - k) / 10;
                }
                else
                    append(&s, prod);

                if (last2->prev == (*l2)->prev)
                    break;
                last2 = last2->prev;
            }
            if (carry != 0)
            {
                append(&s, carry);
                carry = 0;
            }
            reverse(&s);

            append(&t, 1);
            node *r = t;
            while (r->next != t)
            {
                append(&s, 0);
                r = r->next;
            }
            if (L3 != NULL)
                L3 = Add(&L3, &s);
            else
                L3 = s;

            if (last1->prev == (*l1)->prev)
                break;
            last1 = last1->prev;
        }
    }

    if (f)
    {
        int i = 2;
        node *r, *nn, *f1;
        r = L3;
        while (i)
        {
            f1 = f;
            while (1)
            {
                r = r->prev;
                if (f1->next == *l1 || f1->next == *l2)
                    break;
                f1 = f1->next;
            }
            i--;
        }
        nn = (node *)malloc(sizeof(node));
        nn->data = -2;
        nn->prev = r->prev;
        nn->next = r;
        r->prev->next = nn;
        r->prev = nn;
    }

    //traverse(*l1);
    //traverse(*l2);
    return L3;
}

NUM Div(NUM *l1, NUM *l2)
{
    NUM L3, i;
    init(&L3);
    init(&i);
    append(&L3, 0);
    append(&i, 1);
    eq_num(l1, l2);
    int r = 0;

    int precision = 0, gtr;

    if (search(*l1, -2))
    {
        Remove(l1, -2);
        Remove(l2, -2);
    }

    gtr = greator(*l1, *l2);
    while (precision != 15)
    { // precision = no. of digits after decimal points if number is not totally divisible.
        while (gtr != -2)
        {
            if (!precision && (*l2)->data == 0 && r == 0 && (*l1)->data != 0)
            {
                r = 1;
                NUM j = NULL;
                append(&j, 1);
                node *p;
                p = *l2;

                while (p->data == 0)
                {
                    append(&j, 0);
                    p = p->next;
                    append(l2, 0);
                    pop_first(l2);
                }

                gtr = greator(*l1, *l2);
                if (gtr == 0)
                {
                    L3 = Add(&L3, &j);
                    break;
                }
                else if (gtr == -1)
                {
                    while (gtr == -1)
                    {
                        *l1 = Subtract(l1, l2);
                        L3 = Add(&L3, &j);
                        gtr = greator(*l1, *l2);
                    }
                    if (gtr == 0)
                        break;
                }

                if (gtr == -2)
                {
                    j = j->prev;
                    while (j->data == 0)
                    {
                        pop_last(l2);
                        insert_At(l2, 1, 0);
                        gtr = greator(*l1, *l2);
                        while (gtr == -1)
                        {
                            *l1 = Subtract(l1, l2);
                            L3 = Add(&L3, &j);
                            gtr = greator(*l1, *l2);
                        }
                        j = j->prev;
                    }
                    gtr = greator(*l1, *l2);
                }
            }

            else
            {
                *l1 = Subtract(l1, l2);
                L3 = Add(&L3, &i); // incerementing list
                if (gtr == 0)
                    break;
                gtr = greator(*l1, *l2);
            }
        }
        if (gtr == 0)
            break;

        if (!precision)
        {
            while (i->data == 0)
            {
                pop_first(&i);
            }
            append(&L3, -2);
            append(&L3, 0);
            insert_At(&i, 1, 0);
            insert_At(&i, 2, -2);
        }
        if (gtr == -2)
        {
            append(l1, 0);
            if ((*l1)->data == 0)
                pop_first(l1);
            else
                insert_At(l2, 1, 0);
        }
        if (precision)
        {
            node *p, *nn;
            p = i->prev;
            nn = (node *)malloc(sizeof(node));
            nn->data = 0;
            nn->prev = p->prev;
            nn->next = p;
            p->prev->next = nn;
            p->prev = nn;
        }
        gtr = greator(*l1, *l2);

        precision++;
    }

    return L3;
}

NUM Modulo(NUM *l1, NUM *l2)
{
    NUM L3, m;
    init(&L3);
    append(&L3, 0);
    eq_num(l1, l2);
    int r = 0;
    node *f = NULL, *last;
    m = *l1;
    last = m->prev;

    int gtr;
    gtr = greator(*l1, *l2);
    if (gtr == 0)
        return L3;
    if (gtr == -2)
        return *l1;

    if (search(*l1, -2))
    {
        while (last->data != -2)
        {
            last = last->prev;
        }
        f = last->next;
        Remove(l1, -2);
        Remove(l2, -2);
    }

    while (gtr != -2)
    {
        if ((*l2)->data == 0 && r == 0 && (*l1)->data != 0)
        {
            r = 1;
            NUM j = NULL;
            append(&j, 1);
            node *p;
            p = *l2;

            while (p->data == 0)
            {
                append(&j, 0);
                p = p->next;
                append(l2, 0);
                pop_first(l2);
            }
            gtr = greator(*l1, *l2);
            if (gtr == 0)
                break;
            else if (gtr == -1)
            {
                while (gtr == -1)
                {
                    *l1 = Subtract(l1, l2);
                    gtr = greator(*l1, *l2);
                }
                if (gtr == 0)
                    break;
            }

            if (gtr == -2)
            {
                j = j->prev;
                while (j->data == 0)
                {
                    pop_last(l2);
                    insert_At(l2, 1, 0);
                    gtr = greator(*l1, *l2);
                    while (gtr == -1)
                    {
                        *l1 = Subtract(l1, l2);
                        gtr = greator(*l1, *l2);
                    }
                    j = j->prev;
                }
                gtr = greator(*l1, *l2);
            }
        }

        else
        {
            *l1 = Subtract(l1, l2);
            if (gtr == 0)
                break;
            gtr = greator(*l1, *l2);
        }
    }

    if (gtr == -2)
    {
        while ((*l1)->data == 0)
        {
            pop_first(l1);
        }
        return *l1;
    }

    if (f)
    {
        node *nn, *q;
        q = L3;
        while (1)
        {
            q = q->prev;
            if (f->next == m)
                break;
            f = f->next;
        }
        nn = (node *)malloc(sizeof(node));
        nn->data = -2;
        nn->prev = q->prev;
        nn->next = q;
        q->prev->next = nn;
        q->prev = nn;
    }

    return L3;
}

NUM Power(NUM *num1, NUM *num2)
{

    NUM i = NULL, j = NULL;
    append(&i, 1);
    append(&j, 2);

    if (isZero(*num2))
        return i;
    else if (((*num2)->prev->data) % 2 == 0)
    {
        *num2 = Div(num2, &j);
        NUM p = Power(num1, num2);
        return Mult(&p, &p);
    }
    else
    {
        *num2 = Div(num2, &j);
        if (search(*num2, -2))
        {
            node *r = *num2;
            r = r->prev;
            while (r->data != -2)
            {
                r = r->prev;
                pop_last(num2);
            }
            r = NULL;
            pop_last(num2);
        }
        //printf("num2 ");traverse(*num2);
        NUM p = Power(num1, num2);
        NUM q = Mult(&p, &p);
        return Mult(num1, &q);
    }
}

NUM DecimaToBinary(NUM *num)
{
    NUM i = NULL, res = NULL;
    if (isZero(*num))
    {
        append(&res, 0);
        return res;
    }
    append(&i, 1);
    int gtr;
    eq_num(num, &i);
    gtr = greator(*num, i);
    if (gtr != -1)
        return *num;
    // traverse(*num);
    while (!isZero(*num))
    {
        NUM j = NULL;
        append(&j, 2);
        if ((*num)->prev->data % 2 == 0)
            append(&res, 0);
        else
            append(&res, 1);
        *num = Div(num, &j);
        if (search(*num, -2))
        {
            node *r = *num;
            r = r->prev;
            while (r->data != -2)
            {
                r = r->prev;
                pop_last(num);
            }
            r = NULL;
            pop_last(num);
        }
        if (gtr != -1)
            break;
        eq_num(num, &i);
        gtr = greator(*num, i);
    }
    reverse(&res);
    return res;
}

NUM DecimaToOctal(NUM *num)
{
    NUM i = NULL, res = NULL;
    if (isZero(*num))
    {
        append(&res, 0);
        return res;
    }
    append(&i, 7);

    int gtr;
    eq_num(num, &i);
    gtr = greator(*num, i);
    if (gtr != -1)
        return *num;
    while (!isZero(*num))
    {
        NUM rem = NULL, j = NULL, k = NULL;
        append(&j, 8);
        append(&k, 8);
        rem = *num;

        rem = Modulo(&rem, &j);
        append(&res, rem->prev->data);
        *num = Div(num, &k);

        if (search(*num, -2))
        {
            node *r = *num;
            r = r->prev;
            while (r->data != -2)
            {
                r = r->prev;
                pop_last(num);
            }
            r = NULL;
            pop_last(num);
        }
        if (gtr != -1)
            break;
        eq_num(num, &i);
        gtr = greator(*num, i);
    }
    reverse(&res);
    return res;
}

/*

In developement....

NUM DecimaToHex(NUM *num){
    NUM i = NULL, res = NULL;
    if(isZero(*num)){
        append(&res, 0);
        return res;
    }
    append(&i, 1);
    append(&i, 5);

    int gtr;
    eq_num(num, &i);
    gtr = greator(*num, i);
    if(gtr != -1) return *num;

    while(!isZero(*num)){
        NUM rem = NULL, j = NULL, k = NULL;
        append(&j, 1);
        append(&j, 6);
        append(&k, 1);
        append(&k, 6);
        rem = *num;

        rem = Modulo(&rem, &j);
        printf("rem "); traverse(rem);
        printf("%d ", rem->data);


        *num = Div(num , &k);
        if(search(*num, -2)){
            node *r = *num;
            r = r->prev;
            while(r->data != -2){
                r = r->prev;
                pop_last(num);
            }
            r = NULL;
            pop_last(num);
        }
        if(gtr != -1) break;
        eq_num(num, &i);
        gtr = greator(*num, i);
    }
    reverse(&res);
    return res;
}
*/
