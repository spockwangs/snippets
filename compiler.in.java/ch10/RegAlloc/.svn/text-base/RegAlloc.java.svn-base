package RegAlloc;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import java.util.HashMap;
import java.util.Map;
import Graph.Node;
import Graph.NodeList;

public class RegAlloc implements Temp.TempMap {
    public Assem.InstrList instrs;
    private Color temp_map;
    
    public RegAlloc(Frame.Frame f, Assem.InstrList il) {
        instrs = il;
        while (true) {
            /*
             * Do liveness analysis to assemble instructions to generate an
             * interference graph.
             */

            FlowGraph.FlowGraph flow_graph = new FlowGraph.AssemFlowGraph(instrs);
            Liveness interfere_graph = new Liveness(flow_graph);

            /*
             * Do graph coloring.
             */
            temp_map = new Color(interfere_graph, f, f.registers());

            /*
             * If spilled nodes exist, do it again after rewriting the progam.
             */

            if (temp_map.spills().isEmpty())
                break;
            instrs = temp_map.rewriteProgram(instrs);
        }
    }

    /**
     * Return the allocated register of this temporary register.
     */
    public String tempMap(Temp.Temp temp) {
        return temp_map.tempMap(temp);
    }
}


/**
 * This module implements the graph coloring algorithm.
 */
class Color implements Temp.TempMap {
    /*
     * The following list are always mutually disjoint and every node is in
     * exactly one of the lists.
     */

    private List<Node> precolored = new LinkedList<Node>();
    private List<Node> initial = new LinkedList<Node>();
    private List<Node> simplifyWorklist = new LinkedList<Node>();
    private List<Node> freezeWorklist = new LinkedList<Node>();
    private List<Node> spillWorklist = new LinkedList<Node>();
    private List<Node> spilledNodes = new LinkedList<Node>();
    private List<Node> coalescedNodes = new LinkedList<Node>();
    private List<Node> coloredNodes = new LinkedList<Node>();
    private Stack<Node> selectStack = new Stack<Node>();

    /*
     * The following are five sets of move instructions, and every move
     * instruction is in exactly one of these sets.
     */

    private List<Move> coalescedMoves = new LinkedList<Move>();
    private List<Move> constrainedMoves = new LinkedList<Move>();
    private List<Move> frozenMoves = new LinkedList<Move>();
    private List<Move> worklistMoves = new LinkedList<Move>();
    private List<Move> activeMoves = new LinkedList<Move>();

    /*
     * Other data structures.
     */

    // adjacency list representation of interference graph
    private Map<Node, List<Node> > adjList = new HashMap<Node, List<Node> >();

    private int[][] adjSet;
    
    // current degree of each node
    private Map<Node, Integer> degree = new HashMap<Node, Integer>();

    // list move instructions associated with this node
    private Map<Node, List<Move> > moveList = new HashMap<Node, List<Move> >();

    // coalesced nodes
    private Map<Node, Node> alias = new HashMap<Node, Node>();

    // color chosen for each node
    private Map<Node, Temp.Temp> color = new HashMap<Node, Temp.Temp>();

    // # of availabe machine registers
    private int K;

    private Temp.TempList registers;
    private Temp.TempMap initial_alloc;
    private InterferenceGraph graph;
    /**
     * Constructor
     *
     * @param ig interference graph
     * @param initial precolored nodes
     * @param available registers of the target machine
     */
    public Color(InterferenceGraph ig, Temp.TempMap init, Temp.TempList registers) {
        K = registers.size();
        this.registers = registers;
        this.initial_alloc = init;
        this.graph = ig;
        
        build(ig, init);
        makeWorkList();
        do {
            if (!simplifyWorklist.isEmpty())
                simplify();
            else if (!worklistMoves.isEmpty())
                coalesce();
            else if (!freezeWorklist.isEmpty())
                freeze();
            else if (!spillWorklist.isEmpty())
                selectSpill();
        } while (!simplifyWorklist.isEmpty() ||
                 !worklistMoves.isEmpty() ||
                 !freezeWorklist.isEmpty() ||
                 !spillWorklist.isEmpty());
        assignColors();
    }

    /**
     * Return a list of spilled nodes, or null if none.
     */
    public List<Node> spills() {
        return spilledNodes;
    }

    /**
     * Return the allocated register of this temporary register.
     */
    public String tempMap(Temp.Temp t) {
        t = color.get(graph.tnode(t));
        return initial_alloc.tempMap(t);
    }

    /**
     * Constructs adjacency list representation (adjList) and bit matrix (adjSet)
     * representation of the interference graph and also initialize the
     * 'worklistMoves' to contain all the moves in the program.
     *
     * @modify adjList, initial, degree, worklistMoves, moveList
     */
    private void build(InterferenceGraph graph, Temp.TempMap initialMap) {
        adjSet = new int[graph.nodecount][graph.nodecount];
        
        for (NodeList l = graph.nodes(); l != null; l = l.tail) {
            Node n = l.head;
            if (initialMap.tempMap(graph.gtemp(n)) != null) {
                // n is precolored
                precolored.add(n);
                color.put(n, graph.gtemp(n));
            } else {            // n is not precolored
                adjList.put(n, new LinkedList<Node>());
                for (NodeList p = n.adj(); p != null; p = p.tail) {
                    adjList.get(n).add(p.head);
                }
                degree.put(n, new Integer(n.degree()));
                initial.add(n);
            }
            for (NodeList p = n.adj(); p != null; p = p.tail) {
                adjSet[n.mykey][p.head.mykey] = 1;
                adjSet[p.head.mykey][n.mykey] = 1;
            }
        }

        worklistMoves = graph.moves();
        for (Move m : worklistMoves) {
            if (moveList.get(m.src) == null) {
                moveList.put(m.src, new LinkedList());
            }
            moveList.get(m.src).add(new Move(m.src, m.dst));

            if (moveList.get(m.dst) == null) {
                moveList.put(m.dst, new LinkedList());
            }
            moveList.get(m.dst).add(new Move(m.src, m.dst));
        }
    }

    /**
     * Is there an edge between n1 and n2?
     */
    private boolean isAdjacency(Node n1, Node n2) {
        assert n1 != null && n2 != null;

        if (adjSet[n1.mykey][n2.mykey] == 1)
            return true;
        else
            return false;
    }

    /**
     * Initialize various worklists.
     *
     * @modify spillWorklist, freezeWorklist, simplifyWorklist
     */
    private void makeWorkList() {
        for (Node n : initial) {
            if (degree.get(n).intValue() >= K) {
                spillWorklist.add(n);
            } else if (moveRelated(n)) {
                freezeWorklist.add(n);
            } else {
                simplifyWorklist.add(n);
            }
        }
        initial.clear();
    }
    
    /**
     * Rewrite the program to allocate memory locations for each spilled nodes.
     */
    Assem.InstrList rewriteProgram(Assem.InstrList instrs) {
        // TODO
        return null;
    }

    private void simplify() {
        assert !simplifyWorklist.isEmpty();

        Node n = simplifyWorklist.remove(0);
        selectStack.push(n);
        for (Node m : adjacent(n)) {
            decrementDegree(m);
        }
    }

    /**
     * @precondition worklistMoves is not empty
     */
    private void coalesce() {
        Move m = worklistMoves.remove(0);
        Node x, y, u, v;
        x = getalias(m.src);
        y = getalias(m.dst);
        if (precolored.contains(y)) {
            u = y;
            v = x;
        } else {
            u = x;
            v = y;
        }

        if (u == v) {
            coalescedMoves.add(m);
            addWorkList(u);
        } else if (precolored.contains(v) && isAdjacency(u, v)) {
            constrainedMoves.add(m);
            addWorkList(u);
            addWorkList(v);
        } else {
            if (precolored.contains(u)) {
                java.util.Iterator<Node> iter = adjacent(v).iterator();
                while (iter.hasNext()) {
                    if (!OK(iter.next(), u))
                        break;
                }
                if (!iter.hasNext()) {
                    coalescedMoves.add(m);
                    combine(u, v);
                    addWorkList(u);
                } else {
                    activeMoves.add(m);
                }
            } else {
                List<Node> l = adjacent(u);
                l.addAll(adjacent(v));
                if (conservative(l)) {
                    coalescedMoves.add(m);
                    combine(u, v);
                    addWorkList(u);
                } else {
                    activeMoves.add(m);
                }
            }
        }
    }

    /**
     * @precondition freezeWorklist is not empty
     */
    private void freeze() {
        assert !freezeWorklist.isEmpty();
        
        Node u = freezeWorklist.remove(0);
        simplifyWorklist.add(u);
        freezeMoves(u);
    }

    /**
     * @precondition spillWorklist is not empty
     */
    private void selectSpill() {
        assert !spillWorklist.isEmpty();
        
        Node m = spillWorklist.remove(0);
        simplifyWorklist.add(m);
        freezeMoves(m);
    }

    private void assignColors() {
        while (!selectStack.empty()) {
            Node n = selectStack.pop();
            List<Temp.Temp> okColors = initColor(registers);
            for (Node w : adjList.get(n)) {
                if (coloredNodes.contains(getalias(w)) ||
                    precolored.contains(getalias(w))) {
                    okColors.remove(color.get(getalias(w)));
                }
            }
            if (okColors.isEmpty()) {
                spilledNodes.add(n);
            } else {
                coloredNodes.add(n);
                color.put(n, okColors.remove(0));
            }
        }
        for (Node n : coalescedNodes) {
            color.put(n, color.get(getalias(n)));
        }
    }

    /**
     * Is this node related with move?
     */
    private boolean moveRelated(Node n) {
        return (nodeMoves(n).isEmpty() == false);
    }

    /**
     * Return a new list of nodes adjacent to node 'n'.
     */
    private List<Node> adjacent(Node n) {
        assert n != null;

        LinkedList<Node> r = new LinkedList<Node>(adjList.get(n));
        r.removeAll(selectStack);
        r.removeAll(coalescedNodes);
        return r;
    }

    private List<Move> nodeMoves(Node n) {
        assert n != null;

        LinkedList<Move> r = new LinkedList<Move>();
        List<Move> moves = moveList.get(n);
        if (moves == null)
            return r;
        for (Move m : moves) {
            if (activeMoves.contains(m) || worklistMoves.contains(m)) {
                r.add(m);
            }
        }
        return r;
    }

    private void decrementDegree(Node n) {
        if (precolored.contains(n))
            return;
        
        Integer i = degree.get(n);
        degree.put(n, i-1);

        int d = i.intValue();
        if (d == K) {
            List<Node> nodes = adjacent(n);
            nodes.add(n);
            enableMoves(nodes);
            spillWorklist.remove(n);
            if (moveRelated(n)) {
                freezeWorklist.add(n);
            } else {
                simplifyWorklist.add(n);
            }
        }
    }

    private void enableMoves(List<Node> nodes) {
        for (Node node : nodes) {
            for (Move m : nodeMoves(node)) {
                if (activeMoves.contains(m)) {
                    activeMoves.remove(m);
                    worklistMoves.add(m);
                }
            }
        }
    }

    private void addWorkList(Node u) {
        if (!precolored.contains(u) && !moveRelated(u) && degree.get(u) < K) {
            freezeWorklist.remove(u);
            simplifyWorklist.add(u);
        }
    }

    private boolean OK(Node t, Node r) {
        if (precolored.contains(t) || precolored.contains(t) || isAdjacency(t, r))
            return true;
        else
            return false;
    }

    private boolean conservative(List<Node> nodes) {
        int k = 0;
        for (Node n : nodes) {
            if (precolored.contains(n) || degree.get(n) >= K)
                k++;
        }
        return k < K;
    }

    private Node getalias(Node n) {
        assert n != null;
        
        if (coalescedNodes.contains(n)) {
            return getalias(alias.get(n));
        }
        return n;
    }

    private void combine(Node u, Node v) {
        assert u != null && v != null;

        if (freezeWorklist.contains(v)) {
            freezeWorklist.remove(v);
        } else {
            spillWorklist.remove(v);
        }
        coalescedNodes.add(v);
        alias.put(v, u);
        moveList.get(u).addAll(moveList.get(v));
        for (Node t : adjacent(v)) {
            addEdge(t, u);
            decrementDegree(t);
        }
        if (freezeWorklist.contains(u) && degree.get(u) >= K) {
            freezeWorklist.remove(u);
            spillWorklist.add(u);
        }
    }

    private void addEdge(Node u, Node v) {
        assert u != null && v != null;

        if (!isAdjacency(u, v) && u != v) {
            adjSet[u.mykey][v.mykey] = 1;
            adjSet[v.mykey][u.mykey] = 1;
            if (!precolored.contains(u)) {
                adjList.get(u).add(v);
                degree.put(u, degree.get(u)+1);
            }
            if (!precolored.contains(v)) {
                adjList.get(v).add(u);
                degree.put(v, degree.get(v)+1);
            }
        }
    }

    private void freezeMoves(Node u) {
        assert u != null;

        Node v;
        for (Move m : nodeMoves(u)) {
            Node x = m.src;
            Node y = m.dst;
            if (getalias(y) == getalias(u)) {
                v = getalias(x);
            } else {
                v = getalias(y);
            }
            activeMoves.remove(m);
            frozenMoves.add(m);
            if (nodeMoves(v).isEmpty() && degree.get(v) < K) {
                freezeWorklist.remove(v);
                simplifyWorklist.add(v);
            }
        }
    }

    private List<Temp.Temp> initColor(Temp.TempList regs) {
        List<Temp.Temp> r = new LinkedList<Temp.Temp>();
        for (; regs != null; regs = regs.tail) {
            r.add(regs.head);
        }
        return r;
    }
}