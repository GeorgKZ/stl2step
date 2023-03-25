/**
 * \file
 * \brief Файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-43-2016.
 */


namespace express {

#if !defined(ISO130303_43_FIRST) || defined(__DOXYGEN__)


  /**
   *\file

   * <HR>
   * \anchor p43
   * <CENTER><H1>ГОСТ Р ИСО 10303-43-2016</H1></CENTER>
   * <HR>
   * <H2>
   * Системы автоматизации производства и их интеграция —<BR>
   * ПРЕДСТАВЛЕНИЕ ДАННЫХ ОБ ИЗДЕЛИИ И ОБМЕН ЭТИМИ ДАННЫМИ —<BR>
   * Часть 43:<BR>
   * Интегрированный обобщенный ресурс:<BR>
   * Структуры представления
   * </H2>
   */

/**
 * \file
 * \section p43_1 1. Область применения
 * 
 * В настоящем стандарте специфицированы конструкции объединенных обобщенных ресурсов для
 * структур представления. Это - собрания элементов данных об изделии, которые группируются вместе
 * для описания свойств и аспектов изделий.
 *
 * В область применения настоящего стандарта входит:
 * <UL><LI>спецификация контекстов для представления;</LI>
 * <LI>спецификация элементов представления;</LI>
 * <LI>связь элементов представления с одним или более контекстами, в которых они объединяются
 * для представления концепции;</LI>
 * <LI>такая связь элементов представления, когда один элемент используется для определения другого;</LI>
 * <LI>такая структура, обеспечивающая связь двух представлений, когда одно представление участву­ет
 * в определении другого;</LI>
 * <LI>структура, обеспечивающая связь двух представлений, в которой одно представление не уча­ствует
 * в определении другого;</LI>
 * <LI>ограничения, позволяющие избегать рекурсивного определения экземпляров элементов пред­ставления;</LI>
 * <LI>спецификация преобразования одного элемента представления в другой посредством задания
 * исходного и результирующего состояний преобразования;</LI>
 * <LI>спецификация преобразования одного элемента представления в другой посредством задания
 * функции преобразования.</LI></UL>
 * В область применения настоящего стандарта не входит:<BR>
 * <UL><LI>полная спецификация типов представлений, типов элементов представлений и типов контекстов
 * представлений;</LI>
 * <LI>спецификация использований представлений;</LI>
 * <LI>связь представления с каким-либо из возможных его использований;</LI>
 * <LI>ограничения, для которых требуются ориентированная связь между представлениями.
 * <BR><SMALL>Примечание - Отношение между элементами А и В является ориентированным, если смысл отно­шения
 * А к В отличается от смысла отношения В к А. При неориентированном отношении А и В равны. Ориенти­рованное
 * отношение может быть введено в полной комментированной EXPRESS-схеме, в которой используется
 * настоящая схема или ее уточнения;</SMALL></LI>
 * <LI>ограничения, запрещающие циклические структуры, образованные связанными представлениями;</LI>
 * <LI>ограничения, требующие ориентированного отношения между контекстами, в которых существу­ют
 * связанные между собой представления;</LI>
 * <LI>ограничения, запрещающие циклические структуры, образованные связанными между собой
 * контекстами представлений.</LI></UL></P>
 *
 * <P><B>2. Нормативные ссылки</B></P>
 * <P>В настоящем стандарте использованы нормативные ссылки на следующие международные стан­дарты
 * и документы (для датированных ссылок следует использовать указанное издание, для недатиро­ванных
 * ссылок - последнее издание указанного документа, включая все поправки к нему):<BR>
 * ISO 10303-1:1994, Industrial automation systems and integration — Product data representation and
 * exchange — Part 1: Overview and fundamental principles (Системы автоматизации производства и их
 * ин­теграция. Представление данных об изделии и обмен этими данными. Часть 1. Общие представления
 * и основополагающие принципы)<BR>
 * ISO 10303-11:2004, Industrial automation systems and integration — Product data representation and
 * exchange — Part 11: Description methods: The EXPRESS language reference manual (Системы автома­тизации
 * производства и их интеграция. Представление данных об изделии и обмен этими данными. Часть 11.
 * Методы описания. Справочное руководство по языку EXPRESS)<BR>
 * ISO 10303-41:2005, Industrial automation systems and integration — Product data representation and
 * exchange — Part 41: Integrated generic resource: Fundamentals o f product description and support (Систе­мы
 * автоматизации производства и их интеграция. Представление данных об изделии и обмен этими
 * данными. Часть 41. Интегрированный обобщенный ресурс. Основы описания и поддержки изделий)</P>
 *
 * <P><B>3. Термины, определения и сокращения</B></P>
 * <P><B>3.1 Термины и определения</B></P>
 * <P><B>3.1.1 Термины, определенные в ИСО 10303-1</B></P>
 * <P>В настоящем стандарте применены следующие термины:
 * <UL><LI><B>интегрированный ресурс</B> (integrated resource);</LI>
 * <LI><B>приложение</B> (application);</LI>
 * <LI><B>прикладной протокол</B>; ПП (application protocol; АР);</LI>
 * <LI><B>сборочная единица</B> (assembly);</LI>
 * <LI><B>данные</B> (data);</LI>
 * <LI><B>информация</B> (information);</LI>
 * <LI><B>изделие</B> (product);</LI>
 * <LI><B>данные об изделии</B> (product data);</LI>
 * <LI><B>структура</B> (structure).</LI></UL>
 * <P><B>3.1.2 Термины, определенные в ИСО 10303-41</B></P>
 * В настоящем стандарте применены следующие термины:
 * <UL><LI>соглашение об общем понимании (agreement of common understanding);</LI>
 * <LI>EXPRESS-схема с пояснениями (annotated EXPRESS schema).</LI></UL>
 * <P><B>3.1.3 Прочие термины и определения</B></P>
 * В настоящем стандарте применены следующие термины и определения:<BR>
 * 3.1.3.1 <B>контекст представления</B> (context of representation): Основа, используемая для связи
 * друг с другом элементов представления.<BR>
 * 3.1.3.2 <B>элемент представления</B> (element of representation): Элемент данных, используемый
 * в описании представления или непосредственно, или посредством описания других элементов представ­ления.<BR>
 * 3.1.3.3 <B>основанный</B> (founded): Свойство элемента представления, вытекающее, прямо или
 * кос­венно, из его связи с контекстом представления.<BR>
 * 3.1.3.4 <B>представление</B> (representation): Организованное собрание связанных элементов данных,
 * собранных вместе в целях одного или более отдельных применений.<BR>
 * <P><B>3.2 Сокращения</B></P>
 * В настоящем стандарте применено следующее сокращение:<BR>
 * URL — унифицированный указатель информационного ресурса.
 *
 * \section p43_s4 4. Схема Representation (представление)
 *
 * В настоящем разделе с помощью языка EXPRESS, определение которого содержится в
 * ИСО 10303-11, определены информационные требованиям, которые должны выполняться программными
 * реализациями. Далее представлен фрагмент EXPRESS-декларации, с которой начинается
 * опи­сание схемы <B>representation_schema</B>. В нём определены необходимые внешние ссылки.
 * <P><U>EXPRESS-спецификация:</U></P>
 * \verbatim
  *)
  SCHEMA representation_schema;
  REFERENCE FROM basic_attribute_schema   -- ISO 10303-41
    (get_description_value,
     get_id_value);
  REFERENCE FROM measure_schema    -- ISO 10303-41
    (measure_value,
     measure_with_unit);
  REFERENCE FROM support_resource_schema   -- ISO 10303-41
    (bag_to_set,
     identifier,
     label,
     text);
  (*
 \endverbatim
 *
 * <SMALL>Примечания
 * <OL><LI>Схемы, ссылки на которые приведены выше, определены в следующих документах комплекса ИСО 10303:<BR>
 * <B>basic_attribute_schema</B> - ISO 10303-41;<BR>
 * <B>measure_schema</B> - ИСО 10303-41;<BR>
 * <B>support_resource_schema</B> - ИСО 10303-41.</LI>
 * <LI>Графическое представление этих схем приведено в приложении D.</LI></OL></SMALL>
 *
 * <P><B>4.1 Общие положения</B></P>
 * Предметом схемы <B>representation_schema</B> являются структуры, связывающие собрание
 * эле­ментов данных об изделии с контекстом. Эти структуры являются представлениями. Представления
 * используются для описания аспектов изделий. Связи между представлениями и описываемыми теми
 * представлениями аспектами изделий специфицируются в EXPRESS-схемах с пояснениями, в которых
 * используется настоящая EXPRESS-схема или которые являются ее уточнениями. Представления могут
 * использоваться для:
 * <UL><LI>описания свойства или отношения между двумя свойствами, в котором свойства связаны с
 * из­делием в целом или с частью изделия.
 * <P><SMALL>Примечание - Использование представлений для собирания элементов данных об изделии в целях
 * описания свойств изделия специфицировано в ИСО 10303-41, и может быть специф ицировано в EXPRESS-схемах
 * с пояснениями, в которых используются конструкции, специфицированные в настоящей части ИСО 10303 или в
 * ИСО 10303-41 или которые являются уточнениями упомянутых частей ИСО 10303;</SMALL></P></LI>
 * <LI>описания графического изображения.
 * <P><SMALL>Примечание - Использование представлений для собирания элементов данных об изделии в целях
 * описания графического изображения изделия специф ицировано в ИСО 10303-46 [2] и может быть
 * специфициро­вано в EXPRESS-схемах с пояснениями, в которых используются конструкции, специфицированные в настоящей
 * части ИСО 10303 или в ИСО 10303-46 [2] или которые являются уточнениями упомянутых частей ИСО 10303.</SMALL></P></LI></UL>
 * Одно представление может быть составной частью другого представления.
 * <P><B><I>Пример - Форма стены описывается собранием прямых линий и точек. Это представление
 * мо­жет использоваться как составная часть описания формы здания, частью которого является стена.</I></B></P>
 * Каждое представление имеет контекст и собрание элементов, описанных в этом контексте.
 * <P><B><I>Пример - Для представления геометрических элементов контекстом является пространство координат.</I></B></P>
 * Контекст может быть связан с другими контекстами.
 * <P><B><I>Пример - Для каждого здания фабричного комплекса может быть задано местное пространство
 * координат. Эти пространства координат могут быть связаны друг с другом и с пространством
 * ко­ординат фабричного комплекса в целом.</I></B></P>
 * Между представлениями может быть задано преобразование.
 *
 * <P><B>4.2 Основополагающие концепции и предположения</B></P>
 * <I><B>Представление</B></I><BR>
 * К той части настоящей EXPRESS-схемы, которая касается представлений, применяются
 * следу­ющие концепции и допущения:
 *  * представление состоит из собрания элементов представления и контекста. Представление
 * со­ответствует экземпляру объекта representation. За счет такого структурирования могут быть заданы
 * связи между элементами представления. Элементы представления связаны если:<BR>
 * 1) они являются элементами одного и того же представления или<BR>
 * 2) они являются элементами разных представлений, имеющих общий контекст, или<BR>
 * 3) они являются элементами разных представлений, имеющих разные контексты, в том случае,
 * если контексты связаны.
 * <P><I><B>Пример - Рассмотрим две точки со значениями координат (0, 0, 0) и (1, 0, 0). Расстояние между
 * этими точками вычислить невозможно до тех пор, пока для них не будет установлено то ж е самое
 * пространство координат. Сама по себе спецификация точки не содержит достаточных данных для
 * того, чтобы установить, в каком пространстве координат эта точка находится, и для каких
 * дру­гих элементов также используется то ж е самое пространство координат. В настоящем стандарте
 * точка является примером элемента представления, а пространство координат является примером
 * контекста;</B></I></P>
 * * представление может быть использовано более одного раза. Представление отделено от его
 * использования.
 * <P><I><B>Пример - Рассмотрим собрание точек и прямых в пространстве координат. Это собрание
 * мо­жет использоваться для описания формы изделия. Также собрание может использоваться, возможно,
 * с некоторым преобразованием, для описания чертежа или изображения изделия. Ни одно из этих
 * ис­пользований не является частью определения самого собрания.</B></I></P>
 * <P><SMALL>Примечание - В EXPRESS-схемах с пояснениями, в которых используется настоящая EXPRESS-схема
 * или которые являются ее уточнениями, могут присутствовать дальнейшие уточнения представлений.</SMALL></P>
 * <I><B>Контекст представления</B></I><BR>
 * К той части настоящей EXPRESS-схемы, которая касается контекстов представлений,
 * применя­ются следующие допущения:<BR>
 * * представление имеет контекст. Это — контекст, в котором связаны элементы представления.
 * Контекст представления соответствует объекту <B>representation_context</B>;
 * * контекст представления существует только как основа использующих его представлений.
 * Сле­довательно, контексты представлений связаны только в том случае, если связаны представления,
 * ис­пользующие контексты.
 * <P><SMALL>Примечание - В EXPRESS-схемах с пояснениями, в которых используется настоящая EXPRESS-схема
 * или которые являются ее уточнениями, могут присутствовать дальнейшие уточнения контекстов представлений.</SMALL></P>
 * <P><I><B>Пример - К возможным уточнениям относятся контексты для геометрических, топологиче­ских,
 * конечноэлементных и кинематических моделей.</B></I></P>
 * <I><B>Элементы представления</B></I><BR>
 * К той части настоящей EXPRESS-схемы, которая касается элементов представлений,
 * применяют­ся следующие концепции и допущения:
 * * элементы представления или входят непосредственно в представление, или используются в
 * определении других элементов представления, или и то и то.
 *
 * <I><B>Примеры<BR>
 * 1 Точка может быть только элементом, используемым в представлении местоположения
 * изде­лия или может использоваться как конечная точка линии, являющейся только элементом
 * представ­ления кромки изделия. В первом случае точка сама по себе является непосредственным элементов
 * в представлении. Во втором случае точка только используется для определения линейного объекта.<BR>
 * 2 Элемент представления, задающий графическое представление текстовой строки, может
 * быть частью описания чертежа. В этом случае элемент входит в представление непосредственно.
 * В другом случае тот ж е элемент может быть частью размерной надписи. В этом втором случае
 * текст является частью надписи и входит в описание чертежа косвенным образом.</B></I>
 * <P><SMALL>Примечание - Элементы представления, описывающие графическое представление текстовых строк,
 * специфицированы в ИСО 10303-46 [6]. Элементы представления, описывающие размерные надписи,
 * специфици­рованы в ИСО 10303-101 [8];</SMALL></P>
 * * элементы представления могут содержать ссылки друг на друга, образуя таким образом граф
 * элементов, при этом каждый граф имеет распознаваемый корень. Связь корневого элемента графа с
 * контекстом подразумевает связь всех элементов в графе с этим контекстом;<BR>
 * <I><B>Пример — Кривая определяется множеством точек. За счет того, что кривая содержит ссылки
 * на точки, все точки находятся в том же самом пространстве координат, что и кривая.</B></I>
 * * элементы представления собираются в представлениях и связываются с контекстом как с
 * осно­вой, устанавливающей связи между элементами;
 * * элемент представления соответствует экземпляру объекта <B>representation_item</B>;
 * * связь одного или более элементов представления с контекстом обеспечивается посредством
 * объекта representation.
 *
 * <I><B>Связь представлений</B></I><BR>
 * К той части настоящей EXPRESS-схемы, которая касается связи представлений, применяются
 * следующие концепции и допущения:
 * * представление может быть связано с другим представлением;
 * * одно представление может быть связано с другим представлением таким образом, что оба
 * пред­ставления связаны друг с другом, но одно из них не используется для определения другого. Такой тип
 * связи задается посредством объекта <B>representation_relationship</B>;
 * * одно представление может быть связано с другим представлением таким образом, что первое
 * представление используется для определения второго. Такой тип связи задается посредством
 * объек­тов <B>mapped_item</B> и <B>representation_map</B>;
 * * собрания элементов представления могут быть не связаны между собой в двух отдельных
 * кон­текстах, но в то же время быть связанными в третьем контексте, или быть связаны посредством
 * ис­пользования их в связывающей структуре.<BR>
 * <I><B>Пример - Каждое из двух собраний точек и прямых представляет форму изделия. Каждая из этих
 * форм существует в отдельном контексте, независимом и никак не связанным с другим. Для формы
 * сборочной единицы, в которой эти изделия являются составными частями, может существовать
 * третий контекст. В этом третьем контексте все элементы связаны или путем непосредственной
 * связи элементов с этим контекстом или путем связи представлений входящих изделий с
 * представ­лением сборочной единицы.</B></I>
 *
 * <I><B>Преобразование</B></I><BR>
 * К той части настоящей EXPRESS-схемы, которая касается преобразований, применяются следу­
 * ющие концепции и допущения:<BR>
 * * элементы различающихся представлений могут сравниваться если:
 * 1) представления имеют один и тот же контекст, или<BR>
 * 2) определено преобразование, связывающее представления друг с другом;<BR>
 * * преобразование из области определения А в пространство В может быть представлено как
 * функция f. Функция f:A->B принимает каждый элемент а в области А и отображает его в элемент b в
 * пространстве В, т.е. f(a)=b. Полная спецификация преобразования включает:<BR>
 * 1) множество преобразуемых элементов а;<BR>
 * 2) множество элементов Ь, получаемых в результате преобразования;<BR>
 * 3) определение контекста А, общего для множества элементов а;<BR>
 * 4) определение контекста В, общего для множества элементов Ь;<BR>
 * 5) функцию f.
 *
 * Область определения <B>А</B> и пространство <B>В</B> представляются экземплярами объектов <B>representation_context</B>.
 * Каждый из элементов <B>а</B> и <B>b</B> представляются экземплярами объекта <B>representation_item</B>.
 * От­ношения между <B>а</B> и <B>А</B> и между <B>b</B> и <B>В</B> косвенно представляются посредством экземпляров объектов
 * <B>representation</B>: а является элементом представления, контекстом которого является <B>А</B>, а <B>b</B> является
 * элементом представления, контекстом которого является <B>В</B>.
 *
 * В настоящем стандарте используются два подхода к заданию преобразования.
 * 1. Может быть задана функция f. Преобразования такого типа представляются объектом
 * functionally_defined_transformation.
 * Пример — Два представления соотносятся таким образом, что одно повернуто и перекошено
 * относительно другого. Это преобразование может быть задано матрицей.
 *
 * <SMALL>Примечание - Структуры данных, описывающие конкретные функции преобразования, не определены
 * в настоящей части ИСО 10303.</SMALL>
 *
 * <I><B>Пример — Точки на карте связаны с точками земной поверхности с помощью функции,
 * преобразу­ющей трехмерную поверхность в двумерное изображение и применяющей масштабирование.</B></I>
 *
 * 2. Могут быть заданы такой элемент <B>а</B> в контексте <B>А</B> и такой элемент <B>b</B> в контексте <B>В</B>, которых
 * достаточно для вывода функции. Преобразования такого типа представляются объектом
 * <B>item_defined_transformation</B> или отображением, определяемым объектом <B>mapped_item</B>.
 *
 * <I>Пример — Перевод из одной системы координат в другую может быть уникально определен такими
 * двумя представляющими привязочные системы координат экземплярами <B>а1</B> и <B>b1</B> объекта типа
 * <B>axis2_placement_3d</B>, что функция <B>f</B> преобразует входной объект <B>а1</B> в <B>b1</B>.</I>
 *
 * <SMALL>Примечание - Определение объекта <B>axis2_placement_3d</B> дано в ИСО 10303-42 [4].</SMALL>
 *
 * <I><B>Погрешность</B></I><BR>
 * Измеренные или вычисленные численные значения могут быть неточными. Погрешность — это
 * величина доверительного интервала, связанного с этой неточностью. В настоящем стандарте могут
 * быть заданы погрешности для:<BR>
 * 1) нескольких представлений, совместно использующих общий контекст;<BR>
 * 2) отдельных представлений;<BR>
 * 3) отдельных элементов представления.
 *
 * <SMALL>Примечания<BR>
 * 1 Представление погрешностей типа (3) обеспечивается средствами ИСО 10303-45 [5].<BR>
 * 2 Погрешность не связана с допусками или допустимыми отклонениями. Представление последних
 * обеспе­чивается средствами ИСО 10303-47 [7].<BR></SMALL>
 *
 * К той части настоящей EXPRESS-схемы, которая касается неопределенностей, применяются
 * сле­дующие концепции и допущения:
 * * погрешность численных значений может быть задана для всех представлений, совместно
 * ис­пользующих контекст. Это задается посредством объекта global_ uncertainty_assigned_context;
 * * погрешность численных значений может быть задана для представления в данном контексте.
 * Это задается посредством объекта uncertainty_assigned_ representation.
 *
 * Если заданы более одной погрешности, применяются следующие правила старшинства. Погреш­ность,
 * заданная для отдельного элемента представления, имеет преимущество перед погрешностью, заданной
 * посредством объекта uncertainty_assigned_representation для того представления, в которое
 * входит элемент. Погрешность, заданная посредством объекта uncertainty_assigned_representation,
 * имеет преимущество перед погрешностью, задаваемой для нескольких представлений посредством
 * объекта global_uncertainty_assigned_context.
 *
 * <SMALL>Примечание - Погрешность отдельного элемента представления задается посредством объекта
 * <B>qualified_representation_item</B>, определение которого дано в ИСО 10303-45 [5].</SMALL>
 *
 * <I><B>4.3 Определения типов данных схемы representation_schema</B></I>
 */


  /**
   * \brief TYPE compound_item_definition (ГОСТ Р ИСО 10303-43-2016, 4.3.1)
   *
   * <I><B>4.3.1 Тип данных compound_item_definition</B></I><BR>
   * Тип данных <B>compound_item_definition</B> является списком альтернативных типов данных.
   * На­стоящий тип данных предоставляет механизм для ссылки на экземпляры одного из перечисленных
   * типов данных. Альтернативные типы данных обеспечивают различные способы агрегации объектов
   * <B>representation_item</B>.
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    *)
    TYPE compound_item_definition = SELECT
       (list_representation_item,
        set_representation_item);
    END_TYPE;
    (*
   \endverbatim
   */
  class compound_item_definition : public SELECT {

  public:

    /** \brief Конструктор из типа list_representation_item */
    compound_item_definition(const list_representation_item* t);

    /** \brief Конструктор из типа set_representation_item */
    compound_item_definition(const set_representation_item* t);
  };

  /**
   * \brief TYPE founded_item_select (ГОСТ Р ИСО 10303-43-2016, 4.3.2)
   *
   * <I><B>4.3.2 Тип данных founded_item_select</B></I><BR>
   * Тип данных <B>founded_item_select</B> является списком альтернативных типов данных. Настоящий
   * тип данных предоставляет механизм для ссылки на экземпляры одного из перечисленных типов
   * данных.
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    *)
    TYPE founded_item_select = SELECT
       (founded_item,
        representation_item);
    END_TYPE;
    (*
   \endverbatim
   */
  class founded_item_select : public SELECT {

  public:

    /** \brief Конструктор из типа founded_item */
    founded_item_select(const founded_item* t);

    /** \brief Конструктор из типа representation_item */
    founded_item_select(const representation_item* t);
  };

  /**
   * \brief TYPE list_representation_item (ГОСТ Р ИСО 10303-43-2016, 4.3.3)
   *
   * <I><B>4.3.3 Тип данных list_representation_item</B></I><BR>
   * Тип данных <B>list_representation_item</B> представляет упорядоченное множество экземпляров
   * объектов <B>representation_item</B>.
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   <PRE>
    *)
    TYPE list_representation_item = LIST[1:?] OF representation_item;
    END_TYPE;
    (*
   </PRE>
   */
  class list_representation_item : public LIST<representation_item*> {
  };

  /**
   * \brief TYPE set_representation_item (ГОСТ Р ИСО 10303-43-2016, 4.3.4)
   *
   * <I><B>4.3.4 Тип данных set_representation_item</B></I><BR>
   * Тип данных <B>set_representation_item</B> представляет неупорядоченное множество экземпляров
   * объектов <B>representation_item</B>.
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    *)
    TYPE set_representation_item = SET[1:?] OF representation_item;
    END_TYPE;
    (*
   \endverbatim
   */
  class set_representation_item : public SET<representation_item*> {
  };

  /**
   * \brief TYPE representation_or_representation_reference (ISO 10303-43:2021(E), 4.3.4)
   *
   * <B>4.3.4 representation_or_representation_reference</B>
   * The <B>representation_or_representation_reference</B> type is a list of alternate data types. It provides
   * a mechanism to refer to an instance of one of these data types.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    -- IN AP238 STEP-NC/AP242
    TYPE representation_or_representation_reference = SELECT
          (representation,
           representation_reference);
    END_TYPE;
   \endverbatim
   *
   */
  class representation_or_representation_reference : public SELECT {

  public:

    /** \brief Конструктор из типа representation */
    representation_or_representation_reference(const representation* t);

    /** \brief Конструктор из типа representation_reference */
    representation_or_representation_reference(const representation_reference* t);
  };


  /**
   * \brief TYPE transformation (ГОСТ Р ИСО 10303-43-2016, 4.3.5)
   *
   * <I><B>4.3.5 Тип данных transformation</B></I><BR>
   * Тип данных <B>transformation</B> является списком альтернативных типов данных. Настоящий тип
   * дан­ных предоставляет механизм для ссылки на экземпляры одного из перечисленных типов данных.
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    *)
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    TYPE transformation = SELECT
      (functionally_defined_transformation,                        -- Common
       item_defined_transformation,                                -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
       list_item_defined_transformation,                           -- AP242
       set_item_defined_transformation);                           -- AP242
    END_TYPE;
    (*
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_transformation.html">Ссылка.</A>
   */
  class transformation : public SELECT {

  public:

//  /** \brief Конструктор из типа functionally_defined_transformation */
//  transformation(const functionally_defined_transformation* t);
    /** \brief Конструктор из типа item_defined_transformation */
    transformation(const item_defined_transformation* t);
  };

  /**
   * 4.4 Определения объектов схемы representation_schema.
   */

   // 4.4.1 Объект binary_representation_item
   // 4.4.2 Объект bytes_representation_item
   // 4.4.3 Объект compound_representation_item

   /**
    * \brief ENTITY definitional_representation (ГОСТ Р ИСО 10303-43-2016, 4.4.4)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    * \verbatim
     ENTITY definitional_representation
        SUBTYPE OF (representation);
        WHERE
           WR1:
              'STEP_MERGED_AP_SCHEMA.PARAMETRIC_REPRESENTATION_CONTEXT' IN TYPEOF(SELF\representation.context_of_items);
     END_ENTITY;
    \endverbatim
    *
    */
  class definitional_representation : public representation {
    // Explicit LABEL                     name;
    // Explicit SET<REPRESENTATION_ITEM>  items
    // Explicit REPRESENTATION_CONTEXT    context_of_items;
    // Derived  IDENTIFIER                id;
    // Derived  TEXT                      description;

    definitional_representation(const std::string& Name, const representation_context* Context);

    // FUNCTION get_id_value
//    identifier get_id_value();

    // FUNCTION get_description_value
//    text get_description_value();
  };

#endif /* !defined(ISO130303_43_FIRST) */

#if defined(ISO130303_43_FIRST) || defined(__DOXYGEN__)

  /**
   * \brief ENTITY representation_relationship (ГОСТ Р ИСО 10303-43, 4.4.5)
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY representation_relationship;
          name : label;
          description : OPTIONAL text;
          rep_1 : representation_or_representation_reference;
          rep_2 : representation_or_representation_reference;
    END_ENTITY;
   \endverbatim
   *
   */
  class representation_relationship : public GENERIC_ENTITY {

  public:

    label name;        // Название взаимосвязи
    text  description; // OPTIONAL дополнительное описание взаимосвязи
    const representation* rep_1;       // Первый объект взаимосвязи 
    const representation* rep_2;       // Второй объект взаимосвязи


    /**
     * \brief Конструктор.
     *
     * \param [in] Name
     * \param [in] Description
     * \param [in] Rep1
     * \param [in] Rep2
     */
    representation_relationship(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2);

    virtual ~representation_relationship() = default;
  };

#endif /* !defined(ISO130303_43_FIRST) */


  // 4.4.6 Объект definitional_representation_relationship_with_same_context

#if !defined(ISO130303_43_FIRST) || defined(__DOXYGEN__)

  /**
   * \brief ENTITY founded_item (ГОСТ Р ИСО 10303-43-2016, 4.4.7)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY founded_item
       SUPERTYPE OF (ONEOF(b_spline_curve_knot_locator, b_spline_curve_segment, b_spline_surface_knot_locator, b_spline_surface_patch, b_spline_surface_strip, boundary_curve_of_b_spline_or_rectangular_composite_surface, box_domain, character_glyph_style_outline, character_glyph_style_stroke, composite_curve_segment, composite_curve_transition_locator, curve_style, curve_style_font, curve_style_font_and_scaling, curve_style_font_pattern, externally_defined_style, fill_area_style, interpolated_configuration_segment, kinematic_path_segment, plane_angle_and_length_pair, plane_angle_and_ratio_pair, point_style, presentation_style_assignment, rectangular_composite_surface_transition_locator, surface_patch, surface_side_style, surface_style_boundary, surface_style_control_grid, surface_style_fill_area, surface_style_parameter_line, surface_style_segmentation_curve, surface_style_silhouette, surface_style_usage, symbol_style, text_style, view_volume) ANDOR ONEOF(character_glyph_style_outline, character_glyph_style_stroke, curve_style, curve_style_font, curve_style_font_and_scaling, curve_style_font_pattern, externally_defined_style, fill_area_style, point_style, presentation_style_assignment, surface_side_style, surface_style_boundary, surface_style_control_grid, surface_style_fill_area, surface_style_parameter_line, surface_style_segmentation_curve, surface_style_silhouette, surface_style_usage, symbol_style, text_style));
       DERIVE
          users : SET [0:?] OF founded_item_select := using_items(SELF, []);
       WHERE
          WR1:
             SIZEOF(users) > 0;
          WR2:
             NOT (SELF IN users);
    END_ENTITY;
   \endverbatim
   *
   * Объект founded_item — это такой объект, который представляет часть элемента представления.
   * Объект founded_item может использоваться только как часть определения объекта representation_item, и основывается посредством того,
   * что данный объект representation_item включен в представление. Связанный с настоящим объектом объект representation_item может быть
   * включен в представление. Объект founded_item не может быть включен в представление.
   */
  class founded_item : public GENERIC_ENTITY {

  public:
  };



  // 4.4.8 Объект functionally_defined_transformation

  class representation_context;

  /**
   * \brief ENTITY global_uncertainty_assigned_context (ГОСТ Р ИСО 10303-43-2016, 4.4.9)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY global_uncertainty_assigned_context
       SUBTYPE OF (representation_context);
          uncertainty : SET [1:?] OF uncertainty_measure_with_unit;
    END_ENTITY;
   \endverbatim
   *
   */
  class global_uncertainty_assigned_context : public representation_context {

  public:

    LIST<const uncertainty_measure_with_unit*> uncertainty;

    // Конструктор
    global_uncertainty_assigned_context(const std::string& identifier, const std::string& type);
  };

  /**
   * \brief ENTITY item_defined_transformation (ГОСТ Р ИСО 10303-43-2016, 4.4.10)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    ENTITY item_defined_transformation;
          name : label;
          description : OPTIONAL text;
          transform_item_1 : representation_item;
          transform_item_2 : representation_item;
    END_ENTITY;
   \endverbatim
   *
   */
  class item_defined_transformation : public GENERIC_ENTITY {

  private:

    label* name;
    text* description;
    const representation_item* transform_item_1;
    const representation_item* transform_item_2;

  public:

    item_defined_transformation(const std::string& Name, const representation_item* Transform_item_1, const representation_item* Transform_item_2, const std::string& Description = "$");

    virtual ~item_defined_transformation();
  };

#endif /* !defined(ISO130303_43_FIRST) */

  // 4.4.11 Объект mapped_item

  // 4.4.12 Объект parametric_representation_context

#if defined(ISO130303_43_FIRST) || defined(__DOXYGEN__)

  /**
   * \brief ENTITY representation (ГОСТ Р ИСО 10303-43-2016, 4.4.13)
   *
   *<P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY representation
       SUPERTYPE OF (((ONEOF(reinforcement_orientation_basis, ply_angle_representation) ANDOR ONEOF(interpolated_configuration_representation, link_motion_representation_along_path)) ANDOR ONEOF(kinematic_link_representation, kinematic_topology_structure, kinematic_topology_directed_structure, kinematic_topology_network_structure, mechanism_representation, shape_representation)) ANDOR ONEOF(kinematic_topology_structure, kinematic_topology_directed_structure, kinematic_topology_network_structure));
          name : label;
          items : SET [1:?] OF representation_item;
          context_of_items : representation_context;
       DERIVE
          id : identifier := get_id_value(SELF);
          description : text := get_description_value(SELF);
       WHERE
          WR1:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
          WR2:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   * Представление
   */
  class representation : public GENERIC_ENTITY {

  public:

    label name;                // Имя, однозначно идентифицирующее модель

    /** \brief Массив ссылок на элементы представления, связанные с контекстом представления */
    SET<const representation_item*> items;

    const representation_context* context_of_items;    // Контекст представления или комплесный объект

    /** \brief Конструктор неопределённого объекта */
    representation();

    /** \brief Конструктор */
    representation(const std::string& Name, const representation_context* Context_of_items);

    /** \brief Деструктор */
    virtual ~representation() = default;
  };

  /**
   * \brief ENTITY representation_context (ГОСТ Р ИСО 10303-43-2016, 4.4.14)
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    ENTITY representation_context;
          context_identifier : identifier;
          context_type : text;
       INVERSE
          representations_in_context : SET [1:?] OF representation FOR context_of_items;
    END_ENTITY;
   \endverbatim
   *
   * Контекст, связывающий экземпляры объектов representation_item.
   */
  class representation_context : public GENERIC_ENTITY {

  private:

    identifier context_identifier;           // Идентификация контекста представления
    text context_type;	           // Описание типа контекста представления

  public:

    representation_context();

    /** \brief Конструктор */
    representation_context(const std::string& Identifier, const std::string& Type);

    /** \brief Деструктор */
    virtual ~representation_context() = default;
  };


#endif /* defined(ISO130303_43_FIRST) */

#if !defined(ISO130303_43_FIRST) || defined(__DOXYGEN__)

  /**
   * \brief ENTITY representation_item (ГОСТ Р ИСО 10303-43-2016, 4.4.15)
   *
   * <U>EXPRESS-спецификация:</U><BR>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY representation_item
       SUPERTYPE OF ((ONEOF(binary_representation_item, compound_representation_item, mapped_item, value_representation_item) ANDOR ONEOF(boolean_representation_item, date_representation_item, date_time_representation_item, integer_representation_item, logical_representation_item, rational_representation_item, real_representation_item)) ANDOR ONEOF(mapped_item, styled_item));
          name : label;
       WHERE
          WR1:
             SIZEOF(using_representations(SELF)) > 0;
    END_ENTITY;
   \endverbatim
   *
   * Объект \ref express::representation_item "representation_item" представляет элемент представления. На объект \ref express::representation_item "representation_item" ссылается
   * один или более экземпляров объекта \ref express::representation "representation", или же объект \ref express::representation_item "representation_item" используется в определении
   * другого объекта \ref express::representation_item "representation_item".
   */
  class representation_item : public GENERIC_ENTITY {

  private:

    label* name; //  текст, которым называется экземпляр настоящего объекта.

  public:

    /** \brief Конструктор неопределённого типа */
    representation_item() : GENERIC_ENTITY(false), name(nullptr) {
    }

    /** \brief Конструктор */
    representation_item(const std::string& Name);

    /** \brief Деструктор */
    virtual ~representation_item();
  };


  // 4.4.16 Объект representation_item_relationship
  // 4.4.17 Объект representation_map
  // 4.4.18 Объект representation_relationship

  /**
   * \brief ENTITY representation_relationship_with_transformation (ГОСТ Р ИСО 10303-43-2016, 4.4.19)
   *
   * <P><U>EXPRESS-спецификация:</U></P>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    ENTITY representation_relationship_with_transformation
       SUBTYPE OF (representation_relationship);
          transformation_operator : transformation;
       WHERE
          WR1:
             SELF\representation_relationship.rep_1.context_of_items :<>: SELF\representation_relationship.rep_2.context_of_items;
          wr2:
             NOT ('STEP_MERGED_AP_SCHEMA.ITEM_DEFINED_TRANSFORMATION' IN TYPEOF(transformation_operator)) OR item_in_context(transformation_operator\item_defined_transformation.transform_item_1, SELF\representation_relationship.rep_1.context_of_items) AND item_in_context(transformation_operator\item_defined_transformation.transform_item_2, SELF\representation_relationship.rep_2.context_of_items);
    END_ENTITY;
   \endverbatim
   *
   */
  class representation_relationship_with_transformation : public representation_relationship {

  public:

    const transformation* transformation_operator;


    representation_relationship_with_transformation(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2,
      const transformation* Transformation_operator)
      : representation_relationship(Name, Description, Rep1, Rep2), transformation_operator(Transformation_operator) {
      add_attr_info(STEP_ATTR_LIST({ {"transformation_operator", transformation_operator} }, this));
    }
  };

  /**
   * \brief ENTITY representation_reference (ISO 10303-43:2021(E), 4.4.19)
   *
   * <B>4.4.19 representation_reference</B><BR>
   * A <B>representation_reference</B> is an identification based reference to a representation.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    -- IN AP238 STEP-NC/AP242
    ENTITY representation_reference;
          id : identifier;
          context_of_items : representation_context_reference;
    END_ENTITY;
   \endverbatim
   *
   */
  class representation_reference : public GENERIC_ENTITY {
  private:

    /** \brief The identifier that distinguishes the representation_reference. */
    identifier* id;

    /**
     * \brief The <B>representation_context_reference</B> in which the items are related to form a
     * <B>representation_reference</B> of some concept.
     */
    const representation_context_reference* context_of_items;

  public:

    representation_reference(const identifier& Id, const representation_context_reference* Context_of_items) {
      id = new identifier(Id);
      context_of_items = Context_of_items;
      //!!! attributes
    }

    virtual ~representation_reference() {
      delete id;
    }
  };




  /**
   * 4.4.20 Объект uncertainty_assigned_representation
   */


   /**
    * \brief ENTITY uncertainty_measure_with_unit (ГОСТ Р ИСО 10303-43-2016, 4.4.21)
    *
    * <B>4.4.21 uncertainty_measure_with_unit</B>
    *
    * Объект <B>\ref uncertainty_measure_with_unit</B> является таким подтипом объекта,
    * посредством которого задается погрешность, применяемая к мере данного типа.
    * Погрешность, представляемая объектом <B>\ref uncertainty_measure_with_unit</B>,
    * применяется к каждому объекту \ref express::representation_item "representation_item", в котором используется
    * тип меры, заданный объектом, играющим роль атрибута <B>value_component</B> объекта
    * <B>\ref uncertainty_measure_with_unit</B>, в следующих случаях:<BR>
    * * представляющий элемент представления объект \ref express::representation_item "representation_item" входит во
    * множество, играющее роль атрибута items объекта <B>uncertainty_assigned_representation</B>;<BR>
    * * элемент представления, представляемый объектом \ref express::representation_item "representation_item",
    * основан в контексте, представленном объектом <B>\ref global_unit_assigned_context</B>.<BR>
    * * экземпляр объекта \ref express::representation_item "representation_item" является экземпляром объекта
    * <B>qualified_representation_item</B>.
    *
    * <U>EXPRESS-спецификация:</U>
    * \verbatim
     ENTITY uncertainty_measure_with_unit
        SUBTYPE OF (measure_with_unit);
           name : label;
           description : OPTIONAL text;
        WHERE
           WR1:
              valid_measure_value(SELF\measure_with_unit.value_component);
     END_ENTITY;
    \endverbatim
    *
    *
    */
  class uncertainty_measure_with_unit : public measure_with_unit {

  private:

    /** текст, которым называется экземпляр настоящего объекта */
    label* name;

    /** текст, характеризующий погрешность с единицей измерения, представляемую настоящим объектом */
    text* description;

  public:

    /** \brief Конструктор */
    uncertainty_measure_with_unit(const measure_value* Value, const unit* Unit, const std::string& Name, const std::string& Description)
      : measure_with_unit(Value, Unit) {
      name = new label(Name);
      description = new text(Description);
      // Информация об аргументах этого класса
      add_attr_info(STEP_ATTR_LIST({
                                     {"name",        name},
                                     {"description", description, true }
        }, this));
    }

    /** \brief Конструктор */
    uncertainty_measure_with_unit(const measure_value* Value, const unit* Unit, const std::string& Name)
      : measure_with_unit(Value, Unit) {
      name = new label(Name);
      description = new text();
      // Информация об аргументах этого класса
      add_attr_info(STEP_ATTR_LIST({
                                     {"name",        name},
                                     {"description", description, true }
        }, this));
    }

    /** \brief Деструктор */
    ~uncertainty_measure_with_unit() {
      delete description;
      delete name;
    }
  };

  /**
   * 4.4.22 Объект value_representation_item
   */

   /**
    * <B>4.5 Определения функций схемы  representation_schema</B>
    *
    * 4.5.1 Функция acyclic_mapped_representation
    *
    * 4.5.2 Функция acyclic_representation_relationship
    *
    * 4.5.3 Функция item_in_context
    *
    * 4.5.4 Функция using_item
    */


    /**
     * \brief FUNCTION using_items (ГОСТ Р ИСО 10303-43-2016, 4.5.4)
     *
     * <B>4.5.4 using_items</B>
     *
     * <U>EXPRESS-спецификация:</U>
     * \verbatim
      FUNCTION using_items (item : founded_item_select; checked_items : SET[0:?] OF founded_item_select) : SET[0:?] OF founded_item_select;

      LOCAL
            new_check_items    : SET OF founded_item_select;
            result_items       : SET OF founded_item_select;
            next_items         : SET OF founded_item_select;
          END_LOCAL;
          result_items := [];
          new_check_items := checked_items + item;
          -- Find the set of representation_items or founded_items
          -- in which item is used directly.
          next_items := QUERY(z <* bag_to_set( USEDIN(item , '')) |
            ('REPRESENTATION_SCHEMA.REPRESENTATION_ITEM' IN TYPEOF(z)) OR
            ('REPRESENTATION_SCHEMA.FOUNDED_ITEM'        IN TYPEOF(z)));
          -- If the set of next_items is not empty;
          IF SIZEOF(next_items) > 0 THEN
            -- For each element in the set, find the using_items recursively
            REPEAT i := 1 TO HIINDEX(next_items);
              -- Check for loop in data model, i.e. one of the next_items
              -- occurred earlier in the set of check_items;
              IF NOT(next_items[i] IN new_check_items) THEN
                 result_items := result_items + next_items[i] +
                                using_items(next_items[i],new_check_items);
              END_IF;
            END_REPEAT;
          END_IF;
          -- return the set of representation_items or founded_items
          -- in which the input item is used directly and indirectly.
          RETURN (result_items);

      END_FUNCTION;
      \endverbatim
     */
  SET<founded_item_select> using_items(const founded_item_select& item, const SET<founded_item_select>& checked_items);

  /**
   * \brief FUNCTION using_representations (ГОСТ Р ИСО 10303-43-2016, 4.5.5)
   *
   * <B>4.5.5 using_representations</B>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
     FUNCTION using_representations (item : founded_item_select) : SET[0:?] OF representation;

     LOCAL
           results            : SET OF representation;
           result_bag         : BAG OF representation;
           intermediate_items : SET OF founded_item_select;
         END_LOCAL;
         -- Find the representations in which the item is used and add to the
         -- results set.
         results := [];
         result_bag := USEDIN(item,'REPRESENTATION_SCHEMA.REPRESENTATION.ITEMS');
         IF SIZEOF(result_bag) > 0 THEN
           REPEAT i := 1 TO HIINDEX(result_bag);
             results := results + result_bag[i];
           END_REPEAT;
         END_IF;
         -- Find all representation_items or founded_items
         -- by which item is referenced directly or indirectly.
         intermediate_items := using_items(item,[]);
         -- If the set of intermediate items is not empty;
         IF SIZEOF(intermediate_items) > 0 THEN
           -- For each element in the set, add the
           -- representations of that element.
           REPEAT i := 1 TO HIINDEX(intermediate_items);
             result_bag := USEDIN(intermediate_items[i],
                           'REPRESENTATION_SCHEMA.REPRESENTATION.ITEMS');
             IF SIZEOF(result_bag) > 0 THEN
               REPEAT j := 1 TO HIINDEX(result_bag);
                 results := results + result_bag[j];
               END_REPEAT;
             END_IF;
           END_REPEAT;
         END_IF;
         -- Return the set of representation in which the input item is
         -- used directly and indirectly (through intervening
         -- representation_items or founded items).
         RETURN (results);

     END_FUNCTION;
         \endverbatim
   */
  SET<representation> using_representations(const founded_item_select& item);

  // 4.5.6 Функция valid_measure_value


#endif /* !defined(ISO130303_43_FIRST) */

}