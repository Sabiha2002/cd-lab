#include <stdio.h>
#include <string.h>
int productions = 3;
char production_set[3][10] = {"A->aBa", "B->bB", "B->@"};
char lprod[3][10] = {"A", "B", "B"};
char rprod[3][10] = {"aBa", "bB", "@"};
char first[3][10] = {"a", "b", "@"};
char follow[3][10] = {"$", "a", "a"};
char table[3][4][10];


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

void predictiveParserTable(){
    for(int i = 0; i < productions; i++){
        char f[10];
        strcpy(f, first[i]);
        char fl[10];
        strcpy(fl, follow[i]);
        int flag = 0;
        for(int j = 0; f[j] != '\0'; j++){
            if(f[j] != '@'){
                int row = getRow(lprod[i][0]), col = getCol(f[j]);
                strcpy(table[row+1][col+1], production_set[i]);
            }else{
                flag = 1;
                break;
            }
        }
        for(int j = 0; fl[j] != '\0' && flag; j++){
            int row = getRow(lprod[i][0]), col = getCol(fl[j]);
            strcpy(table[row+1][col+1], production_set[i]);
        }
            
    }
}

int main(){
    printf("The grammar is\n");
    for(int i = 0; i < productions; i++){
        printf("%s\n", production_set[i]);
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            strcpy(table[i][j], "");
        }
    }
    printf("The predictive parser table is\n\n");
    predictiveParserTable();
    strcpy(table[1][0], "A");
    strcpy(table[2][0], "B");
    strcpy(table[0][1], "a");
    strcpy(table[0][2], "b");
    strcpy(table[0][3], "$");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("%s\t", table[i][j]);
        }
        printf("\n");
    }
}
