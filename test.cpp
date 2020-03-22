#include <gtest/gtest.h>

extern "C" {
    #include "functionality.h"
}

class TestExecution : public ::testing::Test
{

};

TEST_F(TestExecution, NonParallSucces)
{
    EXPECT_TRUE( (non_parallel() == 0) );
}

TEST_F(TestExecution, ParallSuccess)
{
    EXPECT_TRUE( parallel() == 0);
}