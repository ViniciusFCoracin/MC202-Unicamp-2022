/* Dois números são amigos se, e somente se, a soma dos divisores do primeiro
for igual ao segundo e vice-versa. Esse programa testa se dois números digitados
pelo usuário são ou não amigos.*/

#include <stdio.h>

int eh_amigo(int num1, int num2);
int soma_divisores(int num);

int main(void){
    int num1, num2;
    scanf("%d %d", &num1, &num2);

    if (eh_amigo(num1, num2)){
        printf("%d e %d sao amigos\n", num1, num2);
    }
    else{
        printf("%d e %d nao sao amigos\n", num1, num2);
    }

    return 0;
}

int eh_amigo(int num1, int num2){
    if (soma_divisores(num1) == num2 &&
        soma_divisores(num2) == num1){
        return 1;
    }
    else{
        return 0;
    }
}

int soma_divisores(int num){
    int soma = 0;

    for (int i = 1; i < num; i++){
        if (num % i == 0){
            soma += i;
        }
    }
    return soma;
}