/*
 * table.java -- A simple symble table using single link.
 *
 * Author: wbb 
 * Time-stamp: <2010-06-08 14:31:24 wbb>
 */
 
class Table {
    String id;
    int value;
    Table tail;
    
    Table(String i, int v, Table t) {
        id = i;
        value = v;
        tail = t;
    }
    Table() {
        id = null;
    }
    
    /** Insert a new id-value pair into the table.
     *
     *  @param i the id
     *  @param v the value
     *  @return NONE
     */
    void update(String i, int v) {
        tail = this;
        id = i;
        value = v;
    }

    /** Lookup a vaule corresponding to the id.
     *
     *  @param i the id
     *  @return the value
     */
    int lookup(String i) {
        for (Table t = this; t.id != null; t = t.tail) {
            if (t.id == i)
                return t.value;
        }
        return 0;
    }
}
    