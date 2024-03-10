#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_TEAM_NAME_LEN 31
#define MAX_CUP_NAME_LEN 101

struct team {
    char name[MAX_TEAM_NAME_LEN];
    int points;
    int victories;
    int draws;
    int defeats;
    int goal_diff;
    int goals_pro;
    int goals_against;
    int games;
};


int compare(const void* team1, const void* team2);


int main(void){
    int number_cups;
    scanf("%d", &number_cups);
    while (getchar() != '\n');

    for (int i = 0; i < number_cups; i++){
        char cup_name[MAX_CUP_NAME_LEN];
        scanf("%[^\n]", cup_name);
        while (getchar() != '\n');
            
        int number_teams;
        scanf("%d", &number_teams);
        while (getchar() != '\n');
        struct team teams[number_teams];
        for (int j = 0; j < number_teams; j++){
            scanf("%[^#@\n]", teams[j].name);
            while (getchar() != '\n');
            teams[j].games = 0;
            teams[j].points = 0;
            teams[j].victories = 0;
            teams[j].draws = 0;
            teams[j].defeats = 0;
            teams[j].goal_diff = 0;
            teams[j].goals_pro = 0;
            teams[j].goals_against = 0;
        }

        int number_games;
        scanf("%d", &number_games);
        while (getchar() != '\n');

        for (int j = 0; j < number_games; j++){
            char team1[MAX_TEAM_NAME_LEN];
            char team2[MAX_TEAM_NAME_LEN];
            int goals1, goals2;
            scanf("%[^@#]#%d@%d#%[^@#\n]", team1, &goals1, &goals2, team2);
            while (getchar() != '\n');
                
            for (int k = 0; k < number_teams; k++){
                if (strcmp(teams[k].name, team1) == 0){
                    teams[k].games += 1;
                    teams[k].goals_pro += goals1;
                    teams[k].goals_against += goals2;
                    teams[k].goal_diff += (goals1 - goals2);
                    // Se o time 1 ganhou
                    if (goals1 > goals2){
                        teams[k].victories += 1;
                        teams[k].points += 3;
                    }
                    // Se empataram
                    else if(goals1 == goals2){
                        teams[k].draws += 1;
                        teams[k].points += 1;
                    }
                    // Se o time 1 perdeu
                    else{
                        teams[k].defeats += 1;
                    }
                }

                else if (strcmp(teams[k].name, team2) == 0){
                    teams[k].games += 1;
                    teams[k].goals_pro += goals2;
                    teams[k].goals_against += goals1;
                    teams[k].goal_diff += (goals2 - goals1);
                    if (goals2 > goals1){
                        teams[k].victories += 1;
                        teams[k].points += 3;
                    }
                    else if(goals2 == goals1){
                        teams[k].draws += 1;
                        teams[k].points += 1;
                    }
                    else{
                        teams[k].defeats += 1;
                    }
                }
            }
        }

        // Ordena o array
        qsort(teams, (size_t) number_teams, sizeof(teams[0]), compare);

        // Printa a saída
        printf("%s\n", cup_name);
        for (int j = 0; j < number_teams; j++){
            printf("%d) %s, %dp, %dj (%d-%d-%d), %ds (%d-%d)\n",
            j + 1, teams[j].name, teams[j].points, teams[j].games, teams[j].victories,
            teams[j].draws, teams[j].defeats, teams[j].goal_diff, teams[j].goals_pro,
            teams[j].goals_against);
        }
        if (i + 1 != number_cups) printf("\n");
    }
    return 0;
}


int compare(const void* p1, const void* p2){
    struct team team1 = *((struct team*) p1);
    struct team team2 = *((struct team*) p2);

    if (team1.points != team2.points){
        return team2.points - team1.points;
    }
    else if (team1.victories != team2.victories){
        return team2.victories - team1.victories;
    }
    else if (team1.goal_diff != team2.goal_diff){
        return team2.goal_diff - team1.goal_diff;
    }
    else if (team1.goals_pro != team2.goals_pro){
        return team2.goals_pro - team1.goals_pro;
    }
    else if (team1.games != team2.games){
        return team1.games - team2.games;
    }
    else{
        // Ordena lexicograficamente
        char name1[MAX_TEAM_NAME_LEN];
        char name2[MAX_TEAM_NAME_LEN];

        for (unsigned i = 0; i < strlen(team1.name); i++){
            name1[i] = (char) toupper(team1.name[i]);
        }
        name1[strlen(team1.name)] = '\0';

        for (unsigned i = 0; i < strlen(team2.name); i++){
            name2[i] = (char) toupper(team2.name[i]);
        }
        name2[strlen(team2.name)] = '\0';

        return strcmp(name1, name2);
    }
}
