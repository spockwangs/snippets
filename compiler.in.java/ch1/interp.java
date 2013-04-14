/*
 * interp.java -- A simple interpreter
 *
 * Author: wbb
 * Time-stamp: <2010-06-08 14:34:07 wbb>
 */

import java.lang.Math;          // for Math.max()

class interp {
    static void interp(Stm s) { 
        Table t = new Table();
        s.eval(t);
    }

    static int maxargs(Stm s) { 
        if (s instanceof AssignStm) {
            AssignStm ss = (AssignStm) s;
            return maxargs(ss.exp);
        } else if (s instanceof PrintStm) {
            PrintStm ss = (PrintStm) s;
            ExpList l = ss.exps;
        
            // Count the #parameters of print statement.
            int n = 0;
            while (l instanceof PairExpList) {
                PairExpList ll = (PairExpList) l;
                n++;
                l = ll.tail;
            }
            n++;                // +1 for LastExp

            return Math.max(n, maxargs(l));
        } else if (s instanceof CompoundStm) {
            CompoundStm ss = (CompoundStm) s;
            return Math.max(maxargs(ss.stm1), maxargs(ss.stm2));
        }
        return 0;
    }

    static int maxargs(Exp e) {
        if (e instanceof IdExp ||
            e instanceof NumExp) {
            return 0;
        } else if (e instanceof OpExp) {
            OpExp ee = (OpExp) e;
            return Math.max(maxargs(ee.left), maxargs(ee.right));
        } else if (e instanceof EseqExp) {
            EseqExp ee = (EseqExp) e;
            return Math.max(maxargs(ee.stm), maxargs(ee.exp));
        }
        return 0;
    }

    static int maxargs(ExpList l) {
        if (l instanceof PairExpList) {
            PairExpList ll = (PairExpList) l;
            return Math.max(maxargs(ll.head), maxargs(ll.tail));
        } else if (l instanceof LastExpList) {
            LastExpList ll = (LastExpList) l;
            return maxargs(ll.head);
        }
        return 0;
    }

    public static void main(String args[]) throws java.io.IOException {
        System.out.println(maxargs(prog.prog));
        interp(prog.prog);
    }
}
