
package Mips;

public class MipsMachine implements Frame.Machine {
    /**
     * Call external functions.
     */
    public Tree.Exp externalCall(String func, Tree.ExpList args) {
        return new Tree.CALL(new Tree.NAME(new Temp.Label(func)), args);
    }

    /**
     * Natural word size (in bytes) of this machine.
     */
    public int wordSize() {
        return 4;
    }

    public Temp.Temp FP() {
        return new Temp.Temp("sp");
    }

    public Temp.Temp RV() {
        return new Temp.Temp("eax");
    }
}