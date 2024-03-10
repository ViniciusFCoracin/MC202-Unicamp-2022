#include <stdio.h>

typedef struct{
    int size;
    int internal_size;
} matriosca;

void push(matriosca* stack, int* len, matriosca x);
matriosca pop(matriosca* stack, int* len);
matriosca* last(matriosca* stack, int len);

int main(void){
    int stack_size;
    scanf("%d", &stack_size);

    while (stack_size){
        matriosca stack[stack_size / 2];
        int len = 0;
        int is_matriosca = 1;
        int num;

        for (int i = 0; i < stack_size; i++){
            scanf("%d", &num);

            if (is_matriosca == 1){
                if (len == 0 && num > 0){
                    // Se o primeiro número for positivo
                   is_matriosca = 0;
                }
                else if (len >= 1 && num < 0 && -num > last(stack, len) -> size){
                    // Se tentou colocar uma matriosca maior que a matriosca que a contém
                    is_matriosca = 0;
                }
                else if(num > 0 && num != last(stack, len) -> size){
                    // Problema de aninhamento
                    is_matriosca = 0;
                }
                else if (num > 0 && num == last(stack, len) -> size){
                    // Se fechei com sucesso uma matriosca
                    pop(stack, &len); 
                }
                else{
                    last(stack, len) -> internal_size += -num;
                    
                    // Confiro se a próxima matriosca cabe na anterior, ou se a soma dos tamanhos ultrapassou o limite
                    if (len > 0 && last(stack, len) -> internal_size >= last(stack, len) -> size){
                        is_matriosca = 0;
                        continue;
                    }

                    // Se couber, empilho a matriosca
                    matriosca matri;
                    matri.size = -num;
                    matri.internal_size = 0;
                    push(stack, &len, matri);
                }
            }
        }
        
        (is_matriosca)? printf(":-) Matriosca!\n") : printf(":-( Tente novamente.\n");
        scanf("%d", &stack_size);
    }

    return 0;
}


void push(matriosca* stack, int* len, matriosca x){
    stack[(*len)++] = x;
}


matriosca pop(matriosca* stack, int* len){
    matriosca x = stack[(*len)--
    ];
    
    return x;
}


matriosca* last(matriosca* stack, int len){
    return &stack[len - 1];
}
