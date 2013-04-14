package Graph;

public class Node {
    Graph mygraph;              // In which graph is I?
    public int mykey;
    NodeList succs;             // my successors
    NodeList preds;             // my predecessors

    private Node() { }

    /**
     * Make a node in graph g.
     */
    public Node(Graph g) {
        mygraph=g; 
        mykey= g.nodecount++;
        NodeList p = new NodeList(this, null);
        if (g.mylast==null)
            g.mynodes=g.mylast=p;
        else
            g.mylast = g.mylast.tail = p;
    }

    /**
     * Return my successors.
     */
    public NodeList succ() {
        return succs;
    }

    /**
     * Return my predecessors.
     */
    public NodeList pred() {
        return preds;
    }

    /**
     * Catenate 2 node list.
     */
    NodeList cat(NodeList a, NodeList b) {
        if (a==null)
            return b;
        else
            return new NodeList(a.head, cat(a.tail,b));
    }

    /**
     * Return a union of my successors and predecessors.
     */
    public NodeList adj() {
        return cat(succ(), pred());
    }

    /**
     * Return number of nodes in a list.
     */
    int len(NodeList l) {
        int i=0;
        for(NodeList p=l; p!=null; p=p.tail)
            i++;
        return i;
    }

    /**
     * Return number of my predecessors.
     */
    public int inDegree() {
        return len(pred());
    }

    /**
     * Return number of my successors.
     */
    public int outDegree() {
        return len(succ());
    }

    /**
     * Return sum of in-degree and out-degree.
     */
    public int degree() {
        return inDegree()+outDegree();
    } 

    /**
     * Is node n one of my successors?
     */
    public boolean goesTo(Node n) {
        return Graph.inList(n, succ());
    }

    /**
     * Is node n one of my predecessors?
     */
    public boolean comesFrom(Node n) {
        return Graph.inList(n, pred());
    }

    /**
     * Is node n one of my successors or of my predecessors?
     */
    public boolean adj(Node n) {
        return goesTo(n) || comesFrom(n);
    }

    public String toString() {
        return String.valueOf(mykey);
    }
}
