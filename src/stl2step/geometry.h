/**
 * \file
 *
 * \brief Заголовочный файл с объявлениями классов геометрических примитивов
 */

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

namespace geometry {

  /**
   * \brief Вектор.
   */
  class vector {

  private:

    double X, Y, Z, W;

  public:

    /**
    * \brief Конструктор вектора по умолчанию (нулевого вектора).
    */
    vector() { X = 0.0; Y = 0.0; Z = 0.0; W = 1.0; }

    /**
    * \brief Конструктор вектора от координаты 'a' к координате 'b'.
    *
    * \param [in] a координаты начальной точки вектора
    * \param [in] b координаты конечной точки вектоа
    */
    vector(const vector& a, const vector& b) {
      X = b.X - a.X;
      Y = b.Y - a.Y;
      Z = b.Z - a.Z;
      W = 1.0;
    }

    /**
    * \brief Конструктор вектора по трём координатам.
    *
    * \param [in] x координата X
    * \param [in] y координата Y
    * \param [in] z координата Z
    */
    vector(double x, double y, double z) {
      X = x;
      Y = y;
      Z = z;
      W = 1.0;
    }

//    /**
//     * \brief Отладочный вывод значения вектора.
//     */
//    void print(void) const;

    /**
     * \brief Потоковый вывод значения вектора.
     */
    friend std::ostream& operator<<(std::ostream& os, const vector& v);

    /**
     * \brief Проверка: равенство координат (векторов) с точностью EPSILON_X.
     *
     * \param [in] v вектор, с которым производится сравнение
     * \return true, если разница всех координат векторов меньше точноcти, false в противном случае
     */
    bool operator==(const vector& v) const;

    /**
     * \brief Проверка: равенство координат (векторов) с указанной точностью.
     *
     * \param [in] v вектор, с которым производится сравнение
     * \param [in] epsilon точность, с которой производится сравнение
     * \return true, если разница всех координат векторов меньше точноcти, false в противном случае
     */
    bool is_equal(const vector& v, double epsilon) const;

    /**
     * \brief Проверка: неравенство координат (векторов) с точностью по умолчанию.
     *
     * \param [in] v вектор, с которым производится сравнение
     * \return false, если разница всех координат векторов меньше или равна точноcти, true в противном случае
     */
    bool operator!=(const vector& v) const;

    /**
     * \brief Сравнение векторов (условное, только для выполнения однозначной сортировки).
     *
     * \param [in] v вектор, с которым производится сравнение
     * \return true, если объект условно меньше вектора 'v'
     */
    bool operator<(const vector& v) const;

    // Сложение с вектором
    vector& operator+=(const vector& v);

    // Вычитание вектора
    vector& operator-=(const vector& v);

    vector operator-(const vector& v) const;

    // Деление на число
    vector& operator/=(double d);

    // Векторное произведение
    vector operator*(const vector& v) const;

    // Скалярное произведение
    double scalar(const vector& v) const;

    // Расстояние между векторами
    double distance(const vector& v) const { vector t(*this); t -= v; return t.module(); }

    /**
     * Рассчитать значение модуля вектора.
     *
     * \return значение модуля вектора
     */
    double module(void) const { return sqrt(X * X + Y * Y + Z * Z); }

    /**
     * Рассчитать угол между векторами.
     *
     * \param [in] v вектор, угол с которым требуется рассчитать
     * \return число - угол между объектом и вектором 'v'
     */
    double angle(const vector& v) const { return acos(this->scalar(v) / (this->module() * v.module())); }

    /**
     * Нормализовать вектор.
     *
     * \return нормализованный вектор
     */
    vector normalize(void) const;

    /**
     * Проверка: является ли вектор нулевым (с указанной точностью).
     *
     * \param [in] epsilon точность, с которой производится сравнение
     * \return true, если вектор нулевой с указанной точностью.
     */
    bool is_null(double epsilon);

    /**
     * Получить координату X вектора.
     *
     * \return координату X вектора
     */
    double getX(void) const { return X; }

    /**
     * Получить координату Y вектора.
     *
     * \return координату Y вектора
     */
    double getY(void) const { return Y; }

    /**
     * Получить координату Z вектора.
     *
     * \return координату Z вектора
     */
    double getZ(void) const { return Z; }

    /**
     * \brief Смешанное произведение векторов p1, p2 и p3.
     *
     * \param [in] v1 первый вектор
     * \param [in] v2 второй вектор
     * \param [in] v3 третий вектор
     * \return число - результат смешанного произведения векторов
     */
    static double mix(const vector& v1, const vector& v2, const vector& v3);

    /**
     * Проверка: лежат ли четыре точки в одной плоскости (с указанной точночтью)?
     *
     * \param [in] p0 координаты первой точки
     * \param [in] p1 координаты второй точки
     * \param [in] p2 координаты третьей точки
     * \param [in] p3 координаты четвёртой точки
     * \param [in] epsilon точность, с которой производится сравнение
     * \return
     */
    static bool check_4_points_in_plane(const vector& p0, const vector& p1, const vector& p2, const vector& p3, double epsilon);

    /**
     * Проверка: два вектора коллинеарны (с указанной точночтью)?
     *
     * \param [in] v1 первый вектор
     * \param [in] v2 второй вектор
     * \param [in] epsilon точность, с которой производится сравнение
     * \return true, если векторы коллинеарны с указанной точночтью, и false в противном случае
     */
    static bool check_collinear(const vector& v1, const vector& v2, double epsilon);

    /**
     * Проверка: лежат ли три точки на линии (с указанной точночтью)?
     *
     * \param [in] p0 координаты первой точки
     * \param [in] p1 координаты второй точки
     * \param [in] p2 координаты третьей точки
     * \param [in] epsilon точность, с которой производится сравнение
     * \return true, если три точки лежат на одной линии с указанной точночтью, и false в противном случае
     */
    static bool check_3_points_in_line(const vector& p0, const vector& p1, const vector& p2, double epsilon);
  };

}

#endif /* _GEOMETRY_H */
