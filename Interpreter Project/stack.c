//Stack implementationS
#include "stack.h"

#define MAXSTACK 10
#define EMPTYSTACK -1
int top = EMPTYSTACK;
char items[MAXSTACK];




void push(char c) {
   items[++top] = c;
}

char pop() {
   return items[top--];
}

int full()  {
   return (top+1 == MAXSTACK);
}

int empty()  {
   return (top == EMPTYSTACK);
}
