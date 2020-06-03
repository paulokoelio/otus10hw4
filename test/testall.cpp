#include "version.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <deque>
#include <sstream>

#include "praddr_basefncl.h"
#include "mylib_print_tuple.h"

TEST(testall, fnversion)
{
    const char *first = PROJECT_VERSION;
    const char *second = praddr::version();

    std::string ver(second);

    EXPECT_STREQ(first, second);
    EXPECT_STRCASEEQ(first, second);
    EXPECT_GE(ver.length(), 5);
}

struct TestAll : public ::testing::Test
{
protected:
    std::stringstream test_res;
    std::streambuf *save_cout;
    std::streambuf *stream_buffer_test;

    void SetUp() override
    {
        save_cout = std::cout.rdbuf();
        stream_buffer_test = test_res.rdbuf();
        std::cout.rdbuf(stream_buffer_test);
        test_res.str("");
        test_res.clear();
    }
    void TearDown() override { std::cout.rdbuf(save_cout); }
};

struct TestAllplus : public TestAll
{
protected:
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
};

TEST_F(TestAll, prns)
{
    ASSERT_NO_THROW(praddr::prns());
}

TEST_F(TestAll, printipintegral)
{
    char c0 = -1;
    short s1 = 0;
    int i2 = 2130706433;
    long long l3 = 8875824491850138409LL;
    long long l4 = -347547545004637399LL;

    using namespace praddr;
    using namespace mylib;

    print_ip(c0);
    print_ip(s1);
    print_ip(i2);
    print_ip(l3);
    print_ip(l4);

    EXPECT_EQ("255\n0.0\n127.0.0.1\n123.45.67.89.101.112.131.41\n251.45.67.89.101.112.131.41\n",
              test_res.str());
}

TEST_F(TestAll, printipstring)
{
    std::string s("trololo");

    using namespace praddr;
    using namespace mylib;

    print_ip(s);

    EXPECT_EQ("trololo\n", test_res.str());
}

TEST_F(TestAllplus, printipcontainers)
{
    std::vector<int>    vec = {1, 2, 3, 4, 5};
    std::list<int>      lst(4, 1001);
    std::list<int>      lst2{};
    std::deque<int>     deq(4, 1001);
    notvector<int, int> x;
    notvector<float, float> z2;
    notvector<double, double, double> z3;
    notvector2<int> z1;

    using namespace praddr;
    using namespace mylib;

    print_ip(vec);
    print_ip(lst);
    print_ip(lst2);
    ASSERT_NO_THROW(print_ip(deq));
    print_ip(x);
    print_ip(z1);

    EXPECT_EQ("1.2.3.4.5\n1001.1001.1001.1001\n\ntype is not supported\ntype is not supported\ntype is not supported\n",
              test_res.str());
}

TEST_F(TestAll, printiptuple)
{
    auto tpl0 = std::make_tuple();
    auto tpl1 = std::make_tuple("tuple-1-member");
    auto tpl3 = std::make_tuple("tuple1", "tuple2", "tuple3");
    auto t1 = std::make_tuple("hello", 42, 3.14);
    auto t2 = std::make_tuple(10, 42, 3, 14);
    auto t3 = std::make_tuple(10, 42, 3.14, 8);

    using namespace praddr;
    using namespace mylib;

    ASSERT_NO_THROW(print_ip(tpl0));
    ASSERT_NO_THROW(print_ip(tpl1));
    print_ip(tpl3);
    print_ip(t1);
    print_ip(t2);
    print_ip(t3);

    EXPECT_EQ("\ntuple-1-member\ntuple1.tuple2.tuple3\nTuple is not of single type\n10.42.3.14\nTuple is not of single type\n",
              test_res.str());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}