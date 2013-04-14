package RegAlloc;

import Graph.Node;
import Graph.Graph;
import Graph.NodeList;

abstract public class InterferenceGraph extends Graph {
    /**
     * Return the node related to the temp.
     */
    abstract public Node tnode(Temp.Temp temp);

    /**
     * Return the temp related to the node.
     */
    abstract public Temp.Temp gtemp(Node node);

    /**
     * What move instructions are associated with this graph?
     * This is a hint about what pairs of instructions may be allocated to
     * the same registers.
     */
    abstract public java.util.List<Move> moves();

    /**
     * An estimate of how many extra instructions would be executed if n
     * were kept in memory instead of in registers.
     */
    public int spillCost(Node node) {
        return 1;
    }

    /**
     * Print a human-readable dump for debugging.
     */
    public void show(java.io.PrintStream out) {
        for (NodeList p=nodes(); p!=null; p=p.tail) {
            // pirnt this node
            Node n = p.head;
            out.print(gtemp(n).toString());
            out.print(": ");

            // print the interference nodes of this node
            for(NodeList q = n.adj(); q!=null; q=q.tail) {
                out.print(gtemp(q.head).toString());
                out.print(" ");
            }
            out.println();
        }
    }
}
