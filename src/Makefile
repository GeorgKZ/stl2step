HOSTOS		:= $(shell uname -s | tr A-Z a-z | \
			sed -e 's/\(cygwin\).*/cygwin/')

#
# Расширение '.exe' при использовании Cygwin
#
ifeq ($(HOSTOS),cygwin)
SFX = .exe
else
SFX =
endif

# Компилятор
CC    = gcc-10

# Обрезатель исполняемого файла
STRIP = strip

# Включение всех предупреждений
#CPP_ALL_GCC_WARN = $(shell $(CC) -Q --help=warning | sed -e 's/^\s*\(\-\S*\)\s*\[\w*\]/\1 /gp;d' | \
#sed -e 's/-Wabsolute-value *|-Wbad-function-cast *|-Wc++-compat *//g' | \
#tr -d '\n')
# future: sed -e "$(sed 's:.*:s/&//ig:' wordfile)" textfile
#         sed -E 's/\<('"$(tr '\n' '|' < <(getListOfWords) )"')\>//gI' <(getInFile)
# FOO=${FOO//$WORDTOREMOVE/}
#
# places='austria rome italy venice london'
# echo $places | sed -E 's/austria|italy|london *//g'
# 
# 
# $ str1='austria rome italy venice london'
# $ str2='rome venice'
# $ read -a arr1 <<< "$str1"
# $ read -a arr2 <<< "$str2"
# $ printf '%s\n' "${arr1[@]}" | grep -vf <(printf '%s\n' "${arr2[@]}") | paste -sd ' '
# austria italy london

# Включение всех предупреждений C++
CPP_ALL_WARN = \
-Wabi -Waddress -Waddress-of-packed-member -Waggregate-return -Waggressive-loop-optimizations \
-Walloc-zero -Walloca -Wanalyzer-double-fclose -Wanalyzer-double-free -Wanalyzer-exposure-through-output-file\
-Wanalyzer-file-leak -Wanalyzer-free-of-non-heap -Wanalyzer-malloc-leak -Wanalyzer-null-argument\
-Wanalyzer-null-dereference -Wanalyzer-possible-null-argument -Wanalyzer-possible-null-dereference\
-Wanalyzer-stale-setjmp-buffer -Wanalyzer-tainted-array-index -Wanalyzer-too-complex\
-Wanalyzer-unsafe-call-within-signal-handler -Wanalyzer-use-after-free\
-Wanalyzer-use-of-pointer-in-stale-stack-frame -Warith-conversion -Warray-bounds -Wattribute-warning\
-Wattributes -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch\
-Wbuiltin-macro-redefined -Wcannot-profile\
-Wcast-align -Wcast-align=strict -Wcast-function-type -Wcast-qual -Wchar-subscripts -Wclobbered -Wcomment\
-Wconversion -Wcoverage-mismatch -Wcpp -Wdangling-else -Wdate-time -Wdeprecated\
-Wdeprecated-declarations -Wdisabled-optimization\
-Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches\
-Wduplicated-cond -Wempty-body -Wendif-labels -Wenum-compare -Wexpansion-to-defined\
-Wextra -Wfloat-conversion -Wfloat-equal -Wformat-contains-nul -Wformat-diag -Wformat-extra-args\
-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat-y2k -Wformat-zero-length\
-Wframe-address -Wfree-nonheap-object -Whsa -Wif-not-aligned -Wignored-attributes -Wignored-qualifiers\
-Winit-self -Winline -Wint-in-bool-context -Wint-to-pointer-cast -Winvalid-memory-model\
-Winvalid-pch -Wlogical-not-parentheses -Wlogical-op -Wlong-long -Wlto-type-mismatch\
-Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation\
-Wmissing-attributes -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers\
-Wmissing-include-dirs -Wmissing-profile -Wmultichar\
-Wmultistatement-macros -Wnarrowing -Wnonnull -Wnonnull-compare -Wnull-dereference\
-Wodr -Wopenmp-simd -Woverflow -Woverlength-strings\
-Wpacked -Wpacked-bitfield-compat -Wpacked-not-aligned\
-Wpadded -Wparentheses -Wpedantic -Wpointer-arith -Wpointer-compare\
-Wpragmas -Wprio-ctor-dtor -Wpsabi -Wredundant-decls -Wrestrict -Wreturn-local-addr -Wreturn-type\
-Wsequence-point -Wshadow -Wshadow=compatible-local -Wshadow=local -Wshift-count-negative\
-Wshift-count-overflow -Wshift-negative-value -Wsign-compare -Wsign-conversion -Wsizeof-array-argument\
-Wsizeof-pointer-div -Wsizeof-pointer-memaccess -Wstack-protector -Wstring-compare\
-Wstringop-truncation -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wsuggest-attribute=format\
-Wunknown-pragmas -Wunreachable-code -Wunsafe-loop-optimizations\
-Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-function -Wunused-label\
-Wunused-local-typedefs -Wunused-macros -Wunused-result -Wunused-value -Wunused-variable\
-Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvla -Wvolatile-register-var\
-Wwrite-strings -Wzero-length-bounds \
-Wsuggest-attribute=malloc -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods \
-Wsuggest-final-types -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-outside-range\
-Wswitch-unreachable -Wsync-nand -Wtautological-compare\
-Wtrampolines -Wtrigraphs -Wtype-limits -Wundef -Wuninitialized\

# Отключённые предупреждения C++
CPP_DISABLED_WARN = \
-Wno-system-headers \
-Wno-aggregate-return \
-Wno-undef \
-Wno-zero-as-null-pointer-constant \
-Wno-padded \
-Wno-long-long \
-Wno-inline \
-Wno-suggest-final-types \
-Wno-suggest-final-methods \
-Wno-suggest-attribute=cold \
-Wno-suggest-attribute=const \
-Wno-suggest-attribute=pure \
-Wno-suggest-attribute=noreturn \
-Wno-suggest-attribute=format \
-Wno-unused-function \

# Используемые предупреждения
#CPP_WARN = -Wall -Wextra -Wpedantic \
#-Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond \
#-Wextra-semi -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual \
#-Wredundant-decls -Wsign-conversion -Wsign-promo \
#-Wuninitialized -Wshadow -Wsuggest-override

# Флаги компилятора C++
CPP_FLAGS = $(CPP_ALL_WARN) $(CPP_DISABLED_WARN) -std=c++20 -DTESTONLY
# -DTRACE_AGGREGATE -DTRACE_ARRAY
# -DTRACE_REAL -DTRACE_NUMBER

# Флаги оптимизации компилятора C++
CPP_OPT_FLAGS = -O2 -finline-limit=10000

# Флаги компоновщика
LD_FLAGS =

# Используемые библиотеки
LOADLIBES = -lm -lstdc++

# Префикс для подавления эха выполняемых команд
Q := @

PVS_STUDIO = $(Q)pvs-studio \
--cfg ./PVS-Studio.cfg \
--output-file ./pvs.log \
--platform Linux64 \
--preprocessor gcc \
--analysis-mode 0 \
--sourcetree-root ./ \
--source-file $< \
--language C++ \
--i-file $@ \
--exclude-path tiny_jpeg.h \
--cl-params $(CPP_FLAGS)

PVS_EXCLUDE_WARN = V112,V122,V550,V601,V2014
PVS_CONVERTER = $(Q)plog-converter -t errorfile -a 'GA;OP;CS;64' -d $(PVS_EXCLUDE_WARN) -o ./pvs.txt ./pvs.log > /dev/null


# Файлы, содержащие исходные тексты
CPPS	= stdafx.cpp \
        express_constants.cpp express_functions.cpp express_generic.cpp express_simple.cpp \
        express_simple_boolean.cpp express_simple_integer.cpp express_simple_logical.cpp \
        express_simple_number.cpp express_simple_real.cpp express_simple_string.cpp \
        express_simple_binary.cpp express_aggregate.cpp  \
        iso10303_41.cpp iso10303_42.cpp iso10303_43.cpp iso10303_46.cpp iso10303_517.cpp \
        geometry.cpp shell.cpp support.cpp support_proc_shell.cpp \
        stl2step.cpp err.cpp tests.cpp

# Список целей, которым не нужен файл зависимостей .depend
no-need_depend-targets := clean clobber check docs html
# Признак - цель требует наличия файла зависимостей
need_depend   := 1
# Признак - присутствуют смешанные цели (и с требованием файла зависимостей, и без)
mixed-targets := 0

# Определить требуемые значения переменных need_depend и mixed-targets:
# - если цели включают хотя бы одну цель из списка no-need_depend-targets, то need_depend = 0;
# - если при этом есть хотя бы одна цель не из списка no-need_depend-targets, то mixed_targets = 1;
ifneq ($(filter $(no-need_depend-targets), $(MAKECMDGOALS)),)
	need_depend := 0
	ifneq ($(filter-out $(no-need_depend-targets), $(MAKECMDGOALS)),)
		mixed-targets := 1
	endif
endif

PNAME = stl2step

# Раздел с целями и их обработкой
# ===========================================================================

PHONY += _all
# Цель по умочанию, если в командной строке ничего не задано
_all:		all

# Обработка смешанных целей - последовательно по одной
# ---------------------------------------------------------------------------
ifeq ($(mixed-targets),1)

PHONY += $(MAKECMDGOALS) __build_one_by_one

$(filter-out __build_one_by_one, $(MAKECMDGOALS)): __build_one_by_one
	@:

__build_one_by_one:
	$(Q)set -e; \
	for i in $(MAKECMDGOALS); do \
		$(MAKE) --quiet -f ./Makefile $$i; \
	done

# Обработка одной цели
# ---------------------------------------------------------------------------
else

PHONY += all
# Сборка всего - исполнямого файла
all:		$(PNAME)$(SFX) Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] all\e[m'

# Сборка исполняемого файла
$(PNAME)$(SFX):	$(CPPS:.cpp=.o)
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] linking $@\e[m'
		$(Q)$(CC) $(CPP_FLAGS) $(CPP_OPT_FLAGS) $(LD_FLAGS) -o $@ $^ $(LOADLIBES)
		$(Q)$(STRIP) $@

# Формирование файлов list_type.h, list_entity.h
%.h:		%.txt txt_to_header.sh Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] converting $< to $@\e[m'
		$(Q)./txt_to_header.sh ./$< > ./$@

txt_to_header.sh: Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] producing $@\e[m'
		$(Q)/bin/echo -e '#!/bin/bash' > ./txt_to_header.sh
		$(Q)/bin/echo -e >> ./txt_to_header.sh
		$(Q)/bin/echo -e 'while IFS= read -r line; do' >> ./txt_to_header.sh
		$(Q)/bin/echo -e '    echo class $$line";"' >> ./txt_to_header.sh
		$(Q)/bin/echo -e 'done < $$1' >> ./txt_to_header.sh
		$(Q)chmod +x ./txt_to_header.sh

# Объектные модули, получаемые из файлов с исходными текстами
%.o:		%.cpp Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] compiling $<\e[m'
		$(Q)$(CC) $(CPP_FLAGS) $(CPP_OPT_FLAGS) -c $< -o $@

PHONY += html
# Формирование файла документации при помощи doxygen
html:		Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] doc (html)\e[m'
		$(Q)rm -rf ../doxygen/doxygen.log
		$(Q)rm -rf ../doxygen/output/refman.pdf
		$(Q)rm -rf ../doxygen/latex.log
		$(Q)rm -rf ../refman.pdf
		$(Q)rm -rf ../doxygen/output/html
		$(Q)rm -rf ../doxygen/output/latex
		$(Q)cd ../doxygen; doxygen $(PNAME).Doxyfile > ../doxygen/doxygen.log
		$(Q)cd ../doxygen; find warnings.log -size 0 | xargs rm -f

PHONY += docs
# Формирование файла документации при помощи doxygen и latex
docs:		html Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] doc (pdf) - 1st run\e[m'
		$(Q)cd ../doxygen/output/latex; pdflatex -no-shell-escape refman > /dev/null; true
		$(Q)cd ../doxygen/output/latex; makeindex -q refman.idx
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] doc (pdf) - 2nd run\e[m'
		$(Q)cd ../doxygen/output/latex; pdflatex -no-shell-escape refman > /dev/null; true
		$(Q)latex_count=8 ; \
		while egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log && [ $$latex_count -gt 0 ] ;\
		    do \
		      /bin/echo -e '\e[33m[$(PNAME)] doc (pdf) - cycle run\e[m';\
		      $(Q)/bin/echo -e '\e[33m[$(PNAME)] doc (pdf) - intermediate run\e[m';\
		      pdflatex -no-shell-escape refman > /dev/null;\
		      latex_count=`expr $$latex_count - 1` ;\
		    done
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] doc (pdf) - last run\e[m'
		$(Q)cd ../doxygen/output/latex; makeindex -q refman.idx
		$(Q)cd ../doxygen/output/latex; pdflatex -no-shell-escape refman > /dev/null; true
		$(Q)cp ../doxygen/output/latex/refman.log ../doxygen/latex.log
		$(Q)cp ../doxygen/output/latex/refman.pdf ../refman.pdf


PHONY += clean
# Удаление всех временных файлов
clean:		Makefile
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] clean\e[m'
		$(Q)find . -type f \( \
			-name '*.bak' \
			-o -name '*.tmp' \
			-o -name '*.o' \
			-o -name '*.d' \
			-o -name '*.i' \
			-o -name '*.a' \
			-o -name '*.elf' \
			-o -name '.depend' \
			\) -print | xargs rm -f
		$(Q)rm -f pvs.log PVS-Studio.cfg
		$(Q)rm -rf ../doxygen/doxygen.log
		$(Q)rm -rf ../doxygen/warnings.log
		$(Q)rm -rf ../doxygen/latex.log
		$(Q)rm -rf ../doxygen/output/latex

PHONY += clobber
# Удаление всех временных и результирующих файлов, создаваемых файлов, документации
clobber:	clean
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] clobber\e[m'
		$(Q)rm -f $(PNAME)(SFX) pvs.txt
		$(Q)rm -f list_type.h list_class.h list_entity.h txt_to_header.sh
		$(Q)rm -rf  ../doxygen/output/html
		$(Q)rm -rf  ../refman.pdf


PHONY += check
# Статический анализ исходных текстов при помощи PVS-Studio
check:		list_type.h list_entity.h $(CPPS:.cpp=.i) ./PVS-Studio.cfg
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] generating pvs report\e[m'
		$(PVS_CONVERTER)
		$(Q)rm -f ./PVS-Studio.cfg

# Обработанные препроцессором файлы для PVS-Studio
%.i:		%.cpp ./PVS-Studio.cfg
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] checking $<\e[m'
		$(Q)$(CC) $(CPP_FLAGS) $(CPP_OPT_FLAGS) -E $< -o $@
		$(PVS_STUDIO)

# Файл конфигурции PVS-Studio
./PVS-Studio.cfg: Makefile
		$(Q)/bin/echo > $@
		$(Q)rm -f pvs.log

# ===========================================================================

# Создание файла, содержащего зависимости
.depend:	Makefile list_type.h list_entity.h $(CPPS)
		$(Q)/bin/echo -e '\e[33m[$(PNAME)] generating dependences\e[m'
		$(Q)$(CC) $(CPP_FLAGS) $(CPP_OPT_FLAGS) -M $(CPPS) > $@

ifeq ($(need_depend),1)
-include	.depend
endif

endif

# ===========================================================================
# Исключить всё содержимое переменной PHONY из файлов-целей сборки команды make
.PHONY: $(PHONY)
