#include <limits.h>

#include "weather_utils.h"

int temp_min(WeatherTable a){
    int min = INT_MAX;

    for (unsigned int y = 0; y < YEARS; y++){
        for (month_t m = january; m < MONTHS; m++){
            for (unsigned int d = 0; d < DAYS; d++){
                if (min > a[y][m][d]._min_temp){
                    min = a[y][m][d]._min_temp;
                }
            }
        }
    }
    return min;
}

void temps_maxs_totales(WeatherTable a, int maxs[YEARS]){
    int max;

    for (unsigned int year = 0; year < YEARS; year++){
        max = INT_MIN;
        for (month_t m = january; m < MONTHS; m++){
            for (unsigned int d = 0; d < DAYS; d++){
                if(max < a[year][m][d]._max_temp){
                    max = a[year][m][d]._max_temp;
                }
            }       
        }
        maxs[year] = max;    
    }
}

void precips_maxs_mensuales(WeatherTable a, month_t maxs[YEARS]){
    unsigned int sum_prec = 0u;
    unsigned int max = 0u;
    month_t mes;
    
    for (unsigned int y = 0; y < YEARS; y++){
        max = 0u;
        for (month_t m = january; m < MONTHS; m++){
            sum_prec = 0u;
            for (unsigned int d = 0; d < DAYS; d++){
                sum_prec = sum_prec + a[y][m][d]._rainfall;
            }
            if (max < sum_prec){
                max = sum_prec;
                mes = m;
            }
        }
        maxs[y] = mes;
    }
}