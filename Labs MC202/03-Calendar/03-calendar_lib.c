#include <stdio.h>
#include <time.h>
#define SECONDS_IN_12H 43200

int main(void){
    struct tm rise_time, set_time, actual_day;
    int risen = 0, set = 0;
    int second_not_verified = 0, conversions = 0;
    double total_sec = 0.0;
    int day, month, year, hour1, min1, sec1, hour2, min2, sec2;

    // Salva o primeiro dia
    scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &day, &month, &year, &hour1, &min1, &sec1, &hour2, &min2, &sec2);
    actual_day.tm_sec = sec1;
    actual_day.tm_min = min1;
    actual_day.tm_hour = hour1;
    actual_day.tm_mday = day;
    actual_day.tm_mon = month - 1;
    actual_day.tm_year = year - 1900;

    do{
        if (!risen && hour1 != 99){
            // Se o sol está nascendo em hour1
            rise_time.tm_sec = sec1;
            rise_time.tm_min = min1;
            rise_time.tm_hour = hour1;
            rise_time.tm_mday = day;
            rise_time.tm_mon = month - 1;
            rise_time.tm_year = year - 1900;

            risen = 1;

            if (hour2 != 99){
                // Se o Sol está se pondo em hour2
                set_time.tm_sec = sec2;
                set_time.tm_min = min2;
                set_time.tm_hour = hour2;
                set_time.tm_mday = day;
                set_time.tm_mon = month - 1;
                set_time.tm_year = year - 1900;

                set = 1;
            }
        }

        else if (!risen && hour1 == 99 && hour2 != 99){
            // Se o sol está nascendo em hour2
            rise_time.tm_sec = sec2;
            rise_time.tm_min = min2;
            rise_time.tm_hour = hour2;
            rise_time.tm_mday = day;
            rise_time.tm_mon = month - 1;
            rise_time.tm_year = year - 1900;

            risen = 1;
        }

        else if (risen && hour1 != 99){
            // Se o sol está se pondo em hour1
            rise_time.tm_sec = sec1;
            rise_time.tm_min = min1;
            rise_time.tm_hour = hour1;
            rise_time.tm_mday = day;
            rise_time.tm_mon = month - 1;
            rise_time.tm_year = year - 1900;

            set = 1;
            second_not_verified = 1;
        }

        else if (risen && hour1 == 99 && hour2 != 99){
            // Se o sol está se pondo em hour2
            set_time.tm_sec = sec2;
            set_time.tm_min = min2;
            set_time.tm_hour = hour2;
            set_time.tm_mday = day;
            set_time.tm_mon = month - 1;
            set_time.tm_year = year - 1900;

            set = 1;
        }

        if (risen && set){
            /* Se o sol já nasceu e já se pôs, calculo o lapso de tempo entre esses dois horários, 
               em segundos, e somo-o em total_sec */
            if (rise_time.tm_hour > set_time.tm_hour ||
                (rise_time.tm_hour == set_time.tm_hour && rise_time.tm_min > set_time.tm_min) ||
                (rise_time.tm_hour == set_time.tm_hour && rise_time.tm_min == set_time.tm_min && rise_time.tm_sec >= set_time.tm_sec)
                ){
                    set_time.tm_mday += 1;
                }
            total_sec += difftime(mktime(&set_time), mktime(&rise_time));
            risen = set = 0;            
        }

        if (second_not_verified){
            second_not_verified = 0;
            if (hour2 != 99){
                // Se hour2 for um horário válido
                rise_time.tm_sec = sec2;
                rise_time.tm_min = min2;
                rise_time.tm_hour = hour2;
                rise_time.tm_mday = day;
                rise_time.tm_mon = month - 1;
                rise_time.tm_year = year - 1900;
                
                risen = 1;
            }
        }
    } while ((conversions = scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &day, &month, &year, &hour1,
             &min1, &sec1, &hour2, &min2, &sec2)) != EOF && conversions == 9);

    actual_day.tm_mday += (int) (total_sec / SECONDS_IN_12H);
    mktime(&actual_day);
    printf("%d/%d/%d\n", actual_day.tm_mday, actual_day.tm_mon + 1, actual_day.tm_year + 1900);

    return 0;
}