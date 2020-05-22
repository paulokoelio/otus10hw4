#ifndef PRADDR_BASEFNCL_H_
#define PRADDR_BASEFNCL_H_

#include <iostream>
#include <string>
#include <tuple>

#define UNUSED(variable) (void)variable

namespace praddr
{
    constexpr char ip_delimiter = '.';

    template <
        typename TypeInt,
        typename = std::enable_if_t<std::is_integral<TypeInt>::value>>
    int print_ip(TypeInt indata);

    template <typename TypeStr,
              typename = std::enable_if_t<std::is_same<TypeStr, std::string>::value>>
    int print_ip(const TypeStr &indata);

    template <
        template <class, class> class Vec,
        class Tvec,
        class Alloc>
    int print_ip(const Vec<Tvec, Alloc> &indata);
    
    // template <
    //     template <class...> class Tpl,
    //           typename = std::enable_if_t < std::is_same < Tpl<class... args>, std::tuple<class... args> >::value >> 
    //           int print_ip(TypeTuple tpl);

    template <class... Tpl>
    int print_ip(std::tuple<Tpl...> tpl);

    template <class... Tpl>
    constexpr int unfold(std::tuple<Tpl...> tpl, const size_t it, const size_t max_it);

} // namespace praddr

#include "fn_print_ip.h"  // полная реализация функций находится в отдельном файле

#endif /* PRADDR_BASEFNCL_H_ */