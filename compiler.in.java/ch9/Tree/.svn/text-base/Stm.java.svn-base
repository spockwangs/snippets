package Tree;
abstract public class Stm {
    /**
     * Subexpression-extraction method for each kind of Stm.
     * It is used by Canon.Canon.do_stm() to eliminate ESEQ nodes in the subexpressions.
     */
	abstract public ExpList kids();

    /**
     * Subexpression-insertion method for each kind of Stm.
     * Given an ESEQ-clean version of each subexpression, this builds a new
     * version of the statement.
     */
	abstract public Stm build(ExpList kids);
}

