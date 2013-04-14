package Graph;

public class Graph {
    public int nodecount=0;            // #nodes in this graph
    NodeList mynodes;           // nodes in this graph
    NodeList mylast;            // last node of "mynodes"

    /**
     * Return a list of all node in this graph.
     */
    public NodeList nodes() {
        return mynodes;
    } 

    /**
     * Create a new node in this graph.
     */
    public Node newNode() {
        return new Node(this);
    }

    /**
     * Make sure node n is this graph.
     */
    void check(Node n) {
        if (n.mygraph != this)
            throw new Error("Graph.addEdge using nodes from the wrong graph");
    }

    /**
     * Check if node a is in the list l.
     */
    static boolean inList(Node a, NodeList l) {
        for(NodeList p=l; p!=null; p=p.tail)
            if (p.head==a)
                return true;
        return false;
    }

    /**
     * Add an edge from->to to this graph.
     *
     * Pre-condition: from and to must be in this graph
     */
    public void addEdge(Node from, Node to) {
        check(from); check(to);
        if (from.goesTo(to)) return;
        to.preds=new NodeList(from, to.preds);
        from.succs=new NodeList(to, from.succs);
    }

    /**
     * Delete node a from list l.
     *
     * Pre-condition: l must not be null
     */
    NodeList delete(Node a, NodeList l) {
        if (l==null)
            throw new Error("Graph.rmEdge: edge nonexistent");
        else if (a==l.head)
            return l.tail;
        else
            return new NodeList(l.head, delete(a, l.tail));
    }

    /**
     * Delete the edge from->to from this graph.
     *
     * Pre-condition: the edge must exist already
     */
    public void rmEdge(Node from, Node to) {
        to.preds=delete(from,to.preds);
        from.succs=delete(to,from.succs);
    }

    /**
     * Print a human-readable dump for debugging.
     */
    public void show(java.io.PrintStream out) {
        for (NodeList p=nodes(); p!=null; p=p.tail) {
            // pirnt this node
            Node n = p.head;
            out.print(n.toString());
            out.print(": ");

            // print the successors of this node
            for(NodeList q=n.succ(); q!=null; q=q.tail) {
                out.print(q.head.toString());
                out.print(" ");
            }
            out.println();
        }
    }
}