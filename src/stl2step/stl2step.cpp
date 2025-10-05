/**
 * \file
 *
 * \brief Корневой файл для сборки исполняемого файла
 */

#include "stdafx.h"
#include "err.h"
#include "support.h"
#include "arg_parser.h"

 /**
  * \brief Вывод справки о командной строке.
  */
void print_help() {
  std::cout << "КРАТКАЯ СПРАВКА" << std::endl;
  std::cout << "stl2step <[ДОП. ПАРАМЕТРЫ] --stl in1.stl [ДОП. ПАРАМЕТРЫ] --stl in2.stl ... > <--out результат.step>" << std::endl;
  std::cout << "    in1.stl, in2.stl  - входные файлы формата STL (в том числе группы"  << std::endl;
  std::cout << "                        файлов по маске с использованием джокерных символов)" << std::endl;
  std::cout << "    результат.step    - выходной файл формата STEP" << std::endl;
  std::cout << "    ДОПОЛНИТЕЛЬНЫЕ ПАРАМЕТРЫ:" << std::endl;
  std::cout << "    ------------------- действующие только для следующего файла (группы" << std::endl;
  std::cout << "                        файлов по маске) формата STL:" << std::endl;
  std::cout << "    --copy X Y Z [X Y Z]... - добавить копию (копии) объектов, сдвинутые" << std::endl;
  std::cout << "                             по вектору (X Y Z)" << std::endl;
  std::cout << "пример: добавить две копии файла in1.stl с указанными смещениями" << std::endl;
  std::cout << " stl2step --copy 0.123 1.234 -2.345 1.123 2.234 -5.345 --stl in1.stl --out out.step" << std::endl;
  std::cout << "    --name моё имя    - установить для фигуры, определённой в файле, имя 'моё имя'" << std::endl;
  std::cout << "    ------------------- действующие для всех последующих файлов формата STL" << std::endl;
  std::cout << "                        до изменения или отмены:" << std::endl;
  std::cout << "    --color R G B [A] - установить цвет в пространстве RGB (по умолчанию: 0.5 0.5 0.5 1.0)" << std::endl;
  std::cout << "                       с необязательной прозрачностью (как в параметре -transp)" << std::endl;
  std::cout << "пример: установить цвет 'красный = 0.25, зелёный = 0.3, синий = 1.0' для  in1.stl и in2.stl" << std::endl;
  std::cout << " stl2step --color 0.25 0.3 1 --stl in1.stl --stl in2.stl --out out.step" << std::endl;
  std::cout << "    --transp T        - установить прозрачность: от 0.0 (невидимость)" << std::endl;
  std::cout << "                      до 1.0 (непрозрачность) (по умолчанию: 1.0)" << std::endl;
  std::cout << "    {--ofy|--ofn}     - разрешить/запретить объединение треугольных граней в многоугольные" << std::endl;
  std::cout << "                      (по умолчанию: разрешить)" << std::endl;
  std::cout << "    {--osy|--osn}     - разрешить/запретить разделение разделение граней по отдельным фигурам" << std::endl;
  std::cout << "                      (по умолчанию: разрешить)" << std::endl;
  std::cout << "    {--ocy|--ocn}     - разрешить/запретить замену дублирующихся фигур ссылками" << std::endl;
  std::cout << "                      (по умолчанию: разрешить)" << std::endl;
  std::cout << "    --d0              - отменить вывод отладочных сообщений" << std::endl;
  std::cout << "    --d1              - включить отладочные сообщения уровня 1 (самые общие)" << std::endl;
  std::cout << "    --d2              - включить отладочные сообщения уровня 2" << std::endl;
  std::cout << "    --d3              - включить отладочные сообщения уровня 3 (самые детальные)" << std::endl;
  std::cout << "    --dp              - разрешить профилирование (оценку времени работы отдельных этапов обработки)" << std::endl;
}

/**
 * \brief Функция, вызываемая при запуске исполняемого файла.
 *
 * \param [in] argc Количество аргументов-строк в командной строке.
 * \param [in] argv Аргументы-строки в командной строке.
 * \return код ошибки.
 */
int main(int argc, char* argv[])
{
  /** Алгоритм: */

#if defined(_MSC_VER) && defined(_DEBUG)
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
//std::cout << "MSVC/MINGW32 version" << std::endl;
  UINT OldCP = GetConsoleOutputCP();
  SetConsoleOutputCP(CP_UTF8);
#endif

  /** 1 Сформировать список директив и их параметров из аргументов командной строки */
  arg_parser args;
  int err_parse = args.process_cmdline(const_cast<const char**>(argv), argc);
   
  /** 2 Проверить ошибку отсутствия аргументов программы */
  if (err_parse == -2) {
    print_help();
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err_enum_t::ERROR_OK);
  /** 3 Проверить ошибки разбора командной строки */
  } else if (err_parse == -1) {
    std::cout << "Ошибка формата командной строки: первый аргумент '" << args.get_flag(0) << "' не является флагом" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
  } else if (err_parse == -3) {
    std::cout << "Ошибка формата командной строки: первый аргумент '" << args.get_flag(0) << "' является пустым флагом" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
  }

  /** 4 Инициализировать и начать формирование структур для создания файла STEP */
  express::STEP_API* SAPI = new express::STEP_API(str_remove_path(str_remove_ext(argv[argc - 1])));

  err_enum_t retcode(err_enum_t::ERROR_OK);
  
  /* Набор векторов сдвига для формирования копий фигур */
  std::vector<geometry::vector> copies;
  /* Цвет, который будет присвоен фигурам из STL */
  geometry::vector color(0.5,0.5,0.5);
  /* Прозрачность, которая будет присвоена фигурам из STL */
  double transparency = 1.0;
  /* Имя, которое будет присвоено фигурам из STL */
  std::string shell_name;
  /* Имя, которое будет присвоено результирующему файлу STEP */
  std::string out_file;
  /* true, если в командной строке был файл STL */
  bool input_present = false;

  /** 5 Обработать директивы в цикле */
  for (size_t i = 0; i < args.get_arg_num(); ++i) {

    if (args.get_flag(i).compare("out") == 0) {
      out_file = args.get_parameters(i);
      continue;
    }
    else
    if (args.get_flag(i).compare("copy") == 0) {
      std::vector<std::string> parms = args.get_parameters_set(i);
      if (parms.size() < 3) {
        delete SAPI;
        std::cout << "Ошибка формата командной строки: количество параметров после флага 'copy' меньше трёх" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
        SetConsoleOutputCP(OldCP);
#endif
        return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
      }
      if (parms.size() / 3 * 3 != parms.size()) {
        delete SAPI;
        std::cout << "Ошибка формата командной строки: количество параметров после флага 'copy' не кратно трём" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
        SetConsoleOutputCP(OldCP);
#endif
        return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
      }
      for (size_t t = 0; t < parms.size(); t+= 3) {
        /* Добавить этот вектор сдвига */
        copies.emplace_back(geometry::vector(atof(parms[t+0].c_str()), atof(parms[t+1].c_str()), atof(parms[t+2].c_str())));
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("color") == 0) {
      std::vector<std::string> parms = args.get_parameters_set(i);
      if (parms.size() < 3) {
        delete SAPI;
        std::cout << "Ошибка формата командной строки: количество параметров после флага 'color' меньше трёх" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
        SetConsoleOutputCP(OldCP);
#endif
        return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
      }
      /* Установить этот цвет */
      color = geometry::vector(atof(parms[0].c_str()), atof(parms[1].c_str()), atof(parms[2].c_str()));
      if (parms.size() >= 4) {
        transparency = atof(parms[3].c_str());
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("transp") == 0) {
      std::vector<std::string> parms = args.get_parameters_set(i);
      if (parms.size() < 1) {
        delete SAPI;
        std::cout << "Ошибка формата командной строки: отсутствуют параметры после флага 'transp'" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
        SetConsoleOutputCP(OldCP);
#endif
        return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
      }
      transparency = atof(parms[0].c_str());
      continue;
    }
    else
    if (args.get_flag(i).compare("ofy") == 0) {
      SAPI->set_optim_faces(true);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: enable face optimization - creating multiangle faces" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("ofn") == 0) {
      SAPI->set_optim_faces(false);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: disable face optimization - creating triangle faces" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("ocy") == 0) {
      SAPI->set_optim_clones(true);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: enable shell optimization - removing duplicated CLOSED SHELLs" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("ocn") == 0) {
      SAPI->set_optim_clones(false);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: disable shell optimization - passing duplicated CLOSED SHELLs" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("osy") == 0) {
      SAPI->set_optim_separation(true);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: enable face separation - creating multiple shells per one STL" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("osn") == 0) {
      SAPI->set_optim_separation(false);
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: disable face separation - creating one shell per one STL" << std::endl;
      }
      continue;
    }
    else
    if (args.get_flag(i).compare("d0") == 0) {
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: disable debug output" << std::endl;
      }
      SAPI->set_debug_print3(false);
      SAPI->set_debug_print2(false);
      SAPI->set_debug_print1(false);
      continue;
    }
    else
    if (args.get_flag(i).compare("d1") == 0) {
      SAPI->set_debug_print1(true);
      std::cout << "Command line: set debug output level 1" << std::endl;
      continue;
    }
    else
    if (args.get_flag(i).compare("d2") == 0) {
      SAPI->set_debug_print2(true);
      std::cout << "Command line: set debug output level 2" << std::endl;
      continue;
    }
    else
    if (args.get_flag(i).compare("d3") == 0) {
      SAPI->set_debug_print3(true);
      std::cout << "Command line: set debug output level 3" << std::endl;
      continue;
    }
    else
    if (args.get_flag(i).compare("dp") == 0) {
      SAPI->set_profiling(true);
      continue;
    }
    else
    if (args.get_flag(i).compare("name") == 0) {
      shell_name = args.get_parameters(i);
      continue;
    }
    else
    if (args.get_flag(i).compare("stl") == 0) {
      if (SAPI->get_debug_print1()) {
        std::cout << "Command line: processing STL '" << args.get_parameters(i) << "'" << std::endl;
      }
  
      /* Путь к файлу STL */
      std::string m_path = str_get_path(args.get_parameters(i));

#if defined(_MSC_VER) || defined(__MINGW32__)
      struct _finddata_t ffblk;
      auto Handle = _findfirst(args.get_parameters(i).c_str(), &ffblk);
      if (Handle != -1) {
        for (;;) {
          if (!(ffblk.attrib & _A_SUBDIR)) {
            /** 6 Обработать файл STL в том же цикле */
            if ((retcode = SAPI->process_file(ffblk.name, shell_name, m_path, color, transparency, copies)) != err_enum_t::ERROR_OK) {
              delete SAPI;
              SetConsoleOutputCP(OldCP);
              return static_cast<int>(retcode);
            }
            input_present = true;
         }
          auto Result = _findnext(Handle, &ffblk);
          if (Result == -1) break;
        }
        _findclose(Handle);
      }
#elif defined(__GNUC__) || defined(__DOXYGEN__)
      if (m_path.empty()) m_path = "./";
      /* Маска файла материала без пути */
      std::string m_mask = str_remove_path(args.get_parameters(i));
      DIR* dir = opendir(m_path.c_str());
      if (dir != nullptr) {
        for (;;) {
          struct dirent* entry = readdir(dir);
          if (entry == nullptr) break;
          if (fnmatch(m_mask.c_str(), entry->d_name, FNM_CASEFOLD) == FNM_NOMATCH) continue;
          /** 6 Обработать файл STL в том же цикле */
          if ((retcode = SAPI->process_file(entry->d_name, shell_name, m_path, color, transparency, copies)) != err_enum_t::ERROR_OK) {
            delete SAPI;
            return static_cast<int>(retcode);
          }
          input_present = true;
        }
        closedir(dir);
      }
#else
#error Unknown C++ compiler
#endif
      /* Очистить список копий */
      copies.clear();
    }
    else {
      delete SAPI;
      std::cout << "Ошибка формата командной строки: неизвестный флаг '" << args.get_flag(i) << "'" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
      SetConsoleOutputCP(OldCP);
#endif
      return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
    }
  }  

  /** 7 Проверить ошибку отсутствия в комадной строке хотя бы одного файла STL или результирующего файла */
  if (out_file.empty()) {
    delete SAPI;
    std::cout << "Ошибка формата командной строки: не указан результирующий файл" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
  }

  if (!input_present) {
    delete SAPI;
    std::cout << "Ошибка формата командной строки: не указан ни один файл STL" << std::endl;
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
  }

  /** 8 Сохранить выходной файл STEP */
  err_enum_t err = SAPI->save(out_file.c_str());
  if (err != err_enum_t::ERROR_OK) {
    delete SAPI;
#if defined(_MSC_VER) || defined(__MINGW32__)
    SetConsoleOutputCP(OldCP);
#endif
    return static_cast<int>(err);
  }

  std::cout << "OK" << std::endl;
  
  /** 9 Вывести при необходимости результаты профилирования */
  SAPI->print_prof();
  
  delete SAPI;

#if defined(_MSC_VER) && defined(_DEBUG)
  if (_CrtDumpMemoryLeaks()) {
    std::cout << "Обнаружена утечка памяти!" << std::endl;
  }
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
  SetConsoleOutputCP(OldCP);
#endif
  return static_cast<int>(err_enum_t::ERROR_OK);
}
