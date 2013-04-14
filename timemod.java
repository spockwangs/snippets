/*
 * Copyright (c) 2010 wbb.
 *
 * Measure the time exhausted by various primitive operations in Java.
 */

import java.util.Random;

public class timemod {
    static final int TRIALS = 5;
    public static void main(String[] args) {
        int n = 1000;
        long timesum = 0, start, t;
        double time_per_op;
        int k;
        
        System.out.println("Java Cost Model");

        // Timing empty statment.
        System.out.println("Integer Arithmetic");
        System.out.format("  %1$-20s", "{ }");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    { }
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k++".
        k = 0;
        System.out.format("  %1$-20s", "k++");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k++;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "i + j".
        System.out.format("  %1$-20s", "k=i+j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i + j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i - j".
        System.out.format("  %1$-20s", "k=i-j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i - j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i * j".
        System.out.format("  %1$-20s", "k=i*j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i * j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i / j".
        System.out.format("  %1$-20s", "k=i-j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i / j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i % j".
        System.out.format("  %1$-20s", "k=i%j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i % j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i & j".
        System.out.format("  %1$-20s", "k=i&j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i & j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = i | j".
        System.out.format("  %1$-20s", "k=i|j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i | j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k = ~j".
        System.out.format("  %1$-20s", "k=~j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = ~j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing floating-point arithmetics.
        System.out.println("Floating-point Arithmetic");
        double fk, fi, fj;
        Random random = new Random(System.nanoTime());
        fi = random.nextDouble();
        fj = random.nextDouble();
        
        // Timing "fj = j".
        System.out.format("  %1$-20s", "fj=j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "fk=fi+fj".
        System.out.format("  %1$-20s", "fk=fi+fj");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = fi + fj;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "fk=fi-fj".
        System.out.format("  %1$-20s", "fk=fi-fj");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = fi - fj;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "fk=fi*fj".
        System.out.format("  %1$-20s", "fk=fi*fj");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = fi * fj;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "fk=fi/fj".
        System.out.format("  %1$-20s", "fk=fi/fj");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = fi / fj;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "fk=fi".
        System.out.format("  %1$-20s", "k=i%j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = i % j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing array operations.
        System.out.println("Array Operations");
        int[] x = new int[n];
        for (int i = 0; i < n; i++)
            x[i] = random.nextInt();

        // Timing "k=x[j]+j".
        System.out.format("  %1$-20s", "k=x[j]+j");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    k = x[j] + j;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k=j+x[j]".
        System.out.format("  %1$-20s", "k=j+x[j]");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    k = j + x[j];
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing "k=x[i]+x[j]".
        System.out.format("  %1$-20s", "k=x[i]+x[j]");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    k = x[i] + x[j];
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing comparisons.
        System.out.println("Comparisons");
        System.out.format("  %1$-20s", "if (i<j) k++");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (i<j) k++;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "if (x[i]<x[j]) k++");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (x[i] < x[j]) k++;
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing math functions.
        System.out.println("Math Functions");
        System.out.format("  %1$-20s", "fk=sqrt(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.sqrt(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=sin(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.sin(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=cos(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.cos(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=asin(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.asin(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=acos(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.acos(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=tan(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.tan(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "fk=atan(fi)");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    fk = Math.atan(fi);
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "k=rand()");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    k = random.nextInt();
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        // Timing memory allocation.
        System.out.println("Memory Allocation");
        System.out.format("  %1$-20s", "new int[16]");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    x = new int[16];
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "new int[100]");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    x = new int[100];
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);

        System.out.format("  %1$-20s", "new int[2000]");
        for (int ex = 0; ex < TRIALS; ex++) {
            start = System.nanoTime();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    x = new int[2000];
            t = System.nanoTime() - start;
            System.out.format("%1$13d", t);
            timesum += t;
        }
        time_per_op = (double) timesum / (TRIALS*n*n);
        System.out.format("%1$10.3f\n", time_per_op);
    }
}
