#include <stdio.h>
#include <string.h>
#include<stdbool.h>
char production_set[3][10] = {"A->aBa", "B->bB", "B->@"};
char table[2][3][10] = {{"aBa", "", ""}, {"@", "bB", ""}};
int productions = 3;
char stack[10], s[10];
int i = 0, j = 0;

int getRow(char c){
    switch (c){
        case 'A': return 0;
        case 'B': return 1;
    }
    return 2;
}
int getCol(char c){
    switch (c){
        case 'a': return 0;
        case 'b': return 1;
        case '$': return 2;
    }
    return 3;
}
void printContents(){
    printf("$");
    for(int m = 0; m <= i; m++){
        printf("%c", stack[m]);
    }
    printf("\t");
    for(int m = j; m < strlen(s); m++){
        printf("%c", s[m]);
    }
    printf("$\n");
}

void LL1parser(){
    while(true){
        if(stack[i] == s[j]){
            i--;
            j++;
            printContents();
            if(i < 0 && j < strlen(s) || j >= strlen(s) && i >= 0){
                printf("Error\n");
                return;
            }else if(i < 0 && j >= strlen(s)){
                printf("Accepted\n");
                return;
            }
        }else{
            int row = getRow(stack[i]), col = getCol(s[j]);
            char r[10];
            if(row >= 2 || col >= 3){
                printf("Error\n");
                return;
            }
            strcpy(r, table[row][col]);
            if(r == ""){
                printf("Error\n");
                return;
            }else if(strcmp(r, "@") == 0){
                strcpy(r, "");
            }
            for(int k = strlen(r)-1; k >= 0; k--){
                stack[i++] = r[k];
            }
            i--;
            printContents();
        }
    }
    

}

int main(){
    printf("The grammar is\n");
    for(int i = 0; i < productions; i++){
        printf("%s\n", production_set[i]);
    }
    printf("Enter the input string: ");
    scanf("%s", s);
    stack[0] = 'A';
    printf("Stack\tInput\n");
    printContents();
    LL1parser();
}