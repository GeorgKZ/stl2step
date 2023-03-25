/**
 * \file
 *
 * \brief Файл с определениями функций классов трёхмерных фигур
 */

#ifndef TESTONLY

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"

namespace prim3d {

/** Количество векторов на одну грань */
#define NUM_FACE_VECTS 4

  err_enum_t import(const std::string& fname, std::vector<geometry::vector>& faces) {
    bool                     wassolid = false;
    bool                     wasface = false;
    bool                     wasouterloop = false;
    /** \brief Нормаль новой грани */
    geometry::vector         face_normal;
    /** \brief Вершины новой грани */
    geometry::vector         face_outer[3];
    /** \brief Счётчик вершин в новой грани */
    size_t                   vnum = 0;

    // Прочитать файл STL
    FILE* in;

#if defined(_MSC_VER)
    errno_t err = fopen_s(&in, fname.c_str(), "rt");
    if (err != 0 || in == nullptr)
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    in = fopen(fname.c_str(), "rt");
    if (in == nullptr)
#elif
#error Unknown C++ compiler
#endif
    {
      printf("ERROR (import): Can't open file '%s' for reading\n", fname.c_str());
      return err_enum_t::ERROR_FILE_IO;
    }

    faces.clear();
    for (unsigned linenum = 1;; linenum++) {
      char Buf[1000];

      if (fgets(Buf, sizeof(Buf), in) == nullptr) break;

      // Убрать переводы строки в конце строки
      size_t blen = strlen(Buf);
      if (blen > 1 && Buf[blen - 1] == '\n') blen--;
      if (blen > 1 && Buf[blen - 1] == '\r') blen--;
      Buf[blen] = '\0';

      // Убрать пробелы в начале строки
      const char* B = Buf;
      for (; *B == ' '; ++B);

      // Разбор файла STL
      if (strncmp(B, "solid ", 6) == 0) {
        wassolid = true;
        continue;
      }

      if (wassolid == false) {
        printf("ERROR (import): no 'solid' in line %u!\n", linenum);
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
#elif
#error Unknown C++ compiler
#endif

        if (readed != 3) {
          printf("ERROR (import): can not read coordinates in line %u!\n", linenum);
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        face_normal = geometry::vector(X, Y, Z);
        continue;
      }

      if (wasface == false) {
        printf("ERROR (import): no 'facet' in line %u!\n", linenum);
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      if (strncmp(B, "endfacet", 8) == 0) {
        wasface = false;

        // Можно формировать грань
        faces.emplace_back(face_normal);
        faces.emplace_back(face_outer[0]);
        faces.emplace_back(face_outer[1]);
        faces.emplace_back(face_outer[2]);

        continue;
      }

      if (strncmp(B, "outer loop", 10) == 0) {
        wasouterloop = true;
        vnum = 0;
        continue;
      }

      if (wasouterloop == false) {
        printf("ERROR (import): no 'outer loop in line %u!\n", linenum);
        fclose(in);
        return err_enum_t::ERROR_IMPORT;
      }

      if (strncmp(B, "endloop", 7) == 0) {
        wasouterloop = false;
        continue;
      }

      /* Запомнить координаты вершины */
      if (strncmp(B, "vertex ", 7) == 0) {
        if (vnum >= NUM_FACE_VECTS - 1) {
          printf("ERROR (import): 4th vertex per face in line %u!\n", linenum);
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        float X, Y, Z;
#if defined(_MSC_VER)
        int readed = sscanf_s(&B[7], "%f %f %f", &X, &Y, &Z);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
        int readed = sscanf(&B[7], "%f %f %f", &X, &Y, &Z);
#elif
#error Unknown C++ compiler
#endif
        if (readed != 3) {
          printf("ERROR (import): can not read coordinates in line %u!\n", linenum);
          fclose(in);
          return err_enum_t::ERROR_IMPORT;
        }
        face_outer[vnum++] = geometry::vector(X, Y, Z);
        continue;
      }

      printf("ERROR (import): unknown string in line %u!\n", linenum);
      fclose(in);
      return err_enum_t::ERROR_IMPORT;
    }
    fclose(in);

    if (faces.size() / NUM_FACE_VECTS * NUM_FACE_VECTS != faces.size()) {
      printf("ERROR (import): number of vectors is not a multiple of 4!\n");
      return err_enum_t::ERROR_INTERNAL;
    }

    return err_enum_t::ERROR_OK;
  }

  void vertex::print(const shell* s) const {
    if (s) {
      printf("vertex #%4zu", std::distance(s->vertexes_cbegin(), std::find(s->vertexes_cbegin(), s->vertexes_cend(), this)) + 1);
    }
    else coord.print();
  }

  void edge::print(const shell* s) const {
    if (s) {
      printf("edge #%4zu, ", std::distance(s->edges_cbegin(), std::find(s->edges_cbegin(), s->edges_cend(), this)) + 1);
      printf("start ");
      start_vertex->print(s);
      printf(" -> end ");
      end_vertex->print(s);
      printf(" ");
      if (left_face) {
        printf("left face #%4zu / ", std::distance(s->faces_cbegin(), std::find(s->faces_cbegin(), s->faces_cend(), left_face)) + 1);
      }
      else {
        printf("no left face/ ");
      }
      if (right_face) {
        printf("right face #%4zu", std::distance(s->faces_cbegin(), std::find(s->faces_cbegin(), s->faces_cend(), right_face)) + 1);
      }
      else {
        printf("no right face");
      }
    }
    else {
      start_vertex->print();
      printf("->");
      end_vertex->print();
    }
  }

  void border::print(const shell* s) const {
    printf(" %4zu oriented edges [", edges.size());
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      printf("\n                 ");
      (*it).print(s);
    }
    printf("]");
  }


  void face::print(const shell* s) const {
    if (s == nullptr) {
      printf("N: ");
      normal.print();
      printf(" ");
    }
    else {
      printf("face #%4zu, ", std::distance(s->faces_cbegin(), std::find(s->faces_cbegin(), s->faces_cend(), this)) + 1);
    }
    if (borders.empty()) {
      printf("no borders");
    }
    else {
      if (borders.size() == 1) {
        printf("1 border {");
      }
      else {
        printf("%4zu borders {", borders.size());
      }
      for (auto it = borders.cbegin(); it != borders.cend(); ++it) {
        printf("\n       ");
        (*it).print(s);
      }
      printf("}");
    }
  }



  shell::shell(const std::vector<geometry::vector>& stlf) : clone(nullptr) {
    // Перебор граней, наполнение взаимно индексированных списков вершин и рёбер
    for (auto it = stlf.cbegin(); it != stlf.cend();) {
      // Новая грань на основе нормали из грани
      face* f = new face((*it++));

      // Указатели трёх вершин грани
      vertex* ptr_vertex[3] = {};

      // Обработать три вершины грани
      for (auto i = 0; i <= 2; ++i, ++it) {
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
        ptr_vertex[i]->add_face(f);
      }

      // Три ребра грани
      edge* e[3] = {
        new edge(ptr_vertex[0], ptr_vertex[1], f),
        new edge(ptr_vertex[1], ptr_vertex[2], f),
        new edge(ptr_vertex[2], ptr_vertex[0], f),
      };

      // Добавить рёбра к списку рёбер
      for (auto i = 0; i <= 2; ++i) {
        edges.push_back(e[i]);
      }

      // Добавить указатель на ребро в список указателей на рёбра вершины для 3х вершин
//      ptr_vertex[0]->add_edge(e[0]);
//      ptr_vertex[0]->add_edge(e[2]);
//      ptr_vertex[1]->add_edge(e[0]);
//      ptr_vertex[1]->add_edge(e[1]);
//      ptr_vertex[2]->add_edge(e[1]);
//      ptr_vertex[2]->add_edge(e[2]);


      for (auto i = 0; i <= 2; ++i) {
        ptr_vertex[i]->add_edge(e[i]);
        ptr_vertex[i]->add_edge(e[(i + 2) % 3]);
      }


      // Граница грани
      border b;
      for (auto i = 0; i <= 2; ++i) {
        b.add_edge(oriented_edge(e[i]));
      }

      // Добавить границу в список границ грани
      f->add_border(b);

      // Добавить новую грань в список граней фигуры
      faces.push_back(f);
    }
  }

  std::vector<shell*> shell::separate() {

    std::vector<shell*> Shells; // Фигуры

    /** Снять пометки с граней */
    unmark_faces();

    // Бесконечный цикл, пока есть "ничейные" грани
    for (;;) {
      /** Список указателей на новые грани, которые должны быть помечены */
      std::vector<const face*>   new_faces;
      /** Список указателей на новые вершины, которые должны быть помечены */
      std::vector<const vertex*> new_verts;

      // Список индексов новых вершин пустой
      // Добавляем в список индексов новых граней первую грань, не принадлежащую ни одной фигуре
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        if (!(*it)->is_marked()) {
          (*it)->set_mark(this);
          new_faces.push_back(*it);
          break;
        }
      }

      // Все грани принадлежат каким-то фигурам, большой цикл закончен.
      if (new_faces.empty()) break;

      // Бесконечный цикл, пока оба списка индексов не пустые
      for (;;) {

        // Создание списка индексов новых вершин по списку индексов новых граней
        new_verts.clear();

        // Перебор списка индексов новых граней
        for (auto it = new_faces.cbegin(); it != new_faces.cend(); ++it) {
          // Перебор границ
          for (auto it_b = (*it)->borders_cbegin(); it_b != (*it)->borders_cend(); ++it_b) {
            const auto& b = *it_b; // Граница
            // Перебор рёбер
            for (auto it_e = b.edges_cbegin(); it_e != b.edges_cend(); ++it_e) {
              const auto& ce = *it_e;
              const auto& e = ce.get_base_edge();
              const vertex* v = ce.get_direction() ? e->get_start() : e->get_end(); // Одна из вершин, обазующих текущую грань
              // Обработка вершины
              if (v->is_marked()) continue;
              v->set_mark(this);
              new_verts.push_back(v);
            }
          }
        }
        // Список индексов новых вершин пустой - выходим
        if (new_verts.empty()) break;

        // Создание списка новых граней по списку новых вершин
        new_faces.clear();

        // Перебор списка адресов новых вершин
        for (auto it = new_verts.cbegin(); it != new_verts.cend(); ++it) {
          // Перебор индексов граней, образованных текущей вершину
          for (auto it_e = (*it)->faces_cbegin(); it_e != (*it)->faces_cend(); ++it_e) {
            if (!(*it_e)->is_marked()) {
              (*it_e)->set_mark(this);
              new_faces.push_back(*it_e);
            }
          }
        }

        // Список индексов новых граней пустой - выходим
        if (new_faces.empty()) break;
      }
      // Перенести примитивы новой фигуры в новую фигуру и добавить её в результирующий список
      Shells.push_back(split(this));
    }
    return Shells;
  }

  shell* shell::split(const void* Mark) {
    shell* S = new shell();

    /* Шаг 1 разделения - снять возможные отметки вершин и рёбер */

    unmark_vertexes();
    unmark_edges();

    /* Шаг 2 разделения - отметить вершины и рёбра, соответствующие отмеченным граням */

    // Перебор граней
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
      if ((*it)->get_mark() != Mark) continue;
      // Перебор границ
      for (auto it_b = (*it)->borders_cbegin(); it_b != (*it)->borders_cend(); ++it_b) {
        // Перебор направленных рёбер
        for (auto it_e = (*it_b).edges_cbegin(); it_e != (*it_b).edges_cend(); ++it_e) {
          const edge* e = (*it_e).get_base_edge();
          // Отметить ребро
          e->set_mark(Mark);
          // Отметить вершины ребра
          e->get_start()->set_mark(Mark);
          e->get_end()->set_mark(Mark);
        }
      }
    }

    /*  Шаг 3 разделения - перенести указатели отмеченных вершин в список новой фигуры */

    // Перебор вершин
    for (auto it = vertexes.cbegin(); it != vertexes.cend();) {
      if ((*it)->get_mark() == Mark) {
        // Добавить вершину в новый список
        S->vertexes.push_back(*it);
        // Удалить указатель на вершину из списка исходной фигуры
        it = vertexes.erase(it);
        continue;
      }
      ++it;
    }

    /*  Шаг 4 разделения - перенести указатели отмеченных рёбер в список новой фигуры */

    // Перебор рёбер
    for (auto it = edges.cbegin(); it != edges.cend();) {
      if ((*it)->get_mark() == Mark) {
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
      if ((*it)->get_mark() == Mark) {
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






  bool shell::operator==(const shell& s) const {

    /** Сравнение размеров списков граней */
    if (faces.size() != s.faces.size()) {
      return false;
    }
    /** Сравнение размеров списков вершин */
    if (vertexes.size() != s.vertexes.size()) {
      return false;
    }

    /** Сравнение координат вершин из списка вершин с точностью EPSILON_C */
    for (auto it1 = vertexes.cbegin(), it2 = s.vertexes.cbegin(); it1 != vertexes.cend(); ++it1, ++it2) {
      if (!(*it1)->get_coord().is_equal((*it2)->get_coord(), EPSILON_C)) return false;
    }
    return true;
  }

  void shell::normalize_shell()
  {
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

  err_enum_t shell::merge_edges() {

    /** Снять пометки с рёбер */
    unmark_edges();

    /**
     * Шаг 1 - пометить половину рёбер, встречных к рёбрам второй половины.
     */

     /** Перебрать все рёбра в списке фигуры */
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {

      /** кроме уже отмеченных. */
      if ((*it)->is_marked()) continue;

      /** Перебрать все рёбра, связанные с вершинами данного ребра, */
      auto v1 = (*it)->get_start();
      auto v2 = (*it)->get_end();

      for (auto it_e = v1->edges_cbegin(); it_e != v1->edges_cend(); ++it_e) {
        /** кроме проверяемого ребра. */
        if (*it_e == *it) continue;

        /** Проверка: ребра с такими же начальной и конечной вершиной не должно существовать. */
        if ((*it_e)->get_start() == v1 && (*it_e)->get_end() == v2) {
          printf("ERROR (reduce_edges): found equal edge in shell's edge list\n");
          return err_enum_t::ERROR_INTERNAL;
        }
        /** Когда будет найдено встречное ребро, */
        if ((*it_e)->get_start() == v2 && (*it_e)->get_end() == v1) {
          /** отметить его. */
          if (!(*it)->is_marked()) {
            (*it_e)->set_mark(*it);
          }
          else {
            /** Проверка: найденное встречное ребро не должно быть отмечено. */
            printf("ERROR (reduce_edges): found marked reverse edge in shell's edge list\n");
            return err_enum_t::ERROR_INTERNAL;
          }
          break;
        }
      }
    }

    /**
     * Перебрать все рёбра в списке фигуры, установить немаркированному ребру
     * значение правой грани из значения левой грани встречного отмеченного ребра.
     */
    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      /** Метка отмеченного ребра - это ссылка на встречное неотмеченное ребро. */
      edge* e = static_cast<edge*>(const_cast<void*>((*it)->get_mark()));
      if (e != nullptr) {
        if (e->is_marked()) {
          /** Проверка: найденное встречное ребро не должно быть отмечено. */
          printf("ERROR (reduce_edges): found marked reverse edge in shell's edge list\n");
          return err_enum_t::ERROR_INTERNAL;
        }
        /**  Установить найденному встречному ребру значение правой грани. */
        e->set_right((*it)->get_left());
      }
    }

    /**
     * Шаг 2 - перебрать все направленные рёбра, указатели на отмеченные рёбра
     * заменить на указатели на парные им неотмеченные.
     */

     /** Перебрать грани. */
    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
      /** Перебрать границы грани. */
      for (auto it_b = (*it)->borders_begin(); it_b != (*it)->borders_end(); ++it_b) {
        /** Перебрать направленные рёбра границы грани. */
        for (auto it_e = (*it_b).edges_begin(); it_e != (*it_b).edges_end(); ++it_e) {
          /** Заменить отмеченное ребро на встречное. */
          const edge* e = (*it_e).get_base_edge();
          if (e->is_marked()) {
            const edge* new_e = static_cast<const edge*>(e->get_mark());
            if ((*it_e).get_direction() != true) {
              /** Проверка: заменяемое направленное ребро должно идти в прямом направлении. */
              printf("ERROR (reduce_edges): found marked edge is not 'direct' but 'reverse'\n");
              return err_enum_t::ERROR_INTERNAL;
            }
            (*it_e).set(new_e, false);
          }
        }
      }
    }

    /**
     * Шаг 3 - удалить отмеченные рёбра из списка рёбер фигуры.
     */

     /** Перебрать все отмеченные рёбра в списке фигуры. */
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
    return err_enum_t::ERROR_OK;
  }

  err_enum_t shell::merge_faces(bool debug) {

    /** Список объединённых граней */
    std::vector<face*> unated_shell_faces;

    /** Снять пометки с граней */
    unmark_faces();

    if (debug) {
      printf("****** merge_faces started ******\n");
      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        printf("Old ");
        (*it)->print(this);
        printf("\n");
      }
    }

    /**
     * Шаги 1-5 выполняются в цикле до исчерпания списка граней фигуры.
     */
    for (; !faces.empty();) {

      /** Снять пометки с вершин */
      unmark_vertexes();

      /** Список необработанных граней */
      std::vector<const face*>   new_faces;
      /** Список необработанных вершин */
      std::vector<const vertex*> new_verts;

      /**
       * Шаг 1 - пометить группы граней, котрые войдут в объединённую грань.
       */

      if (debug) {
        printf("********************* STEP 1 ***************************\n");
      }

      /** Взять первую грань из списка граней фигуры */
      const face* first_face = *faces.cbegin();

      if (first_face->is_marked()) {
        printf("ERROR: marked old face on 'step 1' at 'merge_faces'");
        return err_enum_t::ERROR_INTERNAL;
      }

      /** Определить нормаль объединяемой грани по нормали первой грани */
      geometry::vector base_normal = (first_face)->get_normal();

      /** Создать объединённую грань с указанной нормалью */
      face* unated_face = new face(base_normal);

      /** Пометить первую грань */
      first_face->set_mark(unated_face);

      /** Добавить в список необработанных граней первую грань */
      new_faces.push_back(first_face);

      if (debug) {
        printf("Base ");
        first_face->print(this);
        printf("\n");
      }

      /** Цикл продолжается до опустошения одного из списков необработанных (вершин и граней). */
      for (;;) {

        // Создание списка указателей необработанных вершин по списку указателей необработанных граней
        new_verts.clear();

        /** Пометить непомеченные вершины, составляющие грани из списка необработанных граней, и внести их в список необработанных вершин */
        for (auto it = new_faces.cbegin(); it != new_faces.cend(); ++it) {
          for (auto it_b = (*it)->borders_cbegin(); it_b != (*it)->borders_cend(); ++it_b) {
            for (auto it_e = (*it_b).edges_cbegin(); it_e != (*it_b).edges_cend(); ++it_e) {
              const auto& ce = *it_e;
              const auto& e = ce.get_base_edge();
              //            const vertex* v = ce.get_direction() ? e->get_start() : e->get_end(); // Одна из вершин, обазующих текущую грань

                          // Обработка вершины
              const vertex* v1 = e->get_start();
              if (!v1->is_marked()) {
                v1->set_mark(unated_face);
                new_verts.push_back(v1);
              }

              const vertex* v2 = e->get_end();
              if (!v2->is_marked()) {
                v2->set_mark(unated_face);
                new_verts.push_back(v2);
              }
            }
          }
        }

        /** Завершить цикл, если список необработанных вершин пуст */
        if (new_verts.empty()) break;

        // Создание списка необработанных граней по списку необработанных вершин
        new_faces.clear();

        /** Пометить непомеченные грани, включающие вершины из списка необработанных вершины, и внести их в список необработанных граней */
        for (auto it = new_verts.cbegin(); it != new_verts.cend(); ++it) {
          // Перебор граней, включающих вершину
          for (auto it_e = (*it)->faces_cbegin(); it_e != (*it)->faces_cend(); ++it_e) {
            if (!(*it_e)->is_marked()) {
              if ((*it_e)->get_normal().is_equal(base_normal, EPSILON_Y)) {
                if (debug) {
                  printf("Adding ");
                  (*it_e)->print(this);
                  printf("\n");
                }
                (*it_e)->set_mark(unated_face);
                new_faces.push_back(*it_e);
              }
            }
          }
        }

        /** Завершить цикл, если список необработанных граней пуст */
        if (new_faces.empty()) break;
      }

      /**
       * Шаг 2 - перенести границы помеченных граней в новую грань.
       */

      for (auto it = faces.cbegin(); it != faces.cend(); ++it) {
        if ((*it)->get_mark() == unated_face) {
          for (auto it_b = (*it)->borders_cbegin(); it_b != (*it)->borders_cend(); ++it_b) {
            unated_face->add_border(*it_b);
          }
        }
      }

      /**
       * Шаг 3 - Заменить указатели на помеченные грани указателем на новую грань
       */

       /** для всех рёбер */
      for (auto it = vertexes.cbegin(); it != vertexes.cend(); ++it) {
        std::vector<const face*> new_faces_list;
        bool new_face_added = false;
        for (auto it_f = (*it)->faces_cbegin(); it_f != (*it)->faces_cend(); ++it_f) {
          if ((*it_f)->is_marked()) {
            assert((*it_f)->get_mark() == unated_face);
            if (!new_face_added) {
              new_faces_list.push_back(unated_face);
              new_face_added = true;
            }
          }
          else {
            new_faces_list.push_back(*it_f);
          }
        }
        (*it)->set_faces(new_faces_list);
      }

      /** и для всех вершин. */
      for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
        const face* left = (*it)->get_left();
        assert(left != nullptr);
        if (left->is_marked()) {
          assert(left->get_mark() == unated_face);
          (*it)->set_left(unated_face);
        }
        const face* right = (*it)->get_right();
        assert(right != nullptr);
        if (right->is_marked()) {
          assert(right->get_mark() == unated_face);
          (*it)->set_right(unated_face);
        }
      }

      /**
       * Шаг 4 - уничтожить помеченные грани как объекты и удалить их указатели из списка граней фигуры.
       */

      for (auto it = faces.cbegin(); it != faces.cend();) {
        if ((*it)->is_marked()) {
          assert((*it)->get_mark() == unated_face);
          /** Уничтожить объект-грань. */
          delete* it;
          /** Удалить указатель на грань из списка граней фигуры */
          it = faces.erase(it);
          continue;
        }
        ++it;
      }

      /**
       * Шаг 5 - добавить объединённую грань к списку объединённых граней.
       */

      if (debug) {
        printf("********************* STEP 5 ***************************\n");
        printf("New face #%4zu ", unated_shell_faces.size());
        unated_face->print(this);
        printf("\n");
      }

      unated_shell_faces.push_back(unated_face);
    }

    /** Заменить список граней фигуры списком объединённых граней */
    faces.swap(unated_shell_faces);
    return err_enum_t::ERROR_OK;
  }


  err_enum_t shell::reduce_edges(bool debug) {

    /** Снять пометки с рёбер */
    unmark_edges();

    /**
     * Шаг 6 - отметить лишние рёбра, принадлежащие одной грани.
     */

    if (debug) {
      printf("********************* STEP 6 ***************************\n");
    }

    for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
      if ((*it)->get_left() == (*it)->get_right()) {
        if (debug) {
          printf("mark ");
          (*it)->print(this);
          printf("\n");
        }
        (*it)->set_mark(this);
      }
      else {
        if (debug) {
          printf("left ");
          (*it)->print(this);
          printf("\n");
        }
      }
    }

    /**
     * Шаг 7 - для каждой грани удалить отмеченные рёбра из всех границ, объединить границы.
     */

    if (debug) {
      printf("********************* STEP 7 ***************************\n");
    }

    for (auto it = faces.begin(); it != faces.end(); ++it) {
      border new_border;

      if (debug) {
        (*it)->print(this);
        printf("\n");
      }


      size_t skipped = 0;

      /** Перебрать границы грани. */
      for (auto it_b = (*it)->borders_begin(); it_b != (*it)->borders_end(); ++it_b) {
        /** Перебрать направленные рёбра границы грани. */
        for (auto it_e = (*it_b).edges_begin(); it_e != (*it_b).edges_end(); ++it_e) {

          if (!(*it_e).get_base_edge()->is_marked()) {
            new_border.add_edge(*it_e);
          }
          else skipped++;
        }
      }

      if (debug) {
        printf("Added border: ");
        new_border.print(this);
        printf("\n");
      }

      if (new_border.edges_size() < 3) {
        printf("ERROR (reduce_edges): added border with number of edges < 3 in face #%4zu\n", std::distance(faces.begin(), it) + 1);
        return err_enum_t::ERROR_INTERNAL;
      }

      std::vector<border> new_borders;
      new_borders.push_back(new_border);
      (*it)->set_borders(new_borders);
    }

    if (debug) printf("****** merge_faces ended ******\n");

    return err_enum_t::ERROR_OK;
  }

  err_enum_t shell::split_edges_to_borders(bool debug) {

    for (auto it = faces.cbegin(); it != faces.cend(); ++it) {

      /** Проверка: в списке границ должна быть только одна граница */
      if ((*it)->borders_size() != 1) {
        printf("ERROR (split_edges_to_borders): more than 1 border in face #%4zu\n", std::distance(faces.cbegin(), it) + 1);
        return err_enum_t::ERROR_INTERNAL;
      }

      border old_border = *(*it)->borders_cbegin();
      /** Проверка: в старой границе должно быть не меньше трёх рёбер */
      if (old_border.edges_size() < 3) {
        printf("ERROR (split_edges_to_borders): border with number of edges < 3 in face #%4zu\n", std::distance(faces.cbegin(), it) + 1);
        return err_enum_t::ERROR_INTERNAL;
      }


      if (debug) {
        old_border.print(this);
        printf("\n");
      }

      std::vector<border> new_border_list;

      /** Цикл продолжается, пока в старой границе есть ориентированные рёбра. */
      for (; old_border.edges_size() != 0;) {

        border new_border;

        /** Взять из старой границы первое ориентированное ребро, */
        const auto& first_oedge = *old_border.edges_cbegin();
        /** запомнить его стартовую вершину - первую вершину новой грани, */
        const vertex* first_vertex = first_oedge.get_direction() ? first_oedge.get_base_edge()->get_start() : first_oedge.get_base_edge()->get_end();
        /** установить такое же значение для конечной вершины предыдущего ориентированного ребра. */
        const vertex* last_vertex = first_vertex;

        if (debug) { printf("New border. First vertex will be "); first_vertex->print(this); printf("\n"); }

        /** Цикл перебора ориентированных рёбер старой границы. */
        do {
          bool found_oriented_edge = false;
          /** Найти следующее ориентированное ребро, стартовая вершина которого является конечной вершиной предыдущего ребра. */
          for (auto it_e = old_border.edges_begin(); it_e != old_border.edges_end(); ++it_e) {
            const auto& e = (*it_e).get_base_edge();
            if (((*it_e).get_direction() ? e->get_start() : e->get_end()) == last_vertex) {
              /** Добавить это ориентированное ребро в новую границу. */
              new_border.add_edge(*it_e);
              /** Запомнить конечную вершину этого ориентированного ребра */
              last_vertex = (*it_e).get_direction() ? e->get_end() : e->get_start();
              /** Удалить это ориентированное ребро из старой границы. */
              old_border.remove(it_e);

              if (debug) {
                printf("face #%4zu: found %4zu edges, remained %4zu edegs\n",
                  std::distance(faces.cbegin(), it) + 1, new_border.edges_size(), old_border.edges_size());
                printf("Last vertex will be ");
                last_vertex->print(this);
                printf("\n");
              }
              found_oriented_edge = true;
              break;
            }
          }

          if (!found_oriented_edge) {
            printf("ERROR (split_edges_to_borders): can not close edge loop in face #%4zu (found %4zu edges, remained %4zu edegs)\n",
              std::distance(faces.cbegin(), it) + 1,
              new_border.edges_size(),
              old_border.edges_size());
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
}

#endif