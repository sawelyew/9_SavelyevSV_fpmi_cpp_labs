#include "../src/n6func.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(PrimeTest, BasicPrimes) {
    EXPECT_TRUE(IsPrime(1));
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_TRUE(IsPrime(7));
    EXPECT_TRUE(IsPrime(11));
    EXPECT_TRUE(IsPrime(13));
}

TEST(PrimeTest, NonPrimes) {
    EXPECT_FALSE(IsPrime(4));
    EXPECT_FALSE(IsPrime(6));
    EXPECT_FALSE(IsPrime(9));
    EXPECT_FALSE(IsPrime(15));
    EXPECT_FALSE(IsPrime(25));
}

TEST(PrimeTest, OtherCases){
    EXPECT_FALSE(IsPrime(0));
    EXPECT_FALSE(IsPrime(-3));
    EXPECT_TRUE(IsPrime(17));
}

TEST(PrimeTest, MersenNumDefault){
    EXPECT_EQ(CalculateMersenNum(1), 1);
    EXPECT_EQ(CalculateMersenNum(2), 3);
    EXPECT_EQ(CalculateMersenNum(3), 7);
    EXPECT_EQ(CalculateMersenNum(5), 31);
    EXPECT_EQ(CalculateMersenNum(7), 127);
}

TEST(PrimeTest, MersenNumNonPositiveAndNonPrimes){
    EXPECT_THROW(CalculateMersenNum(-1), const char*);
    EXPECT_THROW(CalculateMersenNum(4), const char*);
    EXPECT_THROW(CalculateMersenNum(9), const char*);
}

TEST(PrimeTest, CalcMersNumsToN){
    std::vector<int> expected1{1};
    EXPECT_EQ(CalculateMersenNumsToN(1), expected1);
    std::vector<int> expected2{1, 3, 7, 31};
    EXPECT_EQ(CalculateMersenNumsToN(32), expected2);

    EXPECT_THROW(CalculateMersenNumsToN(-3), const char*);
    EXPECT_THROW(CalculateMersenNumsToN(0), const char*);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}