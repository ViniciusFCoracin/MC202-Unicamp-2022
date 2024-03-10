#include <stdio.h>
#include <math.h>

double calc_distance(double animal_x, double animal_y, double buraco_x, double buraco_y);

int main(void){
    int num_buracos;
    double coelho_x, coelho_y, raposa_x, raposa_y;   // Coordenadas iniciais dos animais
    double buraco_atual_x, buraco_atual_y;   // Coordenadas do buraco do último input
    double coelho_distance, raposa_distance;   // Distância dos animais até o último buraco inputado
    double buraco_escape_x, buraco_escape_y;   // Coordenadas do buraco de escape, se houver
    int escaped = 0;   // Armazena a informação se o coelho já encontrou um buraco no qual possa escapar

    scanf("%d %lf %lf %lf %lf", &num_buracos, &coelho_x, &coelho_y, &raposa_x, &raposa_y);

    for (int i = 0; i < num_buracos; i++){
        scanf("%lf %lf", &buraco_atual_x, &buraco_atual_y);

        // Se o coelho ainda não escapou.
        if (!escaped){
            coelho_distance = calc_distance(coelho_x, coelho_y, buraco_atual_x, buraco_atual_y);
            raposa_distance = calc_distance(raposa_x, raposa_y, buraco_atual_x, buraco_atual_y);

            /* Se o coelho estiver à metade da distância da raposa, então ele pode escapar
               por esse buraco. */
            if (coelho_distance <= raposa_distance / 2.0){
                buraco_escape_x = buraco_atual_x;
                buraco_escape_y = buraco_atual_y;
                escaped = 1;
            }
        }
    }
    
    if (escaped){
        printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", buraco_escape_x, buraco_escape_y);
    }
    else{
        printf("O coelho nao pode escapar.\n");
    }

    return 0;
}

double calc_distance(double animal_x, double animal_y, double buraco_x, double buraco_y){
    // Calcula a distância entre o buraco e o animal.

    return sqrt((animal_x - buraco_x)*(animal_x - buraco_x) + (animal_y - buraco_y)*(animal_y - buraco_y));
}