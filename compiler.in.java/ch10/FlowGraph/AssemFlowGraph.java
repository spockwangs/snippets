package FlowGraph;

import Temp.TempList;
import Temp.LabelList;
import Temp.Label;
import Graph.Node;

/**
 * This module constructs a control flow graph from a instruction list.
 * Each node in this graph represents an instruction.  If instruction m can
 * be followed by instruction n (either by a jump or by falling through),
 * then there will be an edge (m, n) in the graph.
 */
public class AssemFlowGraph extends FlowGraph {
    // A map from Graph.Node to Assem.Instr.
    private java.util.Dictionary<Node, Assem.Instr> mytable =
        new java.util.Hashtable<Node, Assem.Instr>();

    public AssemFlowGraph(Assem.InstrList intrs) {
        Node cur_node, pre_node, next_node;
                    
        cur_node = pre_node = next_node = null;

        /*
         * Make node for each instruction and add edges for fall-through
         * instructions (i.e. without jump targets which are considered later)
         */
        for (Assem.InstrList p = intrs; p != null; p = p.tail) {
            // make a node for the instruction
            cur_node = newNode();
            mytable.put(cur_node, p.head);

            // add an edge from pre node to this node if jump targets of pre node
            // is null
            if (pre_node != null && mytable.get(pre_node).jumps() == null) {
                addEdge(pre_node, cur_node);
            }

            pre_node = cur_node;
        }

        /*
         * Add edges for jump targets.
         */
        java.util.Enumeration<Node> nodes = mytable.keys();
        while (nodes.hasMoreElements()) {
            cur_node = nodes.nextElement();
            Assem.Instr ins = mytable.get(cur_node);
            Assem.Targets ts = ins.jumps();
            if (ts == null)
                continue;
            for (LabelList l = ts.labels; l != null; l = l.tail) {
                next_node = findNode(l.head);
                addEdge(cur_node, next_node);
            }
        }
    }

    /**
     * Return the node associated with a label instruction with the label
     * 'lab'.
     */
    private Node findNode(Label lab) {
        java.util.Enumeration<Node> nodes = mytable.keys();
        while (nodes.hasMoreElements()) {
            Node n = nodes.nextElement();
            Assem.Instr ins = mytable.get(n);
            if (ins instanceof Assem.LABEL &&
                ((Assem.LABEL) ins).label == lab)
                return n;
        }
        return null;
    }

    /**
     * Return the instruction associated with the node n.
     */
    public Assem.Instr instr(Node n) {
        return mytable.get(n);
    }

    /**
     * The set of temporaries defined by this instruction or block 
     */
    public TempList def(Node node) {
        Assem.Instr i = instr(node);
        if (i == null)
            return null;
        return instr(node).def();
    }

    /**
     * The set of temporaries used by this instruction or block 
     */
    public TempList use(Node node) {
        Assem.Instr i = instr(node);
        if (i == null)
            return null;
        return instr(node).use();
    }

    /**
     * True if this node represents a <strong>move</strong> instruction,
     * i.e. one that can be deleted if def=use. 
     */
    public boolean isMove(Node node) {
        Assem.Instr i = instr(node);
        if (i == null)
            throw new Error("bad node; not exist");
        return (i instanceof Assem.MOVE);
    }
}