package RegAlloc;

import Graph.Node;
import Graph.NodeList;
import Temp.TempList;
import Temp.Temp;
import FlowGraph.FlowGraph;

/**
 * This module implements the function of liveness analysis.  It constructs
 * a interference graph from a constrol flow graph.
 *
 * @see Graph.InterferenceGraph 
 */
public class Liveness extends InterferenceGraph {
    // live-out sets for each node
    private java.util.Dictionary<Node, TempList> livemap =
        new java.util.Hashtable<Node, TempList>();

    // live-in sets for each node
    private java.util.Dictionary<Node, java.util.Set<Temp> > livein =
        new java.util.Hashtable<Node, java.util.Set<Temp> >();
    // live-out sets for each node
    private java.util.Dictionary<Node, java.util.Set<Temp> > liveout =
        new java.util.Hashtable<Node, java.util.Set<Temp> >();

    private java.util.Dictionary<Node, Temp> node2tempMap =
        new java.util.Hashtable<Node, Temp>();
    private java.util.Dictionary<Temp, Node> temp2nodeMap =
        new java.util.Hashtable<Temp, Node>();

    private java.util.List<Move> movelist = new java.util.LinkedList<Move>();
    
    public Liveness(FlowGraph flow_graph) {
        /*
         * Calculate the live-out and live-in sets for each node.
         */

        // Init live-in sets and live-out sets to empty set.
        for (NodeList p = flow_graph.nodes(); p != null; p = p.tail) {
            livein.put(p.head, new java.util.TreeSet<Temp>());
            liveout.put(p.head, new java.util.TreeSet<Temp>());
        }
        
        int in_size, out_size;
        boolean done;           // are we done?
        do {
            done = true;
            for (NodeList p = flow_graph.nodes(); p != null; p = p.tail) {
                Node n = p.head; // current node

                // Record initial size of in-set and out-set.
                in_size = in(n).size();
                out_size = out(n).size();

                // update in-set of node n
                java.util.Set<Temp> use_set = setFromList(flow_graph.use(n));
                java.util.Set<Temp> def_set = setFromList(flow_graph.def(n));
                livein.put(n, union(use_set,
                                    diff(out(n), def_set)));

                // update out-set of node n
                java.util.Set<Temp> out_set =
                    new java.util.TreeSet<Temp>();
                for (NodeList q = n.succ(); q != null; q = q.tail) {
                    out_set.addAll(in(q.head));
                }
                liveout.put(n, out_set);

                // Do we reach a fixed point for this node?
                if (in_size != in(n).size() ||out_size != out(n).size()) {
                    done = false;
                }
            }
        } while (!done);

        /*
         * Calculate interference graph from live-in and live-out sets.
         */
        for (NodeList p = flow_graph.nodes(); p != null; p = p.tail) {
            Node n = p.head;
            java.util.Iterator<Temp> iter_liveout = out(n).iterator();

            // add interference edges
            for (TempList q = flow_graph.def(n); q != null; q = q.tail) {
                addTemp(q.head);
                while (iter_liveout.hasNext()) {
                    Temp t = iter_liveout.next();
                    if (flow_graph.isMove(n)) {
                        // add this move instruction
                        addMoveInstr(flow_graph.use(n).head, q.head);

                        // special processing for move instruction
                        if (t == flow_graph.use(n).head)
                            continue;
                    } else {
                        if (t != q.head) 
                            addInterferenceEdge(q.head, t);
                    }
                }
            }

            for (TempList q = flow_graph.use(n); q != null; q = q.tail) {
                addTemp(q.head);
            }
        }
    }

    
    /**
     * Return the node related to the temp.  If none return null.
     */
    public Node tnode(Temp temp) {
        return temp2nodeMap.get(temp);
    }

    /**
     * Return the temp related to the node.  If none return null.
     */
    public Temp gtemp(Node node) {
        return node2tempMap.get(node);
    }

    /**
     * What move instructions are associated with this graph?
     * This is a hint about what pairs of instructions may be allocated to
     * the same registers.
     *
     * @see RegAlloc.Move
     */
    public java.util.List<Move> moves() {
        return movelist;
    }

    /**
     * Add interference edges (t1, t2).
     */
    private void addInterferenceEdge(Temp t1, Temp t2) {
        Node n1, n2;
        n1 = tnode(t1);
        if (n1 == null) {
            n1 = newNode();
            temp2nodeMap.put(t1, n1);
            node2tempMap.put(n1, t1);
        }
        n2 = tnode(t2);
        if (n2 == null) {
            n2 = newNode();
            temp2nodeMap.put(t2, n2);
            node2tempMap.put(n2, t2);
        }
        
        addEdge(n1, n2);
    }

    private void addTemp(Temp t) {
        Node n = tnode(t);
        if (n == null) {
            n = newNode();
            temp2nodeMap.put(t, n);
            node2tempMap.put(n, t);
        }
    }
    
    /**
     * Return in-set of node 'n'.
     */
    private java.util.Set<Temp> in(Node n) {
        return livein.get(n);
    }

    /**
     * Return out-set of node 'n'.
     */
    private java.util.Set<Temp> out(Node n) {
        return liveout.get(n);
    }

    private java.util.Set<Temp> setFromList(TempList l) {
        java.util.Set<Temp> set = new java.util.TreeSet<Temp>();
        for (; l != null; l = l.tail)
            set.add(l.head);
        return set;
    }

    /**
     * Return a union of l1 and l2, and destroy l1 and l2.
     */
    private java.util.Set<Temp> union(java.util.Set<Temp> s1,
                                      java.util.Set<Temp> s2) {
        s1.addAll(s2);
        return s1;
    }

    /**
     * Return a difference set of l1 and l2, and destroy l1 and l2.
     */
    private java.util.Set<Temp> diff(java.util.Set<Temp> s1,
                                     java.util.Set<Temp> s2) {
        s1.removeAll(s2);
        return s1;
    }

    /**
     * Add a move instruction to the movelist.
     */
    private void addMoveInstr(Temp src, Temp dst) {
        /*
         * If the temps src or dst does not exist create it.
         */

        Node sn, dn;
        sn = tnode(src);
        if (sn == null) {
            sn = newNode();
            temp2nodeMap.put(src, sn);
            node2tempMap.put(sn, src);
        }
        dn = tnode(dst);
        if (dn == null) {
            dn = newNode();
            temp2nodeMap.put(dst, dn);
            node2tempMap.put(dn, dst);
        }

        // add the move instruction
        movelist.add(new Move(sn, dn));
    }
}