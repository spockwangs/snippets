package Canon;

public class BasicBlocks {
    public StmListList blocks;  // list of basic blocks
    public Temp.Label done;     // label for epilogue

    private StmListList lastBlock; // track current basic block
    private Tree.StmList lastStm;  // last statement of current basic block

    public BasicBlocks(Tree.StmList stms) {
        done = new Temp.Label();
        mkBlocks(stms);
    }

    /**
     * Add a statement s to the end of 'lastStm'.
     */
    private void addStm(Tree.Stm s) {
        lastStm.tail = new Tree.StmList(s,null);
        lastStm = lastStm.tail;
    }

    /**
     * Expand current basic block or make a new basic block.
     */
    private void doStms(Tree.StmList l) {
        if (l==null) 
            doStms(new Tree.StmList(new Tree.JUMP(done), null));
        else if (l.head instanceof Tree.JUMP 
                 || l.head instanceof Tree.CJUMP) {
            addStm(l.head);
            mkBlocks(l.tail);
        } else if (l.head instanceof Tree.LABEL)
            // If not ending with a JUMP or CJUMP, add a JUMP to the next
            // block's label
            doStms(new Tree.StmList(new Tree.JUMP(((Tree.LABEL)l.head).label), l));
        else {
            addStm(l.head);
            doStms(l.tail);
        }
    }

    /**
     * Add basic blocks to the end of 'blocks'.
     */
    void mkBlocks(Tree.StmList l) {
        if (l==null)
            return;
        else if (l.head instanceof Tree.LABEL) {
            lastStm = new Tree.StmList(l.head,null);
            if (lastBlock==null) // first time
                lastBlock= blocks= new StmListList(lastStm,null);
            else {              // append a new basic block
                lastBlock = lastBlock.tail = new StmListList(lastStm,null);
            }
            doStms(l.tail);
        } else {
            // If witout a label at the beginning, add a new label.
            mkBlocks(new Tree.StmList(new Tree.LABEL(new Temp.Label()), l));
        }
    }
}
