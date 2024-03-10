#include <stdio.h>
#define SECONDS_IN_12H 43200
int months_nonleap_year[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int months_leap_year[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_leap_year(int year);

int calc_timelapse(int year1, int month1, int mday1, int hour1, int min1, int sec1,
                   int year2, int month2, int mday2, int hour2, int min2, int sec2);

void next_day(int* year, int* month, int* mday);

int main(void){
    int rise_mday, rise_month, rise_year, rise_hour, rise_min, rise_sec;
    int set_mday, set_month, set_year, set_hour, set_min, set_sec;
    int first_mday, first_month, first_year;
    int risen = 0, set = 0;
    int second_not_verified = 0, conversions = 0;
    int total_sec = 0;
    int days_passed;
    int day, month, year, hour1, min1, sec1, hour2, min2, sec2;

    // Salva o primeiro dia
    scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &day, &month, &year, &hour1, &min1, &sec1, &hour2, &min2, &sec2);
    
    first_mday = day;
    first_month = month;
    first_year = year;

    do{
        if (!risen && hour1 != 99){
            // Se o sol está nascendo em hour1
            rise_sec = sec1;
            rise_min = min1;
            rise_hour = hour1;
            rise_mday = day;
            rise_month = month;
            rise_year = year;

            risen = 1;

            if (hour2 != 99){
                // Se o Sol está se pondo em hour2
                set_sec = sec2;
                set_min = min2;
                set_hour = hour2;
                set_mday = day;
                set_month = month;
                set_year = year;

                set = 1;
            }
        }

        else if (!risen && hour1 == 99 && hour2 != 99){
            // Se o sol está nascendo em hour2
            rise_sec = sec2;
            rise_min = min2;
            rise_hour = hour2;
            rise_mday = day;
            rise_month = month;
            rise_year = year;

            risen = 1;
        }

        else if (risen && hour1 != 99){
            // Se o sol está se pondo em hour1
            rise_sec = sec1;
            rise_min = min1;
            rise_hour = hour1;
            rise_mday = day;
            rise_month = month;
            rise_year = year;

            set = 1;
            second_not_verified = 1;
        }

        else if (risen && hour1 == 99 && hour2 != 99){
            // Se o sol está se pondo em hour2
            set_sec = sec2;
            set_min = min2;
            set_hour = hour2;
            set_mday = day;
            set_month = month;
            set_year = year;

            set = 1;
        }

        if (risen && set){
            /* Se o sol já nasceu e já se pôs, calculo o lapso de tempo entre esses dois horários, 
               em segundos, e somo-o em total_sec */

            total_sec += calc_timelapse(rise_year, rise_month, rise_mday, rise_hour, rise_min, rise_sec,
            set_year, set_month, set_mday, set_hour, set_min, set_sec);

            if (rise_hour > set_hour ||
                (rise_hour == set_hour && rise_min > set_min) ||
                (rise_hour == set_hour && rise_min == set_min && rise_sec >= set_sec)
                ){
                    total_sec += 86400;
                }
            
            risen = set = 0;            
        }

        if (second_not_verified){
            second_not_verified = 0;
            if (hour2 != 99){
                // Se hour2 for um horário válido
                rise_sec = sec2;
                rise_min = min2;
                rise_hour = hour2;
                rise_mday = day;
                rise_month = month;
                rise_year = year;
                
                risen = 1;
            }
        }
    } while ((conversions = scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &day, &month, &year, &hour1,
             &min1, &sec1, &hour2, &min2, &sec2)) != EOF && conversions == 9);

    days_passed = (int) (total_sec / SECONDS_IN_12H);

    for (int i = 0; i < days_passed; i++){
        // Aumenta o dia inicial um tanto de vezes correpondente a quantos dias se passaram.
        next_day(&first_year, &first_month, &first_mday);
    }

    printf("%d/%d/%d\n", first_mday, first_month, first_year);

    return 0;
}


int is_leap_year(int year){
    // Retorna 1 se o ano for bissexto e 0 caso contrário.

    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))? 1 : 0;
}


int calc_timelapse(int year1, int month1, int mday1, int hour1, int min1, int sec1,
                   int year2, int month2, int mday2, int hour2, int min2, int sec2){
    // Calcula o número de segundos corridos entre dois horários.

    int number_of_days = 0;
    int num_sec, sec_day1, sec_day2;
    int year = year1, month = month1, mday = mday1;
    while (mday < mday2 || month < month2 || year < year2){
        number_of_days += 1;
        next_day(&year, &month, &mday);
    }

    sec_day1 = 3600 * hour1 + 60 * min1 + sec1;
    sec_day2 = 3600 * hour2 + 60 * min2 + sec2;
    num_sec = 86400 * number_of_days + (sec_day2 - sec_day1);

    return num_sec;
}


void next_day(int* year, int* month, int* mday){
    /* Recebe três inteiros, correpondentes a um dia, um mês e um ano, e modifica
    esses números para a data corresponde ao dia seguinte*/

    if (is_leap_year(*year)){
        if (*mday < months_leap_year[*month - 1]){
            // Se não for o último dia do mês
            *mday += 1;
        }
        else if (*mday == months_leap_year[*month - 1] && *month < 12){
            // Se for o último dia do mês, mas não do ano
            *mday = 1;
            *month += 1;
        }
        else if (*mday == months_leap_year[*month - 1] && *month == 12){
            // Se for o último dia do ano
            *mday = 1;
            *month = 1;
            *year += 1;
        }
    }

    else{
        if (*mday < months_nonleap_year[*month - 1]){
            // Se não for o último dia do mês
            *mday += 1;
        }
        else if (*mday == months_nonleap_year[*month - 1] && *month < 12){
            // Se for o último dia do mês, mas não do ano
            *mday = 1;
            *month += 1;
        }
        else if (*mday == months_nonleap_year[*month - 1] && *month == 12){
            // Se for o último dia do ano
            *mday = 1;
            *month = 1;
            *year += 1;
        }
    }
}