/*
Cole Schreiner
caschrei
pa6
BigIntegerTest.cpp
*/


#include "BigInteger.h"
#include <cassert>

int main()
{
    // Test case 1: Subtracting two positive numbers
    BigInteger num1("123456789");
    BigInteger num2("987654321");
    BigInteger expected1("-864197532");
    assert(num1.sub(num2) == expected1);

    // Test case 2: Subtracting a positive number from zero
    BigInteger num3("0");
    BigInteger num4("987654321");
    BigInteger expected2("-987654321");
    assert(num3.sub(num4) == expected2);

    // Test case 3: Subtracting zero from a positive number
    BigInteger num5("123456789");
    BigInteger num6("0");
    BigInteger expected3("123456789");
    assert(num5.sub(num6) == expected3);

    // Test case 4: Subtracting a positive number from a negative number
    BigInteger num7("-123456789");
    BigInteger num8("987654321");
    BigInteger expected4("-1111111110");
    assert(num7.sub(num8) == expected4);

    // Test case 5: Subtracting a negative number from a positive number
    BigInteger num9("987654321");
    BigInteger num10("-123456789");
    BigInteger expected5("1111111110");
    assert(num9.sub(num10) == expected5);

    // Test case 6: Subtracting two negative numbers
    BigInteger num11("-123456789");
    BigInteger num12("-987654321");
    BigInteger expected6("864197532");
    assert(num11.sub(num12) == expected6);

    // Test case 7: Subtracting a number from itself
    BigInteger num13("123456789");
    BigInteger expected7("0");
    assert(num13.sub(num13) == expected7);

}
