/**
 * \file
 * \brief Файл с описанием операторов и встроенных функций языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 12, 15)
 */

namespace express {

  /** \brief <B>OPERATOR IN (ГОСТ Р ИСО 10303-11-2009, 12.2.3)</B>
   *
   * \ref express::IN() "12.2.3 Оператор принадлежности"
   *
   * Оператор принадлежности \ref express::IN() "IN" осуществляет проверку, принадлежит ли данный элемент к
   * какой-либо агрегированной структуре и возвращает ли результат типа \ref express::LOGICAL "LOGICAL".
   * Операнд, расположенный справа от оператора, должен иметь значение агрегированного типа данных, а операнд,
   * расположенный слева, должен быть совместим с базисным типом данного значения агрегированного типа данных.
   * Результат выражения <B>е \ref express::IN() "IN" agg</B> определяется следующим образом:<BR>
   * a) если любой из операндов имеет неопределённое (<B>?</B>) значение, то выражение имеет значение \ref express::LOGICAL.UNKNOWN "UNKNOWN";<BR>
   * b) если существует такой элемент <B>agg[i]</B>, для которого <B>е:=:agg[i]</B>, то выражение имеет значение \ref express::LOGICAL.TRUE "TRUE";<BR>
   * c) если существует элемент <B>agg[i]</B>, имеющий неопределённое (<B>?</B>) значение, то выражение имеет значение \ref express::LOGICAL.UNKNOWN "UNKNOWN";<BR>
   * d) в противном случае, выражение имеет значение \ref express::LOGICAL.FALSE "FALSE".
   * 
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Для того, чтобы проверить, существует ли в агрегированной структуре элемент, имеющий
   * конкретное значение, может быть использована функция \ref express::VALUE_IN() "VALUE_IN" (см. \ref express::VALUE_IN() "15.28").<BR>
   * Проверка принадлежности, определённой разработчиком модели, может быть осуществлена посредством
   * пары функций, названных для примера my_equal (см. примечание в \ref p11_s8_2_5 "8.2.5") и my_in в следующем псевдокоде:</SMALL>
   * 
   <PRE>
       FUNCTION my_in(c:AGGREGATE OF GENERIC: gen; v: GENERIC:gen) : LOGICAL;
         (* "my_in" возвращает значение \ref express::LOGICAL.UNKNOWN "UNKNOWN", если v или с
            имеет неопределённое (?) значение, иначе, возвращает значение \ref express::LOGICAL.TRUE "TRUE",
            если любой элемент из с имеет 'значение' v, иначе, возвращает значение
            \ref express::LOGICAL.UNKNOWN "UNKNOWN", если результатом любого сравнения является
            \ref express::LOGICAL.UNKNOWN "UNKNOWN", иначе возвращает значение \ref express::LOGICAL.FALSE "FALSE" *)
       LOCAL
         result   : \ref express::LOGICAL "LOGICAL";
         unknownp : \ref express::BOOLEAN "BOOLEAN" := \ref express::BOOLEAN.FALSE "FALSE";
       END_LOCAL;
       IF ( (NOT EXISTS (v) ) OR (NOT EXISTS (c) ) THEN
         RETURN (UNKNOWN); END_IF;
       REPEAT i := \ref express::LOINDEX() "LOINDEX"(c) TO \ref express::HIINDEX() "HIINDEX"(c);
         result := my_equal(v, c[i]);
         IF (result = TRUE) THEN
           RETURN (result); END_IF;
         IF (result = UNKNOWN) THEN
           unknownp := TRUE; END_IF;
       END_REPEAT;
       IF (unknownp) THEN
         RETURN (UNKNOWN);
       ELSE
         RETURN (FALSE);
       END_IF;
       END_FUNCTION;
   </PRE>
   *
   * Это может быть использовано, например, следующим образом:
   <PRE>
    LOCAL
      v : a;
      с : \ref express::SET "SET" OF a;
    END_LOCAL;
      ...
    IF my_in(c, v) THEN ...
   </PRE>
   *
   */
  LOGICAL IN(const GENERIC& v, const AGGREGATE_GENERIC& agg);

  /**
   * \brief OPERATOR QUERY (ГОСТ Р ИСО 10303-11-2009, 12.6.7)
   *
   * \ref express::QUERY() "12.6.7 Оператор запроса"
   *
   * Оператор запроса <B>\ref express::QUERY() "QUERY"</B> применяет логическое выражение <B>logical_expression</B> по отдельности к
   * каждому элементу агрегированной структуры и формирует в качестве результата агрегированную
   * структуру, содержащую элементы, для которых значением logical_expression было TRUE. В результате
   * формируется подмножество исходной агрегированной структуры, все элементы которого соответствуют условию,
   * представленному логическим выражением.
   *
   \verbatim
     Синтаксис:
      277 query_expression = QUERY '(' variable_id '<*' aggregate_source '|' logical_expression ')' .
      170 aggregate_source = simple_expression .
      254 logical_expression = expression .
   \endverbatim
   * Правила и ограничения:
   *
   * \param [in] variable_id a) Элемент является неявно объявленной переменной в области видимости оператора запроса.
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Данная переменная не должна быть объявлена где-либо ещё и не существует вне оператора запроса.</SMALL>
   * \param [in] aggregate_source b) Элемент должен быть представлен агрегированной структурой (\ref express::ARRAY_GENERIC "ARRAY",
   * \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET".<BR>
   * c) Если элемент aggregate_source имеет неопределённое (<B>?</B>) значение, то оператор возвращает
   * также неопределённое (?) значение.
   * \param [in] logical_expression d) Третий операнд должен быть выражением, результат которого имеет тип
   * данных \ref express::LOGICAL "LOGICAL".
   * \return подмножество исходной агрегированной структуры, все элементы которого соответствуют условию,
   * представленному логическим выражением <B>logical_expression</B>.
   *
   * Элементы поочередно извлекают из исходной агрегированной структуры, подставляют в
   * logical_expression вместо variable_id и вычисляют значение logical_expression. Если
   * logical_expression имеет значение \ref express::LOGICAL.TRUE "TRUE", то данный элемент добавляют к результату; в противном
   * случае --- не добавляют. Если logical_expression принимает неопределённое (<B>?</B>) значение, то данный
   * элемент не включают в результирующую агрегированную структуру. Данные действия повторяют для
   * каждого элемента исходной агрегированной структуры. Содержимое результирующей агрегированной
   * структуры зависит от конкретного вида агрегированного типа данных:
   *
   * a) Тип данных \ref express::ARRAY_GENERIC "ARRAY": результирующий массив имеет такие же границы и базисный тип, что и
   * исходный массив, но элементы данного массива объявлены как OPTIONAL. Изначально каждый элемент имеет
   * неопределённое (<B>?</B>) значение. Каждый элемент исходного массива, для которого logical_expression
   * имеет значение \ref express::LOGICAL.TRUE "TRUE", помещается на такую же индексную позицию в результирующем массиве.
   *
   * b) Тип данных \ref express::BAG "BAG": результирующий пакет имеет такие же базисный тип и верхнюю границу, что и
   * исходный пакет. Нижняя граница равна нулю. Изначально результирующий пакет является пустым.
   * Каждый элемент исходного пакета, для которого logical_expression имеет значение
   * \ref express::LOGICAL.TRUE "TRUE", добавляется в результирующий пакет.
   *
   * c) Тип данных \ref express::LIST "LIST": результирующий список имеет такие же базисный тип и верхнюю границу, что и
   * исходный список. Нижняя граница равна нулю. Изначально результирующий список является пустым.
   * Каждый элемент из исходного списка, для которого logical_expression имеет значение
   * \ref express::LOGICAL.TRUE "TRUE", добавляется в конец результирующего списка. Порядок следования
   * элементов исходного списка сохраняется.
   *
   * d) Тип данных \ref express::SET "SET": результирующий набор имеет такие же базисный тип и верхнюю границу, что и
   * исходный набор. Нижняя граница равна нулю. Изначально результирующий набор является пустым.
   * Каждый элемент из исходного набора, для которого logical_expression имеет значение
   * \ref express::LOGICAL.TRUE "TRUE", добавляется в результирующий набор.
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Если исходная агрегированная структура является пустой, то результатом будет
   * пустая агрегированная структура.</SMALL>
   *
   * <B><I>Примеры
   *
   * 1 Пусть</I> colour <I>является определённым типом данных, имеющим в качестве базисного типа</I>
   * ENUMERATION<I>, включающий элементы</I> pink <I>и</I> scarlet<I>. В приведенном ниже фрагменте показано, как
   * извлечь из массива colour элементы, являющиеся либо</I> pink<I>, либо</I> scarlet<I>.</I>
   <PRE>
       LOCAL
         colours : \ref express::ARRAY_GENERIC "ARRAY" OF colour;
         reds : \ref express::ARRAY_GENERIC "ARRAY" OF OPTIONAL colour;
       END_LOCAL;
       ...
       reds := QUERY ( element <* colours | ( element = pink )
               OR ( element = scarlet ) ) ;
       ...
   </PRE>
   * <I>2 В данном примере оператор запроса используется для проверки всех экземпляров объектного
   * типа данных point. Результирующий набор содержит все экземпляры объекта point, расположенные в
   * начале координат.</I>
   <PRE>
       RULE two_points_at_origin FOR (point);
         WHERE
         SIZEOF (QUERY(temp <* point | temp = point(0.0,0.0,0.0))) = 2;
       END_RULE;
   </PRE>
   *
   * <I>В данном примере показаны три неявных объявления. Первым является переменная</I> point<I>,
   * которая неявно объявлена в заголовке</I> RULE <I>как набор всех экземпляров</I> point<I>. Вторым является
   * переменная</I> temp<I>, в которую собираются последовательные элементы агрегированной структуры</I>
   * point <I>при выполнении оператора запроса. Третьим является конструктор</I> point<I>, объявление которого
   * следует из объявления его объекта.</I></B>
   *
   */
  const AGGREGATE_GENERIC& QUERY(GENERIC_ENTITY& variable_id, const AGGREGATE_GENERIC& aggregate_source, LOGICAL logical_expression);

  /**
   * \brief FUNCTION ABS (ГОСТ Р ИСО 10303-11-2009, 15.1)
   *
   * \ref express::ABS() "15.1 Арифметическая функция ABS"
   *
   * <B>FUNCTION ABS ( V: NUMBER ) : NUMBER;</B>
   *
   * Функция \ref express::ABS() "ABS" возвращает абсолютное значение числа.
   * \param [in] V --- число.
   * \return абсолютное значение V. Тип данных результата идентичен типу данных параметра V.
   *
   * <B><I>Пример</I> --- ABS ( –10 ) ––> 10</B>
   */
  REAL ABS(const REAL& V);

  /**
   * \brief FUNCTION ABS (ГОСТ Р ИСО 10303-11-2009, 15.1)
   *
   * \ref express::ABS() "15.1 Арифметическая функция ABS"
   *
   * <B>FUNCTION ABS ( V: NUMBER ) : NUMBER;</B>
   *
   * Функция \ref express::ABS() "ABS" возвращает абсолютное значение числа.
   * \param [in] V --- число.
   * \return абсолютное значение V. Тип данных результата идентичен типу данных параметра V.
   *
   * <B><I>Пример</I> --- ABS ( –10 ) ––> 10</B>
   */
  INTEGER ABS(const INTEGER& V);

  /**
   * \brief FUNCTION ACOS (ГОСТ Р ИСО 10303-11-2009, 15.2)
   *
   * \ref express::ACOS() "15.2 Арифметическая функция ACOS"
   *
   * <B>FUNCTION ACOS ( V:NUMBER ) : REAL;</B>
   *
   * Функция ACOS возвращает величину угла, заданного значением косинуса.
   * \param [in] V --- число, представляющее значение косинуса угла.
   * \return значение угла в радианах (0 &le; результат &le; \f$\pi\f$), косинус которого равен значению <B>V</B>.
   * Условие: –1.0 &le; <B>V</B> &le; 1.0.
   *
   * <B><I>Пример</I> --- ACOS ( 0.3 ) ––> 1.266103...</B>
   */
  REAL ACOS(const NUMBER& V);

  /**
   * \brief FUNCTION ASIN (ГОСТ Р ИСО 10303-11-2009, 15.3)
   *
   * \ref express::ASIN() "15.3 Арифметическая функция ASIN"
   *
   * <B>FUNCTION ASIN ( V:NUMBER ) : REAL;</B>
   *
   * Функция ASIN возвращает величину угла, заданного значением синуса.
   * \param [in] V --- число, представляющее значение синуса угла.
   * \return значение угла в радианах (\f$ -\pi/2 \f$ &le; результат &le; \f$ \pi/2 \f$), синус которого равен значению <B>V</B>.
   * Условие: –1.0 &le; <B>V</B> &le; 1.0.
   *
   * <B><I>Пример</I> --- ASIN ( 0.3 ) ––> 3.04692...e-1</B>
   */
  REAL ASIN(const NUMBER& V);

  /**
   * \brief FUNCTION ATAN (ГОСТ Р ИСО 10303-11-2009, 15.4)
   *
   * \ref express::ATAN() "15.4 Арифметическая функция ATAN"
   *
   * <B>FUNCTION ATAN ( V1:NUMBER; V2:NUMBER ) : REAL;</B>
   *
   * Функция ATAN возвращает величину угла, заданного значением тангенса <B>V</B>, где <B>V</B> задано
   * выражением <B>V = V1/V2</B>.
   * \param [in] V1 --- число;
   * \param [in] V2 --- число.
   * \return начение угла в радианах (\f$ -\pi/2 \f$ &le; результат &le; \f$ \pi/2\f$),
   * тангенс которого равен значению <B>V</B>. Если значение параметра <B>V2</B> равно нулю, то результат равен
   * \f$ \pi/2\f$ или \f$ -\pi/2\f$ в зависимости от знака <B>V1</B>.
   *
   * Условие: <B>V1</B> и <B>V2</B> не должны одновременно иметь нулевое значение.
   *
   * <B><I>Пример</I> --- ATAN( –5.5, 3.0) ––> –1.071449...</B>
   */
  REAL ATAN(const NUMBER& V1, const NUMBER& V2);

  /**
   * \brief FUNCTION BLENGTH (ГОСТ Р ИСО 10303-11-2009, 15.5)
   *
   * \ref express::BLENGTH() "15.5 Двоичная функция BLENGTH"
   *
   * <B>FUNCTION BLENGTH ( V:BINARY ) : INTEGER;</B>
   *
   * Функция BLENGTH возвращает число битов в двоичном числе.
   * \param [in] V --- двоичное число.
   * \return реальное число битов в переданном функции двоичном числе.
   *
   * <B><I>Пример --- Использование функции</I> BLENGTH:
   <PRE>
     LOCAL
       n : NUMBER;
       х : BINARY := %01010010 ;
     END_LOCAL;
       ...
       n := BLENGTH ( x ); -- nприсваивается значение 8
   </PRE>
   * </B>
   */
  INTEGER BLENGTH(const BINARY& V);

  /**
   * \brief FUNCTION COS (ГОСТ Р ИСО 10303-11-2009, 15.6)
   *
   * \ref express::COS() "15.6 Арифметическая функция COS"
   *
   * <B>FUNCTION COS ( V:NUMBER ) : REAL;</B>
   *
   * Функция COS возвращает значение косинуса угла.
   * \param [in] V --- число, представляющее значение угла в радианах.
   * \return косинус угла V (–1.0 &le; результат &le; 1.0).
   *
   * <B><I>Пример</I> --- COS ( 0.5 ) ––> 8.77582...Е–1</B>
   */
  REAL COS(const NUMBER& V);

  /**
   * \brief FUNCTION EXISTS (ГОСТ Р ИСО 10303-11-2009, 15.7) 
   *
   * \ref express::EXISTS() "15.7 Универсальная функция EXISTS"
   *
   * <B>FUNCTION EXISTS ( V:GENERIC ) : BOOLEAN;</B>
   *
   * Функция EXISTS возвращает значение \ref express::BOOLEAN.TRUE "TRUE", если у входного параметра
   * существует значение, или значение \ref express::BOOLEAN.FALSE "FALSE", если у входного параметра
   * не существует значения. Функция EXISTS полезна для проверки, задано ли значение для необязательных
   * (OPTIONAL) атрибутов или инициализированы ли переменные.
   * \param [in] V --- выражение, результат которого может иметь любой тип данных.
   * \return \ref express::BOOLEAN.TRUE "TRUE" или \ref express::BOOLEAN.FALSE "FALSE", в зависимости
   * от того, имеет ли <B>V</B> конкретное или неопределённое (<B>?</B>) значение.
   *
   * <B><I>Пример</I> --- IF EXISTS ( a ) THEN ...</B>
   */
  BOOLEAN EXISTS(const GENERIC& V);

  /**
   * \brief FUNCTION EXP (ГОСТ Р ИСО 10303-11-2009, 15.8)
   *
   * \ref express::EXP() "15.8 Арифметическая функция EXP"
   *
   * <B>FUNCTION EXP ( V: NUMBER ) : REAL;</B>
   *
   * Функция EXP возвращает число е (основание системы натуральных логарифмов), возведенное в
   * степень <B>V</B>.
   * \param [in] V --- число.
   * \return значение \f$ e^v \f$.
   *
   * <B><I>Пример</I> --- ЕХР ( 10 ) ––> 2.202646...Е+4</B>
   */
  REAL EXP(const NUMBER& V);

  /**
   * \brief FUNCTION FORMAT (ГОСТ Р ИСО 10303-11-2009, 15.9)
   *
   * \ref express::FORMAT() "15.9 Универсальная функция FORMAT"
   *
   * <B>FUNCTION FORMAT(N : NUMBER; F : STRING) : STRING;</B>
   *
   * Функция \ref express::FORMAT() "FORMAT" возвращает форматированное строковое представление числа.
   * \param [in] N --- число (целое или действительное);
   * \param [in] F --- строка, содержащая команды форматирования.
   * \return строковое представление числа <B>N</B>, отформатированное в соответствии с <B>F</B>. При
   * необходимости строковое представление округляется.
   *
   * Строка форматирования содержит специальные символы, определяющие форму отображения
   * результата. Строка форматирования может быть представлена тремя способами:
   *
   * a) строка форматирования может задавать символьное описание представления результата;
   *
   * b) строка форматирования может задавать описание шаблона представления результата;
   *
   * c) если строка форматирования пуста, то производится стандартное представление результата.
   *
   * <BR>
   *
   */
  STRING FORMAT(const NUMBER& N, const STRING& F);

  /**
   * \brief FUNCTION HIBOUND (ГОСТ Р ИСО 10303-11-2009, 15.10)
   *
   * \ref express::HIBOUND() "15.10 Арифметическая функция HIBOUND"
   *
   * <B>FUNCTION \ref express::HIBOUND() "HIBOUND" ( V:AGGREGATE OF GENERIC ) : \ref express::INTEGER "INTEGER";</B><BR>
   * Функция \ref express::HIBOUND() "HIBOUND" возвращает объявленный верхний индекс объекта типа
   * \ref express::ARRAY_GENERIC "ARRAY" или объявленную верхнюю границу объекта типа
   * \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET".<BR>
   * Параметр: <B>V</B> --- агрегированное значение.<BR>
   * Результат:<BR>
   * a) если типом данных <B>V</B> является \ref express::ARRAY_GENERIC "ARRAY", то возвращаемым
   * значением является объявленный верхний индекс;<BR>
   * b) если типом данных <B>V</B> является \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET",
   * то возвращаемым значением является объявленная верхняя граница; если границы не
   * объявлены или верхняя граница объявлена неопределённой (<B>?</B>), то возвращается
   * неопределённое (<B>?</B>) значение.<BR>
   *
   * <B><I>Пример --- Использование функции</I> \ref express::HIBOUND() "HIBOUND" <I>для вложенных
   * агрегированных значений:</I>
   <PRE>
       LOCAL
         а : \ref express::ARRAY_GENERIC "ARRAY"[–3:19] OF \ref express::SET "SET"[2:4] OF \ref express::LIST "LIST" [0:?] OF \ref express::INTEGER "INTEGER";
         h1, h2, h3 : \ref express::INTEGER "INTEGER";
       END_LOCAL;
       ...
       a[–3] [1] [1] := 2;    –– помещает значение в список
       ...
       h1 := \ref express::HIBOUND() "HIBOUND"(a);           –– =19 (верхний индекс массива)
       h2 := \ref express::HIBOUND() "HIBOUND"(a[–3]);       –– = 4 (верхняя граница набора)
       h3 := \ref express::HIBOUND() "HIBOUND"(a[–3] [1]);   –– = ? (верхняя граница списка (не ограничен))
   </PRE> </B>
   */
  INTEGER HIBOUND(const AGGREGATE_GENERIC& V);
#if 0
  template<class T>
  INTEGER HIBOUND(const AGGREGATE<T>& V) {
    if (V.is_type_name("ARRAY")) {
      /*
       * Если типом данных V является ARRAY, то возвращаемым значением
       * является объявленный верхний индекс.
       */
      return V.bound_2;
    } else {
      if (EXISTS(V.bound_2).is_true()) {
        /*
         * Если типом данных V является BAG, LIST или SET, то возвращаемым
         * значением является объявленная верхняя граница.
         */
        return V.bound_2;
      } else {
        /*
         * Если границы не объявлены или верхняя граница объявлена неопределённой (?),
         * то возвращается неопределённое (?) значение.
         */
        return INTEGER();
      }
    }
  }
#endif
  /**
   * \brief FUNCTION HIINDEX (ГОСТ Р ИСО 10303-11-2009, 15.11)
   *
   * \ref express::HIINDEX() "15.11 Арифметическая функция HIINDEX"
   *
   * <B>FUNCTION \ref express::HIINDEX() "HIINDEX" ( V : AGGREGATE OF GENERIC ) : \ref express::INTEGER "INTEGER";</B><BR>
   * Функция \ref express::HIINDEX() "HIINDEX" возвращает верхний индекс объекта типа \ref express::ARRAY_GENERIC "ARRAY" или
   * число элементов в объекте типа \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET".<BR>
   * Параметр: <B>V</B> --- агрегированное значение.<BR>
   * Результат:<BR>
   * a) если типом данных <B>V</B> является \ref express::ARRAY_GENERIC "ARRAY", то возвращаемым значением является объявленный
   * верхний индекс;<BR>
   * b) если типом данных <B>V</B> является \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET", то возвращаемым
   * значением является фактическое число элементов в агрегированном значении.
   *
   * <B><I>Пример --- Использование функции</I> \ref express::HIINDEX() "HIINDEX" <I>для вложенных агрегированных значений:</I>
   <PRE>
       LOCAL
         а : \ref express::ARRAY_GENERIC "ARRAY"[–3 : 19] OF \ref express::SET "SET"[2 : 4] OF \ref express::LIST "LIST"[0 : ?] OF \ref express::INTEGER "INTEGER";
         h1, h2, h3 : \ref express::INTEGER "INTEGER";
       END_LOCAL;
         a[–3][1][1] := 2;        –– помещает значение в список
         h1 := \ref express::HIINDEX() "HIINDEX"(a);        –– = 19 (верхний индекс массива)
         h2 := \ref express::HIINDEX() "HIINDEX"(a[–3]);    –– = 1 (размер набора) –– это неверно для
                                                         –– заданных границ
                                                         –– набора
       h3 := \ref express::HIINDEX() "HIINDEX"(a[–3] [1]);  –– = 1 (размер списка)
   </PRE> </B>
   */
  INTEGER HIINDEX(const AGGREGATE_GENERIC& V);
#if 0
    INTEGER hiindex;
    if (V.is_type_name("ARRAY")) {
      /*
       * Если типом данных V является ARRAY,
       * то возвращаемым значением является объявленный верхний индекс.
       */
      hiindex = V.bound_2;
    } else {
      /*
       * Если типом данных V является BAG, LIST или SET, то возвращаемым
       * значением является фактическое число элементов в агрегированном значении
       */
      hiindex = V._elements.size();
    }
    return hiindex;
  }
#endif
  /**
   * \brief FUNCTION LENGTH (ГОСТ Р ИСО 10303-11-2009, 15.12)
   *
   * \ref express::LENGTH() "15.12 Строковая функция LENGTH"
   *
   * <B>FUNCTION LENGTH ( V : STRING ) : INTEGER;</B>
   *
   * Функция LENGTH возвращает число символов в строке.
   *
   * \param [in] V --- строковое значение.
   * \return число символов в строке; возвращаемое значение должно быть больше или равно нулю.
   *
   * <B><I>Пример --- Использование функции </I>LENGTH:
   <PRE>
       LOCAL
         n : NUMBER;
         x1 : STRING := 'abc' ;
         x2 : STRING := "0000795E00006238";
       END_LOCAL;
       ...
       n := LENGTH ( x1 ) ; -- n присваивается значение 3
       n := LENGTH ( х2 ) ; -- n присваивается значение 2
   </PRE> </B>
   */
  INTEGER LENGTH(const STRING& V);

  /**
   * \brief FUNCTION LOBOUND (ГОСТ Р ИСО 10303-11-2009, 15.13)
   *
   * \ref express::LOBOUND() "15.13 Арифметическая функция LOBOUND"
   *
   * <B>FUNCTION \ref express::LOBOUND() "LOBOUND" ( V : AGGREGATE OF GENERIC ) : \ref express::INTEGER "INTEGER";</B><BR>
   * Функция \ref express::LOBOUND() "LOBOUND" возвращает объявленный нижний индекс объекта типа \ref express::ARRAY_GENERIC "ARRAY"
   * или объявленную нижнюю границу объекта типа \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET".<BR>
   * Параметр: <B>V</B> --- агрегированное значение.<BR>
   * Результат:<BR>
   * a) если типом данных <B>V</B> является \ref express::ARRAY_GENERIC "ARRAY", то возвращаемым значением является
   * объявленный нижний индекс;<BR>
   * b) если типом данных <B>V</B> является \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET",
   * то возвращаемым значением является объявленная нижняя граница; если нижняя граница
   * не объявлена, то возвращается ноль (0).
   *
   * <B><I>Пример --- Использование функции</I> \ref express::LOBOUND() "LOBOUND" <I>для вложенных агрегированных значений:</I>
   <PRE>
       LOCAL
         а : \ref express::ARRAY_GENERIC "ARRAY" [–3 : 19] OF \ref express::SET "SET" [2 : 4] OF \ref express::LIST "LIST" [0 : ?] OF \ref express::INTEGER "INTEGER";
         h1, h2, h3 : \ref express::INTEGER "INTEGER";
       END_LOCAL;
       ...
       h1 := \ref express::LOBOUND() "LOBOUND" (a);              -- = –3 (нижний индекс массива)
       h2 := \ref express::LOBOUND() "LOBOUND" (a[–3]);          -- = 2 (нижняя граница набора)
       h3 := \ref express::LOBOUND() "LOBOUND" (a[–3][1]);       -- = 0 (нижняя граница списка)
   </PRE> </B>
   */
  INTEGER LOBOUND(const AGGREGATE_GENERIC& V);
#if 0
    if (V.is_type_name("ARRAY")) {
      /*
       * Если типом данных V является ARRAY, то возвращаемым значением
       * является объявленный нижний индекс.
       */
      return V.bound_1;
    } else {
      /*
       * Если типом данных V является BAG, LIST или SET, то возвращаемым
       * значением является является объявленная нижняя граница;
       */
      if (EXISTS(V.bound_1)) {
        return V.bound_1;
      } else {
      /* Если нижняя граница не объявлена, то возвращается ноль (0). */
        INTEGER out;
        out = 0;
        return out;
      }
    }
  }
#endif

  /**
   * \brief FUNCTION LOG (ГОСТ Р ИСО 10303-11-2009, 15.14)
   *
   * \ref express::LOG() "15.14 Арифметическая функция LOG"
   *
   * <B>FUNCTION LOG ( V : NUMBER ) : REAL;</B>
   *
   * Функция LOG возвращает натуральный логарифм числа.
   * \param [in] V --- число.
   * \return действительное число, являющееся натуральным логарифмом V.
   *
   * Условие: <B>V</B> > 0.0
   *
   * <B><I>Пример</I> --- LOG ( 4.5 ) ––> 1.504077...Е0</B>
   */
  REAL LOG(const NUMBER& V);

  /**
   * \brief FUNCTION LOG2 (ГОСТ Р ИСО 10303-11-2009, 15.15)
   *
   * \ref express::LOG2() "15.15 Арифметическая функция LOG2"
   *
   * <B>FUNCTION LOG2 ( V : NUMBER ) : REAL;</B>
   *
   * Функция LOG2 возвращает логарифм числа по основанию два.
   * \param [in] V --- число.
   * \return действительное число, являющееся логарифмом V по основанию два.
   *
   * Условие: <B>V</B> > 0.0
   *
   * <B><I>Пример</I> --- LOG2 ( 8 ) ––> 3.00...Е0</B>
   */
  REAL LOG2(const NUMBER& V);

  /**
   * \brief FUNCTION LOG10 (ГОСТ Р ИСО 10303-11-2009, 15.16)
   *
   * \ref express::LOG10() "15.16 Арифметическая функция LOG10"
   *
   * <B>FUNCTION LOG10 ( V : NUMBER ) : REAL;</B>
   *
   * Функция LOG10 возвращает десятичный логарифм числа.
   * \param [in] V --- число.
   * \return действительное число, являющееся десятичным логарифмом V.
   *
   * Условие: <B>V</B> > 0.0
   *
   * <B><I>Пример</I> --- LOG10 ( 10 ) ––> 1.00...Е0</B>
   */
  REAL LOG10(const NUMBER& V);

  /**
   * \brief FUNCTION LOINDEX (ГОСТ Р ИСО 10303-11-2009, 15.17)
   *
   * \ref express::LOINDEX() "15.17 Арифметическая функция LOINDEX"
   *
   * <B>FUNCTION \ref express::LOINDEX() "LOINDEX" ( V : AGGREGATE OF GENERIC ) : \ref express::INTEGER "INTEGER";</B><BR>
   * Функция \ref express::LOINDEX() "LOINDEX" возвращает нижний индекс агрегированного значения.<BR>
   * Параметр: <B>V</B> --- агрегированное значение.<BR>
   * Результат:<BR>
   * a) если типом данных <B>V</B> является \ref express::ARRAY_GENERIC "ARRAY", то возвращаемым значением является объявленный
   * нижний индекс;<BR>
   * b) если типом данных <B>V</B> является \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET", то возвращаемым
   * значением является единица (1).
   *
   * <B><I>Пример</I> --- <I>Использование функции</I> \ref express::LOINDEX() "LOINDEX" <I>для вложенных агрегированных значений:</I>
   <PRE>
     LOCAL
       а : \ref express::ARRAY_GENERIC "ARRAY"[–3:19] OF \ref express::SET "SET"[2:4] OF \ref express::LIST "LIST" [0 : ?] OF \ref express::INTEGER "INTEGER";
       h1, h2, h3 : \ref express::INTEGER "INTEGER";
     END_LOCAL;
     ...
     h1 := \ref express::LOINDEX() "LOINDEX"(a);          –– = –3 (нижний индекс массива)
     h2 := \ref express::LOINDEX() "LOINDEX"(a[–3]);      –– =  1 (для набора)
     h3 := \ref express::LOINDEX() "LOINDEX"(a[–3] [1]);  –– =  1 (для списка)
   </PRE> </B>
   */
  INTEGER LOINDEX(const AGGREGATE_GENERIC& V);

  /**
   * \brief FUNCTION NVL (ГОСТ Р ИСО 10303-11-2009, 15.18)
   *
   * \ref express::NVL() "15.18 Функция пустого значения NVL"
   *
   * <B>FUNCTION \ref express::NVL() "NVL" (V : GENERIC : GEN1; SUBSTITUTE : GENERIC : GEN1) : GENERIC : GEN1;</B><BR>
   * Функция \ref express::NVL() "NVL" возвращает исходное значение либо альтернативное значение, если входной параметр
   * имеет неопределённое (?) значение.
   * 
   * \param V [in] --- выражение любого типа данных;
   * \param SUBSTITUTE [in] --- выражение, которое не должно иметь неопределённое (?) значение.
   * \return если V не имеет неопределённого (?) значение, то возвращается значение V. В противном
   * случае возвращается SUBSTITUTE.
   *
   * <B><I>Пример --- Функция</I> NVL <I>используется, чтобы подставить ноль (0.0) в качестве
   * значения</I> Z, <I>если</I> Z <I>имеет неопределённое (?) значение:</I>
   <PRE>
    ENTITY unit_vector;
    х, у : REAL;
    z : OPTIONAL REAL;
    WHERE
    x**2 + y**2 + NVL(z, 0.0)**2 = 1.0;
    END_ENTITY
   </PRE>
   * </B>
   */
  template<class T>
  const T& NVL(const T& V, const T& SUBSTITUTE) {
    if (V.is_determinated()) return V;
    else return SUBSTITUTE;
  }

  /**
   * \brief FUNCTION ODD (ГОСТ Р ИСО 10303-11-2009, 15.19)
   *
   * \ref express::ODD() "15.19 Арифметическая функция ODD"
   *
   * <B>FUNCTION ODD ( V : INTEGER ) : LOGICAL;</B>
   *
   * Функция ODD возвращает значение TRUE или FALSE, в зависимости от того, является ли заданное
   * число нечетным или четным.
   * \param [in] V --- целое число.
   * \return если <B>V MOD 2 = 1</B>, то возвращается TRUE, в противном случае, возвращается FALSE.
   *
   * Условие: ноль не считается нечетным числом.
   *
   * <B><I>Пример</I> --- ODD ( 121 ) ––> TRUE</B>
   */
  LOGICAL ODD(const INTEGER& V);

  /**
   * \brief FUNCTION ROLESOF (ГОСТ Р ИСО 10303-11-2009, 15.20)
   *
   * \ref express::ROLESOF() "15.20 Универсальная функция ROLESOF"
   *
   * <B>FUNCTION ROLESOF ( V : GENERIC_ENTITY ) : SET OF STRING;</B>
   *
   * Функция ROLESOF возвращает набор строк, содержащих полные уточненные имена ролей,
   * исполняемых указанным экземпляром объекта. Полное уточненное имя определяется как имя атрибута,
   * уточненное именем схемы и объекта, в которых объявлен данный атрибут (то есть <B>'SCHEMA.ENTITY.ATTRIBUTE'</B>).
   * \param [in] V --- любой экземпляр объектного типа данных.
   * \return набор строковых значений (на верхнем регистре), содержащих полные уточненные имена
   * атрибутов экземпляров объектов, использующих экземпляр <B>V</B>.
   *
   * Если именованный тип данных импортирован посредством операторов <B>USE</B> или <B>REFERENCE</B>, то
   * возвращаются также имя исходной схемы и имя именованного типа данных в этой схеме, если имело
   * место переименование. Поскольку операторы <B>USE</B> могут быть связаны в цепочку, то возвращаются имена
   * всех связанных схем и имена именованного типа данных во всех схемах.
   *
   * <B><I>Пример --- Данный пример демонстрирует возможность использования точки в качестве
   * центра окружности. Функция</I> ROLESOF <I>определяет, какие роли экземпляр объекта исполняет
   * фактически.</I>
   <PRE>
       SCHEMA that_schema;
       ENTITY point;
         x, у, z : REAL;
       END_ENTITY;
       ENTITY line;
         start,
         end : point;
       END_ENTITY;
       END SCHEMA;
       SCHEMA this_schema;
       USE FROM that_schema (point, line);
       CONSTANT
         origin : point := point(0.0, 0.0, 0.0);
       END_CONSTANT;
       ENTITY circle;
         center : point;
         axis : vector;
         radius : REAL;
       END_ENTITY;
       ...
       LOCAL
         p : point := point(1.0, 0.0, 0.0);
         с : circle := circle(p, vector(1, 1, 1), 1.0);
         l : line := line(p, origin);
       END_LOCAL;
         ...
       IF 'THIS_SCHEMA.CIRCLE.CENTRE' IN ROLESOF(p) THEN -- true
         ...
       IF 'THIS_SCHEMA.LINE.START' IN ROLESOF(p) THEN    -- true
         ...
       IF 'THAT_SCHEMA.LINE.START' IN ROLESOF(p) THEN     -- true
         ...
       IF 'THIS_SCHEMA.LINE.END' IN ROLESOF(p) THEN       -- false
   </PRE>
   * </B>
   */
//  SET_GENERIC& ROLESOF(const GENERIC_ENTITY& V);

  /**
   * \brief FUNCTION SIN (ГОСТ Р ИСО 10303-11-2009, 15.21)
   *
   * \ref express::SIN() "15.21 Арифметическая функция SIN"
   *
   * <B>FUNCTION SIN ( V : NUMBER ) : REAL;</B>
   *
   * Функция SIN возвращает значение синуса угла.
   * \param [in] V --- число, представляющее значение угла в радианах.
   * \return синус угла V (–1.0 &le; результат &le; 1.0).
   *
   * <B><I>Пример</I> --- SIN ( PI ) --> 0.0</B>
   */
  REAL SIN(const NUMBER& V);


  /**
   * \brief FUNCTION SIZEOF (ГОСТ Р ИСО 10303-11-2009, 15.22)
   *
   * \ref express::SIZEOF() "15.22 Агрегированная функция SIZEOF"
   *
   * <B>FUNCTION SIZEOF ( V : AGGREGATE OF GENERIC ) : \ref express::INTEGER "INTEGER";</B><BR>
   * Функция \ref express::SIZEOF "SIZEOF" возвращает число элементов в агрегированном значении.
   *
   * \param V [in] агрегированное значение.
   *
   * \return a) если типом данных <B>V</B> является \ref express::ARRAY_GENERIC "ARRAY", то возвращаемым значением
   * является объявленное число элементов в данном агрегированном типе данных;<BR>
   * b) если типом данных V является \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET",
   * то возвращаемым значением является фактическое число элементов в агрегированном значении.
   *
   * <B><I>Пример --- Использование функции</I> SIZEOF:
   <PRE>
       LOCAL
         n : NUMBER;
         у : \ref express::ARRAY_GENERIC "ARRAY"[2:5] OF b;
       END_LOCAL;
       ...
       n := SIZEOF (у);      –– n присваивается значение 4
   </PRE>
   * </B>
   */
  INTEGER SIZEOF(const AGGREGATE_GENERIC& V);

  /**
   * \brief FUNCTION SQRT (ГОСТ Р ИСО 10303-11-2009, 15.23)
   *
   * \ref express::SQRT() "15.23 Арифметическая функция SQRT"
   *
   * FUNCTION SQRT ( V : NUMBER ) : REAL;
   *
   * Функция SQRT возвращает неотрицательное значение квадратного корня числа.
   *
   * \param V [in] любое неотрицательное число.
   * \return неотрицательное значение квадратного корня числа \ref express::SQRT "V".
   *
   * Условие: \ref express::SQRT "V" \f$ \geqslant \f$ 0.0
   *
   * <B><I>Пример</I> --- SQRT(121) ---> 11.0.</B>
   */ 
  REAL SQRT(const NUMBER& V);

  /**
   * \brief FUNCTION TAN (ГОСТ Р ИСО 10303-11-2009, 15.24)
   *
   * \ref express::TAN() "15.24 Арифметическая функция TAN"
   *
   * FUNCTION TAN ( V : NUMBER ) : REAL;
   * 
   * Функция TAN возвращает значение тангенса угла.
   * \param [in] V --- число, представляющее значение угла в радианах.
   * \return тангенс угла. Если угол равен \f$ n\pi/2 \f$, где \f$ n \f$ --- нечетное целое число, то возвращается
   * неопределённое (<B>?</B>) значение.
   *
   * <B><I>Пример</I> --- TAN ( 0.0 ) ---> 0.0</B>
   */
  REAL TAN(const NUMBER& V);

  /**
   * \brief <B>FUNCTION TYPEOF (ГОСТ Р ИСО 10303-11-2009, 15.25)</B>
   *
   * \ref express::TYPEOF() "15.25 Универсальная функция TYPEOF"
   *
   * <B>FUNCTION TYPEOF ( V : GENERIC ) : \ref express::SET "SET" OF STRING;</B><BR>
   * Функция \ref express::TYPEOF() "TYPEOF" возвращает набор строк, содержащих имена всех типов данных, к которым
   * принадлежит данный параметр. За исключением простых типов данных (\ref express::BINARY "BINARY",
   * \ref express::BOOLEAN "BOOLEAN", \ref express::INTEGER "INTEGER", \ref express::LOGICAL "LOGICAL", \ref express::NUMBER "NUMBER",
   * \ref express::REAL "REAL" и \ref express::STRING "STRING") и агрегированных типов данных (\ref express::ARRAY_GENERIC "ARRAY",
   * \ref express::BAG_GENERIC "BAG", \ref express::LIST_GENERIC "LIST", \ref express::SET_GENERIC "SET"), данные
   * имена уточняются именем схемы, содержащей определение данного типа данных.
   * 
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Основным назначением данной функции является проверка, может ли данное значение
   * (переменной или атрибута) использоваться для определённой цели, например, чтобы убедиться в
   * совместимости по присваиванию двух значений. Данная функция может также использоваться, если разные подтипы или
   * конкретизации заданного типа данных должны по-разному трактоваться в некотором контексте.</SMALL>
   * 
   * \param V [in] --- значение любого типа данных.
   * \return набор строковых значение --- имена (на верхнем регистре) всех типов данных, к которым принадлежит <B>V</B>.
   * 
   * Результат: содержимым возвращаемого набора строковых значений являются имена (на верхнем
   * регистре) всех типов данных, к которым принадлежит <B>V</B>. Данные имена уточняются именем схемы,
   * содержащей определение данного типа данных ( <B>'SCHEMA.TYPE'</B> ), если они не относятся к простому или
   * агрегированному типу данных. Возвращаемый набор строковых значений может быть определён посредством
   * следующего алгоритма (данный алгоритм приводится здесь в целях пояснения, а не в качестве
   * предписания какого-либо конкретного вида реализации):<BR>
   * a) возвращаемый набор строковых значений набор инициализируется включением как имени типа
   * данных, к которому принадлежит <B>V</B>, так и именем типа данных, которое представляет экземпляр <B>V</B>
   * (если они различаются), включая имена их схем, если данные типы данных являются именованными типами
   * данных; при этом применяются следующие правила:
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Если фактический параметр, передаваемый функции \ref express::TYPEOF "TYPEOF", был формальным
   * параметром некоторой вычисляемой функции, то «типом данных, к которому принадлежит <B>V</B> (в соответствии
   * с объявлением) является тип данных, объявленный для исходного фактического параметра, или тип данных
   * результата вычисления выражения, определяющего фактический параметр, в соответствии с разделом 12, а не
   * тип данных, объявленный для формального параметра, вместо которого он подставлен:</SMALL>
   *
   * 1) если <B>V</B> является агрегированным значением, то имя типа данных является просто именем
   * агрегированного типа данных (\ref express::ARRAY_GENERIC "ARRAY",  \ref express::BAG "BAG", \ref express::LIST "LIST", \ref express::SET "SET"),
   * а не каким-либо другим,
   *
   * 2) если <B>V</B> является перечисляемым типом данных, базирующимся на другом перечисляемом типе
   * данных, то добавляют имена перечисляемых типов данных, получаемых при прослеживании
   * взаимосвязей <B>BASED_ON</B>, начиная от данного перечисляемого типа данных,<BR>
   * 3) если <B>V</B> является наращиваемым перечисляемым типом данных, то рекурсивно добавляются
   * имена перечисляемых типов данных, являющихся расширениями <B>V</B>.
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Две последние из перечисленных выше позиций справедливы для расширяемого
   * перечисляемого типа данных, который базируется на другом перечисляемом типе данных,</SMALL><BR>
   * 4) если <B>V</B> имеет неопределённое (<B>?</B>) значение, то возвращается пустой набор типа данных
   * \ref express::SET "SET";<BR>
   * b) повторяют следующие действия до тех пор, пока возвращаемый набор не перестанет расширяться:<BR>
   * 1) выполняют следующие действия для всех имен в возвращаемом наборе:
   * - если текущее имя является именем простого типа данных, то пропускают,<BR>
   * - если текущее имя является именем агрегированного типа данных (\ref express::ARRAY_GENERIC "ARRAY",
   * \ref express::BAG "BAG", \ref express::LIST "LIST", \ref express::SET "SET"), то пропускают,<BR>
   * - если текущее имя является именем перечисляемого типа данных, то пропускают,<BR>
   * - если текущее имя является именем выбираемого типа данных, то к возвращаемому набору
   * добавляются имена всех типов данных (с именем схемы) из списка выбора, которые действительно
   * конкретизируются посредством <B>V</B> (данных имен может быть несколько, так как список выбора может
   * содержать имена типов данных, являющихся совместимыми подтипами общего супертипа или
   * конкретизациями одного общего обобщённого типа),<BR>
   * - если текущее имя является именем любого другого вида определённого типа данных, то имя
   * типа данных, на который ссылается определение данного типа данных, включая (при необходимости)
   * имя схемы, добавляется к возвращаемому набору. Если ссылка делается на агрегированный тип
   * данных, то добавляется имя данного агрегированного типа данных,<BR>
   * - если текущее имя является именем объекта, то к возвращаемому набору добавляются имена
   * всех тех подтипов (включая, при необходимости, имя схемы), которые действительно конкретизируются
   * посредством <B>V</B>,
   * 
   * 2) выполняют следующие действия для всех имен в возвращаемом наборе:<BR>
   * - если текущее имя является именем подтипа, то к возвращаемому набору добавляются имена
   * всех его супертипов,<BR>
   * - если текущее имя является именем конкретизации, то к возвращаемому набору добавляются
   * имена всех её обобщений,
   * 
   * 3) выполняют следующие действия для всех имен в возвращаемом наборе и для каждого типа
   * данных \ref express::SELECT "SELECT", у которого текущее имя присутствует в списке выбора:<BR>
   * - добавляют имя выбираемого типа данных к списку,<BR>
   * - если выбираемый тип данных базируется на другом выбираемом типе данных, то добавляют
   * имена выбираемых типов данных, получаемых при прослеживании взаимосвязей <B>BASED_ON</B>, начиная
   * с текущего выбираемого типа данных,<BR>
   * - если выбираемый тип данных является наращиваемым выбираемым типом данных, то рекурсивно
   * добавляют имена выбираемых типов данных, являющихся расширениями текущего выбираемого
   * типа данных,
   * 
   * 4) выполняют следующие действия для всех имен в возвращаемом наборе: если текущее имя
   * импортировано в схему посредством операторов <B>USE</B> или <B>REFERENCE</B>, то в возвращаемый набор
   * добавляют имя из схемы, откуда был осуществлен импорт, уточненное именем данной схемы. Поскольку
   * операторы <B>USE</B> могут быть связаны в цепочки, в возвращаемый набор также добавляют имена из всех
   * связанных схем, уточненные именами соответствующих схем;<BR>
   * c) результатом функции является сформированный возвращаемый набор.<BR>
   * Если <B>V</B> имеет неопределённое (<B>?</B>) значение, то функция \ref express::TYPEOF() "TYPEOF" возвращает пустой набор.
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Функция \ref express::TYPEOF() "TYPEOF" завершает свою работу, когда встречается агрегированный тип
   * данных. Функция не дает информации относительно базисного типа данных агрегированного значения. При
   * необходимости данная информация может быть получена при применении функции \ref express::TYPEOF() "TYPEOF" к
   * допустимым элементам агрегированного значения.</SMALL>
   * 
   * <B><I>Примеры<BR>
   * 1 В контексте следующей схемы:</I>
   <PRE>
       SCHEMA this_schema;
         TYPE
           mylist = \ref express::LIST "LIST" [1 : 20] OF REAL;
         END_TYPE;
         ...
         LOCAL
           lst : mylist;
         END_LOCAL;
         ...
       END_SCHEMA;
   </PRE>
   * <B><I>cледующие условия имеют значение</I> TRUE:</B>
   <PRE>
       TYPEOF (lst) = [ ' THIS_SCHEMA.MYLIST', 'LIST' ]
       TYPEOF (lst [17] ) = [ 'REAL', 'NUMBER' ]
   </PRE>
   * <B><I>2 Действие операторов</I> USE <I>или</I> REFERENCE <I>показано на основе предыдущего примера:</I></B>
      <PRE>
       SCHEMA another_schema;
         REFERENCE FROM this_schema (mylist AS hislist);
         ...
           lst : hislist;
         ...
       END_SCHEMA;
   </PRE>
   * <B><I>В данном контексте следующее выражение имеет значение</I> TRUE:</B>
   <PRE>
    TYPEOF (lst) = [ 'ANOTHER_SCHEMA.HISLIST', ' THIS_SCHEMA.MYLIST', 'LIST' ]
   </PRE> </B>
   */
//  template<class T>
//  SET_GENERIC& TYPEOF(const GENERIC& V);

  /**
   * \brief FUNCTION USEDIN (ГОСТ Р ИСО 10303-11-2009, 15.26)
   *
   * \ref express::USEDIN "15.26 Универсальная функция USEDIN"
   *
   * Функция \ref express::USEDIN "USEDIN" возвращает все экземпляры объекта, в которых используется
   * указанный экземпляр объекта в указанной роли.
   * \param [in] T --- любой экземпляр любого объектного типа данных.
   * \param [in] R --- строка, содержащая полностью уточненное имя атрибута (роли), в соответствии с \ref express::ROLESOF() "15.20"
   * \return все экземпляры объекта, в которых используется указанный экземпляр объекта в
   * указанной роли, возвращаются в форме пакета (типа данных \ref express::BAG "BAG").
   *
   * Если экземпляр <B>Т</B> не исполняет никаких ролей или роль <B>R</B> не указана, то возвращается пустой пакет.
   *
   * Если <B>R</B> представлен пустой строкой, то документируется каждое использование <B>Т</B>. Проверяют все
   * взаимосвязи, направленные к <B>Т</B>. Если взаимосвязь исходит от атрибута с именем <B>R</B>, то экземпляр объекта,
   * содержащий данный атрибут, добавляется к возвращаемому пакету. Отметим, что, если <B>Т</B> не используется,
   * то возвращается пустой пакет.
   *
   * <B><I>Пример --- Данный пример показывает, как может быть использовано правило для проверки
   * того, что должна существовать точка (объект</I> point<I>) в начале координат, используемая как центр
   * окружности. Заметим, что в данном примере выражение</I> QUERY <I>(см. 12.6.7) используется в качестве
   * параметра функции</I> SIZEOF.
   <PRE>
       ENTITY point;
         х, у, z : REAL;
       END_ENTITY;
       ENTITY circle;
         centre : point;
         axis : vector;
         radius : REAL;
       END_ENTITY; ...
       (* Правило "example" находит каждую точку, используемую в качестве центра
          окружности, и затем проверяет, что, по крайней мере, одна из этих точек
          расположена в начале координат *)
       ...
       RULE example FOR (point);
       LOCAL
         circles : SET OF circle := []; \-- пустой набор окружностей
       END_LOCAL;
       REPEAT i := LOINDEX(point) TO HIINDEX(point);
         circles := circles +
                    USEDIN (point [i], 'THIS_SCHEMA.CIRCLE.CENTRE' );
       END_REPEAT;
       WHERE R1 : SIZEOF (
                    QUERY(                                     -- начало запроса
                      at zero <* circles |                     -- взять все точки
                      (at_zero.centre = point ( 0.0, 0.0, 0.0) ) -- в 0, 0, 0
                    )
              ) >= 1;                                       -- по крайней мере, одна
       END_RULE;
   </PRE> </B>
   */
//  BAG_GENERIC& USEDIN(const GENERIC& T, const STRING& R);

  /**
   * \brief FUNCTION VALUE (ГОСТ Р ИСО 10303-11-2009, 15.27)
   *
   * \ref express::VALUE() "15.27 Арифметическая функция VALUE"
   *
   * <B>FUNCTION VALUE ( V : STRING ) : NUMBER ;</B>
   *
   * Функция VALUE возвращает число, представленное строкой.
   * \param [in] V --- строка, содержащая действительный или целочисленный литерал (см. \ref p11_s7_5 "7.5").
   * \return число, соответствующее содержанию строки. Если строка не может быть
   * интерпретирована как действительный или целочисленный литерал, то возвращается неопределённое (<B>?</B>) значение.
   *
   * <B><I>Пример --- В данном примере представлены результаты вызова функции</I> VALUE <I>с разными
   * параметрами:</I>
   <PRE>
       VALUE ( '1.234' ) --> 1.234 (действительное число)
       VALUE ( '20' )    --> 20 (целое число)
       VALUE ( 'abc' )   --> ? (неопределённое значение)
   </PRE> </B>
   */
  NUMBER VALUE(const STRING& V);

  /**
   * \brief FUNCTION VALUE_IN (ГОСТ Р ИСО 10303-11-2009, 15.28)
   *
   * \ref express::VALUE_IN() "15.28 Функция принадлежности VALUE_IN"
   *
   * <B>FUNCTION VALUE_IN ( C : AGGREGATE OF GENERIC : GEN; V : GENERIC : GEN ) : LOGICAL;</B>
   *
   * Функция VALUE_IN возвращает логическое значение в зависимости от того, принадлежит ли
   * конкретное значение к агрегированной структуре.
   * \param [in] C --- агрегированная структура любого типа;
   * \param [in] V --- выражение, совместимое по присваиванию с базисным типом С.
   * \return a) если V или С имеет неопределённое (?) значение, то возвращается значение UNKNOWN;<BR>
   * b) если значение какого-либо элемента из С равно значению V, то возвращается значение TRUE;<BR>
   * c) если какой-либо элемент из С имеет неопределённое (?) значение, то возвращается значение UNKNOWN;<BR>
   * d) во всех других случаях возвращается значение FALSE.
   *
   * <B><I>Пример — Следующая проверка обеспечивает, что существует хотя бы одна точка (объект</I> point<I>),
   * расположенная в начале координат:</I>
   <PRE>
       LOCAL
         points : SET OF point;
       END_LOCAL;
       ...
       IF VALUE_IN (points, point (0.0, 0.0, 0.0)) THEN ...
   </PRE> </B>
   */
  LOGICAL VALUE_IN(const AGGREGATE_GENERIC& C, const GENERIC& V);

  /**
   * \brief FUNCTION VALUE_UNIQUE (ГОСТ Р ИСО 10303-11-2009, 15.29)
   *
   * \ref express::VALUE_UNIQUE() "15.29 Функция уникальности VALUE_UNIQUE"
   *
   * <B>FUNCTION VALUE_UNIQUE ( V : AGGREGATE OF GENERIC) : LOGICAL;</B>
   *
   * Функция VALUE_UNIQUE возвращает логическое значение в зависимости от того, являются ли
   * значения элементов агрегированной структуры уникальными.
   * \param [in] V — агрегированная структура любого типа данных.
   * \return a) если <B>V</B> имеет неопределённое (<B>?</B>) значение, то возвращается значение UNKNOWN;<BR>
   * b) если значения любых двух элементов из V равны, то возвращается значение FALSE;<BR>
   * c) если любой элемент из V имеет неопределённое (<B>?</B>) значение, то возвращается значение UNKNOWN;<BR>
   * d) во всех других случаях возвращается значение TRUE.
   *
   * <B><I>Пример --- Следующая проверка обеспечивает, что все точки (объекты</I> points<I>) в наборе
   * расположены на разных позициях (по определению, эти точки различны, то есть их экземпляры уникальны).</I>
   <PRE>
       IF VALUE_UNIQUE (points) THEN ...
   </PRE> </B>
   */
  LOGICAL VALUE_UNIQUE(const AGGREGATE_GENERIC& V);

  /**
   * \brief PROCEDURE INSERT (ГОСТ Р ИСО 10303-11-2009, 16.1)
   *
   * \ref express::INSERT() "16.1 Процедура INSERT"
   *
   * <B>PROCEDURE INSERT ( VAR L : LIST OF GENERIC : GEN; E : GENERIC : GEN; P : INTEGER );</B>
   *
   * Процедура \ref express::INSERT "INSERT" вставляет элемент на заданную позицию в списке.
   * \param [in, out] L --- значение списка, в который должен быть вставлен элемент;
   * \param [in] E --- экземпляр, вставляемый в список <B>L</B>. <B>Е</B> должен быть совместим с базисным типом <B>L</B>, как
   * указано метками типов в заголовке процедуры;
   * \param [in] P --- целое число, задающее позицию в <B>L</B>, на которую должен быть вставлен элемент <B>Е</B>.
   *
   * Результат: список <B>L</B> модифицируется вставлением <B>Е</B> в <B>L</B> на указанную позицию. <B>Е</B> вставляется
   * непосредственно после существующего элемента, расположенного на позиции <B>Р</B>, если <B>Р</B> = 0, то <B>Е</B>
   * становится первым элементом списка.
   *
   * Условие: <B>0 &le; Р &le; SIZEOF(L)</B>.
   */
//  void INSERT(LIST_GENERIC& L, const GENERIC& E, const INTEGER& P);

  /**
   * \brief PROCEDURE REMOVE (ГОСТ Р ИСО 10303-11-2009, 16.2)
   *
   * \ref express::REMOVE() "16.2 Процедура REMOVE"
   *
   * <B>PROCEDURE REMOVE ( VAR L : LIST OF GENERIC; P : INTEGER );</B>
   *
   * Процедура \ref express::REMOVE() "REMOVE" удаляет элемент из заданной позиции в списке.
   * \param [in, out] L --- значение списка, из которого должен быть удален элемент;
   * \param [in] P --- целое число, задающее позицию в <B>L</B>, из которой должен быть удален элемент.
   *
   * Результат: список <B>L</B> модифицируется удалением элемента, находящегося на заданной позиции <B>Р</B>.
   *
   * Условие: <B>1 &le; Р &le; SIZEOF(L)</B>.
   */
//  void REMOVE(LIST_GENERIC& L, const INTEGER& P);
}
