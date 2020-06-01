#ifndef MYLIB_PRINT_TUPLE_H_
#define MYLIB_PRINT_TUPLE_H_

#include <tuple>
#include <typeinfo>
#include <sstream>
#include <utility>  
#include <iostream> 

// исходный код функций для tuple основан на:
// http://artlang.net/post/c++11-obkhod-elementov-kortezhe-std-tuple/

namespace mylib
{
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
    void operator()(int index, T &&t) // index - это позиция элемента в кортеже
    {                                 // t - значение элемента
        (void)index;
        mylib::data << t << delimiter;
        mylib::types << typeid(t).name() << '\n';
    }
};

template <typename... Args>
void print_ip(std::tuple<Args...> tuple_)
{
    // Обход элементов кортежа и вызов обработчика
    mylib::types.str("");
    mylib::types.clear();
    mylib::data.str("");
    mylib::data.clear();
    for_each(tuple_, mylib::callback());

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

}

#endif /* MYLIB_PRINT_TUPLE_H_ */