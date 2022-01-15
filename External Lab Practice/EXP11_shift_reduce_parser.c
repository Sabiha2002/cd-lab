#include<stdio.h>
#include<string.h>

int productions = 4;
char production_set[4][10] = {"E->E+E", "E->E*E", "E->(E)", "E->a"};
char stack[10], s[10];
int i = 0, j = 0;

void printContents(){
    printf("$");
    for(int m = 0; m < i; m++){
        printf("%c", stack[m]);
    }
    printf("\t");
    for(int m = j; m < strlen(s); m++){
        printf("%c", s[m]);
    }
    printf("$\t");
}

void check(){
    for(int k = 0; stack[k] != '\0'; k++){
        if(stack[k] == 'a'){
            stack[k] = 'E';
            stack[k+1] = '\0';
            printContents();
            printf("Reduce to E\n");
        }
    }
    for(int k = 0; stack[k+2] != '\0'; k++){
        if(stack[k] == 'E' && stack[k+1] == '*' && stack[k+2] == 'E' ){
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            i -= 2;
            printContents();
            printf("Reduce to E\n");
        }
    }
    for(int k = 0; stack[k+2] != '\0'; k++){
        if(stack[k] == 'E' && stack[k+1] == '+' && stack[k+2] == 'E' ){
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            i -= 2;
            printContents();
            printf("Reduce to E\n");
        }
    }
    for(int k = 0; stack[k+2] != '\0'; k++){
        if(stack[k] == '(' && stack[k+1] == 'E' && stack[k+2] == ')' ){
            stack[k] = 'E';
            stack[k+1] = '\0';
            stack[k+2] = '\0';
            i -= 2;
            printContents();
            printf("Reduce to E\n");
        }
    }
}


void shiftReduceParser(){
    while(j < strlen(s)){
        stack[i] = s[j];
        j++;
        i++;
        stack[i] = '\0';
        printContents();
        printf("Shift symbols\n");
        check();
    }
}

int main(){
    printf("The grammar is\n");
    for(int i = 0; i < productions; i++){
        printf("%s\n", production_set[i]);
    }

    printf("Enter the input string: ");
    scanf("%s", s);
    printf("\n");
    printf("Stack\tInput\tAction\n");
    shiftReduceParser();
    if(strlen(stack) == 1 && stack[0] == 'E' && j >= strlen(s)){
        printf("Accepted\n");
    }else{
        printf("Rejected\n");
    }
}