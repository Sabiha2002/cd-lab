#include<stdio.h>
#include<string.h>
char s[10];
int i = 0, error = 0;
void E();
void F(){
    if(s[i] == '('){
        i++;
        E();
        if(s[i] == ')'){
            i++;
        }else{
            error = 1;
        }
    }else if(s[i] == 'a'){
        i++;
    }else{
        error = 1;
    }
}

void Tprime(){
    if(s[i] == '*'){
        i++;
        F();
        Tprime();
    }
}

void T(){
    F();
    Tprime();
}

void Eprime(){
    if(s[i] == '+'){
        i++;
        T();
        Eprime();
    }
}

void E(){
    T();
    Eprime();
}



int main(){
    printf("Enter the input string: ");
    scanf("%s", s);
    E();
    printf("%d\n", i);
    if(i == strlen(s) && error == 0){
        printf("Accepted\n");
    }else{
        printf("Rejected\n");
    }
}