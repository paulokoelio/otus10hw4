#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

#include "version.h"
#include "praddr_basefncl.h"
#include "mylib_print_tuple.h"

using namespace praddr;
using namespace mylib;

int main(int argc, char const *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    try
    {
        print_ip(char(-1));
        print_ip(short(0));
        print_ip(int(2130706433));
        print_ip(8875824491850138409);
        print_ip(std::string("trololo"));
        std::vector<int> vec = {1, 2, 3, 4, 5};
        print_ip(vec);
        std::list<int> lst(4, 1001);
        print_ip(lst);
        auto tpl0 = std::make_tuple();
        auto tpl1 = std::make_tuple("tuple-1-member");
        auto tpl3 = std::make_tuple("tuple1", "tuple2", "tuple3");
        auto t1 = std::make_tuple("hello", 42, 3.14);
        auto t2 = std::make_tuple(10, 42, 3, 14);
        auto t3 = std::make_tuple(10, 42, 3.14, 8);
        print_ip(tpl0);
        print_ip(tpl1);
        print_ip(tpl3);
        print_ip(t1);
        print_ip(t2);
        print_ip(t3);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "print_ip version " << version() << std::endl;
    }

    return 0;
}
