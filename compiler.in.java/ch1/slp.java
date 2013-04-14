/*
 * slp.java -- A simple syntax tree
 *
 * Author: wbb
 * Time-stamp: <2010-06-08 14:32:01 wbb>
 */

abstract class Stm {
    abstract void eval(Table t);
}

class CompoundStm extends Stm {
    Stm stm1, stm2;
    CompoundStm(Stm s1, Stm s2) {stm1=s1; stm2=s2;}

    void eval(Table t) {
        stm1.eval(t);
        stm2.eval(t);
    }
}

class AssignStm extends Stm {
    String id; Exp exp;
    AssignStm(String i, Exp e) {id=i; exp=e;}

    void eval(Table t) {
        t.update(id, exp.eval(t));
    }
}

class PrintStm extends Stm {
    ExpList exps;
    PrintStm(ExpList e) {exps=e;}

    void eval(Table t) {
        /*
         * Evaluate each parameter and print it.
         */
        ExpList l = exps;
        while (l instanceof PairExpList) {
            PairExpList ll = (PairExpList) l;
            System.out.print(ll.head.eval(t) + " ");
            l = ll.tail;
        }
        assert (l instanceof LastExpList):"l is not instance of LastExpList";
        LastExpList le = (LastExpList) l;
        System.out.println(le.head.eval(t));
    }
}

abstract class Exp {
    abstract int eval(Table t);
}

class IdExp extends Exp {
    String id;
    IdExp(String i) {id=i;}

    int eval(Table t) {
        return t.lookup(id);
    }
}

class NumExp extends Exp {
    int num;
    NumExp(int n) {num=n;}

    int eval(Table t) {
        return num;
    }
}

class OpExp extends Exp {
    Exp left, right; int oper;
    final static int Plus=1,Minus=2,Times=3,Div=4;
    OpExp(Exp l, int o, Exp r) {left=l; oper=o; right=r;}

    int eval(Table t) {
        int v1 = left.eval(t);
        int v2 = right.eval(t);

        switch (oper) {
        case OpExp.Plus:
            return v1+v2;
        case OpExp.Minus:
            return v1-v2;
        case OpExp.Times:
            return v1*v2;
        case OpExp.Div:
            return v1 / v2;
        default:
            assert false: "nonrecgonized operator: " + oper;
        }
        return 0;
    }
}

class EseqExp extends Exp {
    Stm stm; Exp exp;
    EseqExp(Stm s, Exp e) {stm=s; exp=e;}

    int eval(Table t) {
        stm.eval(t);
        return exp.eval(t);
    }
}

abstract class ExpList {}

class PairExpList extends ExpList {
    Exp head; ExpList tail;
    public PairExpList(Exp h, ExpList t) {head=h; tail=t;}
}

class LastExpList extends ExpList {
    Exp head; 
    public LastExpList(Exp h) {head=h;}
}
