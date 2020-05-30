#ifndef PRADDR_BASEFNCL_H_
#define PRADDR_BASEFNCL_H_

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <list>

#define UNUSED(variable) (void)variable

namespace praddr
{
    constexpr char ip_delimiter = '.';

    void prns();

    template <
        typename TypeInt,
        typename = std::enable_if_t<std::is_integral<TypeInt>::value>>
    int print_ip(const TypeInt indata);
    
    template <
        template <class...> class Vec,
        class... Other
        >
    int print_ip(const Vec<Other...> &indata);

    // template <
    //     template <class, class...> class Vec,
    //     class Tvec,
    //     class... Other,
    //     std::enable_if_t< 
    //     ! (std::is_same< Vec<Tvec>, std::vector<Tvec>>::value 
    //     || std::is_same< Vec<Tvec>, std::list<Tvec>>::value), 
    //     int > =0
    //     >
    // int print_ip(const Vec<Tvec, Other...> &indata);
    

    template <
        template <class, class...> class Vec,
        class Tvec,
        class... Other,
        std::enable_if_t< 
        (std::is_same< Vec<Tvec>, std::vector<Tvec>>::value 
        || std::is_same< Vec<Tvec>, std::list<Tvec>>::value), 
        int > =0
        >
    int print_ip(const Vec<Tvec, Other...> &indata);

    template <
        class Tvec,
        class Alloc>
    int print_ip(const std::basic_string<Tvec, Alloc> &indata);

    // template <
    //     template <class...> class Tpl,
    //           typename = std::enable_if_t < std::is_same < Tpl<class... args>, std::tuple<class... args> >::value >>
    //           int print_ip(TypeTuple tpl);

    template <class... Tpl >
    int print_ip(std::tuple<Tpl...> tpl);

    template <class T1>
    void pr(T1 t1);

    template <class T1, class... Tnext>
    void pr(T1 t1, Tnext... arg);

    template <
        template <class...> class V,
        typename T,
        typename... Tnext>
    void pr(V<T, Tnext...> vec);

    template <class T1,
              class T2,
              // typename = std::enable_if_t<std::is_same<T1,T2>>::value,
              class... Tpl>
    constexpr int unfold(std::tuple<T1, T2, Tpl...> tpl, const size_t it, const size_t max_it);
    
    template <
        template <class...> class V,
        typename T,
        typename... Tnext
        >
    void pr(V<T, Tnext...> vec);

    // template <>
    // int print_ip(std::tuple<> tpl);

    // template <class... Tpl>
    // constexpr int unfold(std::tuple<Tpl...> tpl, const size_t it, const size_t max_it);

} // namespace praddr

#include "fn_print_ip.h" // полная реализация функций находится в отдельном файле

#endif /* PRADDR_BASEFNCL_H_ */