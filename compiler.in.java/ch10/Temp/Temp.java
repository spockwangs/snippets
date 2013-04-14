package Temp;

/**
 * This class implements a temporary register used by IR.
 */
public class Temp implements java.lang.Comparable<Temp>  {
    private static int count;
    private int num;
    private String reg;

    public Temp() { 
        num = count++;
        reg = "t" + num;
    }

    public Temp(String r) {
        reg = r;
    }
    
    public String toString() {
        return reg;
    }

    public int compareTo(Temp t) {
        return reg.compareTo(t.reg);
    }
}

