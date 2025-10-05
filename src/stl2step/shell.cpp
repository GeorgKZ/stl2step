/**
 * \file
 *
 * \brief Файл с определениями методов классов трёхмерных фигур
 *
 * <BR>
 */

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"

/** \brief Ширина выводимого в отладочных сообшениях числа (номера грани, ребра и т.д.) */
#define PRINT_WIDTH 4

namespace prim3d {

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::primitive "primitive":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::primitive::primitive()
   */
  primitive::primitive() : mark(nullptr) {
  }

  /**
   * \file
   * * \copybrief prim3d::primitive::set_mark(const void*) const
   */
  void prim3d::primitive::set_mark(const void* ptr) const {
    mark = ptr;
  }

  /**
   * \file
   * * \copybrief prim3d::primitive::reset_mark() const
   */
  void prim3d::primitive::reset_mark() const {
    mark = nullptr;
  }

  /**
   * \file
   * * \copybrief prim3d::primitive::is_marked() const
   */
  bool prim3d::primitive::is_marked() const {
    return mark != nullptr;
  }

  /**
   * \file
   * * \copybrief prim3d::primitive::get_mark() const
   */
  const void* prim3d::primitive::get_mark() const {
    return mark;
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::vertex "vertex":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::vertex::vertex()
   */
  vertex::vertex() : coord() {
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::vertex(const geometry::vector&)
   */
  vertex::vertex(const geometry::vector& v) : coord(v) {
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::get_coord() const
   */
  const geometry::vector& vertex::get_coord() const {
    return coord;
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::set_coord(const geometry::vector&)
   */
  void vertex::set_coord(const geometry::vector& v) {
    coord = v;
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::operator==(const prim3d::vertex& v) const
   */
  bool vertex::operator==(const vertex& v) const {
    return coord == v.coord;
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::operator<(const prim3d::vertex& v) const
   */
  bool vertex::operator<(const vertex& v) const {
    return coord < v.coord;
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::add_edge(prim3d::edge*)
   */
  void vertex::add_edge(edge* e) {
    edges.push_back(e);
  }

  /**
   * \file
   * * \copybrief prim3d::vertex::print(const prim3d::shell*) const
   */
  std::string vertex::print(const shell* s) const {
    std::stringstream ss;

    ss << (is_marked() ?  "<M>" : "< >");
    if (s != nullptr) {
      ss << "vertex#" << std::setw(PRINT_WIDTH) << std::distance(s->get_vertexes().cbegin(), std::find(s->get_vertexes().cbegin(), s->get_vertexes().cend(), this)) + 1;
    } else {
      ss << coord;
    }
    return ss.str();
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::edge "edge":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::edge::edge(const prim3d::vertex*, const prim3d::vertex*, const prim3d::face*)
   */
  edge::edge(const vertex* start, const vertex* end, const face* left) :
    start_vertex(start), end_vertex(end), left_face(left), right_face(nullptr) {
  }

  /**
   * \file
   * * \copybrief prim3d::edge::get_start() const
   */
  const vertex* edge::get_start() const {
    return start_vertex;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::get_end() const
   */
  const vertex* edge::get_end() const {
    return end_vertex;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::get_left() const
   */
  const face* edge::get_left() const {
    return left_face;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::set_left(const prim3d::face*)
   */
  void edge::set_left(const face* f) {
    left_face = f;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::get_right() const
   */
  const face* edge::get_right() const {
    return right_face;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::set_right(const prim3d::face*)
   */
  void edge::set_right(const face* f) {
    right_face = f;
  }

  /**
   * \file
   * * \copybrief prim3d::edge::print(const prim3d::shell*) const
   */
  void edge::print(const shell* s) const {
    std::cout << "        ";
    if (is_marked()) std::cout << "<M>"; else std::cout << "< >";
    if (s) {
      auto found = std::find(s->get_edges().cbegin(), s->get_edges().cend(), this);
      if (found == s->get_edges().cend()) {
        std::cout << "edge #**** ";
      } else {
        std::cout << "edge #" << std::setw(PRINT_WIDTH) << std::distance(s->get_edges().cbegin(), found) + 1 << " ";
      }
      std::cout << start_vertex->print(s) << "->" << end_vertex->print(s);

      if (left_face) {
        auto found = std::find(s->get_faces().cbegin(), s->get_faces().cend(), left_face);
        if (found == s->get_faces().cend()) {
          std::cout << " left face#****/";
        } else {
          std::cout << " left face#" << std::setw(PRINT_WIDTH) << std::distance(s->get_faces().cbegin(), found) + 1 << "/";
        }
      }
      else {
        std::cout   << " left face NO  /";
      }
      if (right_face) {
        auto found = std::find(s->get_faces().cbegin(), s->get_faces().cend(), right_face);
        if (found == s->get_faces().cend()) {
          std::cout << "right face#****/";
        } else {
          std::cout << "right face#" << std::setw(PRINT_WIDTH) << std::distance(s->get_faces().cbegin(), found) + 1;
        }
      }
      else {
        std::cout   << " right face NO  /";
      }
    }
    else {
      std::cout << start_vertex->print() << "->" << end_vertex->print();
    }
    std::cout << std::endl;
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::oriented_edge "oriented_edge":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::oriented_edge::oriented_edge(const prim3d::edge*, bool)
   */
  oriented_edge::oriented_edge(const edge* e, bool direction) :
    base_edge(e), forward(direction) {
  }

  /**
   * \file
   * * \copybrief prim3d::oriented_edge::get_base_edge() const
   */
  const edge* oriented_edge::get_base_edge() const {
    return base_edge;
  }

  /**
   * \file
   * * \copybrief prim3d::oriented_edge::get_direction() const
   */
  bool oriented_edge::get_direction() const {
    return forward;
  }

  /**
   * \file
   * * \copybrief prim3d::oriented_edge::set(const prim3d::edge*, bool)
   */
  void oriented_edge::set(const edge* e, bool direction) {
    base_edge = e;
    forward = direction;
  }

  /**
   * \file
   * * \copybrief prim3d::oriented_edge::print(const prim3d::shell*) const
   */
  void oriented_edge::print(const shell* s) const {
    std::cout << "      oriented edge " << (forward ? "direct" : "revers") << std::endl;
    base_edge->print(s);
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::border "border":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::border::add_edge(const prim3d::oriented_edge&)
   */
  void border::add_edge(const oriented_edge& e) {
    edges.push_back(e);
  }

  /**
   * \file
   * * \copybrief prim3d::border::get_edges() const
   */
  const std::vector<oriented_edge>& border::get_edges() const {
    return edges;
  }


  /**
   * \file
   * * \copybrief prim3d::border::edges_num() const
   */
  size_t border::edges_num() const {
    return edges.size();
  }

  /**
   * \file
   * * \copybrief prim3d::border::remove(std::vector<prim3d::oriented_edge>::iterator)
   */
  std::vector<oriented_edge>::iterator border::remove(std::vector<oriented_edge>::const_iterator it) {
    return edges.erase(it);
  }

  /**
   * \file
   * * \copybrief prim3d::border::print(const prim3d::shell*) const
   */
  void border::print(const shell* s) const {
    std::cout << "    border of " << edges.size() << " oriented edges" << std::endl;
    for (auto it_e = edges.cbegin(); it_e != edges.cend(); ++it_e) {
      (*it_e).print(s);
    }
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::face "face":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::face::face(const geometry::vector&)
   */
  face::face(const geometry::vector& n) : primitive(), normal(n) {
  }

  //!!!
  //bool face::operator==(const face& f) const;

  /**
   * \file
   * * \copybrief prim3d::face::get_normal() const
   */
  const geometry::vector& face::get_normal() const {
    return normal;
  }

  /**
   * \file
   * * \copybrief prim3d::face::add_border(const prim3d::border&)
   */
  void face::add_border(const border& b) {
    borders.push_back(b);
  }

  /**
   * \file
   * * \copybrief prim3d::face::set_borders(const std::vector<prim3d::border>&)
   */
  void face::set_borders(const std::vector<border>& new_borders) {
    borders = new_borders;
  }

  /**
   * \file
   * * \copybrief prim3d::face::get_borders() const
   */
  const std::vector<border>& face::get_borders() const {
    return borders;
  }

  /**
   * \file
   * * \copybrief prim3d::face::borders_num() const
   */
  size_t face::borders_num() const {
    return borders.size();
  }

  /**
   * \file
   * * \copybrief prim3d::face::print(const prim3d::shell*) const
   */
  void face::print(const shell* s) const {
    if (is_marked()) std::cout << "  <M>"; else std::cout << "< >";
    if (s == nullptr) {
      std::cout << "Normal " << normal;
    }
    else {
      auto found = std::find(s->get_faces().cbegin(), s->get_faces().cend(), this);
      if (found == s->get_faces().cend()) {
          std::cout << "face #****";
      } else {
          std::cout << "face #" << std::setw(PRINT_WIDTH) << std::distance(s->get_faces().cbegin(), found) + 1;
      }
    }
    std::cout << " of " << borders.size() << " borders" << std::endl;
    for (auto it_b = borders.cbegin(); it_b != borders.cend(); ++it_b) {
      (*it_b).print(s);
    }
  }

  /**
   * \file
   * Функции, являющиеся методами класса \ref prim3d::shell "shell":
   * <BR>
   */

  /**
   * \file
   * * \copybrief prim3d::shell::shell()
   */
  shell::shell() :
    clone(nullptr) {
  }

  /**
   * \file
   * * \copybrief prim3d::shell::shell(const std::vector<geometry::vector>& stlf)
   */
  shell::shell(const std::vector<geometry::vector>& stlf) : clone(nullptr) {
    // Перебор граней, наполнение взаимно индексированных списков вершин и рёбер
    for (auto it = stlf.cbegin(); it != stlf.cend();) {

      // Новая грань на основе нормали из грани
      face* f = new face(*it++);

      // Указатели трёх вершин грани
      vertex* ptr_vertex[3] = {};

      // Обработать три вершины грани
      for (auto i = 0; i < 3; ++i, ++it) {
        // Взять координаты текущей вершины текущей грани

        // Проверить, нет ли уже вершины с такими координатами в списке вершин фигуры
        std::vector<vertex*>::const_iterator it_sv;
        for (it_sv = vertexes.cbegin(); it_sv != vertexes.cend(); ++it_sv) {
          if ((*it_sv)->get_coord() == *it) break;
        }

        if (it_sv == vertexes.cend()) {
          // Такой вершины нет, создать её.
          ptr_vertex[i] = new vertex(*it);
          // Добавить вершину в список вершин фигуры
          vertexes.push_back(ptr_vertex[i]);
        }
        else {
          // Такая вершина есть.
          ptr_vertex[i] = *it_sv;
        }
        // Добавить указатель на грань в список указателей на грани вершины
//!!!	   ptr_vertex[i]->add_face(f);
      }

      // Первое ребро грани
      edge* e1 = new edge(ptr_vertex[0], ptr_vertex[1], f);
      edges.push_back(e1);
      // Второе ребро грани
      edge* e2 = new edge(ptr_vertex[1], ptr_vertex[2], f);
      edges.push_back(e2);
      // Третье ребро грани
      edge* e3 = new edge(ptr_vertex[2], ptr_vertex[0], f);
      edges.push_back(e3);

      // Добавить указатель на ребро в список указателей на рёбра вершины для 3х вершин
      ptr_vertex[0]->add_edge(e1); //-V525
      ptr_vertex[0]->add_edge(e3); //-V525
      ptr_vertex[1]->add_edge(e1); //-V525
      ptr_vertex[1]->add_edge(e2); //-V525
      ptr_vertex[2]->add_edge(e2); //-V525
      ptr_vertex[2]->add_edge(e3); //-V525

      // Граница грани
      border b;
      b.add_edge(oriented_edge(e1));
      b.add_edge(oriented_edge(e2));
      b.add_edge(oriented_edge(e3));

      // Добавить границу в список границ грани
      f->add_border(b);

      // Добавить новую грань в список граней фигуры
      faces.push_back(f);
    }
  }

  /**
   * \file
   * * \copybrief prim3d::shell::~shell()
   */
  shell::~shell() {
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

  /**
   * \file
   * * \copybrief prim3d::shell::get_vertexes() const
   */
  const std::vector<vertex*>& shell::get_vertexes() const {
    return vertexes;
  }


  /**
   * \file
   * * \copybrief prim3d::shell::vertexes_num() const
   */
  size_t shell::vertexes_num() const {
    return vertexes.size();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::get_edges() const
   */
  const std::vector<edge*>& shell::get_edges() const {
    return edges;
  }


  /**
   * \file
   * * \copybrief prim3d::shell::edges_num() const
   */
  size_t shell::edges_num() const {
    return edges.size();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::get_faces() const
   */
  const std::vector<face*>& shell::get_faces() const {
    return faces;
  }


  /**
   * \file
   * * \copybrief prim3d::shell::faces_num() const
   */
  size_t shell::faces_num() const {
    return faces.size();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::get_pos() const
   */
  const geometry::vector& shell::get_pos() const {
    return pos;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::unmark_vertexes() const
   */
  void shell::unmark_vertexes() const {
    for (auto it = vertexes.cbegin(); it != vertexes.cend(); ++it) (*it)->reset_mark();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::unmark_edges() const
   */
  void shell::unmark_edges() const {
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) (*it)->reset_mark();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::unmark_faces() const
   */
  void shell::unmark_faces() const {
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) (*it)->reset_mark();
  }

  /**
   * \file
   * * \copybrief prim3d::shell::merge_edges()
   */
  err_enum_t shell::merge_edges(bool debug) {

    /**
     * Алгоритм:
     *
     * <BR>
     */

    /**
     * 1 Снять пометки с рёбер, после чего перебрать все рёбра в списке рёбер фигуры и
     * пометить одно ребро из каждой пары встречных рёбер указателем на его встречную пару.
     */
    unmark_edges();
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {

      /** &nbsp;&nbsp;1.1 Пропустить уже помеченное ребро. */
      if ((*it)->is_marked()) continue;

      /**
       * &nbsp;&nbsp;1.2 Перебрать все рёбра, связанные с вершинами данного ребра...
       */
      auto v1 = (*it)->get_start();
      auto v2 = (*it)->get_end();

      const std::vector<const edge*>& v1_edge_list = v1->get_edges();
      for (auto it_e = v1_edge_list.cbegin(); it_e != v1_edge_list.cend(); ++it_e) {

        /** &nbsp;&nbsp;&nbsp;&nbsp;...кроме проверяемого ребра. */
        if (*it_e == *it) continue;

        /**
         * &nbsp;&nbsp;1.3 Проверить: ребра с такими же начальной и конечной вершиной
         * не должно существовать.
         */
        if ((*it_e)->get_start() == v1 && (*it_e)->get_end() == v2) {
          std::cout << "ERROR (merge_edges): в списке рёбер фигуры обнаружено ребро - копия существующего." << std::endl;
          if (debug) {
            std::cout << "У ребра #" << std::distance(edges.cbegin(), it) + 1 <<
              "найдена копия #" << std::distance(v1_edge_list.cbegin(), it_e) + 1 << std::endl;
          }
          return err_enum_t::ERROR_INTERNAL;
        }
        /**
         * &nbsp;&nbsp;1.4 Когда будет найдено встречное ребро,...
         */
        if ((*it_e)->get_start() == v2 && (*it_e)->get_end() == v1) {
          /**
           * &nbsp;&nbsp;&nbsp;&nbsp;...пометить его указателем на текущее ребро.
           */
          if (!(*it)->is_marked()) {
            (*it_e)->set_mark(*it);
          }
          else {
            /**
             * &nbsp;&nbsp;&nbsp;&nbsp;При этом найденное встречное ребро не должно быть помечено.
             */
            std::cout << "ERROR (merge_edges): в списке рёбер фигуры обнаружено помеченное обратное ребро" << std::endl;
            return err_enum_t::ERROR_INTERNAL;
          }
          break;
        }
      }
    }

    /**
     * 2 Перебрать все рёбра в списке фигуры, установить немаркированному ребру
     * значение правой грани из значения левой грани встречного помеченного ребра.
     */
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      /** Метка помеченного ребра - это указатель на встречное непомеченное ребро. */
      edge* e = static_cast<edge*>(const_cast<void*>((*it)->get_mark()));
      if (e != nullptr) {
        if (e->is_marked()) {
          /** Проверка: найденное встречное ребро не должно быть помечено. */
          std::cout << "ERROR (merge_edges): в списке рёбер фигуры обнаружено помеченное обратное ребро" << std::endl;
          return err_enum_t::ERROR_INTERNAL;
        }
        /**  Установить найденному встречному ребру значение правой грани. */
        e->set_right((*it)->get_left());
      }
    }

    /**
     * 3 Перебрать все направленные рёбра всех граней фигуры, указатели на помеченные рёбра
     * заменить указателями на парные им непомеченные рёбра.
     */

     /** Перебрать грани. */
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
      /** Перебрать границы грани. */
      for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
        /** Перебрать направленные рёбра границы грани. */
        for (auto it_e = (*it_b).get_edges().begin(); it_e != (*it_b).get_edges().end(); ++it_e) {
          /** Заменить помеченное ребро на встречное. */
          const edge* e = (*it_e).get_base_edge();
          if (e->is_marked()) {
            const edge* new_e = static_cast<const edge*>(e->get_mark());
            if ((*it_e).get_direction() != true) {
              /** Проверка: заменяемое направленное ребро должно идти в прямом направлении. */
              std::cout << "ERROR (merge_edges): found marked edge is not 'direct' but 'reverse'" << std::endl;
              return err_enum_t::ERROR_INTERNAL;
            }
            const_cast<oriented_edge*>(&(*it_e))->set(new_e, false);
          }
        }
      }
    }

    /**
     * 4 Удалить помеченные рёбра из списка рёбер фигуры.
     */

     /** Перебрать все помеченные рёбра в списке фигуры. */
    for (auto it = edges.cbegin(); it != edges.cend();) {
      if ((*it)->is_marked()) {
        /** Уничтожить объект-ребро. */
        delete* it;
        /** Удалить указатель на ребро из списка рёбер фигуры */
        it = edges.erase(it);
        continue;
      }
      ++it;
    }

    unmark_faces();
    unmark_edges();
    unmark_vertexes();

    return err_enum_t::ERROR_OK;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::normalize_shell()
   */
  void shell::normalize_shell() {

    pos = geometry::vector(0, 0, 0);

    /** Поиск условного центра (это не центр масс! Просто условный центр для возможности сравнения фигур) */
    for (auto it = vertexes.cbegin(); it != vertexes.cend(); ++it) {
      pos += (*it)->get_coord();
    }
    /** Условный центр - это среднее арифметическое всех координат  */
    pos /= static_cast<double>(vertexes.size());

    /** Вычитание координат условного центра из координат всех вершин */
    for (auto it = vertexes.begin(); it != vertexes.end(); ++it) {
      (*it)->set_coord((*it)->get_coord() - pos);
    }

    /** Сортировка списка указателей на вершины по координатам с лямбда-функцией */
    std::sort(vertexes.begin(), vertexes.end(), [](const vertex* a, const vertex* b) {return a->get_coord() < b->get_coord(); });
  }

  /**
   * \file
   * * \copybrief prim3d::shell::operator==(const prim3d::shell&) const
   */
  bool shell::operator==(const shell& s) const {

    /**
     * Алгоритм:
     * <BR>
     */

    /**
     * 1 Сравнить размеры списков граней, если они различны, то фигуры различаются;
     */
    if (faces.size() != s.faces.size()) {
      return false;
    }
    /**
     * 2 Сравнить размеры списков вершин, если они различны, то фигуры различаются;
     */
    if (vertexes.size() != s.vertexes.size()) {
      return false;
    }

    /**
     * 3 Сравнить координаты вершин из списка вершин с точностью EPSILON_C, если имеется хотя бы
     * одно отличие, то фигуры различаюся, если все совпадают, то фигуры равны. 
     */
    for (auto it1 = vertexes.cbegin(), it2 = s.vertexes.cbegin(); it1 != vertexes.cend(); ++it1, ++it2) {
      if (!(*it1)->get_coord().is_equal((*it2)->get_coord(), EPSILON_C)) return false;
    }
    return true;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::set_clone(const prim3d::shell*)
   */
  void shell::set_clone(const shell* ptr) {
    clone = ptr;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::get_clone() const
   */
  const shell* shell::get_clone() const {
    return clone;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::is_clone() const
   */
  bool shell::is_clone() const {
    return clone != nullptr;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::separate()
   */
  std::vector<shell*> shell::separate() {

    std::vector<shell*> Shells; // Фигуры

    /** Снять пометки с граней */
    unmark_faces();

    // Бесконечный цикл, пока есть "ничейные" грани
    for (;;) {
      /** Список указателей на новые грани, которые должны быть помечены */
      std::vector<const face*> new_faces;
      /** Список указателей на новые рёбра, которые должны быть помечены */
      std::vector<const edge*> new_edges;

      // Список указателей новых рёбер пустой
      // Добавляем в список указателей новых граней первую грань, не принадлежащую ни одной фигуре
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        if (!(*it)->is_marked()) {
          (*it)->set_mark(this);
          new_faces.push_back(*it);
          break;
        }
      }

      // Все грани принадлежат каким-то фигурам, большой цикл закончен.
      if (new_faces.empty()) break;

      // Бесконечный цикл, пока оба списка не пустые
      for (;;) {

        // Пустой список указателей рёбер новой фигупы будет наполнен по списку указателей граней новой фигуры
        new_edges.clear();

        // Перебор списка указателей граней новой фигуры
        for (auto it = new_faces.cbegin(); it != new_faces.cend(); ++it) {
          // Перебор границ
          for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
            const auto& b = *it_b; // Граница
            // Перебор рёбер
            for (auto it_e = b.get_edges().cbegin(); it_e != b.get_edges().cend(); ++it_e) {
              const auto& ce = *it_e;
              const auto& e = ce.get_base_edge();
              if (!e->is_marked()) {
                e->set_mark(this);
                new_edges.push_back(e);
              }
            }
          }
        }
        // Список указателей граней новой фигуры пустой - выходим
        if (new_edges.empty()) break;

        // Наполнение списка граней для новой фигуры на основе списка новых рёбер
        new_faces.clear();

        // Перебор списка рёбер для новой фигуры
        for (auto it = new_edges.cbegin(); it != new_edges.cend(); ++it) {
          // Перебор левой и правой граней ребра
          const face* left = (*it)->get_left();
          if (!left->is_marked()) {
            left->set_mark(this);
            new_faces.push_back(left);
          }
          const face* right = (*it)->get_right();
          if (!right->is_marked()) {
            right->set_mark(this);
            new_faces.push_back(right);
          }
        }
        // Список индексов новых граней пустой - выходим
        if (new_faces.empty()) break;
      }
      // Перенести примитивы новой фигуры в новую фигуру и добавить её в результирующий список
      Shells.push_back(split(this));
    }

    // Снять пометки со всех списков фигур
    for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
      unmark_faces();
      unmark_vertexes();
      unmark_edges();
    }

    return Shells;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::split(const void*)
   */
  shell* shell::split(const void* marker) {
    shell* S = new shell();

    /* Шаг 1 разделения - снять возможные отметки вершин и рёбер */

    unmark_vertexes();
    unmark_edges();

    /* Шаг 2 разделения - отметить вершины и рёбра, соответствующие помеченным граням */

    // Перебор граней
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
      if ((*it)->get_mark() != marker) continue;
      // Перебор границ
      for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
        // Перебор направленных рёбер
        for (auto it_e = (*it_b).get_edges().cbegin(); it_e != (*it_b).get_edges().cend(); ++it_e) {
          const edge* e = (*it_e).get_base_edge();
          // Отметить ребро
          e->set_mark(marker);
          // Отметить вершины ребра
          e->get_start()->set_mark(marker);
          e->get_end()->set_mark(marker);
        }
      }
    }

    /*  Шаг 3 разделения - перенести указатели помеченных вершин в список новой фигуры */

    // Перебор вершин
    for (auto it = vertexes.cbegin(); it != vertexes.cend();) {
      if ((*it)->get_mark() == marker) {
        // Добавить вершину в новый список
        S->vertexes.push_back(*it);
        // Удалить указатель на вершину из списка исходной фигуры
        it = vertexes.erase(it);
        continue;
      }
      ++it;
    }

    /*  Шаг 4 разделения - перенести указатели помеченных рёбер в список новой фигуры */

    // Перебор рёбер
    for (auto it = edges.cbegin(); it != edges.cend();) {
      if ((*it)->get_mark() == marker) {
        // Добавить ребро в новый список
        S->edges.push_back(*it);
        // Удалить указатель на ребро из списка исходной фигуры
        it = edges.erase(it);
        continue;
      }
      ++it;
    }

    /*  Шаг 7 разделения - наполнить список граней новой фигуры */

    // Перебор граней
    for (auto it = faces.cbegin(); it != faces.cend();) {
      if ((*it)->get_mark() == marker) {
        // Добавить грань в новый список
        S->faces.push_back(*it);
        // Удалить указатель на грань из списка исходной фигуры
        it = faces.erase(it);
        continue;
      }
      ++it;
    }
    return S;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::merge_faces(bool)
   */
  void shell::merge_faces(bool debug) {

    /**
     * Алгоритм:
     * <BR>
     */

    /**
     * 1 Определить список объединённых граней.
     */
    std::vector<face*> unated_shell_faces;

    if (debug) {
      std::cout << std::endl;
      std::cout << "* merge_edges *******************************************************" << std::endl;
      std::cout << "* Список исходных граней до объединения                             *" << std::endl;
      std::cout << "*********************************************************************" << std::endl;
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        (*it)->print(this);
        std::cout << std::endl;
      }
      std::cout << std::endl;
      std::cout << "* merge_edges *******************************************************" << std::endl;
      std::cout << "* Далее в цикле выполняются шаги 1-5 до исчерпания списка граней.   *" << std::endl;
      std::cout << "*********************************************************************" << std::endl;
    }

    /**
     * 2 В цикле выполнять шаги с первого по пятый до исчерпания списка исходных граней:
     */
    for (; !faces.empty();) {

      /**
       * &nbsp;&nbsp;2.1 Снять пометки с рёбер и граней фигуры, с объединённых граней.
       */
      unmark_faces();
      unmark_edges();
      unmark_vertexes();

      /**
       * &nbsp;&nbsp;2.2 Создать пустой список необработанных граней.
       */
      std::vector<const face*> new_faces;

      /**
       * &nbsp;&nbsp;2.3 Создать пустой список необработанных рёбер.
       */
      std::vector<const edge*> new_edges;

      /**
       * &nbsp;&nbsp;2.4 Шаг 1 - пометить группу граней, котрые войдут в объединённую грань.
       */

      if (debug) {
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Шаг 1 - пометить группу граней, котрые войдут в объединённую      *" << std::endl;
        std::cout << "* грань.                                                            *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
      }

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.1 Взять первую грань из списка граней фигуры.
       */
      const face* first_face = *faces.cbegin();

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.2 Определить нормаль объединяемой грани по нормали первой грани.
       */
      geometry::vector base_normal = (first_face)->get_normal();

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.3 Создать объединённую грань с указанной нормалью, пометить её собой.
       */
      face* unated_face = new face(base_normal);
      unated_face->set_mark(unated_face); //-V678

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.4 Пометить первую грань объединённой гранью.
       */
      first_face->set_mark(unated_face);

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.5 Добавить в список необработанных граней первую грань.
       */
      new_faces.push_back(first_face);

      if (debug) {
        std::cout << "Первая грань (помечена, помещена в список необработанных граней)" << std::endl;
        first_face->print(this);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Цикл первого шага продолжается до опустошения одного из списков   *" << std::endl;
        std::cout << "* необработанных (рёбер и граней).                                  *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
      }

      /**
       * &nbsp;&nbsp;&nbsp;&nbsp;2.4.6 Выполнять цикл до опустошения списка необработанных рёбер
       * или списка необработанных граней.
       */
      for (;;) {

        /**
         * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.6.1 Пометить непомеченные рёбра, составляющие
         * грани из списка необработанных граней, и составить из них список необработанных рёбер. 
         */
        new_edges.clear();
        // перебор необработанных граней
        for (auto it = new_faces.cbegin(); it != new_faces.cend(); ++it) {
          // перебор границ необработанных граней
          for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
            // перебор ориентированных рёбер границ необработанных граней
            for (auto it_e = (*it_b).get_edges().cbegin(); it_e != (*it_b).get_edges().cend(); ++it_e) {
              // базовое ребро ориентированного ребра
              const edge* e = (*it_e).get_base_edge();
              if (!e->is_marked()) {
                e->set_mark(unated_face);
                new_edges.push_back(e);
              }
            }
          }
        }

        /** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.6.2 Если список необработанных рёбер пуст, это ошибка. */
        assert(!new_edges.empty());

        /**
         * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.6.3 Пометить непомеченные грани, включающие
         * рёбра из списка необработанных рёбер, и составить из них список необработанных граней
         */
        new_faces.clear();
        for (auto it = new_edges.cbegin(); it != new_edges.cend(); ++it) {
          // Перебор граней, включающих текущее ребро
          const face* edge_faces[2];
          edge_faces[0] = (*it)->get_left();
          edge_faces[1] = (*it)->get_right();
          for (size_t i = 0; i < 2; ++i) {
            if (!edge_faces[i]->is_marked() &&
                 edge_faces[i]->get_normal().is_equal(base_normal, EPSILON_Y)) {
              if (debug) {
                std::cout << "Непомеченная грань (с ребром из списка необработанных рёбер) в нужной плоскости вносится в список необработанных граней" << std::endl;
                edge_faces[i]->print(this);
                std::cout << std::endl;
              }
              edge_faces[i]->set_mark(unated_face);
              new_faces.push_back(edge_faces[i]);
            }
          }
        }

        /**
         * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.6.4 Завершить цикл, если список необработанных граней пуст.
         * В спсике необработанных рёбер - рёбра новой объединённой грани.
         */
        if (new_faces.empty()) {
          if (debug) {
            std::cout << std::endl;
            std::cout << "* merge_edges *******************************************************" << std::endl;
            std::cout << "* Список необработанных граней пуст.                                *" << std::endl;
            std::cout << "*********************************************************************" << std::endl;
          }
          break;
        }
      }

      /**
       * &nbsp;&nbsp;2.5 Шаг 2 - перенести границы помеченных граней в новую грань.
       */

      if (debug) {
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Шаг 2 - перенести границы помеченных граней в новую грань.        *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
      }

      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        if ((*it)->get_mark() == unated_face) {
          for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
            unated_face->add_border(*it_b);
          }
        }
      }

      /**
       * &nbsp;&nbsp;2.6 Шаг 3 - Заменить указатели на помеченные грани указателем на объединённую грань
       */

      if (debug) {
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Шаг 3.1 - заменить указатели на помеченные грани указателем на    *" << std::endl;
        std::cout << "* новую грань для всех вершин и рёбер объединённой грани.           *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
      }

      // перебор границ объединённой грани
      for (auto it_b = unated_face->get_borders().cbegin(); it_b != unated_face->get_borders().cend(); ++it_b) {
        // перебор направленных рёбер границы объединённой грани
        for (auto it_oe = (*it_b).get_edges().cbegin(); it_oe != (*it_b).get_edges().cend(); ++it_oe) {
          // получить ребро, соответствующее направленному ребру
          edge* e = const_cast<edge*>((*it_oe).get_base_edge());
          // Если левая от ребра грань помечена объединённой гранью, заменить её указатель на указатель объединённой грани
          const face* left = e->get_left();
          assert(left != nullptr);
          if (left != unated_face && left->get_mark() == unated_face ) {
            if (debug) {
              std::cout << "Замена левой грани для ребра: ";
              e->print(this);
              std::cout << std::endl;
              std::cout << std::endl << "Старая левая грань: ";
              left->print(this);
              std::cout << std::endl;
              std::cout << std::endl << "Новая левая грань #" << unated_shell_faces.size() + 1 << std::endl;
            }
            e->set_left(unated_face);
          }

          // Если правая от ребра грань помечена объединённой гранью, заменить её указатель на указатель объединённой грани
          const face* right = e->get_right();
          assert(right != nullptr);
          if (right != unated_face && right->get_mark() == unated_face) {
            if (debug) {
              std::cout << "Замена правой грани для ребра: ";
              e->print(this);
              std::cout << std::endl << "Старая правая грань: ";
              right->print(this);
              std::cout << std::endl << "Новая правая грань #" << unated_shell_faces.size() + 1 << std::endl;
            }
            e->set_right(unated_face);
          }
        }
      }
      
      /**
       * &nbsp;&nbsp;2.7 Шаг 4 - уничтожить помеченные грани как объекты и удалить их указатели
       * из списка граней фигуры, перебирая грани фигуры:
       */

      if (debug) {
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Шаг 4 - уничтожить помеченные грани как объекты и удалить их      *" << std::endl;
        std::cout << "* указатели из списка граней фигуры.                                *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
      }

      for (auto it = faces.cbegin(); it != faces.cend();) {
        if ((*it)->is_marked()) {
          assert((*it)->get_mark() == unated_face);
          /** &nbsp;&nbsp;&nbsp;&nbsp;2.7.1 Уничтожить помеченную грань. */
          delete *it;
          /** &nbsp;&nbsp;&nbsp;&nbsp;2.7.2 Удалить указатель на удалённую грань из списка граней фигуры. */
          it = faces.erase(it);
          continue;
        }
        ++it;
      }

      /**
       * &nbsp;&nbsp;2.8 Шаг 5 - добавить объединённую грань к списку объединённых граней.
       */

      if (debug) {
        std::cout << std::endl;
        std::cout << "* merge_edges *******************************************************" << std::endl;
        std::cout << "* Шаг 5 - добавить объединённую грань к списку объединённых граней. *" << std::endl;
        std::cout << "*********************************************************************" << std::endl;
        std::cout << "Добавляется объединённая грань #" << unated_shell_faces.size() + 1 << ":" << std::endl;
        unated_face->print(this);
        std::cout << std::endl;
      }
      unated_shell_faces.push_back(unated_face);
    }

    /**
     * 3 Заменить исходный список граней фигуры списком объединённых граней.
     */
    faces.swap(unated_shell_faces);

    if (debug) {
      std::cout << std::endl;
      std::cout << "* merge_edges *******************************************************" << std::endl;
      std::cout << "* Список объединённых граней                                        *" << std::endl;
      std::cout << "*********************************************************************" << std::endl;
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        (*it)->print(this);
        std::cout << std::endl;
      }
    }
  }

  /**
   * \file
   * * \copybrief prim3d::shell::reduce_edges(bool)
   */
  err_enum_t shell::reduce_edges(bool debug) {

    /**
     * Алгоритм:
     * <BR>
     */

    /**
     * 1 Снять пометки с рёбер
     */
    unmark_edges();

    /**
     * 2 Шаг 6 - отметить лишние рёбра, принадлежащие одной грани.
     */

    if (debug) {
      std::cout << std::endl;
      std::cout << "* reduce_edges ******************************************************" << std::endl;
      std::cout << "* Шаг 6 - отметить лишние рёбра, принадлежащие одной грани.         *" << std::endl;
      std::cout << "*********************************************************************" << std::endl;
    }

    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      if ((*it)->get_left() == (*it)->get_right()) {
        if (debug) {
          std::cout << "mark ";
          (*it)->print(this);
          std::cout << std::endl;
        }
        (*it)->set_mark(this);
      }
      else {
        if (debug) {
          std::cout << "left ";
          (*it)->print(this);
          std::cout << std::endl;
        }
      }
    }

    /**
     * 3 Шаг 7 - для каждой грани удалить помеченные рёбра из всех границ, объединить границы.
     */

    if (debug) {
      std::cout << std::endl;
      std::cout << "* reduce_edges ******************************************************" << std::endl;
      std::cout << "* Шаг 7 - для каждой грани удалить помеченные рёбра из всех границ, *" << std::endl;
      std::cout << "* объединить границы.                                               *" << std::endl;
      std::cout << "* Старые значения граней:                                           *" << std::endl;
      for (auto it = faces.begin(); it != faces.end(); ++it) {
        (*it)->print(this);
        std::cout << std::endl;
      }
      std::cout << "*********************************************************************" << std::endl;
    }

    for (auto it = faces.begin(); it != faces.end(); ++it) {
      border new_border;

      if (debug) {
        std::cout << "  Грань #" << std::distance(faces.begin(), it) + 1 << std::endl;
      }

      /** Перебрать границы грани. */
      for (auto it_b = (*it)->get_borders().cbegin(); it_b != (*it)->get_borders().cend(); ++it_b) {
        /** Перебрать направленные рёбра границы грани. */
        for (auto it_e = (*it_b).get_edges().cbegin(); it_e != (*it_b).get_edges().cend(); ++it_e) {
          if (!(*it_e).get_base_edge()->is_marked()) {
            new_border.add_edge(*it_e);
          }
        }
      }

      if (debug) {
        std::cout << "  Создана граница: ";
        new_border.print(this);
        std::cout << std::endl;
      }

      if (new_border.edges_num() < 3) {
        std::cout << "ERROR (reduce_edges): создана граница с числом рёбер = " << new_border.edges_num() << " < 3 in face #" << std::distance(faces.begin(), it) + 1 << std::endl;
        return err_enum_t::ERROR_INTERNAL;
      }

      std::vector<border> new_borders;
      new_borders.push_back(new_border);
      (*it)->set_borders(new_borders);
    }

    /**
     * 4 Вернуть код успешного завершения \ref err_enum_t::ERROR_OK "ERROR_OK".
     */
    return err_enum_t::ERROR_OK;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::split_edges_to_borders(bool)
   */
  err_enum_t shell::split_edges_to_borders(bool debug) {

    if (debug) {
      std::cout << std::endl;
      std::cout << "* split_edges_to_borders ********************************************" << std::endl;
      std::cout << "* Шаг 8 - преобразование рёбер в границы.                           *" << std::endl;
      std::cout << "*********************************************************************" << std::endl;
    }

    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {

      /** Проверка: в списке границ должна быть только одна граница */
      if ((*it)->borders_num() != 1) {
        std::cout << "ERROR (split_edges_to_borders): more than 1 border in face #" << std::distance(faces.cbegin(), it) + 1 << std::endl;
        return err_enum_t::ERROR_INTERNAL;
      }

      border old_border = *(*it)->get_borders().cbegin();
      /** Проверка: в старой границе должно быть не меньше трёх рёбер */
      if (old_border.edges_num() < 3) {
        std::cout << "ERROR (split_edges_to_borders): border with number of edges < 3 in face #" << std::distance(faces.cbegin(), it) + 1 << std::endl;
        return err_enum_t::ERROR_INTERNAL;
      }

      if (debug) {
        std::cout << std::endl << "Грань #" << std::distance(faces.cbegin(), it) + 1 << std::endl << "Старая граница: ";
        old_border.print(this);
        std::cout << std::endl;
      }

      std::vector<border> new_border_list;

      /** Цикл продолжается, пока в старой границе есть ориентированные рёбра. */
      for (; old_border.edges_num() != 0;) {

        border new_border;

        /** Взять из старой границы первое ориентированное ребро, */
        const auto& first_oedge = *old_border.get_edges().cbegin();
        /** запомнить его стартовую вершину - первую вершину новой грани, */
        const vertex* first_vertex = first_oedge.get_direction() ? first_oedge.get_base_edge()->get_start() : first_oedge.get_base_edge()->get_end();
        /** установить такое же значение для конечной вершины предыдущего ориентированного ребра. */
        const vertex* last_vertex = first_vertex;

        if (debug) {
          std::cout << "Новая граница:" << std::endl << "  вершина ";
          first_vertex->print(this);
          std::cout << std::endl;
        }

        /** Цикл перебора ориентированных рёбер старой границы. */
        do {
          bool found_oriented_edge = false;
          /** Найти следующее ориентированное ребро, стартовая вершина которого является конечной вершиной предыдущего ребра. */
          for (auto it_e = old_border.get_edges().cbegin(); it_e != old_border.get_edges().cend(); ++it_e) {
            const auto& e = (*it_e).get_base_edge();
            if (((*it_e).get_direction() ? e->get_start() : e->get_end()) == last_vertex) {
              /** Добавить это ориентированное ребро в новую границу. */
              new_border.add_edge(*it_e);
              /** Запомнить конечную вершину этого ориентированного ребра */
              last_vertex = (*it_e).get_direction() ? e->get_end() : e->get_start();
              /** Удалить это ориентированное ребро из старой границы. */
              old_border.remove(it_e);

              if (debug) {
                std::cout << "  вершина ";
                last_vertex->print(this);
                std::cout << std::endl;

                std::cout <<
                  "  найдено рёбер: " << new_border.edges_num() <<
                  ", осталось найти: " << old_border.edges_num() << std::endl;
              }
              found_oriented_edge = true;
              break;
            }
          }

          if (!found_oriented_edge) {
            std::cout << "ERROR (split_edges_to_borders): can not close edge loop in face #" << std::distance(faces.cbegin(), it) + 1 <<
            "(found " << new_border.edges_num() <<
            " edges, remained " << old_border.edges_num() <<
            " edegs)" << std::endl;
            return err_enum_t::ERROR_INTERNAL;
          }

          /** Если конечная вершина этого ребра совпадает с первой вершиной новой грани, завершить цикл. */
        } while (last_vertex != first_vertex);

        /** Добавить новую границу в список новых границ. */
        new_border_list.push_back(new_border);
      }
      (*it)->set_borders(new_border_list);
    }
    return err_enum_t::ERROR_OK;
  }

  /**
   * \file
   * * \copybrief prim3d::shell::print() const
   */
  void shell::print() const {
    std::cout << (is_marked() ? "<M>" : "< >");
    std::cout << "Shell of " << vertexes.size() << " vertexes, " << edges.size() << " edges, " << faces.size() << " faces" << std::endl;
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      std::cout << "  - edge #" << std::distance(edges.cbegin(), it) + 1 << ":" << std::endl;
      (*it)->print();
    }
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
      std::cout << "  - face #" << std::distance(faces.cbegin(), it) + 1 << ":" << std::endl;
      (*it)->print();
    }
  }

/** \brief Количество векторов (координат), определяющих одну грань (нормаль и три вершины) */
#define NORMAL_NUM 1
#define COORDS_NUM 3

  /**
   * \file
   * * \copybrief prim3d::shell::import(const std::string&, std::vector<geometry::vector>&)
   */
  err_enum_t shell::import(const std::string& fname, std::vector<geometry::vector>& faces) {
    bool                     wassolid = false;
    bool                     wasface = false;
    bool                     wasouterloop = false;
    geometry::vector         face_normal;      /** Нормаль новой грани */
    geometry::vector         face_outer[COORDS_NUM]; /**  Вершины новой грани */
    size_t                   face_line;        /** Номер строки, в которой начинается описание новой грани */
    size_t                   vnum = 0;         /** Счётчик вершин в новой грани */
    size_t                   line_num = 0;     /** Счётчик строк импортируемого файла */
    std::vector<size_t>      facet_lines;      /** Номера строк, в которых начинается описание граней */

    // Прочитать файл STL
    FILE* in;

#if defined(_MSC_VER)
    errno_t err = fopen_s(&in, fname.c_str(), "rt");
    if (err != 0 || in == nullptr)
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    in = fopen(fname.c_str(), "rt");
    if (in == nullptr)
#else
# error Unknown C++ compiler
#endif
    {
      std::cout << "ERROR (import): Can't open file '" << fname << "' for reading" << std::endl;
      return err_enum_t::ERROR_FILE_IO;
    }

    faces.clear();
    for (;;) {
      char Buf[1000];

      if (fgets(Buf, sizeof(Buf), in) == nullptr) break;
      line_num ++;

//!!! Свести любое количество пробелов/табуляций к одному пробелу!

      // Убрать переводы строки в конце строки
      size_t blen = strlen(Buf);
      if (blen > 1 && Buf[blen - 1] == '\n') blen--;
      if (blen > 1 && Buf[blen - 1] == '\r') blen--;
      Buf[blen] = '\0';

      // Убрать пробелы в начале строки
      const char* B = Buf;
      for (; *B == ' '; ++B);
      if (*B == '\0') {
        std::cout << "ERROR (import): no text in line #" << line_num << std::endl;
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      // Разбор файла STL
      if (strncmp(B, "solid ", 6) == 0) {
        wassolid = true;
        continue;
      }

      if (wassolid == false) {
        std::cout << "ERROR (import): no 'solid' in line #" << line_num << "!" << std::endl;
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      if (strncmp(B, "endsolid ", 9) == 0) {
        wassolid = false;
        break;
      }

      if (strncmp(B, "facet normal ", 13) == 0) {
        float X, Y, Z;
        wasface = true;
#if defined(_MSC_VER)
        int readed = sscanf_s(&B[13], "%f %f %f", &X, &Y, &Z);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
        int readed = sscanf(&B[13], "%f %f %f", &X, &Y, &Z);
#else
# error Unknown C++ compiler
#endif

        if (readed != 3) {
          std::cout << "ERROR (import): can not read coordinates in line #" << line_num << "!" << std::endl;
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        face_normal = geometry::vector(X, Y, Z);
        face_line = line_num;
        continue;
      }

      if (wasface == false) {
        std::cout << "ERROR (import): no 'facet' in line #" << line_num << "!" << std::endl;
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      if (strncmp(B, "endfacet", 8) == 0) {
        wasface = false;

        // Входной контроль: нет ли уже такой грани?
        bool add_face = true;
        for (auto it = faces.cbegin(); it != faces.cend();) {
          const geometry::vector& nr = *it ++;
          const geometry::vector& p1 = *it ++;
          const geometry::vector& p2 = *it ++;
          const geometry::vector& p3 = *it ++;

          if (nr == face_normal) {
            if ((p1 == face_outer[0] && p2 == face_outer[1] && p3 == face_outer[2]) ||
                (p1 == face_outer[0] && p2 == face_outer[2] && p3 == face_outer[1]) ||
                (p1 == face_outer[1] && p2 == face_outer[2] && p3 == face_outer[0]) ||
                (p1 == face_outer[1] && p2 == face_outer[0] && p3 == face_outer[2]) ||
                (p1 == face_outer[2] && p2 == face_outer[0] && p3 == face_outer[1]) ||
                (p1 == face_outer[2] && p2 == face_outer[1] && p3 == face_outer[0])) {
               add_face = false;
               std::cout << "WARNING (import): одинаковые грани в строке #" <<
                 facet_lines[std::distance(faces.cbegin(), it) / (NORMAL_NUM + COORDS_NUM) - 1]  << " и в строке #" << face_line << std::endl;
               break;
            }
          }
        }
        
        if (add_face) {
          // Можно формировать грань
          faces.emplace_back(face_normal);
          faces.emplace_back(face_outer[0]);
          faces.emplace_back(face_outer[1]);
          faces.emplace_back(face_outer[2]);
          facet_lines.push_back(face_line);
        }
        continue;
      }

      if (strncmp(B, "outer loop", 10) == 0) {
        wasouterloop = true;
        vnum = 0;
        continue;
      }

      if (wasouterloop == false) {
        std::cout << "ERROR (import): no 'outer loop' in line #" << line_num << "!" << std::endl;
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      if (strncmp(B, "endloop", 7) == 0) {
        wasouterloop = false;
        continue;
      }

      // Запомнить координаты вершины
      if (strncmp(B, "vertex ", 7) == 0) {
        if (vnum >= 3) {
          std::cout << "ERROR (import): 4th vertex per face in line #" << line_num << "!" << std::endl;
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        float X, Y, Z;
#if defined(_MSC_VER)
        int readed = sscanf_s(&B[7], "%f %f %f", &X, &Y, &Z);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
        int readed = sscanf(&B[7], "%f %f %f", &X, &Y, &Z);
#else
# error Unknown C++ compiler
#endif
        if (readed != 3) {
          std::cout << "ERROR (import): can not read coordinates in line #" << line_num << "!" << std::endl;
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        face_outer[vnum++] = geometry::vector(X, Y, Z);
        continue;
      }

      std::cout << "ERROR (import): unknown keyword in line #" << line_num << "!" << std::endl;
      fclose(in);
      return err_enum_t::ERROR_IMPORT;
    }
    fclose(in);

    if (faces.size() / (NORMAL_NUM + COORDS_NUM) * (NORMAL_NUM + COORDS_NUM) != faces.size()) {
      std::cout << "ERROR (import): количество прочитанных векторов не кратно " << (NORMAL_NUM + COORDS_NUM) << std::endl;
      return err_enum_t::ERROR_INTERNAL;
    }

    return err_enum_t::ERROR_OK;
  }
}
