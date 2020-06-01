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
 
    template <class T1>
    void pr(T1 t1);

    template <class T1, class... Tnext>
    void pr(T1 t1, Tnext... arg);

    template <
        template <class...> class V,
        typename T,
        typename... Tnext>
    void pr(V<T, Tnext...> vec);

} // namespace praddr

#include "fn_print_ip.h" // полная реализация функций находится в отдельном файле

#endif /* PRADDR_BASEFNCL_H_ */