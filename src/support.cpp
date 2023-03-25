/**
 * \file
 *
 * \brief Файл с определениями классов высокоуровневого интерфейса создания выходного файла.
 */

#ifndef TESTONLY

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"
#include "support.h"

uint64_t get_sys_time();

 /**
  * \brief Напечатать символ в качестве индикатора прогресса.
  *
  * \param [in] symbol выводимый на экран символ
  * \param [in] s кратность вывода
  */
static void print_dot(char symbol, int s) {
  static int l = 0;

  if ((l % s) == 0) {
#if defined(_MSC_VER)
    putchar(symbol);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    // Хак для Линукса, который выводит строку только после перевода строки
    static int n = 0;
    putchar(symbol);
    printf("\n%c[A", 0x1B);
    for (int i = 0; i < n; i++) printf("%c[C", 0x1B);
    n++;
#elif
#error Unknown C++ compiler
#endif
  }
  l++;
}

/**
 * \brief Получить системное время в миллисекундах.
 *
 * \return системное время
 */
#if defined(__GNUC__) || defined(__DOXYGEN__)
static uint64_t get_sys_time() {
  struct timespec spec;

  clock_gettime(CLOCK_REALTIME, &spec);

  return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
}
#endif


namespace express {


  STEP_API::STEP_API(const std::string& name) :
    g_name(name),

    start_full_time(0),
    optim_faces_time1(0),
    optim_faces_time2(0),
    optim_faces_time3(0),
    optim_shells_time(0),
    optim_clones_time(0),
    edges_reducing(0),
    creating_steps(0),
    writing_file(0),


    DEBUG_PRINT(false),
    DEBUG_PRINT2(false),
    DEBUG_PRINT3(false),
    PROFILING(false),

    OPTIM_FACES(true),
    OPTIM_CLONES(true),
    OPTIM_SEPARATION(true)

  {
    start_full_time = get_sys_time();

    // Единицы измерения: длина, угол и объёмный угол
    named_unit* t_legth_group = new length_unit();
    S.push_back(t_legth_group);
    auto t_si_unit = new si_unit(si_unit_name::metre, si_prefix::milli);
    noS.push_back(t_si_unit);
    t_legth_group->add_complex(t_si_unit);
    named_unit* t_angle_group = new plane_angle_unit();
    S.push_back(t_angle_group);
    t_si_unit = new si_unit(si_unit_name::radian);
    noS.push_back(t_si_unit);
    t_angle_group->add_complex(t_si_unit);
    named_unit* t_sangle_group = new solid_angle_unit();
    S.push_back(t_sangle_group);
    t_si_unit = new si_unit(si_unit_name::steradian);
    noS.push_back(t_si_unit);
    t_sangle_group->add_complex(t_si_unit);
    /**************************************************************************/
    // ISO 10303-41
    // Погрешность измерения длины
    auto t_unit1 = new unit(t_legth_group);
    noS.push_back(t_unit1);
    g_length_measure = new length_measure(EPSILON_X);
    noS.push_back(g_length_measure);
    g_measure_value = new measure_value(g_length_measure);
    noS.push_back(g_measure_value);
    g_uncert_measure_with_unit = new uncertainty_measure_with_unit(g_measure_value, t_unit1, "distance_accuracy_value", "confusion accuracy");
    S.push_back(g_uncert_measure_with_unit);
    // Все погрешности
    g_global_uncertainly_assigned_context = new global_uncertainty_assigned_context("", "");
    noS.push_back(g_global_uncertainly_assigned_context);
    g_global_uncertainly_assigned_context->uncertainty += g_uncert_measure_with_unit;
    // Все единицы измерения
    g_global_unit_assigned_context = new global_unit_assigned_context("", "");
    noS.push_back(g_global_unit_assigned_context);
    g_global_unit_assigned_context->units += (unit)*t_unit1;
    auto t_unit2 = new unit(t_angle_group);
    noS.push_back(t_unit2);
    g_global_unit_assigned_context->units += (unit)*t_unit2;
    auto t_unit3 = new unit(t_sangle_group);
    noS.push_back(t_unit3);
    g_global_unit_assigned_context->units += (unit)*t_unit3;
    // Геометрический контекст, точность представления (Формирование экземпляра сложного объекта (complex entity instance))
    g_representation_context_group = new geometric_representation_context("3D SPACE", "3D Context with UNIT and UNCERTAINTY", INTEGER(3));
    S.push_back(g_representation_context_group);
    g_representation_context_group->add_complex(g_global_uncertainly_assigned_context);
    g_representation_context_group->add_complex(g_global_unit_assigned_context);

    /**************************************************************************/
    // Контекст приложения - общий для всех изделий
    g_application_context = new application_context("automotive design");
    S.push_back(g_application_context);
    // Определение прикладного протокола - общее для всех изделий
    g_application_protocol_definition = new application_protocol_definition("draft international standard", "automotive_design", 1998, g_application_context);
    S.push_back(g_application_protocol_definition);
    /**************************************************************************/
    // Контекст изделия - общий для всех изделий
    g_product_context = new product_context("3D Mechanical Parts", g_application_context, "mechanical");
    S.push_back(g_product_context);
    // Изделие целиком
    g_product = new product(g_name, g_name);
    S.push_back(g_product);
    g_product->frame_of_reference += g_product_context;
    // Категория изделия - общая для всех изделий
    g_related_product_category = new product_related_product_category("part","");
    S.push_back(g_related_product_category);
    g_related_product_category->products += g_product;
    // Категория изделия - общая для всех изделий
    g_product_category = new product_category("part");
    S.push_back(g_product_category);
    // Определённыая версия (вариант, разновидность) базового изделия
    g_formation = new product_definition_formation("", "", g_product);
    S.push_back(g_formation);
    // Контекст определения изделия - общий для всех изделий
    g_product_definition_context = new product_definition_context("part definition", g_application_context, "design");
    S.push_back(g_product_definition_context);
    // Конктретный вид версии изделия
    //!!!
    const product_definition* g_product_definition = new product_definition("", "", g_formation, g_product_definition_context);
    S.push_back(g_product_definition);
    g_product_definition_or_reference = new product_definition_or_reference(g_product_definition);
    noS.push_back(g_product_definition_or_reference);

    /**************************************************************************/
    // Мировая система координат
    g_location = new cartesian_point("", 0, 0, 0);
    S.push_back(g_location);
    g_axis = new direction("", 0, 0, 1);
    S.push_back(g_axis);
    g_ref_direction = new direction("", 1, 0, 0);
    S.push_back(g_ref_direction);
    g_axis2_placement_3d = new axis2_placement_3d("", g_location, g_axis, g_ref_direction);
    S.push_back(g_axis2_placement_3d);

    /**************************************************************************/
    // Представление информации о форме
    g_shape_representation = new shape_representation("", g_representation_context_group);
    S.push_back(g_shape_representation);
    g_shape_representation->items += g_axis2_placement_3d;
    // Форма изделия

    //!!!
    auto t_characterized_product_definition = new characterized_product_definition(g_product_definition);
    noS.push_back(t_characterized_product_definition);
    auto t_characterized_definition = new characterized_definition(t_characterized_product_definition);
    noS.push_back(t_characterized_definition);
    g_product_definition_shape = new product_definition_shape("", "", t_characterized_definition);
    S.push_back(g_product_definition_shape);


    // Представление определённой формы
    //!!!
    auto t_definition = new represented_definition(g_product_definition_shape);
    noS.push_back(t_definition);
    g_shape_definition_representation = new shape_definition_representation(t_definition, g_shape_representation);
    S.push_back(g_shape_definition_representation);
  }


  err_enum_t STEP_API::save(const char* name) {

    FILE* out;

    if (DEBUG_PRINT) printf("Opening file '%s' for writing\n", name);

#if defined(_MSC_VER)
    const char* CRLF = "\n";
    errno_t err = fopen_s(&out, name, "wt");
    if (err != 0 || out == nullptr)
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    const char* CRLF = "\r\n";
    out = fopen(name, "wt");
    if (out == nullptr)
#elif
#error Unknown C++ compiler
#endif
    {
    printf("ERROR (save): can't open file '%s' for writing\n", name);
    return err_enum_t::ERROR_FILE_IO;
    }

    if (DEBUG_PRINT)  printf("Setting IDs\n");

    uint64_t start_time = get_sys_time();

    // Задать уникальные идентификаторы примитивам
    unsigned int k = 1;
    for (std::vector<const GENERIC_ENTITY*>::const_iterator Sit = S.begin(); Sit != S.end(); ++Sit) {
      if (*Sit != nullptr) (*Sit)->set_id(k++);
    }

    if (DEBUG_PRINT) printf("Writing primitives\n");

  // Получить текущие время/дату, записать заголовок
//  time_t now = time(0);
//  struct tm *tm = localtime(&now);

    // ISO 10303-21, 5.6
    fprintf(out, "ISO-10303-21;%s", CRLF);
    fprintf(out, "HEADER;%s", CRLF);
    fprintf(out, "FILE_DESCRIPTION( ('STEP AP214'), '1');%s", CRLF);
    fprintf(out, "FILE_NAME( '%s.step', '%i-%02i-%02iT%02i:%02i:%02i', ('Author'), (''), 'Processor', 'stl2step', '');%s",
      g_name.c_str(),
#if 0
      tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec,
#else
      2022, 2, 7, 17, 35, 32,
#endif
      CRLF);
    fprintf(out, "FILE_SCHEMA (( 'AUTOMOTIVE_DESIGN' ));%s", CRLF);
    fprintf(out, "ENDSEC;%s", CRLF);
    fprintf(out, "DATA;%s", CRLF);


    // Записать все примитивы
    for (auto ci = S.cbegin(); ci != S.cend(); ++ci) {
      if (*ci != nullptr) {
        fprintf(out, "%s%s", (*ci)->print().c_str(), CRLF);
        if (DEBUG_PRINT3) printf("%s\n", (*ci)->print().c_str());
      }
      else {
        printf("ERROR (save): Trying to print nullptr entity");
        fclose(out);
        return err_enum_t::ERROR_INTERNAL;
      }
    }

    // Записать окончание
    fprintf(out, "ENDSEC;%sEND-ISO-10303-21;%s", CRLF, CRLF);
    fclose(out);

    if (PROFILING) writing_file += get_sys_time() - start_time;

    return err_enum_t::ERROR_OK;
  }

  STEP_API::~STEP_API() {

    /** Уничтожение примитивов, которые были выведены в файл STEP */
    for (auto it = S.begin(); it != S.end(); ++it) {
      delete* it;
    }

    /** Уничтожение примитивов, которые не были выведены в файл STEP */
    for (auto it = noS.begin(); it != noS.end(); ++it) {
      delete* it;
    }
  }




err_enum_t STEP_API::process_file(
  const std::string& name,
  const std::string& shell_name,
  const std::string& path,
  const geometry::vector& color,
  double transparency,
  const std::vector<geometry::vector>& clones) {

  // Цвет объектов файла
  double R = color.getX();
  double G = color.getY();
  double B = color.getZ();

  // Имя файла материала с путём
  std::string f_name(path);
  f_name.append(name);

  // Имя материала без пути и расширения
  std::string m_name = str_remove_path(str_remove_ext(name));

  // Геометрический контекст, точность представления (формирование экземпляра сложного объекта (complex entity instance))
  representation_context* m_representation_context_group = new geometric_representation_context("", "", INTEGER(3));
  S.push_back(m_representation_context_group);
  m_representation_context_group->add_complex(g_global_uncertainly_assigned_context);
  m_representation_context_group->add_complex(g_global_unit_assigned_context);
  auto t_representation_context = new representation_context("", "");
  noS.push_back(t_representation_context);
  m_representation_context_group->add_complex(t_representation_context);

  // Изделие - набор фигур из одного материала
  product* m_product = new product(m_name, m_name);
  S.push_back(m_product);
  m_product->frame_of_reference += g_product_context;
  g_related_product_category->products += m_product;
  // Определённая версия (вариант, разновидность) базового изделия - для материала
  product_definition_formation* m_formation = new product_definition_formation("", "", m_product);
  S.push_back(m_formation);
  // Конктретный вид версии изделия
  product_definition* m_product_definition = new product_definition("", "", m_formation, g_product_definition_context);
  S.push_back(m_product_definition);

  product_definition_or_reference* m_product_definition_or_reference = new product_definition_or_reference(m_product_definition);
  noS.push_back(m_product_definition_or_reference);
  // **************************************************************************
  // Представление информации о форме
  shape_representation* m_shape_representation = new shape_representation("", m_representation_context_group);
  S.push_back(m_shape_representation);
  m_shape_representation->items += g_axis2_placement_3d;
  // Форма изделия - материал
  //!!!
  auto m_characterized_product_definition = new characterized_product_definition(m_product_definition);
  noS.push_back(m_characterized_product_definition);
  auto m_characterized_definition = new characterized_definition(m_characterized_product_definition);
  noS.push_back(m_characterized_definition);
  product_definition_shape* m_product_definition_shape = new product_definition_shape("", "", m_characterized_definition);
  S.push_back(m_product_definition_shape);
  // Представление определённой формы

  auto t_definition = new represented_definition(m_product_definition_shape);
  noS.push_back(t_definition);
  shape_definition_representation* m_shape_definition_representation = new shape_definition_representation(t_definition, m_shape_representation);
  S.push_back(m_shape_definition_representation);

  // Взаимосвязь между объектом в целом и материалом
  // Система координат объектов из одного материала
  cartesian_point* m_location = new cartesian_point("", 0, 0, 0);
  S.push_back(m_location);
  direction* m_axis = new direction("", 0, 0, 1);
  S.push_back(m_axis);
  direction* m_ref_direction = new direction("", 1, 0, 0);
  S.push_back(m_ref_direction);
  axis2_placement_3d* m_axis2_placement_3d = new axis2_placement_3d("", m_location, m_axis, m_ref_direction);
  S.push_back(m_axis2_placement_3d);
  m_shape_representation->items += m_axis2_placement_3d;
  // Определение преобразования

  //!!!
  item_defined_transformation* mg_item_defined_transformation = new item_defined_transformation("", m_axis2_placement_3d, g_axis2_placement_3d, "");
  S.push_back(mg_item_defined_transformation);
  transformation* t_transformation = new transformation(mg_item_defined_transformation);
  noS.push_back(t_transformation);

  // Отношение представления с преобразованием (формирование экземпляра сложного объекта (complex entity instance))
  representation_relationship* mg_representation_rel_group = new representation_relationship("", "", g_shape_representation, m_shape_representation);
  S.push_back(mg_representation_rel_group);

  const auto t_representation_relationship_with_transformation = new representation_relationship_with_transformation("", "", g_shape_representation, m_shape_representation, t_transformation);
  noS.push_back(t_representation_relationship_with_transformation);
  auto t_shape_representation_relationship = new shape_representation_relationship("", "", g_shape_representation, m_shape_representation);
  noS.push_back(t_shape_representation_relationship);
  mg_representation_rel_group->add_complex(t_representation_relationship_with_transformation);
  mg_representation_rel_group->add_complex(t_shape_representation_relationship);

  // Связь с объектом вышестоящей иерархии

  next_assembly_usage_occurrence* mg_next_assembl = new next_assembly_usage_occurrence("", m_name, m_name, g_product_definition_or_reference, m_product_definition_or_reference, "");
  S.push_back(mg_next_assembl);

  // Форма изделия
  //!!!
  auto t_characterized_product_definition = new characterized_product_definition(mg_next_assembl);
  noS.push_back(t_characterized_product_definition);
  auto t_characterized_definition = new characterized_definition(t_characterized_product_definition);
  noS.push_back(t_characterized_definition);
  product_definition_shape* mg_product_definition_shape = new product_definition_shape("", "", t_characterized_definition);
  S.push_back(mg_product_definition_shape);
  // Связь представления формы с определением изделия
  // !!!
  auto mg_context_dependent_shape_representation = new context_dependent_shape_representation(static_cast<const shape_representation_relationship*>(mg_representation_rel_group), mg_product_definition_shape);
  S.push_back(mg_context_dependent_shape_representation);
  // Цвет граней
  colour_rgb* m_colour_rgb = new colour_rgb("", R, G, B);
  S.push_back(m_colour_rgb);


  //!!! Прозрачность
  surface_style_element_select* m1_surface_style_element_select = nullptr;
  if (transparency != 1.0) {
    auto m_surface_style_transparent = new surface_style_transparent(transparency);
    S.push_back(m_surface_style_transparent);

    auto t_rendering_properties_select = new rendering_properties_select(m_surface_style_transparent);
    noS.push_back(t_rendering_properties_select);

    auto m_surface_style_rendering_with_properties = new surface_style_rendering_with_properties(shading_surface_method::val::constant_shading, m_colour_rgb);
    S.push_back(m_surface_style_rendering_with_properties);

    m_surface_style_rendering_with_properties->properties += t_rendering_properties_select;
    m1_surface_style_element_select = new surface_style_element_select(m_surface_style_rendering_with_properties);
    noS.push_back(m1_surface_style_element_select);
  }

  // Заполнение области цветом
  fill_area_style_colour* Fill_area_style_colour = new fill_area_style_colour("", m_colour_rgb);
  S.push_back(Fill_area_style_colour);

  auto t_fill_style_select = new fill_style_select(Fill_area_style_colour);
  noS.push_back(t_fill_style_select);
  // Стиль заполнения области цветом
  fill_area_style* m_fill_area_style = new fill_area_style("");
  S.push_back(m_fill_area_style);
  m_fill_area_style->fill_styles += t_fill_style_select;
  // Стиль заполнении области поверхности
  surface_style_fill_area* Surface_style_fill_area = new surface_style_fill_area(m_fill_area_style);
  S.push_back(Surface_style_fill_area);
  auto t_surface_style_element_select = new surface_style_element_select(Surface_style_fill_area);
  noS.push_back(t_surface_style_element_select);
  // Стиль поверхности
  surface_side_style* m_surface_side_style = new surface_side_style("");
  S.push_back(m_surface_side_style);
  m_surface_side_style->styles += t_surface_style_element_select;
  if (transparency != 1.0) {
    m_surface_side_style->styles += m1_surface_style_element_select;
  }
  // Использование стиля поверхности - для обоих сторон
  const auto t_surface_side_style_select = new surface_side_style_select(m_surface_side_style);
  noS.push_back(t_surface_side_style_select);

  surface_style_usage* Surface_style_usage = new surface_style_usage(surface_side::both, t_surface_side_style_select);
  S.push_back(Surface_style_usage);

  auto t_presentation_style_select = new presentation_style_select(Surface_style_usage);
  noS.push_back(t_presentation_style_select);
  // Присвоение стилей
  auto m_presentation_style_assignment = new presentation_style_assignment();
  S.push_back(m_presentation_style_assignment);
  m_presentation_style_assignment->styles += t_presentation_style_select;
  // Общее представление - 3D и свойства поверхности
  const auto m_mechanical_design_geometric_presentation_representation = new mechanical_design_geometric_presentation_representation("", g_representation_context_group);
  S.push_back(m_mechanical_design_geometric_presentation_representation);


  if (DEBUG_PRINT) {
    if (shell_name.empty()) {
      if (transparency != 1.0) {
        printf("Importing %s, colour = %.3f,%.3f,%.3f (%.3f)\n", f_name.c_str(), R, G, B, transparency);
      } else {
        printf("Importing %s, colour = %.3f,%.3f,%.3f\n", f_name.c_str(), R, G, B);
      }
    } else {
      if (transparency != 1.0) {
        printf("Importing %s (%s), colour = %.3f,%.3f,%.3f (%.3f)\n", f_name.c_str(), shell_name.c_str(), R, G, B, transparency);
      } else {
        printf("Importing %s (%s), colour = %.3f,%.3f,%.3f\n", f_name.c_str(), shell_name.c_str(), R, G, B);
      }
    }
  }

  std::vector<geometry::vector> F;                // Массив граней объекта

  err_enum_t err = prim3d::import(f_name, F);
  if (err != err_enum_t::ERROR_OK) return err;


  // Массив фигур как результат разбора граней по фигурам
  std::vector<prim3d::shell*> Shells;


  if (DEBUG_PRINT) printf("%zu faces, creating shells\n", F.size());

  uint64_t start_time = get_sys_time();

  prim3d::shell* sh = new prim3d::shell(F);

  if (OPTIM_SEPARATION) {
    Shells = sh->separate();
  }
  else {
    Shells.push_back(sh);
  }

  delete sh;

  // Перебор фигур: вычисление условного центра и "нормализация" координат относительно него
  for (auto it = Shells.begin(); it != Shells.end(); ++it) {
    (*it)->normalize_shell();
  }
  if (PROFILING) optim_shells_time += get_sys_time() - start_time;

  // Проверка наличия фигур в списке
  if (Shells.size() == 0) {
    printf("ERROR (process_file): no shells in file '%s'\n", name.c_str());
    return err_enum_t::ERROR_INTERNAL;
  }

  if (DEBUG_PRINT) {
    if (Shells.size() == 1) {
      printf("1 shell created:\n");
      printf("%zu faces, %zu vertexes. Pos=",
        (*Shells.begin())->faces_size(), (*Shells.begin())->vertexes_size());
      (*Shells.begin())->get_pos().print();
      printf("\n");
    }
    else {
      printf("%zu shells created:\n", Shells.size());
      for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
        printf("#%tu: %zu faces, %zu vertexes. Pos=",
          std::distance(Shells.cbegin(), it) + 1, (*it)->faces_size(), (*it)->vertexes_size());
        (*it)->get_pos().print();
        printf("\n");
      }
    }
  }

  // Выявление клонов
  if ((Shells.size() > 1) && OPTIM_CLONES) {

    if (DEBUG_PRINT) printf("Detecting clones\n");

    start_time = get_sys_time();
    // Тут приходится сравнивать кажую фигуру с каждой. Сортировка может ускорить этот этап.
    for (auto it_s1 = Shells.begin(); it_s1 != Shells.end(); ++it_s1) {
      for (auto it_s2 = it_s1 + 1; it_s2 != Shells.end(); ++it_s2) {
        if ((*it_s2)->is_clone()) {
          continue;
        }
        if (**it_s1 == **it_s2) {
          // it_s2 является клоном it_s1.
          (*it_s2)->set_clone(*it_s1);

          if (DEBUG_PRINT) printf("Clone found (%zu is clone of %zu)\n", std::distance(Shells.begin(), it_s2) + 1, std::distance(Shells.begin(), it_s1) + 1);
        }
      }
    }
    if (PROFILING) optim_clones_time += get_sys_time() - start_time;
  }

  start_time = get_sys_time();

  /** Перебор фигур: удаление парных рёбер */
  for (auto it = Shells.begin(); it != Shells.end(); ++it) {
    if ((*it)->is_clone()) continue;
    (*it)->merge_edges();
  }

  if (PROFILING)  edges_reducing += get_sys_time() - start_time;

  /** Перебор фигур: объединение треугольных граней в многоугольные */
  for (auto it = Shells.begin(); it != Shells.end(); ++it) {
    if ((*it)->is_clone()) continue;

    if (!DEBUG_PRINT) print_dot('.', 5);

    if (OPTIM_FACES) {
      if (DEBUG_PRINT) printf("Optimizing faces (shell #%zu of %zu)\n", std::distance(Shells.begin(), it) + 1, Shells.size());
      start_time = get_sys_time();
      err = (*it)->merge_faces(DEBUG_PRINT2);
      if (PROFILING)  optim_faces_time1 += get_sys_time() - start_time;
      if (err != err_enum_t::ERROR_OK) return err;
      start_time = get_sys_time();
      err = (*it)->reduce_edges(DEBUG_PRINT2);
      if (PROFILING)  optim_faces_time2 += get_sys_time() - start_time;
      if (err != err_enum_t::ERROR_OK) return err;
      start_time = get_sys_time();
      err = (*it)->split_edges_to_borders(DEBUG_PRINT3);
      if (PROFILING)  optim_faces_time3 += get_sys_time() - start_time;
      if (err != err_enum_t::ERROR_OK) return err;
    }
  }

  if (DEBUG_PRINT) printf("Creating %zu STEP shells\n", Shells.size());
  // Цикл по всем фигурам
  start_time = get_sys_time();
  for (auto it_s = Shells.begin(); it_s != Shells.end(); ++it_s) {
    (*it_s)->reset_mark();
    // кроме клонов!
    if ((*it_s)->is_clone()) {
      if (DEBUG_PRINT) printf("Skipped STEP shell clone #%zu of %zu\n", std::distance(Shells.begin(), it_s) + 1, Shells.size());
      continue;
    }

    err = CreateShell(**it_s);
    if (err != err_enum_t::ERROR_OK) return err;

    if (DEBUG_PRINT) printf("Created STEP shell  #%zu of %zu (%zu faces, %zu edges, %zu vertexes)\n",
      std::distance(Shells.begin(), it_s) + 1, Shells.size(), (*it_s)->faces_size(), (*it_s)->edges_size(), (*it_s)->vertexes_size());
  }

  // Создание объектов (фигур, закнутых оболочек)
  if (DEBUG_PRINT) printf("Creating %zu STEP products\n", Shells.size());

  for (auto it_s = Shells.cbegin(); it_s != Shells.cend(); ++it_s) {
    // Оболочка из граней
    char sname[100];
    const closed_shell* s_closed_shell;
    bool save_shell = false;
    size_t source = -1;
    if ((*it_s)->is_clone()) {
      // Это клон - ссылаемся на существующую фигуру
      const auto& orig_shell = *(*it_s)->get_clone();
      s_closed_shell = static_cast<const closed_shell*>(orig_shell.get_mark());
      // Определить номер, на какую фигуру ссылается клон.
      for (auto it_s2 = Shells.cbegin(); it_s2 != Shells.cend(); ++it_s2) {
        if (*it_s2 == &orig_shell) {
          source = std::distance(Shells.cbegin(), it_s2) + 1;
          break;
        }
      }
      sprintf(sname, "%s (clone of #%zu), shell #%zu of %zu", shell_name.empty() ? "object" : shell_name.c_str(), source, std::distance(Shells.cbegin(), it_s) + 1, Shells.size());
    } else {
      // Это оригинальная фигура - состоит из граней
      s_closed_shell = static_cast<const closed_shell*>((*it_s)->get_mark());
      save_shell = true;
      if (Shells.size() > 1) {
        sprintf(sname, "%s, shell #%zu of %zu", shell_name.empty() ? "object" : shell_name.c_str(), std::distance(Shells.cbegin(), it_s) + 1, Shells.size());
      } else {
        sprintf(sname, "%s", shell_name.empty() ? "object" : shell_name.c_str());
      }
    }

    process_shell(sname,
    s_closed_shell,
    save_shell,
    m_presentation_style_assignment,
    m_mechanical_design_geometric_presentation_representation,
    m_axis2_placement_3d,
    m_shape_representation,
    m_product_definition_or_reference,
    (*it_s)->get_pos());

    // Перебор координат смещения копий фигуры
    for (auto vit = clones.cbegin(); vit != clones.cend(); ++vit) {

      char cname[100];
      if ((*it_s)->is_clone()) {
        if (clones.size() > 1) {
          sprintf(cname, "%s (clone of #%zu, copy %zu of %zu), shell #%zu of %zu",
            shell_name.empty() ? "object" : shell_name.c_str(),
            source,
            std::distance(clones.cbegin(), vit) + 1,
            clones.size(),
            std::distance(Shells.cbegin(), it_s) + 1,
            Shells.size());

        } else {
          sprintf(cname, "%s (clone of #%zu, copy), shell #%zu of %zu",
            shell_name.empty() ? "object" : shell_name.c_str(),
            source,
            std::distance(Shells.cbegin(), it_s) + 1,
            Shells.size());
        }
      } else {
        if (Shells.size() > 1) {
          if (clones.size() > 1) {
            sprintf(cname, "%s (copy #%zu of #%zu), shell #%zu of %zu",
              shell_name.empty() ? "object" : shell_name.c_str(),
              std::distance(clones.cbegin(), vit) + 1,
              clones.size(),
              std::distance(Shells.cbegin(), it_s) + 1,
              Shells.size());
          } else {
            sprintf(cname, "%s (copy), shell #%zu of %zu",
              shell_name.empty() ? "object" : shell_name.c_str(),
              std::distance(Shells.cbegin(), it_s) + 1,
              Shells.size());
          }
        } else {
          if (clones.size() > 1) {
            sprintf(cname, "%s (copy #%zu of %zu)",
              shell_name.empty() ? "object" : shell_name.c_str(),
              std::distance(clones.cbegin(), vit) + 1,
              clones.size());
          } else {
            sprintf(cname, "%s (copy)",
              shell_name.empty() ? "object" : shell_name.c_str());
          }
        }
      }

      process_shell(cname,
        s_closed_shell,
        false,
        m_presentation_style_assignment,
        m_mechanical_design_geometric_presentation_representation,
        m_axis2_placement_3d,
        m_shape_representation,
        m_product_definition_or_reference,
        *vit + (*it_s)->get_pos());
    }
  }

  for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
    delete* it;
  }

  if (PROFILING) creating_steps += get_sys_time() - start_time;


  return err_enum_t::ERROR_OK;
}

err_enum_t STEP_API::CreateShell(const prim3d::shell & sh)
{
  closed_shell* s_closed_shell = new closed_shell("");
  sh.set_mark(s_closed_shell);

  /** Снять пометки с вершин */
  sh.unmark_vertexes();
  /** Снять пометки с рёбер */
  sh.unmark_edges();

  /** Цикл по всем граням фигуры для создания граней advanced_face */
  for (auto it_f = sh.faces_cbegin(); it_f != sh.faces_cend(); ++it_f) {

    if (!DEBUG_PRINT) print_dot('.', 300);

    // Проверка грани на наличие границ
    if ((*it_f)->borders_size() == 0) {
      printf("ERROR (CreateShell): Face with no bordres\n");
      return err_enum_t::ERROR_INTERNAL;
    }

    // Проверка списка границ грани
    for (auto it = (*it_f)->borders_cbegin(); it != (*it_f)->borders_cend(); ++it) {
      if ((*it).edges_size() < 3) {
        printf("ERROR (CreateShell): face #%zu, border #%zu with %zu edges/vertexes\n",
          std::distance(sh.faces_cbegin(), it_f) + 1,
          std::distance((*it_f)->borders_cbegin(), it) + 1,
          (*it).edges_size());
        return err_enum_t::ERROR_INTERNAL;
      }
    }

    if (DEBUG_PRINT2) {
      printf("Adding face #%zu from %zu: %zu borders (",
        std::distance(sh.faces_cbegin(), it_f) + 1, sh.faces_size(), (*it_f)->borders_size());
      for (auto it = (*it_f)->borders_cbegin(); it != (*it_f)->borders_cend(); ++it) {
        printf("%zu ", (*it).edges_size());
      }
      printf(")\n");
    }

    // Направление - ось Z в системе координат грани (нормаль к грани)
    const geometry::vector& normal = (*it_f)->get_normal();
    // направление - нормаль к грани
    direction* norm_dir = new direction("", normal.getX(), normal.getY(), normal.getZ());

    // Первая граница
    const prim3d::border& b = *(*it_f)->borders_cbegin();

    // Первое направленное ребро первой границы
    const prim3d::oriented_edge& ce1 = *b.edges_cbegin();

    // Ребро, на которое ссылается направленное
    const prim3d::edge* e1 = ce1.get_base_edge();

    const prim3d::vertex* fv1 = e1->get_start();
    const prim3d::vertex* fv2 = e1->get_end();

    geometry::vector fvd = geometry::vector(fv1->get_coord(), fv2->get_coord()).normalize();

    // Точка - начало отсчёта в системе координат грани (координаты первой вершины первой границы)
    const geometry::vector& vv1 = fv1->get_coord();
    cartesian_point* plane_cp = new cartesian_point("", vv1.getX(), vv1.getY(), vv1.getZ());
    // Направление - ось X в системе координат грани (направление точка 0 - точка 1)
    direction* plane_dir = new direction("", fvd.getX(), fvd.getY(), fvd.getZ());
    // Локальная система координат грани
    const axis2_placement_3d* plane_axis = new axis2_placement_3d("", plane_cp, norm_dir, plane_dir);
    // Плоскость грани - это плоскость XY в системе координат грани
    const plane* face_plane = new plane("", plane_axis);
    // Грань
    advanced_face* aface = new advanced_face("", face_plane, TRUE);

    // Добавить грань
    S.push_back(aface);
    // Добавить плоскость грани
    S.push_back(face_plane);
    // Добавить систему координат
    S.push_back(plane_axis);
    // Добавить точку
    S.push_back(plane_cp);
    // Добавить нормаль к грани
    S.push_back(norm_dir);
    // Добавить направление ребра грани
    S.push_back(plane_dir);

    // Перебор границ из списка границ грани
    for (auto it_l = (*it_f)->borders_cbegin(); it_l != (*it_f)->borders_cend(); ++it_l) {

      // Петля из рёбер
      edge_loop* Edge_loop = new edge_loop("");
      // Граница
      face_outer_bound* Face_outer_bound = new face_outer_bound("", Edge_loop, TRUE);

      S.push_back(Edge_loop);
      S.push_back(Face_outer_bound);
      aface->bounds += Face_outer_bound;

      // Перебор ориентированных рёбер границы
      for (auto it = (*it_l).edges_cbegin(); it != (*it_l).edges_cend(); ++it) {

        const prim3d::oriented_edge& ce2 = *it;
        const prim3d::edge* e2 = ce2.get_base_edge();

        const edge_curve* curve = static_cast<const edge_curve*>(e2->get_mark());

        if (curve == nullptr) {
          // кривая ребра не создана

          const prim3d::vertex* v1 = e2->get_start();
          const prim3d::vertex* v2 = e2->get_end();

          if (!v1->is_marked()) {
            const auto& crd = v1->get_coord();
            // Декартова точка
            const cartesian_point* p = new cartesian_point("", crd.getX(), crd.getY(), crd.getZ());
            // Точка вершины
            const vertex_point* v = new vertex_point("", p);
            v1->set_mark(v);
            S.push_back(v);
            S.push_back(p);
          }
          if (!v2->is_marked()) {
            // Декартова точка
            const geometry::vector& vv2 = v2->get_coord();
            const cartesian_point* p = new cartesian_point("", vv2.getX(), vv2.getY(), vv2.getZ());
            // Точка вершины
            const vertex_point* v = new vertex_point("", p);
            v2->set_mark(v);

            S.push_back(v);
            S.push_back(p);
          }

          // Вектор ребра
          geometry::vector vd = geometry::vector(v1->get_coord(), v2->get_coord()).normalize();
          // Направление ребра
          const direction* dir = new direction("", vd.getX(), vd.getY(), vd.getZ());
          // Вектор, задающий направление ребра
          const vector* vect = new vector("", dir, REAL(1.0));
          // Начальная точка отрезка
          const auto& evv = v1->get_coord();
          const cartesian_point* line_pc = new cartesian_point("", evv.getX(), evv.getY(), evv.getZ());
          // Отрезок, задающий рёбро
          const line* Line = new line("", line_pc, vect);
          // Кривая ребра
          curve = new edge_curve("", static_cast<const vertex*>(v1->get_mark()), static_cast<const vertex*>(v2->get_mark()), Line, TRUE);
          e2->set_mark(curve);

          S.push_back(curve);
          S.push_back(Line);
          S.push_back(line_pc);
          S.push_back(vect);
          S.push_back(dir);
        }

        // Ориентированное ребро
        oriented_edge* Edge = new oriented_edge("", curve, ce2.get_direction() ? TRUE : FALSE);
        // Добавить ориентированное ребро в границу
        Edge_loop->edge_list += Edge;
        S.push_back(Edge);
      }
    }
    s_closed_shell->cfs_faces += aface;
  }
  return err_enum_t::ERROR_OK;
}

void STEP_API::print_prof() const {

  if (writing_file + creating_steps + edges_reducing + optim_faces_time1 + optim_faces_time2 + optim_faces_time3 + optim_shells_time + optim_clones_time != 0) {
    long long unsigned full_time = get_sys_time() - start_full_time;

    printf("\nProfiling:\n");
    printf("Full time:                    %6llu ms\n", full_time);
    // Разбиение граней на отдельные фигуры
    if (optim_shells_time) printf("Shells separation:            %6llu ms (%2.2f%%)\n", optim_shells_time, 100.0 * optim_shells_time / full_time);
    // Выявление фигур-клонов
    if (optim_clones_time) printf("CLOSED SHELLs optimization:   %6llu ms (%2.2f%%)\n", optim_clones_time, 100.0 * optim_clones_time / full_time);
    // Удаление перных рёбер
    if (edges_reducing)    printf("Edges reducing:               %6llu ms (%2.2f%%)\n", edges_reducing, 100.0 * edges_reducing / full_time);
    // Объединение треугольных граней в многоугольные
    if (optim_faces_time1) printf("Faces optimization (step1):   %6llu ms (%2.2f%%)\n", optim_faces_time1, 100.0 * optim_faces_time1 / full_time);
    if (optim_faces_time2) printf("Faces optimization (step2):   %6llu ms (%2.2f%%)\n", optim_faces_time2, 100.0 * optim_faces_time2 / full_time);
    if (optim_faces_time3) printf("Faces optimization (step3):   %6llu ms (%2.2f%%)\n", optim_faces_time3, 100.0 * optim_faces_time3 / full_time);
    //  Создание примитивов STEP
    if (creating_steps)    printf("SPEP objects creating:        %6llu ms (%2.2f%%)\n", creating_steps, 100.0 * creating_steps / full_time);
    // Запись файла
    if (writing_file)      printf("File writing:                 %6llu ms (%2.2f%%)\n", writing_file, 100.0 * writing_file / full_time);
  }
}

  }

  std::string str_remove_ext(const std::string& filename) {
    std::string newname(filename);
    auto index = filename.rfind('.');
    if (index != std::string::npos) {
      newname.resize(index);
    }
    return newname;
  }

  std::string str_remove_path(const std::string& filename) {
    auto index1 = filename.rfind('\\');
    index1 = index1 == std::string::npos ? 0 : index1 + 1;
    auto index2 = filename.rfind('/');
    index2 = index2 == std::string::npos ? 0 : index2 + 1;
    return filename.substr(std::max(index1, index2));
  }

  std::string str_get_path(const std::string& filename) {
    std::string path(filename);
    size_t index1 = path.rfind('\\');
    index1 = index1 == std::string::npos ? 0 : index1 + 1;
    size_t index2 = path.rfind('/');
    index2 = index2 == std::string::npos ? 0 : index2 + 1;
    path.resize(std::max(index1, index2));
    return path;
  }


#endif