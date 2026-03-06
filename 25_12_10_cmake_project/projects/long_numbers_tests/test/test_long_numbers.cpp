#include "long_number.hpp"
#include <gtest/gtest.h>

TEST(AdditionTest, Simple) {
    tar::LongNumber num1("123");
    tar::LongNumber num2 ("456");
    EXPECT_TRUE((num1 + num2 ) == tar::LongNumber("579")) 
		<< num1 << " + " << num2 << " = 579";
}

TEST(AdditionTest, WithCarry) {
    tar::LongNumber num1("999");
    tar::LongNumber num2 ("1");
    EXPECT_TRUE((num1 + num2 ) == tar::LongNumber("1000")) 
		<< num1 << " + " << num2 << " = 1000";
}


TEST(AdditionTest, NegativeNumbers) {
    tar::LongNumber num1("-100");
    tar::LongNumber num2 ("-200");
    EXPECT_TRUE((num1 + num2 ) == tar::LongNumber("-300")) 
		<< num1 << " + " << num2 << " = -300";
}

TEST(AdditionTest, MixedSigns) {
    tar::LongNumber num1("500");
    tar::LongNumber num2 ("-200");
    EXPECT_TRUE((num1 + num2 ) == tar::LongNumber("300"))
		<< num1 << " + " << num2 << " = 300";
}

TEST(AdditionTest, Zero) {
    tar::LongNumber num1("12345");
    tar::LongNumber num2 ("0");
    EXPECT_TRUE((num1 + num2 ) == tar::LongNumber("12345"))
		<< num1 << " + " << num2 << " = 12345";
}

TEST(SubtractionTest, Simple) {
    tar::LongNumber num1("500");
    tar::LongNumber num2 ("200");
    EXPECT_TRUE((num1 - num2 ) == tar::LongNumber("300"))
		<< num1 << " - " << num2 << " = 300";
}

TEST(SubtractionTest, WithBorrow) {
    tar::LongNumber num1("1000");
    tar::LongNumber num2 ("1");
    EXPECT_TRUE((num1 - num2 ) == tar::LongNumber("999"))
		<< num1 << " - " << num2 << " = 999";
}

TEST(SubtractionTest, NegativeResult) {
    tar::LongNumber num1("100");
    tar::LongNumber num2 ("500");
    EXPECT_TRUE((num1 - num2 ) == tar::LongNumber("-400"))
		<< num1 << " - " << num2 << " = -400";
}

TEST(SubtractionTest, NegativeNumbers) {
    tar::LongNumber num1("-500");
    tar::LongNumber num2 ("-200");
    EXPECT_TRUE((num1 - num2 ) == tar::LongNumber("-300"))
		<< num1 << " - " << num2 << " = -300";
}

TEST(SubtractionTest, SameNumber) {
    tar::LongNumber num("12345");
    EXPECT_TRUE((num - num) == tar::LongNumber("0"))
		<< num << " - " << num << " = 0";
}

TEST(MultiplicationTest, Simple) {
    tar::LongNumber num1("12");
    tar::LongNumber num2 ("3");
    EXPECT_TRUE((num1 * num2 ) == tar::LongNumber("36"))
		<< num1 << " * " << num2 << " = 36";
}

TEST(MultiplicationTest, LargeNumbers) {
    tar::LongNumber num1("123");
    tar::LongNumber num2 ("456");
    EXPECT_TRUE((num1 * num2 ) == tar::LongNumber("56088"))
		<< num1 << " * " << num2 << " = 56088";
}

TEST(MultiplicationTest, ByZero) {
    tar::LongNumber num1("12345");
    tar::LongNumber num2 ("0");
    EXPECT_TRUE((num1 * num2 ) == tar::LongNumber("0"))
		<< num1 << " * " << num2 << " = 0";
}

TEST(MultiplicationTest, NegativeNumbers) {
    tar::LongNumber num1("-12");
    tar::LongNumber num2 ("3");
    EXPECT_TRUE((num1 * num2 ) == tar::LongNumber("-36"))
		<< num1 << " * " << num2 << " = -36";
}

TEST(MultiplicationTest, BothNegative) {
    tar::LongNumber num1("-447");
    tar::LongNumber num2 ("-365");
    EXPECT_TRUE((num1 * num2 ) == tar::LongNumber("163155"))
		<< num1 << " * " << num2 << " = 163155";
}

TEST(DivisionTest, Simple) {
    tar::LongNumber num1("100");
    tar::LongNumber num2 ("5");
    EXPECT_TRUE((num1 / num2 ) == tar::LongNumber("20"))
		<< num1 << " / " << num2 << " = 20";
}

TEST(DivisionTest, WithRemainder) {
    tar::LongNumber num1("100");
    tar::LongNumber num2 ("3");
    EXPECT_TRUE((num1 / num2 ) == tar::LongNumber("33"))
		<< num1 << " / " << num2 << " = 33";
}

TEST(DivisionTest, ByOne) {
    tar::LongNumber num1("12345");
    tar::LongNumber num2 ("1");
    EXPECT_TRUE((num1 / num2 ) == tar::LongNumber("12345"))
		<< num1 << " / " << num2 << " = 12345";
}

TEST(DivisionTest, SmallerDividend) {
    tar::LongNumber num1("5");
    tar::LongNumber num2 ("100");
    EXPECT_TRUE((num1 / num2 ) == tar::LongNumber("0"))
		<< num1 << " / " << num2 << " = 0";
}

TEST(DivisionTest, NegativeNumbers) {
    tar::LongNumber num1("-100");
    tar::LongNumber num2 ("5");
    EXPECT_TRUE((num1 / num2 ) == tar::LongNumber("-20"))
		<< num1 << " / " << num2 << " = -20";
}

TEST(ModuloTest, Simple) {
    tar::LongNumber num1("100");
    tar::LongNumber num2 ("3");
    EXPECT_TRUE((num1 % num2 ) == tar::LongNumber("1"))
		<< num1 << " % " << num2 << " = 1";
}

TEST(ModuloTest, NoRemainder) {
    tar::LongNumber num1("100");
    tar::LongNumber num2 ("5");
    EXPECT_TRUE((num1 % num2 ) == tar::LongNumber("0"))
		<< num1 << " % " << num2 << " = 0";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}