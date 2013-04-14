
package Frame;

public interface Machine {
    abstract public Tree.Exp externalCall(String func, Tree.ExpList args);
    abstract public int wordSize();
    abstract public Temp.Temp FP();
    abstract public Temp.Temp RV();
}