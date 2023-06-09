/**
 * \file
 *
 * \brief Точность выполнения операций
 */

#ifndef _PRECISION_H
#define _PRECISION_H

/**
 * \defgroup precision Точность выполнения операций сравнения
 * \ingroup infrastructure
 * \{
 */

/** Точность сравнения координат, она же погрешность измерения длины, указанная в файле STEP */
#define EPSILON_X   1.E-7
/** Точность сравнения нормалей граней (определение, лежат ли треугольники в одной плоскости) */
#define EPSILON_Y   8.E-3
/** Точность сравнения координат при поиске клонов */
#define EPSILON_C   1.E-4

/**
 * \}
 */

#endif /* _PRECISION_H */