#include <gtest/gtest.h>

extern "C" {
    #include "functionality.h"
}

class TestExecution : public ::testing::Test
{

};

TEST_F(TestExecution, NonParallSucces)
{
    if(non_parallel() == 0)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure();
    
}

TEST_F(TestExecution, ParallSuccess)
{
    if(parallel() == 0)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure();
}