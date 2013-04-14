/*
 * Copyrith (c) 2010.
 *     Wang Bingbing.  All rights reserved.
 *
 * Simple arbitrary precision integer arithmetic (+, -, *, / and %) using
 * simple intuitive algorithms.
 *
 * See "big-integer.h" for implementation details.
 *
 * Author: 王兵兵 (wbbtiger@gmail.com)
 * Date: 2010-08-14 11:27:16
 */

#include "big-integer.h"

#include <stdexcept>
#include <climits>
#include <algorithm>
#include <cassert>

// #bits in a number block
#define NBITS (sizeof(BigInteger::elem_type)*CHAR_BIT)

const BigInteger::elem_type BigInteger::base = ULONG_MAX;

using namespace std;

BigInteger::BigInteger(int i)
{
    unsigned long l;
    if (i >= 0) {
        ispositive_ = true;
        l = i;
    } else {
        ispositive_ = false;
        l = -i;
    }
    int_list_.push_back(l);
    assert(checkRI());
}

BigInteger::BigInteger(const string& str) throw (invalid_argument)
    : ispositive_(true), int_list_(1, 0)
{
    int i = 0;
    bool sign;
    if (str[i] == '-') {
        i++;
        sign = false;
    } else {
        sign = true;
        if (str[i] == '+')
            i++;
    }
    assert(checkRI());
    
    const char digits[] = "0123456789";
    const BigInteger ten(10);
    for (; (size_t) i < str.size(); i++) {
        const char *p = find(digits, digits+sizeof(digits), str[i]);
        if (p == digits+sizeof(digits))
            throw invalid_argument(string("invalid digits '") + str[i] + string("'"));
        int d = p-digits;
        *this = *this * ten + BigInteger(d);
    }
    ispositive_ = sign;

    // No negative 0.
    if (int_list_.front() == 0)
        ispositive_ = true;
    assert(checkRI());
}

// NOTE: this is private and used internally.  Do *not* remove it.
BigInteger::BigInteger(elem_type l)
    : ispositive_(true), int_list_(1, 0)
{
    int_list_.front() = l;
    assert(checkRI());
}

BigInteger operator+(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());
    BigInteger ret;
    bool sign;
    if ((left.ispositive_ && right.ispositive_) ||
        (!left.ispositive_ && !right.ispositive_)) {
        sign = left.ispositive_;
        ret = BigInteger::add(left, right);
        ret.ispositive_ = sign;
        assert(ret.checkRI());
        return ret;
    }

    if (left.ispositive_ && !right.ispositive_)
        return BigInteger::sub(left, right);

    // left is negative and right is positive
    return BigInteger::sub(right, left);
}       

BigInteger operator-(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());

    BigInteger ret;
    if (left.ispositive_ && right.ispositive_)
        return BigInteger::sub(left, right);
    if (!left.ispositive_ && !right.ispositive_)
        return BigInteger::sub(right, left);
    if (left.ispositive_ && !right.ispositive_) {
        return BigInteger::add(left, right);
    }

    // left is negative and right is positive
    ret = BigInteger::add(left, right);
    ret.ispositive_ = false;
    assert(ret.checkRI());
    return ret;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());

    if (left.int_list_.front() == 0 || right.int_list_.front() == 0)
        return BigInteger(0);
    bool sign = left.ispositive_ == right.ispositive_;
    BigInteger ret = BigInteger::mul(left, right);
    ret.ispositive_ = sign;
    assert(ret.checkRI());
    return ret;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right)
    throw (invalid_argument)
{
    assert(left.checkRI());
    assert(right.checkRI());

    if (right.int_list_.front() == 0)
        throw invalid_argument("divide by 0");
    
    if (left.int_list_.front() == 0)
        return BigInteger(0);
    bool sign = left.ispositive_ == right.ispositive_;
    BigInteger ret = BigInteger::div(left, right, NULL);
    if (ret.int_list_.front() != 0)
        ret.ispositive_ = sign;
    assert(ret.checkRI());
    return ret;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right)
    throw (invalid_argument)
{
    assert(left.checkRI());
    assert(right.checkRI());

    if (right.int_list_.front() == 0)
        throw invalid_argument("divide by 0");
    if (left.int_list_.front() == 0)
        return BigInteger(0);
    bool sign = left.ispositive_;
    BigInteger ret;
    BigInteger::div(left, right, &ret);
    if (ret.int_list_.front() != 0)
        ret.ispositive_ = sign;
    assert(ret.checkRI());
    return ret;
}

BigInteger operator-(const BigInteger& integer)
{
    assert(integer.checkRI());
    if (integer.int_list_.front() == 0)
        return integer;
    BigInteger ret = integer;
    ret.ispositive_ = !ret.ispositive_;
    assert(ret.checkRI());
    return ret;
}

bool operator<(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) < 0;
}

bool operator<=(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) <= 0;
}

bool operator>=(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) >= 0;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& integer)
{
    assert(integer.checkRI());
    
    BigInteger ten(10), zero(0), t = integer, residue;
    string s;
    const char digits[] = "0123456789";

    if (!t.ispositive_)
        s = "-";
    t.ispositive_ = true;
    do {
        t = BigInteger::div(t, ten, &residue);
        assert(residue.int_list_.front() <= 9 && residue.int_list_.size() == 1);
        s += digits[residue.int_list_.front()];
    } while (t > zero);

    if (s[0] == '-')
        reverse(s.begin()+1, s.end());
    else
        reverse(s.begin(), s.end());
    out << s;
    return out;
}    

std::istream& operator>>(std::istream& input, BigInteger& integer)
{
    assert(integer.checkRI());

    string s;
    input >> s;
    integer = BigInteger(s);
    return input;
}

bool operator>(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) > 0;
}

bool operator==(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) == 0;
}

bool operator!=(const BigInteger& left, const BigInteger& right)
{
    return BigInteger::cmp(left, right) != 0;
}

/*
 * Add 2 integers regardless of the sign.  Take them as positive.
 */
BigInteger BigInteger::add(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());

    // Make paddend points to shorter big integer and paugend longer big integer.
    const BigInteger *paddend = NULL, *paugend = NULL;
    size_type augend_size, addend_size;
    if (left.int_list_.size() >= right.int_list_.size()) {
        paugend = &left;
        paddend = &right;
    } else {
        paugend = &right;
        paddend = &left;
    }
    augend_size = paugend->int_list_.size();
    addend_size = paddend->int_list_.size();

    // Now augend has more significent bits than addend.
    // Split each number block to 2 halves and do addition to avoid overflow.
    elem_type hi1, lo1, hi2, lo2, cbit = 0;
    list<elem_type>::const_reverse_iterator iter_augend = paugend->int_list_.rbegin();
    list<elem_type>::const_reverse_iterator iter_addend = paddend->int_list_.rbegin();
    BigInteger result;
    result.int_list_.clear();
    for (; iter_addend != paddend->int_list_.rend(); ++iter_addend, ++iter_augend) {
        assert(cbit == 0 || cbit == 1);

        hi1 = *iter_augend;
        lo1 = hi1 & ((~(elem_type)0) >> NBITS/2);
        hi1 >>= NBITS/2;

        hi2 = *iter_addend;
        lo2 = hi2 & ((~(elem_type)0) >> NBITS/2);
        hi2 >>= NBITS/2;

        lo1 += lo2 + cbit;      // add low part plus previous carry bit
        hi1 += hi2;             // add high part
        hi1 += lo1 >> NBITS/2;  // add carry bit from low part
        lo1 = lo1 & ((~(elem_type) 0) >> NBITS/2); // discard carry bit

        // Now hi1 and lo1 hold high and low part of sum.
        assert((lo1 >> NBITS/2) == 0);
        result.int_list_.push_front(hi1 << NBITS/2 | lo1);
        cbit = hi1 >> NBITS/2;
    }

    // If carry_bit is not 0 we should add it.
    assert(cbit == 0 || cbit == 1);
    for (; iter_augend != paugend->int_list_.rend(); ++iter_augend) {
        if (cbit == 0) {
            result.int_list_.push_front(*iter_augend);
        } else {
            if (*iter_augend == base) {
                result.int_list_.push_front(0);
            } else {
                result.int_list_.push_front(*iter_augend + 1);
                cbit = 0;
            }
        }
    }
    assert(cbit == 0 || cbit == 1);
    if (cbit == 1) {
        result.int_list_.push_front(1);
    }

    assert(result.checkRI());
    return result;
}

/*
 * Subtract 2 integers regardless of sign.  Take them as positive.
 */
BigInteger BigInteger::sub(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());
    
    // Make 'psubend' points to bigger integer.
    const BigInteger *psubend, *psubtractor;
    BigInteger result;
    int r;
    if ((r = BigInteger::cmpabs(left, right)) == 0) {
        return result;
    } else if (r < 0) {
        psubend = &right;
        psubtractor = &left;
        result.ispositive_ = false;
    } else {
        psubend = &left;
        psubtractor = &right;
        result.ispositive_ = true;
    }
    result.int_list_.clear();
    
    // Compute 'psubend' - 'psubtractor'.
    // Split number block to 2 halves to compute the subtraction.
    // That is (hi1*2^n + lo1) - (hi2*2^n + lo2).
    unsigned long hi1, lo1, hi2, lo2, cbit, pre_cbit = 0;
    list<elem_type>::const_reverse_iterator iter_subend =
        psubend->int_list_.rbegin();
    list<elem_type>::const_reverse_iterator iter_subtractor =
        psubtractor->int_list_.rbegin();
    for (; iter_subtractor != psubtractor->int_list_.rend();
         ++iter_subtractor, ++iter_subend) {
        assert(pre_cbit == 0 || pre_cbit == 1);
        
        hi1 = *iter_subend;
        hi2 = *iter_subtractor;
        if (hi1 < hi2 || ((hi1 == hi2) && pre_cbit != 0))
            cbit = 1;           // we need borrow a bit from high order.
        else
            cbit = 0;

        lo1 = hi1 & ((~(elem_type) 0) >> NBITS/2);
        hi1 >>= NBITS/2;
        hi1 += cbit << NBITS/2;

        lo2 = hi2 & ((~(elem_type) 0) >> NBITS/2);
        hi2 >>= NBITS/2;

        // If low part is smaller, borrow a bit from high part.
        if (lo1 < lo2 + pre_cbit) {
            lo1 += 1 << NBITS/2;
            --hi1;
        }

        // Now we're sure high and low parts are both larger engough to do
        // subtraction.
        assert(hi1 >= hi2 && lo1 >= lo2+pre_cbit);
        lo1 -= lo2 + pre_cbit;
        hi1 -= hi2;

        // Record we borrowed a bit from higher order block.
        pre_cbit = cbit;

        // Now hi1*2^n + lo1 is the result of this subtraction.
        assert((hi1 >> NBITS/2) == 0 && (lo1 >> NBITS/2) == 0);
        result.int_list_.push_front(hi1 << NBITS/2 | lo1);
    }

    // Process the remaining blocks of subend.
    // Note about the carry bit.
    assert(pre_cbit == 0 || pre_cbit == 1);
    for (; iter_subend != psubend->int_list_.rend(); ++iter_subend, ++iter_subtractor) {
        if (pre_cbit == 0) {
            result.int_list_.push_front(*iter_subend);
        } else {
            if (*iter_subend == 0) {
                // we need borrow a bit.
                result.int_list_.push_front(base);
            } else {
                result.int_list_.push_front(*iter_subend - 1);
                pre_cbit = 0;
            }
        }
    }

    // Strip off leading 0s in the result.
    while (result.int_list_.front() == 0 && !result.int_list_.empty())
        result.int_list_.pop_front();
    if (result.int_list_.empty())
        result.int_list_.push_back(0);

    assert(result.checkRI());
    return result;
}

/*
 * Multiply 2 big integers regardless of sign.  Take them as positive.
 */
BigInteger BigInteger::mul(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());
    
    // Make 'pmultiplicand' points to the integer with more blocks.
    const BigInteger *pmultiplicand, *pmultiplier;
    if (left.int_list_.size() < right.int_list_.size()) {
        pmultiplier = &left;
        pmultiplicand = &right;
    } else {
        pmultiplier = &right;
        pmultiplicand = &left;
    }

    // Do multiplication.
    list<elem_type>::const_reverse_iterator
        iter_multiplier = pmultiplier->int_list_.rbegin(),
        iter_multiplicand;
    BigInteger result;
    int v = 0;
    for (; iter_multiplier != pmultiplier->int_list_.rend(); ++iter_multiplier, v++) {
        int k = 0;
        BigInteger tmp;
        for (iter_multiplicand = pmultiplicand->int_list_.rbegin();
             iter_multiplicand != pmultiplicand->int_list_.rend();
             ++iter_multiplicand, k++) {
            BigInteger tmp2 = BigInteger::mul(*iter_multiplier, *iter_multiplicand);
            tmp2.shift_left(k);
            tmp = add(tmp, tmp2);
        }
        tmp.shift_left(v);
        result = add(result, tmp);
    }

    assert(result.checkRI());
    return result;
}

/*
 * Divide left with right (i.e. left / right) regardless of sign.  Take
 * them as positive.  Return the quotient.
 *
 * @param left dividend
 * @param right divisor
 * @param presidue records computed residue if not NULL
 */
BigInteger BigInteger::div(const BigInteger& left, const BigInteger& right,
                           BigInteger* presidue)
{
    // Check representation invariant.
    assert(left.checkRI());
    assert(right.checkRI());
    assert(right.int_list_.front() != 0);

    if (BigInteger::cmpabs(left, right) < 0) {
        if (presidue != NULL)
            *presidue = left;
        return BigInteger(0);
    }

    // Now i'm sure left >= right.
    // Evaluate the #blocks of quotient.
    size_type quotient_size = left.int_list_.size() - right.int_list_.size();
    BigInteger dividend = left, divisor = right;
    divisor.shift_left(quotient_size);
    if (BigInteger::cmpabs(divisor, dividend) <= 0)
        quotient_size++;
    else
        divisor.shift_right(1);

    // Now we know the quotient has 'quotient_size' number blocks.
    // According to long division algorithm, we need find 'quotient_size'
    // quotients.  First we guess one and then converge to the right one.
    // To find the right quotient quickly i use binary-search-like algorithm.
    BigInteger result;
    result.int_list_.clear();
    for (int i = 0; (size_type) i < quotient_size; i++) {
        // If dividend is less than divisor the quotient must be 0.
        if (BigInteger::cmpabs(dividend, divisor) < 0) {
            if (!result.int_list_.empty())
                result.int_list_.push_back(0);
            divisor.int_list_.pop_back();
            continue;
        }

        // Guess the quotient upper limit.  To make use of binary search we
        // must maintain the invariant: the right quotient is in range [1,
        // q), where q <= 'base'.  So we must first eliminate the special
        // condition that the quotient may be 'base'.
        elem_type q;
        BigInteger tmp;
        tmp = BigInteger::mul(divisor, BigInteger(base));
        if (BigInteger::cmpabs(tmp, dividend) <= 0) {
            // Special condition: the quotient is 'base'.
            q = base;
            goto quotient;
        }
        // Make a guess.  I'm sure the quotient < 'base'.
        if (dividend.int_list_.size() > divisor.int_list_.size())
            q = base;
        else {
            q = dividend.int_list_.front() / divisor.int_list_.front();
            if (q != base)
                ++q;
        }
        assert(q > 1);
        
        // The right quotient is in range [1, q).  Use binary search to
        // find the right one.
        elem_type l, u, m;
        l = 1;
        u = q;
        while (l+1 != u) {
            // loop invariant: l*divisor <= dividend < u*divisor and l < u
            m = (u-l)/2 + l;
            tmp = BigInteger::mul(divisor, BigInteger(m));
            if (BigInteger::cmpabs(tmp, dividend) <= 0) {
                // m is too small
                l = m;
            } else {
                // m is too big
                u = m;
            }
        }
        // assert: l+1 == u && l*divisor <= dividend < u*divisor
        assert(l+1 == u);
        assert(BigInteger::cmpabs(BigInteger::mul(divisor, BigInteger(l)), dividend) <= 0);
        assert(BigInteger::cmpabs(BigInteger::mul(divisor, BigInteger(u)), dividend) > 0);
        
        // Now l must be the right quotient.
        tmp = BigInteger::mul(divisor, BigInteger(l));
        q = l;

    quotient:        
        // q is the right quotient and tmp is q*divisor.
        assert(q > 0);
        result.int_list_.push_back(q);
        dividend = sub(dividend, tmp);
        assert(BigInteger::cmpabs(dividend, divisor) < 0);
        divisor.int_list_.pop_back();
    }

    assert(dividend.checkRI());

    // Check the residue is smaller than the divisor.
    assert(BigInteger::cmpabs(dividend, right) < 0);
    if (presidue != NULL)
        *presidue = dividend;

    assert(result.checkRI());

    // Check the equation: dividend = divisor*quotient + residue
    // 'dividend' is the residue, 'result' is the quotient, 'right' is the
    // divisor and 'left' is the dividend.
    assert(BigInteger::cmpabs(add(mul(result, right), dividend), left) == 0);
    return result;
}

/*
 * Compare absolute value of 2 integers.  Return 1 if left > right, 0 if
 * left == right, or -1 if left < right.
 */
int BigInteger::cmpabs(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());

    size_type left_size = left.int_list_.size();
    size_type right_size = right.int_list_.size();
    int ret;
    if (left_size < right_size) {
        ret =  -1;
    } else if (left_size > right_size) {
        ret = 1;
    } else {
        // Now left and right have the same number of blocks.  We compare block
        // by block from high order to low.
        list<elem_type>::const_iterator iter_left, iter_right;
        iter_left = left.int_list_.begin();
        iter_right = right.int_list_.begin();
        for (; iter_left != left.int_list_.end(); ++iter_left, ++iter_right) {
            if (*iter_left < *iter_right) {
                ret = -1;
                goto end;
            } else if (*iter_left > *iter_right) {
                ret = 1;
                goto end;
            }
        }
        ret = 0;
    }
    
end:
    return ret;
}

int BigInteger::cmp(const BigInteger& left, const BigInteger& right)
{
    assert(left.checkRI());
    assert(right.checkRI());
    
    if (left.ispositive_ && !right.ispositive_)
        return 1;
    if (!left.ispositive_ && right.ispositive_)
        return -1;

    int ret = cmpabs(left, right);
    if (!left.ispositive_)
        ret = -ret;
    return ret;
}

/*
 * Multiply 2 small positive integers.
 */
BigInteger BigInteger::mul(elem_type left, elem_type right)
{
    elem_type hi1, lo1, hi2, lo2, t1, t2, h, l;

    hi1 = left >> NBITS/2;
    lo1 = left & ((~(elem_type) 0) >> NBITS/2);

    hi2 = right >> NBITS/2;
    lo2 = right & ((~(elem_type) 0) >> NBITS/2);
    
    h = hi1 * hi2;
    l = lo1 * lo2;
    t1 = hi1 * lo2;
    t2 = hi2 * lo1;

    h += t1 >> NBITS/2;
    h += t2 >> NBITS/2;
    t1 &= (~(elem_type) 0) >> NBITS/2;
    t2 &= (~(elem_type) 0) >> NBITS/2;

    t1 += t2 + (l >> NBITS/2);
    l &= (~(elem_type) 0) >> NBITS/2;
    h += t1 >> NBITS/2;
    assert((l >> NBITS/2) == 0); // high part of lo1 should be 0
    l |= t1 << NBITS/2;
    
    // Now h and l hold the high and low part of the result.
    BigInteger ret;
    ret.int_list_.clear();
    if (h != 0) { 
        ret.int_list_.push_back(h);
    }
    ret.int_list_.push_back(l);

    assert(ret.checkRI());
    return ret;
}
    
/*
 * Shift left by 'n' blocks.
 */
BigInteger& BigInteger::shift_left(unsigned long n)
{
    assert(checkRI());

    if (int_list_.front() != 0) {
        while (n-- > 0)
            int_list_.push_back(0);
    }

    assert(checkRI());
    return *this;
}

/*
 * Shift logically right by 'n' blocks.
 */
BigInteger& BigInteger::shift_right(unsigned long n)
{
    assert(checkRI());
    
    while (n-- > 0 && !int_list_.empty())
        int_list_.pop_back();
    if (int_list_.empty())
        int_list_.push_back(0);

    assert(checkRI());
    return *this;
}
