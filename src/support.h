/**
 * \file
 *
 * \brief Файл с описаниями классов высокоуровневого интерфейса создания выходного файла.
 */

#ifndef _SUPPORT_H
#define _SUPPORT_H

#include "stdafx.h"
#include <time.h>
#include <stdio.h>
#include <string>

#include "err.h"
#include "geometry.h"
#include "shell.h"
#include "express.h"

namespace express {

  /**
   * \brief Высокоуровневый интерфейс для создания файла STEP.
   */
  class STEP_API {

  private:

    /** Массив сохраняемых в файл STEP, то есть именованных объектов */
    std::vector<const express::GENERIC_ENTITY*> S;

    /** Массив несохраняемых в файл STEP, то есть неименованных объектов */
    std::vector<const express::GENERIC*> noS;

    length_measure* g_length_measure;
    measure_value* g_measure_value;
    uncertainty_measure_with_unit* g_uncert_measure_with_unit;
    global_uncertainty_assigned_context* g_global_uncertainly_assigned_context;
    global_unit_assigned_context* g_global_unit_assigned_context;
    product_context* g_product_context;
    product* g_product;
    product_related_product_category* g_related_product_category;
    product_category* g_product_category;
    product_definition_formation* g_formation;
    application_context* g_application_context;
    application_protocol_definition* g_application_protocol_definition;
    product_definition_context* g_product_definition_context;
    product_definition_or_reference* g_product_definition_or_reference;
    shape_representation* g_shape_representation;
    axis2_placement_3d* g_axis2_placement_3d;
    representation_context* g_representation_context_group;
    cartesian_point* g_location;
    direction* g_axis;
    direction* g_ref_direction;
    product_definition_shape* g_product_definition_shape;
    shape_definition_representation* g_shape_definition_representation;

    /** Имя выходного файла без расширения и без пути */
    std::string                               g_name;

    /** Полное время обработки */
    long long unsigned                        start_full_time;
    /** Объединение треугольных граней в многоугольные (новые грани) */
    long long unsigned                        optim_faces_time1;
    /** Объединение треугольных граней в многоугольные (удаление рёбер) */
    long long unsigned                        optim_faces_time2;
    /** Объединение треугольных граней в многоугольные (составление границ) */
    long long unsigned                        optim_faces_time3;
    /** Разбиение граней на отдельные фигуры */
    long long unsigned                        optim_shells_time;
    /** Выявление фигур-клонов */
    long long unsigned                        optim_clones_time;
    /** Удаление парных рёбер */
    long long unsigned                        edges_reducing;
    /** Создание примитивов STEP */
    long long unsigned                        creating_steps;
    /** Запись файла STEP */
    long long unsigned                        writing_file;

    /** Отладочный вывод, уровень 1 */
    bool                                      DEBUG_PRINT;
    /** Отладочный вывод, уровень 2 */
    bool                                      DEBUG_PRINT2;
    /** Отладочный вывод, уровень 3 */
    bool                                      DEBUG_PRINT3;
    /** Измерять временные интервалы операций */
    bool                                      PROFILING;

    /** Объединять треугольные грани в многоугольные */
    bool                                      OPTIM_FACES;
    /** Выявлять клоны объектов */
    bool                                      OPTIM_CLONES;
    /** Выполнять разделение треугольников из STL на фигуры */
    bool                                      OPTIM_SEPARATION;

  public:

    /**
     * \brief Конструктор класса STEP_API
     *
     * \param [in] name имя создаваемого файла STEP
     */
    STEP_API(const std::string& name);

    /**
     * Деструктор класса STEP_API.
     *
     */
    ~STEP_API();

    /**
     * \brief Формирование структур иерархии STEP на основе импортированного файла STL.
     *
     * \param [in] name имя файла STL
     * \param [in] shell_name имя фигуры, изображённой в файле STL
     * \param [in] path путь к файлу STL
     * \param [in] color цвет, в который должны быть раскрашены фигуры, полученные из файла STL
     * \param [in] transparency прозрачность фигур, полученных из файла STL (0.0 - полная прозрачность, 1.0 - непрозрачность)
     * \param [in] clones список смещений для формирования фигур-клонов
     * \return код ошибки или ERROR_OK в случае успешного завершения
     */
    err_enum_t process_file(
      const std::string& name,
      const std::string& shell_name,
      const std::string& path,
      const geometry::vector& color,
      double transparency,
      const std::vector<geometry::vector>& clones);

    /**
     * \brief Формирование структур иерархии STEP на для однй фигуры.
     * \param [in] product_name Название изделия в иерархии
     * \param [in] s_closed_shell Объект "Замкнутая оболочка"
     * \param [in] save_shell необходимость указать в выходном файле объект "Замкнутая оболочка"
     * \param [in] m_presentation_style_assignment Объект "Присвоение стиля представления"
     * \param [in out] m_mechanical_design_geometric_presentation_representation !!!
     * \param [in] m_axis2_placement_3d Объект "Расположение трёхмерного объекта по двум осям"
     * \param [in] m_shape_representation Объект "Представление формы"
     * \param [in] m_product_definition_or_reference Объект "Определение продукта или ссылка"
     * \param [in] pos Координаты центра фигуры
     */
    err_enum_t process_shell(
      const std::string& product_name,
      const closed_shell* s_closed_shell,
      bool save_shell,
      const presentation_style_assignment* m_presentation_style_assignment,
      mechanical_design_geometric_presentation_representation* m_mechanical_design_geometric_presentation_representation,
      const axis2_placement_3d* m_axis2_placement_3d,
      const shape_representation* m_shape_representation,
      const product_definition_or_reference* m_product_definition_or_reference,
      const geometry::vector& pos);

    /**
     * \brief Создать объекты иерархии STEP для фигуры sh.
     *
     * \param [in] sh фигура
     * \return код ошибки
     */
    err_enum_t CreateShell(const prim3d::shell& sh);

    /**
     * \brief Сохранить файл в формате STEP.
     *
     * \param [in] name имя файла STEP
     * \return ошибки или ERROR_OK в случае успешного завершения
     */
    err_enum_t save(const char* name);

    /**
     * \brief Вывод на экран результатов профилирования.
     *
     */
    void print_prof() const;

    /**
     * \brief Включить или выключть отладочный вывод, уровень 1
     *
     * \param [in] val значение отладочного вывода, уровень 1
     */
    void set_debug_print1(bool val) {
      DEBUG_PRINT = val;
    }

    /**
     * \brief Получить значение отладочного вывода, уровень 1
     * \return возвращаемое значение отладочного вывода, уровень 1
     */
    bool get_debug_print1() const { return DEBUG_PRINT; }

    /**
     * \brief Включить или выключть отладочный вывод, уровень 2
     *
     * \param [in] val значение отладочного вывода, уровень 2
     */
    void set_debug_print2(bool val) {
      DEBUG_PRINT = val;
      DEBUG_PRINT2 = val;
    }

    /**
     * \brief Включить или выключть отладочный вывод, уровень 3
     *
     * \param [in] val значение отладочного вывода, уровень 3
     */
    void set_debug_print3(bool val) {
      DEBUG_PRINT = val;
      DEBUG_PRINT2 = val;
      DEBUG_PRINT3 = val;
    }

    /**
     * \brief Включить или выключить режим объединения треугольных граней в многоугольные
     *
     * \param [in] val значение режима объединения треугольных граней в многоугольные
     */
    void set_optim_faces(bool val) {
      OPTIM_FACES = val;
    }

    /**
     * \brief Включить или выключить режим выявления клонов объектов
     *
     * \param [in] val значение режима выявления клонов объектов
     */
    void set_optim_clones(bool val) {
      OPTIM_CLONES = val;
    }

    /**
     * \brief Включить или выключить режим разделения треугольников из STL на фигуры
     *
     * \param [in] val значение режима разделения треугольников из STL на фигуры
     */
    void set_optim_separation(bool val) {
      OPTIM_SEPARATION = val;
    }

    /**
     * \brief Включить или выключить режим измерения временных интервалов операций
     *
     * \param [in] val значение режима измерения временных интервалов операций
     */
    void set_profiling(bool val) {
      PROFILING = val;
    }
  };
}

/**
 * \brief Получить имя файла без расширения.
 * \param [in] filename полное имя файла
 * \return имя файла без расширения
 */
std::string str_remove_ext(const std::string& filename);

/**
 * \brief Получить имя файла без пути.
 * \param [in] filename полное имя файла
 * \return имя файла без пути
 */
std::string str_remove_path(const std::string& filename);

/**
 * \brief Получить путь из полного имени файла.
 * \param [in] filename полное имя файла
 * \return путь к файлу
 */
std::string str_get_path(const std::string& filename);

#endif /* _SUPPORT_H */
