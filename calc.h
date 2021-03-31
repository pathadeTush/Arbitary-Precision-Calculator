
typedef struct node{
    int data;
    struct node *next, *prev;
}node;

typedef node* NUM;

void init(NUM *l);

void append(NUM *l, int d);

int pop(NUM *l);

void traverse(NUM l);

void insertAt(NUM *l, int i, int d);

int len(NUM l);

int frac_len(NUM l);

void destroy(NUM *l);

void insert_At(NUM *l, int posn, int num);

int search(NUM l, int num);

void Remove(NUM *l, int num);

void Remove_At(NUM *l, int pos);

void pop_last(NUM *l);

void pop_first(NUM *l);

void reverse(NUM *l);

int greator(NUM l1, NUM l2);

int fgreator(NUM l1, NUM l2);


void eq_num(NUM *l1, NUM *l2);

NUM Add(NUM *l1, NUM *l2);

NUM Subtract(NUM *l1, NUM *l2);

NUM Mult(NUM *l1, NUM *l2);

NUM Div(NUM *l1, NUM *l2);

NUM Modulo(NUM *l1, NUM *l2);

NUM Power(NUM *num1, NUM *num2);

NUM DecimaToBinary(NUM *num);

NUM DecimaToOctal(NUM *num);




int isZero(NUM l);

void traverse_expr(NUM l);

int peek(NUM l);

int isDigit(int d);

int isOpr(int d);

void init_num(NUM *post, NUM *l);

int pop(NUM *l);

void push_list(NUM *soln, NUM *l);

void evaluatePostfix(NUM *post);



