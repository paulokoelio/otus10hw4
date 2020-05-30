#include <cassert>
#include <exception>
#include <iostream>
#include <string>
// #include <vector>
// #include <sstream>
// #include <map>

#include "version.h"
#include "praddr.h"
#include "praddr_basefncl.h"
#include <vector>
#include <list>
#include <tuple>

// -------for tests only-----------
template <class Vec, class Tvec, class... Args>
struct notvector
{
    Vec mainobj{0};
    Tvec index{0};
};

template <class Vec, class... Args>
struct notvector2
{
    Vec mainobj{0};
};

    notvector<int, int> x;
    notvector<float, float> z2;
    notvector<double, double, double> z3;
    notvector2<int> z1;
// -------END for tests only-----------

using namespace praddr;

int main(int argc, char const *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    try
    {
        print_ip(char(-1));
        print_ip(short(0));
        print_ip(int(2130706433));
        print_ip( 8875824491850138409 );
        print_ip(-347547545004637399);
        print_ip(std::string("trololo"));

        std::vector<int> vec = {1,2,3,4,5};
        std::list<int> lst (4,1001);
        auto tpl1 = std::make_tuple("tuple-1-member");
        auto tpl0 = std::make_tuple();
        auto tpl3 = std::make_tuple("tuple1","tuple2","tuple3");
        
        print_ip(vec);
        print_ip(lst);
        // print_ip(tpl1);
        UNUSED(tpl1);
        print_ip(tpl3);
        print_ip(z1);
        print_ip(z2);
        print_ip(z3);
        pr(9, 8, 7, 6, 5);
        // print_ip(tpl2);
        UNUSED(tpl0);
        // UNUSED(lst);
        // template <class...>
        // using vec = std::vector<int, class...>;
        // is_accepted<true, vec> trst;
        // trst.test();



    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "ipaddr version " << version() << std::endl;
    }

    return 0;
}
