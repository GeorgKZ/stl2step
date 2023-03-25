/**
 * \file
 *
 * \brief Файл с определениями классов трёхмерных фигур
 *
 * Классы из этого файла используются для описания трёхмерных фигур.
 * Это вершины, рёбра, границы, грани, фигуры. Классы этих примитивов содержат списки
 * индексов, позволяющих обращаться к элементам из связанных классов.
 * Такие списки индексов позволяют осуществлять эффективные операции
 * со списками примитивив, не прибегая к сравнению
 * "каждый с каждым", приводящему к квадратичной сложности операций.
 */

#ifndef _SHELL_H
#define _SHELL_H

#include "err.h"
#include "geometry.h"

namespace prim3d {

  /**
   * \brief Базовый класс для геометрических примитивов.
   *
   */
  class primitive {

  private:

    /** метка (указатель), которой будет отмечен этот примитив. */
    mutable const void* mark;

  public:

    /**
     * \brief Конструктор по умолчанию.
     *
     */
    primitive() : mark(nullptr) {}

    /**
     * \brief Пометить примитив меткой.
     *
     * \param [in] ptr метка(указатель), которой будет отмечен примитив
     */
    void set_mark(const void* ptr) const {
      mark = ptr;
    }

    /**
     * \brief Снять с примитива метку.
     *
     */
    void reset_mark() const {
      mark = nullptr;
    }

    /**
     * \brief Проверить, помечен ли примитив.
     * \return true, если отмечен и false, если нет
     */
    bool is_marked() const {
      return mark != nullptr;
    }

    /**
     * \brief Получить указатель на метку, котрой помечен примитив.
     * \return указатель на метку, которой был отмечен примитив, или nullptr, если этого не было
     */
    const void* get_mark() const {
      return mark;
    }

  };

  class edge;
  class face;
  class shell;

  /**
   * \brief Вершина
   */
  class vertex : public primitive {

  private:


    /** координата вершины в простанстве. */
    geometry::vector                           coord;

    /** список указателей на грани фигуры, включающие данную вершину. */
    std::vector<const face*>         faces;
    /** список указателей на рёбра фигуры, включающим данную вершину. */
    std::vector<const edge*>         edges;

  public:

    /**
     * \brief Конструктор вершины по умолчанию.
     *
     */
    vertex() : coord() {}

    /**
     * \brief Конструктор вершины с установкой значения координаты.
     *
     * \param [in] v устанавливаемая координата вершины.
     */
    vertex(const geometry::vector& v) : coord(v) {}

    /**
     * \brief Получить координаты вершины
     * \return вектор, определяющий координаты вершины в пространстве.
     */
    const geometry::vector& get_coord() const { return coord; }

    /**
     * \brief Установить координаты вершины.
     * \param [in] v вектор, определяющий координаты вершины в пространстве.
     */
    void set_coord(const geometry::vector& v) { coord = v; }

    /**
     * \brief Выполнить сравнение координат вершин (равно)
     * \param [in] v вершина, с которой происходит сравнение
     * \return результат сравнения координат вершин
     */
    bool operator==(const vertex& v) const {
      return coord == v.coord;
    }

    /**
     * \brief Выполнить сравнение координат вершин (меньше)
     *
     * Такое сравнение нужно для выполнения однозначной
     * сортировки, которая используется, например, при
     * сравнении двух списков вершин.
     *
     * \param [in] v вершина, с которой происходит сравнение.
     * \return результат сравнения координат вершин.
     */
    bool operator<(const vertex& v) const { return coord < v.coord; }


    std::vector<const face*>::const_iterator faces_cbegin() const {
      return faces.cbegin();
    }

    std::vector<const face*>::const_iterator faces_cend() const {
      return faces.cend();
    }

    std::vector<const edge*>::const_iterator edges_cbegin() const {
      return edges.cbegin();
    }

    std::vector<const edge*>::const_iterator edges_cend() const {
      return edges.cend();
    }

    /**
     * \brief Добавить указатель на грань в список указателей на грани вершины.
     * \param [in] f указатель на грань из списка указателей на грани фигуры
     */
    void add_face(face* f) {
      faces.push_back(f);
    }

    void set_faces(const std::vector<const face*>& new_faces) {
      faces = new_faces;
    }

    /**
     * \brief Добавить указатель на ребро в список указателей на рёбра вершины.
     * \param [in] e указатель на ребро из списка указателей на ребра фигуры
     */
    void add_edge(edge* e) {
      edges.push_back(e);
    }

    /**
     * \brief Вывод информации о вершине
     */
    void print(const shell* s = nullptr) const;
  };

  /**
   * \brief Ребро.
   *
   * Ребро ссылается на две вершины. Направлением ребра считается
   * направление от начальной вершины к конечной.
   * Ребро всегда касается двух граней - левой и правой. Для левой грани
   * ребро всегда направлено в прямую сторону, а правой - в обратную.
   */
  class edge : public primitive {

  private:

    /** Указатель на вершину фигуры, соответствующую начальной вершине ребра */
    const vertex* start_vertex;
    /** Указатель на вершину фигуры, соответствующую конечной вершине ребра */
    const vertex* end_vertex;

    /** Индекс в списке граней фигуры, соответствующий левой грани ребра */
    const face* left_face;
    /** Индекс в списке граней фигуры, соответствующий правой грани ребра */
    const face* right_face;

  public:

    /**
     * \brief Конструктор.
     *
     */
    edge(const vertex* start, const vertex* end, const face* left, const face* right = nullptr) :
      start_vertex(start), end_vertex(end), left_face(left), right_face(right) {
    }

    const vertex* get_start() const { return start_vertex; }

    const vertex* get_end() const { return end_vertex; }

    const face* get_left() const { return left_face; }

    void set_left(const face* f) { left_face = f; }

    const face* get_right() const { return right_face; }

    void set_right(const face* f) { right_face = f; }

    /**
     * \brief Вывод информации о ребре.
     */
    void print(const shell* s = nullptr) const;
  };

  /**
   * \brief Направленное ребро.
   *
   * Так как ребро всегда принадлежит двум граням, оно входит в две границы,
   * принадлежащие двум разным граням. Для одной из границ ребро направлено
   * в прямую сторону, для другой - в обратную.
   */

  class oriented_edge {

  private:

    /** Индекс в списке рёбер фигуры */
    const edge* base_edge;
    /** Направление ребра */
    bool forward;

  public:

    oriented_edge(const edge* e, bool direction = true) : base_edge(e), forward(direction) {}

    const edge* get_base_edge() const {
      return base_edge;
    }

    bool get_direction() const {
      return forward;
    }

    void set(const edge* e, bool direction) {
      base_edge = e;
      forward = direction;
    }

    void print(const shell* s = nullptr) const {
      printf("(");
      base_edge->print(s);
      printf(" %s )", forward ? "direct" : "reverse");
    }
  };

  /**
   * \brief Граница.
   *
   * Грань имеет внешнюю границу и может иметь несколько внутренних,
   * соответствующих отверстиям в грани. Граница состоит из цепочки рёбер.
   */
  class border {

  private:

    /** Цепочка рёбер, образующих границу */
    std::vector<oriented_edge> edges;

  public:

    void add_edge(const oriented_edge& e) { edges.push_back(e); }

    std::vector<oriented_edge>::const_iterator edges_cbegin() const { return edges.cbegin(); }

    std::vector<oriented_edge>::const_iterator edges_cend() const { return edges.cend(); }

    std::vector<oriented_edge>::iterator edges_begin() { return edges.begin(); }

    std::vector<oriented_edge>::iterator edges_end() { return edges.end(); }

    size_t edges_size() const { return edges.size(); }

    std::vector<oriented_edge>::iterator remove(std::vector<oriented_edge>::iterator it) {
      return edges.erase(it);
    }

    void print(const shell* s = nullptr) const;
  };

  /**
   * \brief Грань.
   *
   * Грань имеет внешнюю границу и может иметь несколько внутренних,
   * соответствующих отверстиям в грани.
   */

  class face : public primitive {

  private:

    /** единичный вектор, определяющий нормаль грани. */
    geometry::vector normal;
    /** Список границ, образующих грань */
    std::vector<border> borders;

  public:

    /**
     * \brief Конструктор грани с установкой значения нормали.
     * \param [in] n присваемое нормали грани значение.
     */
    face(const geometry::vector& n) : normal(n) {}

    /**
     * \brief Получить вектор нормали грани
     * \return вектор нормали грани.
     */
    const geometry::vector& get_normal() const {
      return normal;
    }

    /**
     * \brief Добавить границу к списку границ грани.
     *
     */
    void add_border(const border& b) {
      borders.push_back(b);
    }

    /**
     * \brief Заменить список гранииц грани на указанный.
     *
     * \param [in] new_borders новый список границ грани
     */
    void set_borders(const std::vector<border>& new_borders) {
      borders = new_borders;
    }

    std::vector<border>::const_iterator borders_cbegin() const { return borders.cbegin(); }
    std::vector<border>::const_iterator borders_cend() const { return borders.cend(); }

    std::vector<border>::iterator borders_begin() { return borders.begin(); }
    std::vector<border>::iterator borders_end() { return borders.end(); }

    size_t borders_size() const { return borders.size(); }

    void print(const shell* s = nullptr) const;
  };

  /**
   * \brief Замкнутая трёхмерная фигура.
   *
   * Фигура содержит грани, рёбра и вершины, составляющие замкнутую оболочку.
   */
  class shell : public primitive {

  private:

    /** \brief Вершины, входящие в фигуру */
    std::vector<vertex*> vertexes;

    /** \brief Рёбра, входящие в фигуру */
    std::vector<edge*> edges;

    /** \brief Грани, образующие фигуру */
    std::vector<face*> faces;

    /** \brief Координаты условного центра фигуры */
    geometry::vector pos;

    /** \brief Указатель на фигуру, клоном которй является данная фигура, или nullptr */
    const shell* clone;

  public:

    /**
     * \brief Конструктор фигуры по умолчанию.
     *
     */
    shell() : clone(nullptr) {}

    /**
     * \brief Конструктор фигуры на основе списка граней
     *
     * \param [in] stlf список векторов (4 вектора на грань - нормаль и три вершины).
     */
    shell(const std::vector<geometry::vector>& stlf);

    /** \brief Деструктор фигуры */
    ~shell() {
      for (auto it = vertexes.cbegin(); it != vertexes.cend(); ++it) {
        delete(*it);
      }
      for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
        delete(*it);
      }
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        delete(*it);
      }
    }

    std::vector<vertex*>::const_iterator vertexes_cbegin() const {
      return vertexes.cbegin();
    }

    std::vector<vertex*>::const_iterator vertexes_cend() const {
      return vertexes.cend();
    }

    size_t vertexes_size() const { return vertexes.size(); }

    std::vector<edge*>::const_iterator edges_cbegin() const {
      return edges.cbegin();
    }

    std::vector<edge*>::const_iterator edges_cend() const {
      return edges.cend();
    }

    size_t edges_size() const { return edges.size(); }

    std::vector<face*>::const_iterator faces_cbegin() const {
      return faces.cbegin();
    }

    std::vector<face*>::const_iterator faces_cend() const {
      return faces.cend();
    }

    size_t faces_size() const { return faces.size(); }

    const geometry::vector& get_pos() const { return pos; }

    void unmark_vertexes() const {
      for (auto it = vertexes.cbegin(); it != vertexes.cend(); ++it) (*it)->reset_mark();
    }

    void unmark_edges() const {
      for (auto it = edges.cbegin(); it != edges.cend(); ++it) (*it)->reset_mark();
    }

    void unmark_faces() const {
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) (*it)->reset_mark();
    }

    /**
     * \brief Удалить лишнюю половину рёбер.
     *
     * Из пары одинаковых, но встречно направленных рёбер оставить
     * только одно ребро. Одновременно привести в соответствие списки
     * ориентированных рёбер, ссылающихся на рёбра.
     *
     * \return код ошибки.
     */
    err_enum_t merge_edges();

    /**
     * \brief Приведение координат вершин фигуры к условному центру.
     *
     * Операция, заключающаяся в вычислении координат условного центра,
     * как среднего арифметического координат вершин фигуры, и вычитании
     * этих координат из координат всех вершин для превращения их в относительные.
     * Эту операцию необходимо выполнять для всех фигур перед началом выявления
     * клонов в списке фигур. Также выполняется сортировка списка вершин.
     */
    void normalize_shell();

    /**
     * \brief Сравнение фигур.
     *
     * \param [in] s фигура, с которой происходит сравнение
     * \return результат сравнения фигур
     */
    bool operator==(const shell& s) const;

    /**
     * \brief Установить указатель на фигуру, клоном которой являеся данная.
     * \param [in] ptr указатель на фигуру, клоном которой являеся данная.
     */
    void set_clone(const shell* ptr) {
      clone = ptr;
    }

    /**
     * \brief Получить указатель на фигуру, клоном которой являеся данная.
     * \return указатель на фигуру, клоном которой являеся данная или nullptr.
     */
    const shell* get_clone() const {
      return clone;
    }

    /**
     * \brief Проверить, является ли фигура клоном другой фигуры
     * \return true, если фигура является клоном другой фигуры, и false в протиыном случае.
     */
    bool is_clone() const { return clone != nullptr; }


    /**
     * \brief Разделить грани фигуры по не связанным фигурам
     * \return список фигур.
     *
     * Распределить грани из списка фигуры по отдельным фигурам,
     * создать и заполнить внутренних структур новых фигур.
     * Из исходной фигуры разобранные по новым фигурам
     * примитивы удаляются.
     *
     */
    std::vector<shell*> separate();

    /**
     * \brief Создать отдельную фигуру, состоящую из отмеченных граней
     * \param [in] mark указатель на метку, которой отмечены грани.
     * \return фигуру из отмеченных граней.
     *
     * Из исходной фигуры перенесённые в новую фигуру примитивы удаляются.
     *
     */
    shell* split(const void* mark);

    /**
     * \brief Объединить треугольные грани в многоугольные
     * \param [in] debug выводить отладочную информацию.
     * \return код ошибки.
     */
    err_enum_t merge_faces(bool debug);

    /**
     * \brief Удалить избыточные рёбра в многоугольных гранях
     *
     * \param [in] debug выводить отладочную информацию
     * \return код ошибки
     */
    err_enum_t reduce_edges(bool debug);


    /**
     * \brief Упорядочить рёбра в границы
     *
     * Разобрать рёбра, наполняющие единственную границу,
     * по нескольком (при необходимости) границам, выстраивая
     * из них замкнутую цепочку.
     *
     * \param [in] debug выводить отладочную информацию
     * \return код ошибки
     */
    err_enum_t split_edges_to_borders(bool debug);

    void print() const { printf("Shell: %zu vertexes, %zu edges, %zu faces\n", vertexes.size(), edges.size(), faces.size()); }
  };

  /**
   * \brief Импорт информации о треугольниках из файла STL.
   *
   * \param [in] fname имя импортируемого файла
   * \param [out] faces список треугольных граней (4 вектора на грань - нормаль и три вершины)
   * \return в случае ошибки - код ошибки ERROR_FILE_IO или ERROR_IMPORT, в случае успешного импорта ERROR_OK
   */
  err_enum_t import(const std::string& fname, std::vector<geometry::vector>& faces);

}

#endif /* _SHELL_H */
