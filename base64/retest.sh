#!/bin/bash

# exit on any error
set -e

rm -f test.*
touch test.0
for i in 1 2 3 4 5 6 9 10 11 99 100 101 333 334 335 999 1000 1001; do
    ./genbytes $i >test.$i
done

for i in test.*; do
    echo Testing $i
    ./encode <$i >x0                       # your encoder
    ./decode <x0 >y0                       # your decoder
    cmp $i y0                                 # compare to original
    ./encode <$i >x1                       # your encoder
    openssl enc -d -base64 <x1 >y1            # our decoder
    cmp $i y1                                 # compare to original
    openssl enc -e -base64 <$i >x2            # our encoder
    ./decode <x2 >y2                       # your decoder
    cmp $i y2                                 # compare to original
done
rm -f x0 x1 x2 y0 y1 y2 test.*

# Test if the decoder can detect errors from the input.
# #bytes of input is not multiples of 4.
rm -f error1.*
for i in 1 2 3 5 6 7 9 10 11 13 14 15 17 18 19 21 101 102 103 105 999 1001 1002 1003; do
    for ((j=0; j < i; j++)); do
        echo "a" >> error1.$i
    done
done
for i in error1.*; do
    echo "Testing $i"
    ./decode <$i &>/dev/null && exit 1 || :
done
rm -f error1.*

# Single '=' is not in the right place.
rm -f error2.*
for ((i = 0; i < 200; i++)); do
    : $((r = i%4))
    if [ $r == 3 ]; then
        continue
    fi
    for ((j = 0; j < i; j++)); do
        echo -n "a" >> error2.$i
    done
    echo -n "=" >> error2.$i
    : $((r = (i+1)%4))
    : $((r = 4-r))
    for ((j = 0; j < r; j++)); do
        echo -n "a" >> error2.$i
    done
    echo >>error2.$i
done
for i in error2.*; do
    echo "Testing $i"
    ./decode <$i &>/dev/null && exit 1 || :
done
rm -f error2.*

# Double '=' is not in the right place.
rm -f error3.*
for ((i = 0; i < 200; i++)); do
    : $((r = i%4))
    if [ $r != 0 -a $r != 1 ]; then
        continue
    fi
    for ((j = 0; j < i; j++)); do
        echo -n "a" >> error3.$i
    done
    echo -n "==" >> error3.$i
    : $((r = (i+2)%4))
    : $((r = 4-r))
    for ((j = 0; j < r; j++)); do
        echo -n "a" >> error3.$i
    done
    echo >>error3.$i
done
for i in error3.*; do
    echo "Testing $i"
    ./decode <$i &>/dev/null && exit 1 || :
done
rm -f error3.* 