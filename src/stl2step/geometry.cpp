/**
 * \file
 *
 * \brief Файл с определениями функций классов геометрических примитивов
 */

#include "stdafx.h"
#include "precision.h"
#include "geometry.h"

namespace geometry {

//  void vector::print(void) const {
//    std::cout << "(" << X << " " << Y << " " << Z << ")";
//  }

  std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << "(" << v.getX() << " " << v.getY() << " " << v.getZ() << ")";
    return os;
  }

  bool vector::operator==(const vector& v) const {
    return is_equal(v, EPSILON_X);
  }

  bool vector::is_equal(const vector& v, double epsilon) const {
    return (fabs(this->X - v.X) < epsilon) && (fabs(this->Y - v.Y) < epsilon) && (fabs(this->Z - v.Z) < epsilon);
  }

  bool vector::is_null(double epsilon) {
    return fabs(this->X) < epsilon && fabs(this->Y) < epsilon && fabs(this->Z) < epsilon;
  }

  bool vector::operator!=(const vector& v) const {
    return !(*this == v);
  }

  bool vector::operator<(const vector& v) const {
    if (X < v.X) return true;
    if (X > v.X) return false;
    if (Y < v.Y) return true;
    if (Y > v.Y) return false;
    if (Z < v.Z) return true;
    if (Z > v.Z) return false;
    /** Если все координаты равны */
    return false;
  }

  vector& vector::operator+=(const vector& v) {
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
  }

  vector& vector::operator-=(const vector& v) {
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
  }

  vector vector::operator-(const vector& v) const {
    return vector(X - v.X, Y - v.Y, Z - v.Z);
  }

  vector& vector::operator/=(double d) {
    X /= d;
    Y /= d;
    Z /= d;
    return *this;
  }

  vector vector::operator*(const vector& v) const {
    return vector(v.Y * Z - v.Z * Y, v.Z * X - v.X * Z, v.X * Y - v.Y * X);
  }

  double vector::scalar(const vector& v) const {
    return X * v.X + Y * v.Y + Z * v.Z;
  }

  vector vector::normalize(void) const {
    double length = sqrt(X * X + Y * Y + Z * Z);
    return vector(X / length, Y / length, Z / length);
  }

  double vector::mix(const vector& v1, const vector& v2, const vector& v3) {
    /** скалярное произведение вектора v1 на векторное произведение векторов v2 и v3 */
    return v1.scalar(v2 * v3);
  }

  bool vector::check_4_points_in_plane(const vector& p0, const vector& p1, const vector& p2, const vector& p3, double epsilon) {
    /** Проверка: смешанное произведение векторов равно нулю? */
    return fabs(mix(vector(p0, p1), vector(p0, p2), vector(p0, p3))) < epsilon;
  }

  bool vector::check_collinear(const vector& v1, const vector& v2, double epsilon) {
    /** Проверка: векторное произведение - это нулевой вектор? */
    return (v1 * v2).is_null(epsilon);
  }

  bool vector::check_3_points_in_line(const vector& p0, const vector& p1, const vector& p2, double epsilon) {
    /** Проверка: вектора p1-p2 и p2-p3 коллинеарны? */
    return check_collinear(vector(p0, p1), vector(p0, p2), epsilon);
  }
}
