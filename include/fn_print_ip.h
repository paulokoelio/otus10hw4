#ifdef PRADDR_BASEFNCL_H_
#ifndef FN_PRINT_IP_H_
#define FN_PRINT_IP_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <functional>

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

        std::move(res); // делаем std::move чтобы избежать создания новой строки при возврате
        return res;
    }

    // template <class T1, class... Tnext>
    // void pr(T1 t1, Tnext... arg)        // эта форма функции для данного ДЗ не используется
    // {
    //     std::cout << t1 << ip_delimiter;
    //     pr(arg...);
    // }

    template <class T1>
    void pr(T1 t1)
    {
        std::cout << t1 << '\n';
    }

    template <
        template <class...> class V,
        typename T,
        typename... Tnext>
    void pr(V<T, Tnext...> vec)
    {
        if (vec.empty())
        {
            std::cout << std::endl;
            return;
        }

        auto iter = vec.cbegin();
        std::cout << *iter;
        iter++;
        while (iter != vec.cend())
        {
            std::cout << ip_delimiter << *iter;
            iter++;
        }
        std::cout << std::endl;
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

    template <
        template <class...> class Vec,
        class... Other>
    int print_ip(const Vec<Other...> &indata)
    {
        prns();
        UNUSED(indata);
        return 0;
    }

    template <
        template <class, class...> class Vec,
        class Tvec,
        class... Other,
        std::enable_if_t<
            (std::is_same<Vec<Tvec>, std::vector<Tvec>>::value 
            || std::is_same<Vec<Tvec>, std::list<Tvec>>::value),
            int> = 0>
    int print_ip(const Vec<Tvec, Other...> &indata)
    {
        pr(indata);
        return 0;
    }

    template <
        class Tvec,
        class Alloc>
    int print_ip(const std::basic_string<Tvec, Alloc> &indata)
    {
        std::cout << indata.c_str() << std::endl;
        return 0;
    }

} // namespace praddr

#endif /* FN_PRINT_IP_H_ */
#endif /* PRADDR_BASEFNCL_H_ */