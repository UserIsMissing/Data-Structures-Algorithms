/*
Cole Schreiner
caschrei
pa6
BigInteger.cpp
*/


#include <iostream>
#include <string>
#include <sstream>
#include "List.h"
#include "BigInteger.h"

// BASE = 10^POWER
// POWER is 0 <= POWER <= 9
const int POWER = 9;
const long BASE = 1000000000; // 1 Billion

void shiftList(List &L, int p);
void removeLeadingZeros(List &L);
void makePositive(BigInteger &L);
List sumList(List &A, List &B);
List scalarMultList(long M, List *B, int *count);

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger()
{
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x)
{
    if (x == 0)
    {
        signum = 0;
        digits = List();
    }
    else if (x > 0)
    {
        signum = 1;
        digits = List();
        while (x > 0)
        {
            digits.moveBack();
            digits.insertBefore(x % BASE);
            x /= BASE;
        }
    }
    else
    {
        signum = -1;
        digits = List();
        x = -x;
        while (x > 0)
        {
            digits.moveBack();
            digits.insertBefore(x % BASE);
            x /= BASE;
        }
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s)
{
    int signPos = 0;
    if (s[0] == '-') {
        signum = -1;
        signPos = 1;
    } else if (s[0] == '+') {
        signum = 1;
        signPos = 1;
    } else {
        signum = 1;
    }
    ListElement factor = 1, sum = 0;
    for (int i = s.size() - 1; i >= signPos; i--) {
        sum += (s[i] - '0') * factor;
        factor *= 10;
        if (factor == BASE) {
            digits.insertAfter(sum);
            sum = 0;
            factor = 1;
        } else if (i == signPos) {
            digits.insertAfter(sum);
        }
    }
    while (digits.peekNext() == 0) {
        digits.eraseAfter();
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger &N)
{
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const
{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger &N) const
{
    if (this->signum > N.signum)
    {
        return 1;
    }
    else if (this->signum < N.signum)
    {
        return -1;
    }

    if (this->digits.length() > N.digits.length())
    {
        return 1;
    }
    else if (this->digits.length() < N.digits.length())
    {
        return -1;
    }

    List A = this->digits;
    List B = N.digits;
    A.moveFront();
    B.moveFront();

    while (A.position() != A.length() && B.position() != B.length())
    {
        if (A.peekNext() > B.peekNext())
        {
            return 1;
        }
        else if (A.peekNext() < B.peekNext())
        {
            return -1;
        }
        A.moveNext();
        B.moveNext();
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero()
{
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate()
{
    if (signum == 0)
    {
        return;
    }
    signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger &N) const
{
    if (this->signum == 0)
    {
        return N;
    }
    if (N.signum == 0)
    {
        return *this;
    }

    BigInteger numA = *this;
    BigInteger numB = N;
    BigInteger tempA = *this;
    BigInteger tempB = N;
    makePositive(tempA);
    makePositive(tempB);
    // if tempB is larger than tempA, swap them
    // if (tempA.compare(tempB) == -1)
    // {
    //     numA = N;
    //     numB = *this;
    // }

    List A = this->digits;
    List B = N.digits;
    List S = List();
    int sgn = 1;
    if (this->signum == -1 && N.signum == -1) // -A + -B = -(A + B)
    {
        sgn = -1;
    }
    else if (this->signum == -1 && N.signum == 1) // -A + B = B - A
    {
        numA.negate();
        return numB.sub(numA);
    }
    else if (this->signum == 1 && N.signum == -1) // A + -B = A - B
    {
        // if tempB is larger than tempA, swap them
        if (tempA.compare(tempB) == -1)
        {
            numA = N;
            numB = *this;
            numA.negate();
            BigInteger result = numA.sub(numB);
            result.negate();
            return result;
        }
        else
        {
            numB.negate();
            return numA.sub(numB);
        }
    }

    A.moveBack();
    B.moveBack();
    int carry = 0;
    while (A.position() != 0 && B.position() != 0)
    {
        int sum = A.peekPrev() + B.peekPrev() + carry;
        S.moveFront();
        S.insertBefore(sum % BASE);
        carry = sum / BASE;
        A.movePrev();
        B.movePrev();
    }
    while (A.position() != 0)
    {
        int sum = A.peekPrev() + carry;
        S.moveFront();
        S.insertBefore(sum % BASE);
        carry = sum / BASE;
        A.movePrev();
    }
    while (B.position() != 0)
    {
        int sum = B.peekPrev() + carry;
        S.moveFront();
        S.insertBefore(sum % BASE);
        carry = sum / BASE;
        B.movePrev();
    }
    if (carry > 0)
    {
        S.moveFront();
        S.insertBefore(carry);
    }
    BigInteger result = BigInteger();
    result.signum = sgn;
    result.digits = S;
    return result;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger &N) const
{
    if (this->signum == 0)
    {
        return N;
    }
    if (N.signum == 0)
    {
        return *this;
    }
    if (this->compare(N) == 0)
    {
        return BigInteger();
    }

    BigInteger result = BigInteger();
    BigInteger numA = *this;
    BigInteger numB = N;
    BigInteger tempA = *this;
    BigInteger tempB = N;
    makePositive(tempA);
    makePositive(tempB);
    bool swapped = false;
    // if tempB is larger than tempA, swap them
    if (tempA.compare(tempB) == -1)
    {
        numA = N;
        numB = *this;
        swapped = true;
    }

    if (numA.signum == -1 && numB.signum == -1) // -A - -B = B - A
    {
        // numA.negate();
        // numB.negate();
        makePositive(numA);
        makePositive(numB);
        if (swapped == true)
        {
            result = numB.sub(numA);
            result.negate();
            return result;
        }
        else
        {
            result = numA.sub(numB);
            result.negate();
            return result;
        }
    }
    if (this->signum == -1 && N.signum == 1) // -A - B = -(A + B)
    {
        makePositive(numA);
        makePositive(numB);
        result = numA.add(numB);
        result.negate();
        return result;
    }
    if (this->signum == 1 && N.signum == -1) // A - -B = A + B
    {
        numB.negate();
        return numA.add(numB);
    }

    List A = numA.digits;
    List B = numB.digits;

    List D = List();
    int sgn = 1;
    A.moveBack();
    B.moveBack();
    int borrow = 0;
    while (A.position() != 0 && B.position() != 0)
    {
        int diff = A.peekPrev() - B.peekPrev() - borrow;
        if (diff < 0)
        {
            diff += BASE;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        D.moveFront();
        D.insertBefore(diff);
        A.movePrev();
        B.movePrev();
    }
    while (A.position() != 0)
    {
        int diff = A.peekPrev() - borrow;
        if (diff < 0)
        {
            diff += BASE;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        D.moveFront();
        D.insertBefore(diff);
        A.movePrev();
    }
    if (swapped == true)
    {
        sgn = -1;
    }
    removeLeadingZeros(D);
    result.signum = sgn;
    result.digits = D;
    return result;
}

// mult()
// Returns a BigInteger representing the product of this and N.
// Multiply two large number together. They will be represented by a list of longs.
BigInteger BigInteger::mult(const BigInteger &N) const
{
    BigInteger result;

    if (this->signum == 0 || N.signum == 0)
    {
        return BigInteger();
    }
    if (this->signum == 1 && N.signum == 1)
    {
        result.signum = 1;
    }
    else if (this->signum == -1 && N.signum == -1)
    {
        result.signum = 1;
    }
    else
    {
        result.signum = -1;
    }

    result.signum = this->signum * N.signum;
    if (result.signum == 0)
    {
        return result;
    }
    List numA = List(digits);
    List numB = List(N.digits);
    numA.moveBack();
    while (numA.position() > 0)
    {
        List empty;
        int i = 0;
        while (i < numA.length() - numA.position())
        {
            empty.insertAfter(0);
            i++;
        }
        long carry = 0;
        numB.moveBack();
        while (numB.position() > 0)
        {
            long product = numB.peekPrev() * numA.peekPrev() + carry;
            carry = 0;
            if (product >= BASE)
            {
                carry = product / BASE;
                product = product % BASE;
            }
            empty.insertAfter(product);
            numB.movePrev();
        }
        if (carry)
        {
            empty.insertAfter(carry);
        }
        result.digits = sumList(result.digits, empty);
        numA.movePrev();
    }
    return result;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string()
{
    std::string result = "";
    if (signum == 0)
    {
        return "0";
    }
    if (signum == -1)
    {
        result += "-";
    }
    digits.moveFront();
    while (digits.position() < digits.length())
    {
        std::stringstream ss;
        ss << digits.peekNext();
        std::string digit = ss.str();
        int length = digit.length();
        int i = 0;
        while (i < POWER - length && digits.position() != 0)
        {
            digit = "0" + digit;
            i++;
        }
        result += digit;
        digits.moveNext();
    }
    return result;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N)
{
    stream << N.to_string();
    return stream;
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B)
{
    return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B)
{
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B)
{
    return (A.compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B)
{
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B)
{
    return (A.compare(B) >= 0);
}

// operator+()
// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B)
{
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B)
{
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B)
{
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B)
{
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B)
{
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B)
{
    A = A.mult(B);
    return A;
}

// // Helper Functions ---------------------------------------------------------
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List &L, int p)
{
    for (int i = 0; i < p; i++)
    {
        L.moveBack();
        L.insertBefore(0);
    }
}

// removeLeadingZeros()
// Removes leading zeros from L.
void removeLeadingZeros(List &L)
{
    L.moveFront();
    while (L.position() != L.length() && L.peekNext() == 0)
    {
        L.moveNext();
        L.eraseBefore();
    }
}

// makePositive()
// Changes the sign of each integer in List L to positive. Used by sub().
void makePositive(BigInteger &L)
{
    if (L.sign() == 0)
    {
        return;
    }
    if (L.sign() == -1)
    {
        L.negate();
    }
}

// sumList()
// Adds two lists A and B, storing the result in S. The sign parameter determines whether to add or subtract.
List sumList(List &A, List &B)
{
    List S;
    A.moveBack();
    B.moveBack();
    int carry = 0;
    while (A.position() != 0 || B.position() != 0)
    {
        int sum = carry;
        if (A.position() != 0)
        {
            sum += A.peekPrev();
            A.movePrev();
        }
        if (B.position() != 0)
        {
            sum += B.peekPrev();
            B.movePrev();
        }
        S.moveFront();
        S.insertBefore(sum % BASE);
        carry = sum / BASE;
    }
    if (carry != 0)
    {
        S.moveFront();
        S.insertBefore(carry);
    }
    return S;
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
List scalarMultList(long M, List *B, int *count)
{
    List L;
    long carry = 0;
    long foo = 0;
    B->moveBack();
    for (B->moveBack(); B->position() != 0; B->movePrev())
    {
        foo = (B->peekPrev() * M) + carry;
        carry = foo / BASE;
        foo = foo % BASE;
        L.insertAfter(foo);
    }
    if (carry > 0)
    {
        L.insertAfter(carry);
    }
    L.moveBack();
    int i = 0;
    while (i < *count)
    {
        L.insertAfter(0);
        i++;
    }
    return L;
}