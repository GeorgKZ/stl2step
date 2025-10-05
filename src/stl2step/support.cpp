/**
 * \file
 *
 * \brief Файл с определениями методов классов высокоуровневого интерфейса создания выходного файла
 */

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"
#include "support.h"

 /**
  * \brief Напечатать символ в качестве индикатора прогресса.
  *
  * \param [in] symbol выводимый на экран символ
  * \param [in] s кратность вывода
  */
static void print_dot(char symbol, int s) {
  static int l = 0;

  if ((l % s) == 0) {
    std::cout.flush();
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::cout << symbol;
    std::setvbuf(stdout, nullptr, _IOLBF, 4 * 1024);
  }
  l++;
}

#if defined(__MINGW32__)
# include <windows.h>

  typedef union _UFILETIME {
    uint64_t   u64;
    FILETIME ft;
  } UFILETIME;

# ifndef POW10_9
#  define POW10_9                 1000000000
# endif

# ifndef POW10_7
#  define POW10_7                 10000000
# endif

# ifndef DELTA_EPOCH_IN_100NS
#  define DELTA_EPOCH_IN_100NS INT64_C(116444736000000000)
# endif
#endif

/**
 * \brief Получить системное время в миллисекундах.
 *
 * \return системное время
 */
static uint64_t get_sys_time(void) {
#if defined(_MSC_VER)
  SYSTEMTIME systime;
  FILETIME filetime;

  GetSystemTime(&systime);
  if (!SystemTimeToFileTime(&systime, &filetime)) {
    return 0;
  }

  union {
    uint64_t qword;
    struct {
      uint32_t low;
      uint32_t high;
    } dword;
  } ns_since_1601 = { 0 };

  // copy the result into the ULARGE_INTEGER; this is actually
  // copying the result into the ns_since_1601 int64_t.
  ns_since_1601.dword.low = filetime.dwLowDateTime;
  ns_since_1601.dword.high = filetime.dwHighDateTime;

  // Compute the number of milliseconds since 1601; we have to
  // divide by 10,000, since the current value is the number of 100ns
  // intervals since 1601, not ms.
  return (ns_since_1601.qword / 10000);
#elif defined(__GNUC__) || defined(__DOXYGEN__)

# if defined(__MINGW32__)
  UFILETIME ct;
  struct timespec spec;
  GetSystemTimeAsFileTime(&ct.ft);
  uint64_t t = ct.u64 - DELTA_EPOCH_IN_100NS;
  spec.tv_sec = t / POW10_7;
  spec.tv_nsec = ((int) (t % POW10_7)) * 100;
  return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
# else
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
# endif

#else
  #error Unknown C++ compiler
#endif

}

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
    auto t_si_unit = new si_unit(si_unit_name::val::metre, si_prefix::val::milli);
    noS.push_back(t_si_unit);
    t_legth_group->add_complex(t_si_unit);
    named_unit* t_angle_group = new plane_angle_unit();
    S.push_back(t_angle_group);
    t_si_unit = new si_unit(si_unit_name::val::radian);
    noS.push_back(t_si_unit);
    t_angle_group->add_complex(t_si_unit);
    named_unit* t_sangle_group = new solid_angle_unit();
    S.push_back(t_sangle_group);
    t_si_unit = new si_unit(si_unit_name::val::steradian);
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
    g_global_uncertainly_assigned_context->add_uncert(g_uncert_measure_with_unit);
    // Все единицы измерения
    g_global_unit_assigned_context = new global_unit_assigned_context();
    noS.push_back(g_global_unit_assigned_context);
    g_global_unit_assigned_context->add_unit(t_unit1);
    auto t_unit2 = new unit(t_angle_group);
    noS.push_back(t_unit2);
    g_global_unit_assigned_context->add_unit(t_unit2);
    auto t_unit3 = new unit(t_sangle_group);
    noS.push_back(t_unit3);
    g_global_unit_assigned_context->add_unit(t_unit3);
    // Геометрический контекст, точность представления (Формирование экземпляра сложного объекта (complex entity instance))
    g_representation_context_group = new geometric_representation_context("3D SPACE", "3D Context with UNIT and UNCERTAINTY", 3);
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
    g_product->add_frame(g_product_context);
    // Категория изделия - общая для всех изделий
    g_related_product_category = new product_related_product_category("part");
    S.push_back(g_related_product_category);
    g_related_product_category->add_product(g_product);
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
    g_axis = new direction("", 3, 0, 0, 1);
    S.push_back(g_axis);
    g_ref_direction = new direction("", 3, 1, 0, 0);
    S.push_back(g_ref_direction);
    g_axis2_placement_3d = new axis2_placement_3d("", g_location, g_axis, g_ref_direction);
    S.push_back(g_axis2_placement_3d);

    /**************************************************************************/
    // Представление информации о форме
    g_shape_representation = new shape_representation("", g_representation_context_group);
    S.push_back(g_shape_representation);
    g_shape_representation->add_item(g_axis2_placement_3d);
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

    if (DEBUG_PRINT) std::cout << "Opening file '" << name << "' for writing" << std::endl;

#if defined(_MSC_VER)
    const char* CRLF = "\n";
    errno_t err = fopen_s(&out, name, "wt");
    if (err != 0 || out == nullptr)
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    const char* CRLF = "\r\n";
    out = fopen(name, "wt");
    if (out == nullptr)
#else
# error Unknown C++ compiler
#endif
    {
      std::cout << "ERROR (save): can't open file '" << name << "' for writing" << std::endl;
      return err_enum_t::ERROR_FILE_IO;
    }

    if (DEBUG_PRINT) {
      std::cout << "Setting IDs" << std::endl;
    }

    uint64_t start_time = get_sys_time();

    // Задать уникальные идентификаторы примитивам
    unsigned int k = 1;
    for (std::vector<const STEP_ENTITY*>::const_iterator Sit = S.begin(); Sit != S.end(); ++Sit) {
      if (*Sit != nullptr) (*Sit)->set_id(k++);
    }

    if (DEBUG_PRINT) {
      std::cout << "Writing primitives" << std::endl;
    }

  // Получить текущие время/дату, записать заголовок
#ifndef CONSTANT_TIME
  time_t now = time(0);
  struct tm *tm = localtime(&now);
#endif

    // ISO 10303-21, 5.6
    fprintf(out, "ISO-10303-21;%s", CRLF);
    fprintf(out, "HEADER;%s", CRLF);
    fprintf(out, "FILE_DESCRIPTION( ('STEP AP214'), '2;1');%s", CRLF);
    fprintf(out, "FILE_NAME( '%s.step', '%i-%02i-%02iT%02i:%02i:%02i', ('Author'), (''), 'Processor', 'stl2step', '');%s",
      g_name.c_str(),
#ifndef CONSTANT_TIME
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
        if (DEBUG_PRINT3) {
//          std::cout << (*ci)->print() << std::endl;
        }
      }
      else {
        std::cout << "ERROR (save): Trying to print nullptr entity" << std::endl;
        fclose(out);
        return err_enum_t::ERROR_INTERNAL;
      }
    }

    // Записать окончание
    fprintf(out, "ENDSEC;%sEND-ISO-10303-21;%s", CRLF, CRLF);
    fclose(out);

    // Засечь время записи файла
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
  representation_context* m_representation_context_group = new geometric_representation_context("", "", 3);
  S.push_back(m_representation_context_group);
  m_representation_context_group->add_complex(g_global_uncertainly_assigned_context);
  m_representation_context_group->add_complex(g_global_unit_assigned_context);
  auto t_representation_context = new representation_context("", "");
  noS.push_back(t_representation_context);
  m_representation_context_group->add_complex(t_representation_context);

  // Изделие - набор фигур из одного материала
  product* m_product = new product(m_name, m_name);
  S.push_back(m_product);
  m_product->add_frame(g_product_context);
  g_related_product_category->add_product(m_product);
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
  m_shape_representation->add_item(g_axis2_placement_3d);
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
  direction* m_axis = new direction("", 3, 0, 0, 1);
  S.push_back(m_axis);
  direction* m_ref_direction = new direction("", 3, 1, 0, 0);
  S.push_back(m_ref_direction);
  axis2_placement_3d* m_axis2_placement_3d = new axis2_placement_3d("", m_location, m_axis, m_ref_direction);
  S.push_back(m_axis2_placement_3d);
  m_shape_representation->add_item(m_axis2_placement_3d);
  // Определение преобразования

  //!!!
  item_defined_transformation* mg_item_defined_transformation = new item_defined_transformation("", m_axis2_placement_3d, g_axis2_placement_3d);
  S.push_back(mg_item_defined_transformation);
  transformation* t_transformation = new transformation(mg_item_defined_transformation);
  noS.push_back(t_transformation);

  // Отношение представления с преобразованием (формирование экземпляра сложного объекта (complex entity instance))
  representation_relationship* mg_representation_rel_group = new representation_relationship("", "", g_shape_representation, m_shape_representation);
  S.push_back(mg_representation_rel_group);

  auto t_representation_relationship_with_transformation = new representation_relationship_with_transformation("", "", g_shape_representation, m_shape_representation, t_transformation);
  noS.push_back(t_representation_relationship_with_transformation);
  auto t_shape_representation_relationship = new shape_representation_relationship("", "", g_shape_representation, m_shape_representation);
  noS.push_back(t_shape_representation_relationship);
  mg_representation_rel_group->add_complex(t_representation_relationship_with_transformation);
  mg_representation_rel_group->add_complex(t_shape_representation_relationship);

  // Связь с объектом вышестоящей иерархии

  next_assembly_usage_occurrence* mg_next_assembl = new next_assembly_usage_occurrence("", m_name, m_name, g_product_definition_or_reference, m_product_definition_or_reference);
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

  // Прозрачность
  surface_style_element_select* m1_surface_style_element_select = nullptr;
  if (transparency != 1.0) {
    auto m_surface_style_transparent = new surface_style_transparent(transparency);
    S.push_back(m_surface_style_transparent);

    auto t_rendering_properties_select = new rendering_properties_select(m_surface_style_transparent);
    noS.push_back(t_rendering_properties_select);

    auto m_surface_style_rendering_with_properties = new surface_style_rendering_with_properties(shading_surface_method::val::constant_shading, m_colour_rgb);
    S.push_back(m_surface_style_rendering_with_properties);

    m_surface_style_rendering_with_properties->add_properties(t_rendering_properties_select);
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
  m_fill_area_style->add_style(t_fill_style_select);
  // Стиль заполнении области поверхности
  surface_style_fill_area* Surface_style_fill_area = new surface_style_fill_area(m_fill_area_style);
  S.push_back(Surface_style_fill_area);
  auto t_surface_style_element_select = new surface_style_element_select(Surface_style_fill_area);
  noS.push_back(t_surface_style_element_select);
  // Стиль поверхности
  surface_side_style* m_surface_side_style = new surface_side_style("");
  S.push_back(m_surface_side_style);
  m_surface_side_style->add_style(t_surface_style_element_select);
  if (transparency != 1.0) {
    m_surface_side_style->add_style(m1_surface_style_element_select);
  }

  // Использование стиля поверхности - для обоих сторон
  const auto t_surface_side_style_select = new surface_side_style_select(m_surface_side_style);
  noS.push_back(t_surface_side_style_select);

  surface_style_usage* Surface_style_usage = new surface_style_usage(surface_side::val::both, t_surface_side_style_select);
  S.push_back(Surface_style_usage);

  auto t_presentation_style_select = new presentation_style_select(Surface_style_usage);
  noS.push_back(t_presentation_style_select);
  // Присвоение стилей
  auto m_presentation_style_assignment = new presentation_style_assignment();
  S.push_back(m_presentation_style_assignment);
  m_presentation_style_assignment->add_style(t_presentation_style_select);
  // Общее представление - 3D и свойства поверхности
  mechanical_design_geometric_presentation_representation* m_mechanical_design_geometric_presentation_representation = new mechanical_design_geometric_presentation_representation("", g_representation_context_group);
  S.push_back(m_mechanical_design_geometric_presentation_representation);


  if (DEBUG_PRINT) {
    if (shell_name.empty()) {
      std::cout << "Importing " << f_name << ", colour = " << R << "," << G << "," << B << std::endl;
    } else {
      std::cout << "Importing " << f_name << " (" << shell_name << "), colour = " << R << "," << G << "," << B << std::endl;
    }
  }

  /**
   * Создать список нормалей и рёбер, испортировать в него файл.
   */
  std::vector<geometry::vector> F;
  err_enum_t err = prim3d::shell::import(f_name, F);
  if (err != err_enum_t::ERROR_OK) return err;

  if (DEBUG_PRINT) {
    std::cout << F.size() << " faces, creating shells" << std::endl;
  }

  uint64_t start_time;

  /**
   * Создать объединённую фигуру из импортированных граней.
   */
  prim3d::shell* sh = new prim3d::shell(F);

  /**
   * Для объединённой фигуры удалить парные рёбра в списке рёбер,
   * засечь время удаления парных рёбер.
   */
  start_time = get_sys_time();
  err = sh->merge_edges(DEBUG_PRINT2);
  if (err != err_enum_t::ERROR_OK) {
    if (!shell_name.empty()) std::cout << "Ошибка при обработке '" << shell_name << "'" << std::endl;
    delete sh;
    return err;
  }
  if (PROFILING) edges_reducing += get_sys_time() - start_time;

  /**
   * При необходимости разделить объединённую фигуру на отдельные фигуры, определить время
   * разделения на фигуры.
   */
  std::vector<prim3d::shell*> Shells;
  if (OPTIM_SEPARATION) {
    start_time = get_sys_time();
    // Массив фигур как результат разбора граней по фигурам
    Shells = sh->separate();
    delete sh;
    if (PROFILING) optim_shells_time += get_sys_time() - start_time;
  }
  else {
    // Объединённая фигура содержит только одну фигуру
    Shells.push_back(sh);
  }

  /**
   * При необходимости вычислить условный центр и выполнить "нормализацию" координат
   * относительно него для каждой фигуры, определить время нормализации координат.
   */
  if (OPTIM_CLONES) {
    start_time = get_sys_time();
    for (auto it = Shells.begin(); it != Shells.end(); ++it) {
      (*it)->normalize_shell();
    }
    if (PROFILING) optim_clones_time += get_sys_time() - start_time;
  }

  // Проверка наличия фигур в списке
  if (Shells.size() == 0) {
    std::cout << "ERROR (process_file): отсутствуют фигуры в файле '" << name << "'" << std::endl;
    return err_enum_t::ERROR_INTERNAL;
  }

  if (DEBUG_PRINT) {
    if (Shells.size() == 1) {
      std::cout << "создана фигура:" << std::endl <<
      (*Shells.begin())->faces_num() << " faces, " << 
      (*Shells.begin())->vertexes_num() << " vertexes. Pos=" <<
      (*Shells.begin())->get_pos();
    }
    else {
      std::cout << Shells.size() << " фигур создано:" << std::endl;
      for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
        std::cout << std::distance(Shells.cbegin(), it) + 1 << ": " << (*it)->faces_num() << \
        " " << (*it)->vertexes_num() << " вершин. Условный центр=" << (*it)->get_pos();
      }
    }
    std::cout << std::endl;
  }

  /**
   * При необходимости выполнить выявление клонов фигур, определить время выяления клонов.
   */
  if ((Shells.size() > 1) && OPTIM_CLONES) {

    if (DEBUG_PRINT) {
      std::cout << "Выявление фигур-клонов" << std::endl;
    }

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
          if (DEBUG_PRINT) std::cout << "Clone found (" << std::distance(Shells.begin(), it_s2) + 1 << " is clone of " << std::distance(Shells.begin(), it_s1) + 1 << std::endl;
        }
      }
    }
    if (PROFILING) optim_clones_time += get_sys_time() - start_time;

    if (DEBUG_PRINT3) {
      for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
        (*it)->print();
      }
    }
  }

  /**
   * При необходимости для каждой фигуры объединенить соседние треугольные грани, лежащие
   * в одной плоскости, в многоугольные. Определить время каждого шага объединения.
   */
  if (OPTIM_FACES) {
    for (auto it = Shells.begin(); it != Shells.end(); ++it) {
      if ((*it)->is_clone()) continue;

      if (DEBUG_PRINT) {
        std::cout << "Объединение плоских граней (фигура #" << std::distance(Shells.begin(), it) + 1 << " из " << Shells.size() << ")" << std::endl;
      } else {
        print_dot('.', 5);
      }

      start_time = get_sys_time();
      (*it)->merge_faces(DEBUG_PRINT2);
      if (PROFILING) optim_faces_time1 += get_sys_time() - start_time;

      start_time = get_sys_time();
      err = (*it)->reduce_edges(DEBUG_PRINT2);
      if (PROFILING) optim_faces_time2 += get_sys_time() - start_time;
      if (err != err_enum_t::ERROR_OK) return err;

      start_time = get_sys_time();
      err = (*it)->split_edges_to_borders(DEBUG_PRINT3);
      if (PROFILING) optim_faces_time3 += get_sys_time() - start_time;
      if (err != err_enum_t::ERROR_OK) return err;
    }
  }

  if (DEBUG_PRINT) std::cout << "Creating " << Shells.size() << " STEP shells" << std::endl;
  // Цикл по всем фигурам
  start_time = get_sys_time();
  for (auto it_s = Shells.begin(); it_s != Shells.end(); ++it_s) {
    (*it_s)->reset_mark();
    // кроме клонов!
    if ((*it_s)->is_clone()) {
      if (DEBUG_PRINT) std::cout << "Skipped STEP shell clone #" << std::distance(Shells.begin(), it_s) + 1 << " of " << Shells.size() << std::endl;
      continue;
    }

    err = CreateShell(**it_s);
    if (err != err_enum_t::ERROR_OK) return err;

    if (DEBUG_PRINT) std::cout << "Created STEP shell  #" << std::distance(Shells.begin(), it_s) + 1 << " of " << Shells.size() << " (" << (*it_s)->faces_num() << " faces, " << (*it_s)->edges_num() << " edges, " << (*it_s)->vertexes_num() << " vertexes)" << std::endl;
  }

  // Создание объектов (фигур, закнутых оболочек)
  if (DEBUG_PRINT) std::cout << "Creating " << Shells.size() << " STEP products" << std::endl;

  for (auto it_s = Shells.cbegin(); it_s != Shells.cend(); ++it_s) {
    // Оболочка из граней
    std::stringstream sname;
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
      sname << (shell_name.empty() ? "object" : shell_name) << " (clone of #" << source << "), shell #" << std::distance(Shells.cbegin(), it_s) + 1 << " of " << Shells.size();
    } else {
      // Это оригинальная фигура - состоит из граней
      s_closed_shell = static_cast<const closed_shell*>((*it_s)->get_mark());
      save_shell = true;
      if (Shells.size() > 1) {
        sname << (shell_name.empty() ? "object" : shell_name) << ", shell #" << std::distance(Shells.cbegin(), it_s) + 1 << " of " << Shells.size();
      } else {
        sname << (shell_name.empty() ? "object" : shell_name.c_str());
      }
    }

    process_shell(sname.str(),
    **it_s,
    s_closed_shell,
    save_shell,
    m_presentation_style_assignment,
    m_mechanical_design_geometric_presentation_representation,
    m_axis2_placement_3d,
    m_shape_representation,
    m_product_definition_or_reference,
    nullptr);

    // Перебор координат смещения копий фигуры
    for (auto vit = clones.cbegin(); vit != clones.cend(); ++vit) {

      std::stringstream cname;
      if ((*it_s)->is_clone()) {
        if (clones.size() > 1) {
          cname << (shell_name.empty() ? "object" : shell_name /* .c_str() */ ) <<
            " (clone of #" << source <<
            ", copy " << std::distance(clones.cbegin(), vit) + 1 <<
            " of " << clones.size() <<
            "), shell #" << std::distance(Shells.cbegin(), it_s) + 1 << " of " << Shells.size();
        } else {
          cname << (shell_name.empty() ? "object" : shell_name.c_str()) <<
            " (clone of #" << source <<
            ", copy), shell #" << std::distance(Shells.cbegin(), it_s) + 1 <<
            " of " << Shells.size();
        }
      } else {
        if (Shells.size() > 1) {
          if (clones.size() > 1) {
            cname << (shell_name.empty() ? "object" : shell_name.c_str()) <<
              " (copy #" << std::distance(clones.cbegin(), vit) + 1 <<
              " of #" << clones.size() <<
              "), shell #" << std::distance(Shells.cbegin(), it_s) + 1 <<
              " of " << Shells.size();
          } else {
            cname << (shell_name.empty() ? "object" : shell_name.c_str()) <<
              " (copy), shell #" << std::distance(Shells.cbegin(), it_s) + 1 <<
              " of " << Shells.size();
          }
        } else {
          if (clones.size() > 1) {
            cname << (shell_name.empty() ? "object" : shell_name.c_str()) <<
              " (copy #" << std::distance(clones.cbegin(), vit) + 1 <<
              " of " << clones.size() << ")";
          } else {
            cname << (shell_name.empty() ? "object" : shell_name.c_str()) << " (copy)";
          }
        }
      }

      process_shell(cname.str(),
        **it_s,
        s_closed_shell,
        false,
        m_presentation_style_assignment,
        m_mechanical_design_geometric_presentation_representation,
        m_axis2_placement_3d,
        m_shape_representation,
        m_product_definition_or_reference,
        &*vit);
    }
  }

  for (auto it = Shells.cbegin(); it != Shells.cend(); ++it) {
    delete* it;
  }

  // Засечь время создания примитовов STEP
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
  for (auto it_f = sh.get_faces().cbegin(); it_f != sh.get_faces().cend(); ++it_f) {

    if (!DEBUG_PRINT) {
      print_dot('.', 300);
    }

    // Проверка грани на наличие границ
    if ((*it_f)->borders_num() == 0) {
      std::cout << "ERROR (CreateShell): Face with no bordres" << std::endl;
      return err_enum_t::ERROR_INTERNAL;
    }

    // Проверка списка границ грани
    for (auto it = (*it_f)->get_borders().cbegin(); it != (*it_f)->get_borders().cend(); ++it) {
      if ((*it).edges_num() < 3) {
        std::cout << "ERROR (CreateShell): face #" << std::distance(sh.get_faces().cbegin(), it_f) + 1 << \
          ", border #" << std::distance((*it_f)->get_borders().cbegin(), it) + 1 << " with " << (*it).edges_num() << " edges/vertexes" << std::endl;
        return err_enum_t::ERROR_INTERNAL;
      }
    }

    if (DEBUG_PRINT2) {
      std::cout << "Adding face #" << std::distance(sh.get_faces().cbegin(), it_f) + 1 << \
        " from " << sh.faces_num() << ": " << (*it_f)->borders_num() << \
        ((*it_f)->borders_num() == 1 ? " border (" : " borders (");
      for (auto it_borders = (*it_f)->get_borders().cbegin(); it_borders != (*it_f)->get_borders().cend(); ++it_borders) {
        std::cout << (*it_borders).edges_num() << " ";
      }
      std::cout << ")" << std::endl;
    }

    // Направление - ось Z в системе координат грани (нормаль к грани)
    const geometry::vector& normal = (*it_f)->get_normal();
    // направление - нормаль к грани
    direction* norm_dir = new direction("", 3, normal.getX(), normal.getY(), normal.getZ());

    // Первая граница
    const prim3d::border& b = *(*it_f)->get_borders().cbegin();

    // Первое направленное ребро первой границы
    const prim3d::oriented_edge& ce1 = *b.get_edges().cbegin();

    // Ребро, на которое ссылается направленное
    const prim3d::edge* e1 = ce1.get_base_edge();

    const prim3d::vertex* fv1 = e1->get_start();
    const prim3d::vertex* fv2 = e1->get_end();

    geometry::vector fvd = geometry::vector(fv1->get_coord(), fv2->get_coord()).normalize();

    // Точка - начало отсчёта в системе координат грани (координаты первой вершины первой границы)
    const geometry::vector& vv1 = fv1->get_coord();
    cartesian_point* plane_cp = new cartesian_point("", vv1.getX(), vv1.getY(), vv1.getZ());
    // Направление - ось X в системе координат грани (направление точка 0 - точка 1)
    direction* plane_dir = new direction("", 3, fvd.getX(), fvd.getY(), fvd.getZ());
    // Локальная система координат грани
    const axis2_placement_3d* plane_axis = new axis2_placement_3d("", plane_cp, norm_dir, plane_dir);
    // Плоскость грани - это плоскость XY в системе координат грани
    const plane* face_plane = new plane("", plane_axis);
    // Грань
    advanced_face* aface = new advanced_face("", face_plane, BTrue);

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
    for (auto it_l = (*it_f)->get_borders().cbegin(); it_l != (*it_f)->get_borders().cend(); ++it_l) {

      // Петля из рёбер
      edge_loop* Edge_loop = new edge_loop("");
      // Граница
      const face_outer_bound* Face_outer_bound = new face_outer_bound("", Edge_loop, BTrue);

      S.push_back(Edge_loop);
      S.push_back(Face_outer_bound);
      aface->add_bound(Face_outer_bound);

      // Перебор ориентированных рёбер границы
      for (auto it = (*it_l).get_edges().cbegin(); it != (*it_l).get_edges().cend(); ++it) {

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
          const direction* dir = new direction("", 3, vd.getX(), vd.getY(), vd.getZ());
          // Вектор, задающий направление ребра
          const vector* vect = new vector("", dir, 1);
          // Начальная точка отрезка
          const auto& evv = v1->get_coord();
          const cartesian_point* line_pc = new cartesian_point("", evv.getX(), evv.getY(), evv.getZ());
          // Отрезок, задающий рёбро
          const line* Line = new line("", line_pc, vect);
          // Кривая ребра
          curve = new edge_curve("", static_cast<const vertex*>(v1->get_mark()), static_cast<const vertex*>(v2->get_mark()), Line, BTrue);
          e2->set_mark(curve);

          S.push_back(curve);
          S.push_back(Line);
          S.push_back(line_pc);
          S.push_back(vect);
          S.push_back(dir);
        }

        // Ориентированное ребро
        const oriented_edge* Edge = new oriented_edge("", curve, ce2.get_direction() ? BTrue : BFalse);
        // Добавить ориентированное ребро в границу
        Edge_loop->add_edge(Edge);
        S.push_back(Edge);
      }
    }
    s_closed_shell->add_face(aface);
  }
  return err_enum_t::ERROR_OK;
}

void STEP_API::print_prof() const {

  if (writing_file + creating_steps + edges_reducing + optim_faces_time1 + optim_faces_time2 + optim_faces_time3 + optim_shells_time + optim_clones_time != 0) {
    long long unsigned full_time = get_sys_time() - start_full_time;

    std::cout << std::endl <<"Профилирование:" << std::endl;
                           std::cout << "Всего затрачено времени:      " << std::setw(6) << full_time         << " ms" << std::endl;
    // Разбиение граней на отдельные фигуры
    if (optim_shells_time) std::cout << "Разделение на фигуры:         " << std::setw(6) << optim_shells_time << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(optim_shells_time) / static_cast<double>(full_time) << "%)" << std::endl;
    // Выявление фигур-клонов
    if (optim_clones_time) std::cout << "Выявление клонов:             " << std::setw(6) << optim_clones_time << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(optim_clones_time) / static_cast<double>(full_time) << "%)" << std::endl;
    // Удаление парных рёбер
    if (edges_reducing)    std::cout << "Удаление парных рёбер:        " << std::setw(6) << edges_reducing    << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(edges_reducing) / static_cast<double>(full_time) << "%)" << std::endl;
    // Объединение треугольных граней в многоугольные
    if (optim_faces_time1) std::cout << "Объединение граней (шаг 1):   " << std::setw(6) << optim_faces_time1 << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(optim_faces_time1) / static_cast<double>(full_time) << "%)" << std::endl;
    if (optim_faces_time2) std::cout << "Объединение граней (шаг 2):   " << std::setw(6) << optim_faces_time2 << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(optim_faces_time2) / static_cast<double>(full_time) << "%)" << std::endl;
    if (optim_faces_time3) std::cout << "Объединение граней (шаг 3):   " << std::setw(6) << optim_faces_time3 << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(optim_faces_time3) / static_cast<double>(full_time) << "%)" << std::endl;
    //  Создание примитивов STEP
    if (creating_steps)    std::cout << "Создание примитивов SPEP:     " << std::setw(6) << creating_steps    << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(creating_steps) / static_cast<double>(full_time) << "%)" << std::endl;
    // Запись файла
    if (writing_file)      std::cout << "Запись файла:                 " << std::setw(6) << writing_file      << " ms (" << std::fixed << std::setprecision(2) << 100.0 * static_cast<double>(writing_file) / static_cast<double>(full_time) << "%)" << std::endl;
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
