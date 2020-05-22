#ifdef PRADDR_BASEFNCL_H_
#ifndef FN_PRINT_IP_H_
#define FN_PRINT_IP_H_

#include <iostream>
#include <string>
#include <cmath>

namespace praddr
{

    template <typename Type>
    std::string divide(Type data)
    {
        size_t size = sizeof(data);
        std::string del(1, ip_delimiter);
        // разбиение data на байты используя разделитель (delimiter)

        const Type *pdata = &data;
        const unsigned char *pbyte = reinterpret_cast<const unsigned char *>(pdata);
        std::string res{std::to_string(static_cast<const int>(*pbyte))};

        for (size_t it = 1; it < size; ++it)
            res = std::to_string(static_cast<const int>(pbyte[it])) + del + res;

        res = std::move(res); // делаем std::move чтобы избежать создания новой строки при возврате
        return res;
    }

    template <
        typename TypeInt,
        typename = std::enable_if_t<std::is_integral<TypeInt>::value>>
    int print_ip(const TypeInt indata)
    {
        TypeInt data = indata;
        if (sizeof(data) == 1)
            std::cout << static_cast<int>(static_cast<unsigned char>(data)) << std::endl;
        else
            std::cout << divide(data).c_str() << std::endl;
        return 0;
    }

    template <typename TypeStr,
              typename = std::enable_if_t<std::is_same<TypeStr, std::string>::value>>
    int print_ip(const TypeStr &indata)
    {
        std::cout << indata.c_str() << std::endl;
        return 0;
    }

    template <
        template <class, class> class Vec,
        class Tvec,
        class Alloc>
    int print_ip(const Vec<Tvec, Alloc> &indata)
    {
        static_assert(&Vec<Tvec, Alloc>::empty,
                      "No function empty() exist for template of used type");
        if (indata.empty())
        {
            std::cout << std::endl;
            return 0;
        }

        static_assert(&Vec<Tvec, Alloc>::cbegin,
                      "No function cbegin() exist for template of used type");
        static_assert(&Vec<Tvec, Alloc>::cend,
                      "No function cend() exist for template of used type");
        auto iter = indata.cbegin();
        std::cout << *iter;
        iter++;
        while (iter != indata.cend())
        {
            std::cout << "." << *iter;
            iter++;
        }
        std::cout << std::endl;
        return 0;
    }

    template <class... Tpl>
    int print_ip(std::tuple<Tpl...> tpl)
    {
        if ( std::tuple_size<decltype(tpl)>::value == 0)
        {
            std::cout << std::endl;
            return 0;
        }
        if (std::tuple_size<decltype(tpl)>::value == 1)
        {
            std::cout << std::get<0>(tpl) << std::endl;
            return 0;
        }
        // constexpr size_t iter_max = std::tuple_size<decltype(tpl)>::value;
        // unfold(tpl, 1, iter_max);
        // std::cout << std::get<iter_max - 1>(tpl) << std::endl;
        return 0;
    }


    template <class... Tpl>
    constexpr int unfold(std::tuple<Tpl...> tpl, const size_t it, const size_t max_it)
    {
        // static_assert( (std::is_same<std::get<it-1>(tpl), std::get<it>(tpl)>::value), "tuple's elements are not of the same type");

        // std::cout << std::get<it-1>(tpl) << " . " ;
        return it < (max_it - 1) ? unfold( tpl, it+1, max_it) : 0;
    }

} // namespace praddr

#endif /* FN_PRINT_IP_H_ */
#endif /* PRADDR_BASEFNCL_H_ */