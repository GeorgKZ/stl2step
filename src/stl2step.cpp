/**
 * \file
 *
 * \brief Корневой файл для сборки исполняемого файла.
 */

#ifndef TESTONLY
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include "err.h"

#ifndef TESTONLY

#include "support.h"

 /**
  * \brief Вывод справки о командной строке.
  */
void print_help() {
  puts("HELP:");
  puts("stl2step <[OPTIONS] -stl in1.stl [OPTIONS] -stl in2.stl ... > <output.step>");
  puts("    in1.stl, in2.stl - input STL files (filemask allowed)");
  puts("    output.step      - output STEP file");
  puts("    OPTIONS:");
  puts("    ------------------ next STL file option:");
  puts("    -copy X Y Z      - add copy moved along vector (X Y Z)");
  puts("example: add two in1.stl copies with specified coordinates offsets");
  puts(" stl2step  -copy 0.123 1.234 -2.345 -copy 1.123 2.234 -5.345 in1.stl out.step");
  puts("    -name my name    - set shell name 'my name'");
  puts("    ------------------ all next STL files options until changing or disabling:");
  puts("    -color R G B     - set RGB color (default: 0.5 0.5 0.5)");
  puts("example: set color Red = 0.25, Green = 0.3, Blue = 1.0 for in1.stl and in2.stl");
  puts(" stl2step -color 0.25 0.3 1 in1.stl in2.stl out.step");
  puts("    -transp T        - set transparency: 0.0 - invisible, 1.0 - solid (default: 1.0)");
  puts("    {-ofy|-ofn}      - enable/disable face optimization - creating multiangle/triangle faces (default: enable)");
  puts("    {-osy|-osn}      - enable/disable face separation - creating multiple shells/one shell per one STL (default: enable)");
  puts("    {-ocy|-ocn}      - enable/disable shell optimization - removing/passing duplicated CLOSED SHELLs (default: enable)");
  puts("    -d0              - disable debug output");
  puts("    -d1              - set debug output level 1");
  puts("    -d2              - set debug output level 2");
  puts("    -d3              - set debug output level 3");
  puts("    -dp              - enable time profiling");
  puts("");
  puts("stl2step -test");
  puts("    run internal tests");
  puts("stl2step -test detailed");
  puts("    run internal tests with detailed output");
}

/** \brief Минимально возможное количество аргументов (сама программа, -stl, файл STL, выходной файл) */
#define MINARGS 4

/**
 * \brief Функция, вызываемая при запуске исполняемого файла.
 *
 * \param [in] argc Количество аргументов-строк в командной строке.
 * \param [in] argv Аргументы-строки в командной строке.
 * \return код ошибки.
 */
int main(int argc, char* argv[])
{
#if defined(_MSC_VER) && defined(_DEBUG)
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
#endif

  if (argc >= 2 && strcmp(argv[1], "-test") == 0) {
    void run_tests(bool);
    bool detailed = false;

    if (argc >= 3 && strcmp(argv[2], "detailed") == 0) {
      detailed = true;
    }

    try {
      run_tests(detailed);
    }
    catch(const char *err) {
      printf("%s\n", err);
      return static_cast<int>(err_enum_t::ERROR_INTERNAL);
    }
    catch(express::exception& e) {
      printf("%s\n", e.what());
      return static_cast<int>(err_enum_t::ERROR_INTERNAL);
    }
    catch(...) {
      printf("Common exception\n");
      return static_cast<int>(err_enum_t::ERROR_INTERNAL);
    }
    return static_cast<int>(err_enum_t::ERROR_OK);
  }

  /** 1. Проверка на минимально допустимое количество аргументов программы */
  if (argc < MINARGS) {
    if (argc > 1) printf("ERROR (command line): number of arguments is less than %i\n", MINARGS - 1);
    print_help();
    return static_cast<int>(err_enum_t::ERROR_CMD_FORMAT);
  }

  try {
    /** 2. Инициализация и начало формирования структур для вывода в файл STEP */
    express::STEP_API* SAPI = new express::STEP_API(str_remove_path(str_remove_ext(argv[argc - 1])));
  
    /** 3. Обработка аргументов в цикле до предпоследнего (последний всегда имя файла STEP) */
  
    {
      err_enum_t retcode(err_enum_t::ERROR_OK);
  
      /* Набор векторов сдвига для формирования копий фигур */
      std::vector<geometry::vector> copies;
      int copy_mode = -1;
      double x = 0;
      double y = 0;
      double z = 0;
      /* Цвет, который будет присвоен фигурам из STL */
      double r = 0.5;
      double g = 0.5;
      double b = 0.5;
      geometry::vector color(r,g,b);
      int color_mode = -1;
      /* Прозрачность, которая будет присвоена фигурам из STL */
      double t = 1.0;
      double transparency = t;
      int transp_mode = -1;
      /* Имя, которое будет присвоено фигурам из STL */
      std::string shell_name;
      int name_mode = -1;
  
      for (int argi = 1; argi < argc - 1; argi++) {
  
        if (copy_mode == 0) {
          x = atof(argv[argi]);
          copy_mode = 1;
          continue;
        }
        if (copy_mode == 1) {
          y = atof(argv[argi]);
          copy_mode = 2;
          continue;
        }
        if (copy_mode == 2) {
          z = atof(argv[argi]);
          /* Добавить этот вектор сдвига */
          copies.emplace_back(geometry::vector(x, y, z));
          copy_mode = -1;
          continue;
        }
  
        if (color_mode == 0) {
          r = atof(argv[argi]);
          color_mode = 1;
          continue;
        }
        if (color_mode == 1) {
          g = atof(argv[argi]);
          color_mode = 2;
          continue;
        }
        if (color_mode == 2) {
          b = atof(argv[argi]);
          /* Сохранить цвет */
          color = geometry::vector(r, g, b);
          color_mode = -1;
          continue;
        }
  
        if (transp_mode == 0) {
          t = atof(argv[argi]);
          /* Сохранить прозрачность */
          transparency = t;
          transp_mode = -1;
          continue;
        }
  
        if (name_mode != -1) {
          if (argv[argi][0] == '-') {
            name_mode = -1;
          }
          else {
            /* Сохранить имя */
            if (name_mode == 0) {
              shell_name.clear();
            }
            else {
              shell_name = shell_name + " ";
            }
            shell_name = shell_name + argv[argi];
            name_mode++;
            continue;
          }
        }
  
        if (strcmp(argv[argi], "-ofy") == 0) {
          SAPI->set_optim_faces(true);
          if (SAPI->get_debug_print1()) {
            printf("Command line: enable face optimization - creating multiangle faces\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-ofn") == 0) {
          SAPI->set_optim_faces(false);
          if (SAPI->get_debug_print1()) {
            printf("Command line: disable face optimization - creating triangle faces\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-ocy") == 0) {
          SAPI->set_optim_clones(true);
          if (SAPI->get_debug_print1()) {
            printf("Command line: enable shell optimization - removing duplicated CLOSED SHELLs\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-ocn") == 0) {
          SAPI->set_optim_clones(false);
          if (SAPI->get_debug_print1()) {
            printf("Command line: disable shell optimization - passing duplicated CLOSED SHELLs\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-osy") == 0) {
          SAPI->set_optim_separation(true);
          if (SAPI->get_debug_print1()) {
            printf("Command line: enable face separation - creating multiple shells per one STL\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-osn") == 0) {
          SAPI->set_optim_separation(false);
          if (SAPI->get_debug_print1()) {
            printf("Command line: disable face separation - creating one shell per one STL\n");
          }
          continue;
        }
  
        if (strcmp(argv[argi], "-d0") == 0) {
          if (SAPI->get_debug_print1()) {
            printf("Command line: disable debug output\n");
          }
          SAPI->set_debug_print3(false);
          SAPI->set_debug_print2(false);
          SAPI->set_debug_print1(false);
          continue;
        }
  
        if (strcmp(argv[argi], "-d1") == 0) {
          SAPI->set_debug_print1(true);
          printf("Command line: set debug output level 1\n");
          continue;
        }
  
        if (strcmp(argv[argi], "-d2") == 0) {
          SAPI->set_debug_print2(true);
          printf("Command line: set debug output level 2\n");
          continue;
        }
  
        if (strcmp(argv[argi], "-d3") == 0) {
          SAPI->set_debug_print3(true);
          printf("Command line: set debug output level 3\n");
          continue;
        }
  
        if (strcmp(argv[argi], "-dp") == 0) {
          SAPI->set_profiling(true);
          continue;
        }
  
        if (strcmp(argv[argi], "-copy") == 0) {
          copy_mode = 0;
          continue;
        }
  
        if (strcmp(argv[argi], "-name") == 0) {
          name_mode = 0;
          continue;
        }
  
        if (strcmp(argv[argi], "-color") == 0) {
          color_mode = 0;
          continue;
        }
  
        if (strcmp(argv[argi], "-transp") == 0) {
          transp_mode = 0;
          continue;
        }
  
        if (SAPI->get_debug_print1()) {
          printf("Command line: processing STL '%s'\n", argv[argi]);
        }
  
        /* Путь к файлу STL */
        std::string m_path = str_get_path(argv[argi]);

#if defined(_MSC_VER)
        struct _finddata_t ffblk;
        auto Handle = _findfirst(argv[argi], &ffblk);
        if (Handle != -1) {
          for (;;) {
            if (!(ffblk.attrib & _A_SUBDIR)) {
              /** 4. Обработка файла в том же цикле файла STL */
              if ((retcode = SAPI->process_file(ffblk.name, shell_name, m_path, color, transparency, copies)) != err_enum_t::ERROR_OK) return static_cast<int>(retcode);
            }
            auto Result = _findnext(Handle, &ffblk);
            if (Result == -1) break;
          }
          _findclose(Handle);
        }
#elif defined(__GNUC__) || defined(__DOXYGEN__)
        if (m_path.empty()) m_path = "./";
        /* Маска файла материала без пути */
        std::string m_mask = str_remove_path(argv[argi]);
        DIR* dir = opendir(m_path.c_str());
        if (dir != nullptr) {
          for (;;) {
            struct dirent* entry = readdir(dir);
            if (entry == nullptr) break;
            if (fnmatch(m_mask.c_str(), entry->d_name, FNM_CASEFOLD) == FNM_NOMATCH) continue;
            /** 4. Обработка файла в том же цикле файла STL */
            if ((retcode = SAPI->process_file(entry->d_name, shell_name, m_path, color, transparency, copies)) != err_enum_t::ERROR_OK) {
              return static_cast<int>(retcode);
            }
          }
          closedir(dir);
        }
#elif
#error Unknown C++ compiler
#endif
        copies.clear();
      }
    }

    /** 5. Сохранение выходного файла STEP */
    err_enum_t err = SAPI->save(argv[argc - 1]);
    if (err != err_enum_t::ERROR_OK) return static_cast<int>(err);
  
    /** 6. Вывод результатов профилирования */
    SAPI->print_prof();
  
    delete SAPI;
  }
  catch(express::exception& e) {
    printf("%s\n", e.what());
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch(...) {
    printf("Common exception\n");
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }

  printf("OK\n");

#if defined(_MSC_VER) && defined(_DEBUG)
  if (_CrtDumpMemoryLeaks()) {
    printf("Memory leak is found!");
  }
#endif

  return static_cast<int>(err_enum_t::ERROR_OK);
}

#else

int main(int argc, char* argv[])
{
  bool detailed = false;

  if (argc >= 3 && strcmp(argv[1], "-test") == 0 && strcmp(argv[2], "detailed") == 0) {
      detailed = true;
  }

  try {
    run_tests(detailed);
  }
  catch(express::exception& e) {
    printf("EXPRESS exception at %s:\n%s\n", e.where(), e.what());
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  /* std::logic_error */
  catch (std::invalid_argument const& e) {
    std::cout << "std::exception::logic_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::domain_error const& e) {
    std::cout << "std::exception::logic_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::length_error const& e) {
    std::cout << "std::exception::logic_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::out_of_range const& e) {
    std::cout << "std::exception::logic_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  /* runtime_error */
  catch (std::range_error const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::overflow_error const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::underflow_error const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::ios_base::failure const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::filesystem::filesystem_error const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (std::system_error const& e) {
    std::cout << "std::exception::runtime_error: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  /* std errors */
  catch (const std::bad_typeid& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_any_cast& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_cast& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_optional_access& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_weak_ptr& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_function_call& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_array_new_length& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_alloc& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_exception& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch (const std::bad_variant_access& e) {
    std::cout << "std::exception: " << e.what() << '\n';
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  catch(...) {
    printf("Common exception\n");
    return static_cast<int>(err_enum_t::ERROR_INTERNAL);
  }
  return 0;
}

#endif