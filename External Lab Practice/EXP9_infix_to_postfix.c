#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

char s[10], stack[10];

struct Node{
    char data;
    struct Node* next;
};
struct Node* top = NULL;

void push(char c){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = c;
    temp->next = top;
    top = temp;
}

void pop(){
    if(top != NULL){
        struct Node* temp = top;
        top = top->next;
        free(temp);
    }
}

char getTop(){
    if(top == NULL){
        return '.';
    }
    return top->data;
}
int priority(char c){
    switch(c){
        case '*': return 10;
        case '/': return 9;
        case '+': return 8;
        case '-': return 7;
    }
    return -1;
}
int main(){
    printf("Enter the input string: ");
    scanf("%s", s);
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == '('){
            push(s[i]);
        }else if(s[i] == ')'){
            while(getTop() != '('){
                char c = getTop();
                printf("%c", c);
                pop();
            }
            pop();
        }else if(priority(s[i]) == -1){
            printf("%c", s[i]);
        }else{
            while(priority(getTop()) >= priority(s[i])){
                char c = getTop();
                printf("%c", c);
                pop();
            }
            push(s[i]);
        }
    }
    while(top != NULL){
        char c = getTop();
        printf("%c", c);
        pop();
    }
    return 0;
}