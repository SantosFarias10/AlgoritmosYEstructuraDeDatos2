#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "array_helpers.h"

/**
 * @brief Calcula la menor temperatura minima historica registrada
 * @details Analiza el array, especificamente a[y][m][j]._min_temp buscando la menor temperatura minima y guardandola en la variable min
 * @param[in] a es un array del tipo abstracto WeatherTable
 * @return La variable min con la menor temperatura minima del arreglo a
*/
int temp_min(WeatherTable a);

/**
 * @brief Guarda todas las mayores temperaturas maximas del arreglo en otro arreglo
 * @details Del arreglo a compara todas las mayores temperaturas maximas de cada anio y guardandolas en el arreglo maxs
 * @param[in] a Arreglo del tipo abstracto WeatherTable
 * @param[in] maxs Arreglo de enteros donde guardaremos los resultados
 * @return El arreglo maxs con todas las mayores temperaturas maximas de cada anio
*/
void temps_maxs_totales(WeatherTable a, int maxs[YEARS]);

/**
 * @brief Calcula el mes con mas precipitaciones de cada anio
 * @details Suma las precipitaciones de cada dia del mismo mes para despues comparar cada mes y este mes con mas precipitaciones guardarlo en el arreglo maxs, asi quedando refistrado cual fue el mes con mas precipitaciones de cada anio
 * @param[in] a Arreglo del tipo abstracto WeatherTable
 * @param[in] maxs Arreglo de enteros donde guardaremos los resultados
 * @return El arreglo maxs con todos los meses de cada anio con mas precipitaciones
*/
void precips_maxs_mensuales(WeatherTable a, month_t maxs[YEARS]);

#endif