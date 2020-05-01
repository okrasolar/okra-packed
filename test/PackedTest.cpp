#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Packed.h"

#include <string.h>

TEST_GROUP(BootLogicTest){
    virtual void setup()
    {
    }
};

TEST(BootLogicTest, FirstBoot)
{
    printf("TESTING!!!");
}

