/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"
#include <algorithm>
#include <unordered_map>

#define LARGE 1000000

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              onMST and notOnMST are two vectors defined in
 *              GraphAlgorithms.hpp
 *              that you can use to store which nodes are both in/not in the
 *              MST. These are cleared at the start of the MST computation for 
 *              you. To access the nodes that a specific node connects to
 *              you, you can use the vector<Node *> edges which is part
 *              of the Node struct in structs.hpp
 *              You can compare two nodes to see if they are the same by
 *              comparing the id attribute of a Node.
 *              You can calculate distance from one node to another by calling
 *              the double distance(Node a) function of the Node struct.
 *              Whenever you decide to add an edge between two nodes
 *              to the MST, you can use the provided drawEdge function
 *              in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * OUTLINE
 * onMST.append(node0)
 * 
 * for node in graph:
 *  notOnMST.append(node)
 *
 * while len(notOnMST) != 0:
 *  dist = {}
 *
 *  for node in onMST:
 *      for nodes connected to node:
 *          if nodes in notOnMST:
 *              dist[node.distance(nodes)] = [node, nodes]
 * 
 *  min_node = dist[min(dist)]
 *  draw(min_node[0], min_node[1])
 *  onMST.append(min_node[1])
 *  notOnMST.remove(min_node[1])
 *
 */
void buildMSTPrim(Graph g, GraphApp *app) {
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());

    onMST.push_back(g.nodes[0]);

    for (unsigned int i = 1; i < g.nodes.size(); i++)
    {
        notOnMST.push_back(g.nodes[i]);
    }

    unordered_map<double, vector<Node*>> dist;

    // while there are remaning nodes
    while (notOnMST.size() != 0)
    {
        Node *node;
        
        // for node in MST
        for (unsigned int i = 0; i < onMST.size(); i++)
        {
            node = onMST[i];

            // for nodes connected to this node
            for (unsigned int j = 0; j < node->edges.size(); j++)
            {
                Node *node_connected = node->edges[j];

                // check if node in MST                
                bool in_tree = false;

                for (unsigned int k = 0; k < onMST.size(); k++)
                {
                    if (node_connected->id == onMST[k]->id)
                    {
                        in_tree = true;
                        break;
                    }
                }

                // if this node is not in MST, compute distance
                if (!in_tree)
                {   
                    double weight = node->distance(*node_connected);
                    vector<Node*> pair;
                    pair.push_back(node);
                    pair.push_back(node_connected);
                    dist[weight] = pair;
                }    
            }
        }

        // find node with minimum distance
        unordered_map<double, vector<Node*>>::iterator min_dist 
            = min_element(dist.begin(), dist.end());
        vector<Node*> node_min = min_dist->second; 
        drawEdge(node_min[0], node_min[1], g.edges, app, true);
        int ind;
    
        for (unsigned int i = 0; i < notOnMST.size(); i++)
        {
            if (node_min[1]->id == notOnMST[i]->id)
            {
                ind = i;
                break;
            }
        }
        
        onMST.push_back(node_min[1]);
        notOnMST.erase(notOnMST.begin() + ind);
        
        dist.clear();
    }
}

/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than
 *passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              You'll want to use a priority queue to determine which edges
 *              to add first. We've created the priority queue for you
 *              along with the compare function it uses. All you need to do
 *              is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 *              The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *              to be able to join trees later!
 *              To know which tree a node is in, use the which_tree attribute.
 *              You can still use the edges, distance, and id
 *              attributes of a Node.
 *              When connecting trees, you can call the
 *              kruskalFloodFill function
 *              defined in structs.hpp on a node to convert it and its
 *              MST connected nodes to a different tree number recursively.
 *              As in Prim's algorith, call drawEdge to add a connection between
 *              two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * OUTLINE
 * for edge in graph:
 *  edge_queue.push(edge)
 * 
 * while len(edge_queue) != 0:
 *  min_edge = edge_queue.top()
 *  
 * if min_edge not in MST:
 *  MST.append(min_edge)
 *  
 * edge_queue.pop()
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

        // each node begins as its own tree
        for (unsigned int i = 0; i < g.nodes.size(); i++)
        {
            g.nodes[i]->which_tree = i;
        }

        // add edges to priority queue
        for (unsigned int i = 0; i < g.edges.size(); i++)
        {
            KruskalEdge *edge = new KruskalEdge;
            edge->weight = g.edges[i]->weight;
            edge->u = g.edges[i]->a;
            edge->v = g.edges[i]->b;
            edge_queue.push(edge);
        }

        while (edge_queue.size() != 0)
        {   
            KruskalEdge *min_edge = edge_queue.top();

            // if min_edge does not create a cycle, connect
            if (min_edge->u->which_tree != min_edge->v->which_tree)
            {
                min_edge->u->kruskalFloodFill(min_edge->v->which_tree);
                min_edge->u->kruskal_edges.push_back(min_edge->v);
                min_edge->v->kruskal_edges.push_back(min_edge->u);
                drawEdge(min_edge->u, min_edge->v, g.edges, app, true);
            }            

            edge_queue.pop();
            delete min_edge;
        }

    for (unsigned int i = 0; i < g.nodes.size(); i++)
    {
        g.nodes[i]->kruskal_edges.clear();
    }
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 *        shortest path algorithm
 *
 * @param start Index of start node of path to find
 *              Can access the Node * element by using
 *              g.nodes[start]
 * @param end   Index of end node of path to find
 *              Can access the Node * element by using g.nodes[end]
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              You can use the distance_to_start attribute of the Node struct
 *              in structs.hpp to keep track of what the distance from each
 *              Node to the start node during computation
 *              You can use the previous attribute of the Node struct
 *              in structs.hpp to keep track of the path you are taking to
 *              later backtrack.
 *              To access the nodes that a specific node connects to you, you
 *              can use the vector<Node *> edges which is part of the Node struct
 *              in structs.hpp
 *              Whenever you decide to add an edge between two nodes
 *              to the MST, you can use the provided drawEdge function in
 *              GraphAlgorithms.cpp
 *
 * OUTLINE
 * source.distance = 0
 * nodes = {source: source.distance}
 * 
 * for node != source:
 *  node.distance = large_num
 *  nodes[node] = node.distance
 *
 * while len(nodes) != 0:
 *  min_node = nodes[min(node.distance)]
 *  
 *  for neighbours to node:
 *      if neighbours.distance > 
 *          min_node.distance + weight(min_node, neighbours):
 *              neighbours.distance = min_node.distance + weight(min_node, neighbours)
 *              neighbours.prev = min_node
 *  
 *  nodes.remove(min_node)
 *
 * return nodes
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    Node* source = g.nodes[start];
    source->distance_to_start = 0;
    source->previous = nullptr;

    dist.push_back(source->distance_to_start);
    nodes.push_back(source);

    for (unsigned int i = 0; i < g.nodes.size(); i++)
    {
        if (g.nodes[i]->id != source->id)
        {
            g.nodes[i]->distance_to_start = LARGE;
            g.nodes[i]->previous = nullptr;
            nodes.push_back(g.nodes[i]);
            dist.push_back(g.nodes[i]->distance_to_start);
        }
    }

    while (nodes.size() != 0)
    {
        // find node with minimum edge weight
        vector<double>::iterator it = min_element(dist.begin(), dist.end());
        int ind = it - dist.begin();
        Node *min_node = nodes[ind];
        
            // investigate its neighbours
            for (unsigned int j = 0; j < min_node->edges.size(); j++)
            {
                Node *neighbour = min_node->edges[j];
                double weight;

                // check if node has been investigated
                bool go = false;

                for (unsigned int i = 0; i < nodes.size(); i++)
                {
                    if (neighbour->id == nodes[i]->id)
                    {
                        go = true;
                        break;
                    }
                }

                // if it has not been investigated...
                if (go)
                {
                    for (unsigned int k = 0; k < g.edges.size(); k++)
                    {
                        // get edge weight between nodes
                        if (((g.edges[k]->a == min_node) && (g.edges[k]->b == neighbour)) ||
                            ((g.edges[k]->b == min_node) && (g.edges[k]->a == neighbour)))
                        {
                            weight = g.edges[k]->weight;
                        }
                    }
                
                    // if found a smaller distance, set this new distance
                    if (neighbour->distance_to_start > min_node->distance_to_start + weight)
                    {
                        neighbour->distance_to_start = min_node->distance_to_start + weight;
                        neighbour->previous = min_node;

                        // update dist
                        for (unsigned int i = 0; i < nodes.size(); i++)
                        {
                            if (neighbour->id == nodes[i]->id)
                            {
                                dist[i] = neighbour->distance_to_start;
                            }
                        }
                    }
                } 
            }

            nodes.erase(nodes.begin() + ind);
            dist.erase(it);
        
    }

    Node *temp = g.nodes[end];

    while (temp != nullptr)
    {
        drawEdge(temp, temp->previous, g.edges, app, false);
        temp = temp->previous;     
    }
} 

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 *          nodes to connect given. This is done by iterating through the edges
 *          to find the correct edge given the nodes.
 *
 * @param pt1   One side of edge to draw
 * @param pt2   Other side of edge to draw
 * @param edges Vector of edges in the graph
 * @param app   Graphics application class
 * @param mst   True if we are adding edge to MST, False if we are adding edge
 *              to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
