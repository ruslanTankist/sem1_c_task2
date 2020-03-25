#include <gtest/gtest.h>

extern "C" {
    #include "functionality.h"
}

class TestExecution : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            array = NULL;
        }
        void TearDown() override
        {
            free_array(array);
        }
        char * array;
};

TEST_F(TestExecution, NonParallSuccess)
{
    bool correct = true;
    array = non_parallel();
    if (array != NULL)
        for (int i = 0; i < REQUIRED_SIZE; i++)
            if((int)array[i] != (i % 4))
            {
                correct = false;
                break;
            }
    EXPECT_TRUE(correct);
}

TEST_F(TestExecution, ParallSuccess)
{
    bool correct = true;
    array = parallel();
    if (array != NULL)
        for (int i = 0; i < REQUIRED_SIZE; i++)
            if((int)array[i] != (i % 4))
            {
                correct = false;
                break;
            }
    EXPECT_TRUE(correct);
}