#include<stdio.h>
#include<string.h>
#include<ctype.h>
char production_set[10][10];
int flag;

void addToResult(char result[], char c){
    int i;
    for(i = 0; result[i] != '\0'; i++){
        if(result[i] == c){
            return;
        }
    }
    result[i] = c;
    result[i+1] = '\0';
}

void FIRST(char c, int n, char result[]){
    if(!isupper(c)){
        addToResult(result, c);
        return;
    }else{
        for(int i = 0; i < n; i++){
            if(production_set[i][0] == c){
                if(production_set[i][2] == '@'){
                    addToResult(result, '@');
                }
                else{
                    int j = 2;
                    while(production_set[i][j] != '\0'){
                        char sub_result[10];
                        sub_result[0] = '\0';
                        int found_epsilon = 0;
                        FIRST(production_set[i][j], n, sub_result);
                        for(int k = 0; sub_result[k] != '\0'; k++){
                            if(sub_result[k] != '@'){
                                addToResult(result, sub_result[k]);
                            }else{
                                found_epsilon = 1;
                            }
                        }
                        if(!found_epsilon){
                            flag = 0;
                            break;
                        }
                        j++;
                    }
                    if(flag){
                        addToResult(result, '@');
                    }
                }
            }
        }
    }
}

void FOLLOW(char c, int n, char result[]){
    if(!isupper(c)){
        return;
    }
    if(production_set[0][0] == c){
        addToResult(result, '$');
    }
    for(int i = 0; i < n; i++){
        for(int j = 2; production_set[i][j] != '\0'; j++){
            if(production_set[i][j] == c){
                int found_epsilon;
                while(production_set[i][++j] != '\0'){
                    found_epsilon = 0;
                    char sub_result[10];
                    sub_result[0] = '\0';
                    FIRST(production_set[i][j], n, sub_result);
                    for(int k = 0; sub_result[k] != '\0'; k++){
                        if(sub_result[k] != '@'){
                            addToResult(result, sub_result[k]);
                        }else{
                            found_epsilon = 1;
                        }
                    }
                    if(found_epsilon == 0){
                        break;
                    }
                }
                if(found_epsilon){
                    if(production_set[i][0] != c)FOLLOW(production_set[i][0], n, result);
                }
            }
        }
    }
}
int main(){
    int n;
    printf("Enter number of productions: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        printf("Enter production %d: ", i+1);
        scanf("%s", production_set[i]);
    }
    int choice = 1;
    do{
        char ch, result[10];
        flag = 1;
        result[0] = '\0';
        printf("Find FOLLOW of? ");
        scanf(" %c", &ch);
        FOLLOW(ch, n, result);
        printf("FOLLOW(%c): {", ch);
        for(int i = 0; result[i] != '\0'; i++){
            printf(" %c ", result[i]);
        }
        printf("}\n");
        printf("Enter 1 to continue: ");
        scanf("%d", &choice);
    }while(choice == 1);
    return 0;
}