/**
\file
\brief Заголовочный файл с определениями шаблонных функций для tuple

Заголовочный файл с определением функций print_ip() для данных типа tuple, 
а также с определением универсальной вспомогательной функции 
for_each(tuple , callback) производящей обход всех элементов tuple во время
компиляции и обрабатывающей их функцией callback.
Код функций для tuple основан на исходном коде представленном на сайте:
http://artlang.net/post/c++11-obkhod-elementov-kortezhe-std-tuple/
*/

#ifndef MYLIB_PRINT_TUPLE_H_
#define MYLIB_PRINT_TUPLE_H_

#include <tuple>
#include <typeinfo>
#include <sstream>
#include <utility>
#include <iostream>

namespace mylib
{
    /// Разделитель, выводимый между элементами tuple-я
    constexpr char delimiter = '.';

    static std::stringstream data;
    static std::stringstream types;

    template <int index, typename Callback, typename... Args>
    struct iterate_tuple
    {
        static void next(std::tuple<Args...> &t, Callback callback)
        {
            // Уменьшаем позицию и рекурсивно вызываем этот же метод
            iterate_tuple<index - 1, Callback, Args...>::next(t, callback);

            // Вызываем обработчик и передаем ему позицию и значение элемента
            callback(index, std::get<index>(t));
        }
    };

    // Частичная специализация для индекса 0 (завершает рекурсию)
    template <typename Callback, typename... Args>
    struct iterate_tuple<0, Callback, Args...>
    {
        static void next(std::tuple<Args...> &t, Callback callback)
        {
            callback(0, std::get<0>(t));
        }
    };

    // Частичная специализация для индекса -1 (пустой кортеж)
    template <typename Callback, typename... Args>
    struct iterate_tuple<-1, Callback, Args...>
    {
        static void next(std::tuple<Args...> &t, Callback callback)
        {
            (void)t;
            (void)callback;
            // ничего не делаем
        }
    };

    // "Волшебный" for_each для обхода элементов кортежа (compile time!):
    //
/**
Шаблонная вспомогательная внутренняя функция обхода кортежа tuple
с обработкой функцией callback (структура с перегруженным оператором () )
\param[in] t кортеж (tuple) выводимый на печать
\param[in] callback функция-структура в которой обрабатывается каждый элемент кортежа
*/
    template <typename Callback, typename... Args>
    void for_each(std::tuple<Args...> &t, Callback callback)
    {
        // Размер кортежа
        int const t_size = std::tuple_size<std::tuple<Args...>>::value;

        // Запускаем рекурсивный обход элементов кортежа во время компиляции
        mylib::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
    }

    struct callback
    {
        template <typename T>
        void operator()(int index, T &&t)
        {
            (void)index;
            mylib::data << t << delimiter;
            mylib::types << typeid(t).name() << '\n';
        }
    };

/**
Шаблонная функция вывода на печать значения заданного кортежем
(std::tuple) при условии совпадения всех типов данных входящих в кортеж
\param[in] tuple_ кортеж с выводимыми значениями
*/
    template <typename... Args>
    void print_ip(std::tuple<Args...> tuple_)
    {
        // Обход элементов кортежа и вызов обработчика
        mylib::types.str("");
        mylib::types.clear();
        mylib::data.str("");
        mylib::data.clear();
        for_each(tuple_, mylib::callback());
        // Выводим tuple на печать с проверкой типов всех элементов на идентичность
        bool sametype = true;
        int number = 0;
        std::string firsttype;
        for (std::string line; std::getline(mylib::types, line); ++number)
        {
            if (number == 0)
                firsttype = line;
            sametype = sametype && (line == firsttype);
        }
        if (number == 0)
        {
            std::cout << '\n';
            return;
        }
        if (!sametype)
        {
            std::cout << "Tuple is not of single type" << '\n';
            return;
        }
        std::string datastring(mylib::data.str());
        datastring.resize(datastring.length() - 1);
        std::cout << datastring.c_str() << '\n';
    }

} // namespace mylib

#endif /* MYLIB_PRINT_TUPLE_H_ */