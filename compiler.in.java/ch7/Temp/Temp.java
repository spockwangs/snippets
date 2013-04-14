package Temp;

public class Temp  {
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
}

