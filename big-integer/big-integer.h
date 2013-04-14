/*
 * big-integer.h
 *
 * Copyright (c) 2010
 *
 * Author: wbbtiger@gmail.com
 *
 * Implement arbitrary precision integer arithmetic (+, -, *, / and %).
 */

#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <cassert>
#include <iostream>
#include <list>
#include <stdexcept>
#include <iterator>
#include <algorithm>

// Do arithmetic (addition, subtraction, multiplication, division and
// residue) with arbitrary precision.
//
// The big integer is represented using sign-magnitude method: a sign and a
// list of number blocks.  The sign is a 'boolean' because we just need two
// states, and the number blocks are linked to a list so std::list is
// appropriate where each number block is an 'unsigned long'.
//
// The algorithm is easy, just like what we learned in pupils' school how
// to do arithmetic manually.
//
// Representation Invariant
//   'int_list_' is not empty
//   no leading zeros except for zero
//   zero is always positive
class BigInteger {
public:
     BigInteger(int i = 0);
     explicit BigInteger(const std::string& str) throw (std::invalid_argument);

private:
     typedef unsigned long elem_type;
     typedef std::list<elem_type>::size_type size_type;

     static const elem_type base; // maximum of a number block

     explicit BigInteger(elem_type l);

     friend BigInteger operator+(const BigInteger& left, const BigInteger& right);
     friend BigInteger operator-(const BigInteger& left, const BigInteger& right);
     friend BigInteger operator*(const BigInteger& left, const BigInteger& right);
     friend BigInteger operator/(const BigInteger& left, const BigInteger& right)
          throw (std::invalid_argument);
     friend BigInteger operator%(const BigInteger& left, const BigInteger& right)
          throw (std::invalid_argument);
     friend BigInteger operator-(const BigInteger& integer);

     friend bool operator<(const BigInteger& left, const BigInteger& right);
     friend bool operator>(const BigInteger& left, const BigInteger& right);
     friend bool operator<=(const BigInteger& left, const BigInteger& right);
     friend bool operator>=(const BigInteger& left, const BigInteger& right);
     friend bool operator==(const BigInteger& left, const BigInteger& right);
     friend bool operator!=(const BigInteger& left, const BigInteger& right);        

     friend std::ostream& operator<<(std::ostream& out, const BigInteger& integer);
     friend std::istream& operator>>(std::istream& input, BigInteger& integer);

     static BigInteger add(const BigInteger& int_left, const BigInteger& int_right);
     static BigInteger sub(const BigInteger& int_left, const BigInteger& int_right);
     static BigInteger mul(const BigInteger& int_left, const BigInteger& int_right);     
     static BigInteger mul(elem_type left, elem_type right);
     static BigInteger div(const BigInteger& left, const BigInteger& right,
                           BigInteger *presidue);
     static int cmp(const BigInteger& left, const BigInteger& right);
     static int cmpabs(const BigInteger& int_left, const BigInteger& int_right);

     // Check representation invariant.  See top comments for details.
     bool checkRI() const {
          return (!int_list_.empty()) &&
               (int_list_.front() != 0 || int_list_.size() == 1) &&
               (int_list_.front() == 0 ? ispositive_ : true);
     }

     // Print the number block list for debugging.
     void print() const {
          assert(checkRI());
          std::copy(int_list_.begin(), int_list_.end(),
                    std::ostream_iterator<elem_type>(std::cout, " "));
          std::cout << std::endl;
     }

     // Shift the number blocks left by 'n' blocks.
     BigInteger& shift_left(unsigned long n);

     // Shift the number blocks right logically by 'n' blocks.
     BigInteger& shift_right(unsigned long n);

     bool ispositive_;          // true for positive, false for negative
     std::list<elem_type> int_list_; // a list of number blocks
};
    
#endif  // ! BIG_INTEGER_H_
