/*
 * Copyrith (c) 2010 wbb.
 *
 * Author: wbb@gmail.com
 *
 * Generate test cases for big-integer.
 */

import java.math.BigInteger;

public class gentests {
    public static void main(String[] args) {
        // Single block and single block.
        // No carry bits.
        genTestcases(BigInteger.ZERO, BigInteger.ZERO);
        genTestcases(BigInteger.ZERO, BigInteger.ONE);
        genTestcases(BigInteger.ONE, BigInteger.ZERO);
        genTestcases(BigInteger.TEN, BigInteger.ONE);
        genTestcases(BigInteger.ONE, BigInteger.TEN);
        // Carry bits.
        genTestcases(new BigInteger("FFFFFFF1", 16), new BigInteger("FFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("FFFFFFF1", 16));
        
        // Single block and double block.
        // No carry bits in lowest block.
        genTestcases(BigInteger.ZERO, new BigInteger("100000000", 16));
        genTestcases(BigInteger.ONE, new BigInteger("112345678", 16));
        genTestcases(new BigInteger("12345678", 16), new BigInteger("187654321", 16));
        // Have carry bits in lowest block.
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("1FFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));

        // Single block and triple block.
        // No carry bits in lowest block.
        genTestcases(BigInteger.ZERO, new BigInteger("10000000000000000", 16));
        genTestcases(BigInteger.TEN, new BigInteger("10000000000000000", 16));
        genTestcases(BigInteger.TEN, new BigInteger("1123456789987654321", 16));
        // Have carry bits in lowest block.
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("112345678FFFFFFFF", 16));
        // Have carry bits in the second block.
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("1FFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFF", 16), new BigInteger("10000000000000000", 16));
        genTestcases(BigInteger.ZERO, new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));

        // Double block and signle block.
        // No carry bits in the lowest block.
        genTestcases(new BigInteger("100000000", 16), BigInteger.ZERO);
        genTestcases(new BigInteger("112345678", 16), new BigInteger("12345678", 16));
        // Have carry bits in the lowest block.
        genTestcases(new BigInteger("1FFFFFFFF", 16), new BigInteger("FFFFFFFF", 16));
        // Have carry bits in the second block.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFF", 16));
        genTestcases(new BigInteger("100000000", 16), new BigInteger("FFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), BigInteger.ZERO);
        
        // Double block and double block.
        // No carry bits in both blocks.
        genTestcases(new BigInteger("112345678", 16), new BigInteger("112345678", 16));
        // Carry bits in the lowest block only.
        genTestcases(new BigInteger("1FFFFFFFF", 16), new BigInteger("FFFFFFFFF", 16));
        // Carry bits in the second block only.
        genTestcases(new BigInteger("FFFFFFFF12345678", 16), new BigInteger("FFFFFFFF12345678", 16));
        // Carry bits in both blocks.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("100000000", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("100000000", 16));

        // Double and Triple block.
        // No carry bits in lowest block.
        genTestcases(new BigInteger("123456789", 16), new BigInteger("11234567812345678", 16));
        // Carry bits in the lowest block.
        genTestcases(new BigInteger("FFFFFFFFF", 16), new BigInteger("112345678FFFFFFFF", 16));
        // Carry bits in the second block only.
        genTestcases(new BigInteger("FFFFFFFF12345678", 16), new BigInteger("1FFFFFFFF12345678", 16));
        // Carry bits in 2 lowest blocks.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("1FFFFFFFFFFFFFFFF", 16));
        // Carry bits in three blocks.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("100000000", 16), new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFF", 16), new BigInteger("10000000000000000", 16));

        // Triple block and single block.
        // No carry bits.
        genTestcases(new BigInteger("11234567812345678", 16), BigInteger.TEN);
        // Carry bits in the lowest block.
        genTestcases(new BigInteger("112345678FFFFFFFF", 16), new BigInteger("FFFFFFFF", 16));
        // Carry bits in the second block.
        genTestcases(new BigInteger("1FFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFF", 16));
        // Carry bits in the triple block.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), BigInteger.ZERO);
        genTestcases(new BigInteger("10000000000000000", 16), new BigInteger("FFFFFFFF", 16));

        // Triple block and double block.
        // No carry bits.
        genTestcases(new BigInteger("11234567812345678", 16), new BigInteger("1234567812345678", 16));
        // Carry bits in the lowest block.
        genTestcases(new BigInteger("112345678FFFFFFFF", 16), new BigInteger("12345678FFFFFFFF", 16));
        // Carry bits in the second block only.
        genTestcases(new BigInteger("1FFFFFFFF12345678", 16), new BigInteger("FFFFFFFF12345678", 16));
        // Carry bits in the lowest 2 blocks.
        genTestcases(new BigInteger("1FFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));
        // Carry bits in three blocks.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("10000000000000000", 16), new BigInteger("FFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), new BigInteger("100000000", 16));

        // Triple block and triple block.
        // No carry bits.
        genTestcases(new BigInteger("11234567812345678", 16), new BigInteger("11234567812345678", 16));
        // Carry bits in the lowest block.
        genTestcases(new BigInteger("112345678FFFFFFFF", 16), new BigInteger("112345678FFFFFFFF", 16));
        // Carry bits in the second block.
        genTestcases(new BigInteger("1FFFFFFFF12345678", 16), new BigInteger("1FFFFFFFF12345678", 16));
        // Carry bits in the third block.
        genTestcases(new BigInteger("FFFFFFFF1234567812345678", 16), new BigInteger("FFFFFFFF1234567812345678", 16));
        // Carry bits in the lowest 2 blocks
        genTestcases(new BigInteger("1FFFFFFFFFFFFFFF", 16), new BigInteger("1FFFFFFFFFFFFFFFF", 16));
        // Carry bits in all three blocks.
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("10000000000000000", 16), new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16));
        genTestcases(new BigInteger("FFFFFFFFFFFFFFFFFFFFFFFF", 16), new BigInteger("10000000000000000", 16));
    }

    static void genTestcases(final BigInteger left, final BigInteger right) {
        System.out.println(left + "\t+\t" + right + "\t" + left.add(right));
        System.out.println(left.negate() + "\t+\t" + right + "\t" + left.negate().add(right));
        System.out.println(left + "\t+\t" + right.negate() + "\t" + left.add(right.negate()));
        System.out.println(left.negate() + "\t+\t" + right.negate() + "\t" + left.negate().add(right.negate()));

        System.out.println(left + "\t-\t" + right + "\t" + left.subtract(right));
        System.out.println(left.negate() + "\t-\t" + right + "\t" + left.negate().subtract(right));
        System.out.println(left + "\t-\t" + right.negate() + "\t" + left.subtract(right.negate()));
        System.out.println(left.negate() + "\t-\t" + right.negate() + "\t" + left.negate().subtract(right.negate()));

        System.out.println(left + "\t*\t" + right + "\t" + left.multiply(right));
        System.out.println(left.negate() + "\t*\t" + right + "\t" + left.negate().multiply(right));
        System.out.println(left + "\t*\t" + right.negate() + "\t" + left.multiply(right.negate()));
        System.out.println(left.negate() + "\t*\t" + right.negate() + "\t" + left.negate().multiply(right.negate()));

        if (right.compareTo(BigInteger.ZERO) == 0) {
            System.out.println(left + "\t/\t" + right + "\t" + "invalid");
            System.out.println(left.negate() + "\t/\t" + right + "\t" + "invalid");
            System.out.println(left + "\t/\t" + right.negate() + "\t" + "invalid");
            System.out.println(left.negate() + "\t/\t" + right.negate() + "\t" + "invalid");
        } else {
            System.out.println(left + "\t/\t" + right + "\t" + left.divide(right));
            System.out.println(left.negate() + "\t/\t" + right + "\t" + left.negate().divide(right));
            System.out.println(left + "\t/\t" + right.negate() + "\t" + left.divide(right.negate()));
            System.out.println(left.negate() + "\t/\t" + right.negate() + "\t" + left.negate().divide(right.negate()));
        }
    }
}
