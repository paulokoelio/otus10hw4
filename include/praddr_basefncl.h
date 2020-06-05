/**
\file
\brief Заголовочный файл с объявлением шаблонных функций

Заголовочный файл с объявлением основных функций. 
Шаблонные функции приведены в порядке, необходимом для правильного задания шаблонов.
*/
#ifndef PRADDR_BASEFNCL_H_
#define PRADDR_BASEFNCL_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>

#define UNUSED(variable) (void)variable

namespace praddr
{
    constexpr char ip_delimiter = '.';
/**
Внутренняя функция печатает сообщение в случае неподдерживаемых форматов аргументов
*/
    void prns();

/**
Шаблонная функция вывода на печать значения интегрального типа с разбиением по байтам
\param[in] indata выводимое значение
*/
    template <
        typename TypeInt,
        typename = std::enable_if_t<std::is_integral<TypeInt>::value>>
    int print_ip(const TypeInt indata);

    template <
        template <class...> class Vec,
        class... Other>
    int print_ip(const Vec<Other...> &indata);

/**
Шаблонная функция вывода на печать значения заданного вектором std::vector
или классом std::list
\param[in] indata выводимое значение
*/
    template <
        template <class, class...> class Vec,
        class Tvec,
        class... Other,
        std::enable_if_t<
            (std::is_same<Vec<Tvec>, std::vector<Tvec>>::value 
            || std::is_same<Vec<Tvec>, std::list<Tvec>>::value),
            int> = 0>
    int print_ip(const Vec<Tvec, Other...> &indata);

/**
Шаблонная функция вывода на печать значения заданного std::string
\param[in] indata выводимое значение
*/
    template <
        class Tvec,
        class Alloc>
    int print_ip(const std::basic_string<Tvec, Alloc> &indata);

/**
Внутренняя шаблонная функция для вывода на печать одного значения простого типа
\param[in] t1 выводимое значение
*/
    template <class T1>
    void pr(T1 t1);

// эта форма функции для данного ДЗ не используется
    // template <class T1, class... Tnext>
    // void pr(T1 t1, Tnext... arg);

/**
Внутренняя шаблонная функция для вывода на печать нескольких значений
контейнерного класса (шаблонного класса)
\param[in] vec выводимый на печать контейнер со значения
*/
    template <
        template <class...> class V,
        typename T,
        typename... Tnext>
    void pr(V<T, Tnext...> vec);

} // namespace praddr

#include "fn_print_ip.h" // полная реализация функций находится в отдельном файле

#endif /* PRADDR_BASEFNCL_H_ */