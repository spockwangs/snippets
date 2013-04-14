package Symbol;

class Binder {
    Object value;
    Symbol prevtop;
    Binder tail;

    /*
     * Which scope is this binding in?.  0 represents the top scope, 1
     * represents the nested scope in 0, 2 the nested scope in 1 and so on.
     * Used to check redefinition in the same scope.
     */
    int scope;

    Binder(Object v, Symbol p, Binder t, int s) {
        value=v;
        prevtop=p;
        tail=t;
        scope = s;
    }
}

/**
 * The Table class is similar to java.util.Dictionary, except that
 * each key must be a Symbol and there is a scope mechanism.
 */


public class Table {

    private java.util.Dictionary dict = new java.util.Hashtable();
    private Symbol top;
    private Binder marks;
    private int currScope = 0;  // tracking current scope

    public Table(){}

    /**
     * Gets the object associated with the specified symbol in the Table.
     */
    public Object get(Symbol key) {
        Binder e = (Binder)dict.get(key);
        if (e==null) return null;
        else return e.value;
    }	

    /**
     * Puts the specified value into the Table, bound to the specified Symbol.
     */
    public void put(Symbol key, Object value) {
        dict.put(key, new Binder(value, top, (Binder)dict.get(key), currScope));
        top = key;
    }

    /**
     * Set the value of 'key' to 'value'.
     */
    public void set(Symbol key, Object value) {
        Binder e = (Binder) dict.get(key);
        if (e == null)
            return;
        dict.put(key, new Binder(value, e.prevtop, e.tail, e.scope));
    }
    
    /**
     * Remembers the current state of the Table.
     */
    public void beginScope() {
        assert (currScope >= 0) : "Scope error";
        currScope++;
        marks = new Binder(null,top,marks, currScope);
        top=null;
    }

    /** 
     * Restores the table to what it was at the most recent beginScope
     *	that has not already been ended.
     */
    public void endScope() {
        assert (currScope > 0) : "Scope error";
        currScope--;
        while (top!=null) {
            Binder e = (Binder)dict.get(top);
            if (e.tail!=null) dict.put(top,e.tail);
            else dict.remove(top);
            top = e.prevtop;
        }
        top=marks.prevtop;
        marks=marks.tail;
    }
  
    /**
     * Returns an enumeration of the Table's symbols.
     */
    public java.util.Enumeration keys() {return dict.keys();}

    /**
     * Check if 'key' has already been defined in current scope.
     */
    public boolean isRedefinition(Symbol key) {
        Binder b = (Binder) dict.get(key);

        assert (b == null || b.scope <= currScope) : "Scope error";
        
        if (b == null || b.scope != currScope)
            return false;
        else
            return true;
    }
}

