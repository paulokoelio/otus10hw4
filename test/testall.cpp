#include "version.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "praddr.h"
#include "praddr_basefncl.h"

TEST(testall, fn_version)
{
    const char *first = PROJECT_VERSION;
    const char *second = praddr::version();

    std::string ver(second);

    EXPECT_STREQ(first, second);
    EXPECT_STRCASEEQ(first, second);
    EXPECT_GE(ver.length(), 5);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}