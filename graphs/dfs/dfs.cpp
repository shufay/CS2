/* debugging example */

#include <iostream>
#include <vector>

using namespace std;

class Node
{
    int value;
    std::vector<Node*> edges;
    bool visited;

public:
    // insert constructors, destructors,
    // accessors, and mutators here
    Node();
    ~Node();
    int get_val();
    void set_val(int val);
    void print_edges();
    void add_edge(Node *edg);
    void rem_edge();
    bool dfs(int to_find);
};

Node::Node()
{
    value = 0;
    visited = false;
}

Node::~Node(){}

int Node::get_val()
{
    return value;
}

void Node::set_val(int val)
{
    value = val;
}

void Node::print_edges()
{
    if (edges.size() != 0)
    {
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            cout << "node " << value << " connected to: " << edges[i]->value << endl;
        }
    }

    else
    {
        cout << "node " << value << " connected to: " << "No edges" << endl;
    }
}

void Node::add_edge(Node *edg)
{
    edges.push_back(edg);
}

void Node::rem_edge()
{
    edges.pop_back();
}

// true indicates that the value was found, and false indicates that the value was not found.

/*
The dfs goes on forever if there is a cycle. This could be resolved by 
adding a member variable "visited" to each node so that it does not 
visit the same node twice. 
*/ 
bool Node::dfs(int to_find)
{
    if(this->value == to_find)
    {
        return true;
    }

    std::vector<Node*>::iterator i;
    this->visited = true;

    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        
        if (!(n->visited))
        {
            bool r = n->dfs(to_find);
            if(r)
            {
                return r;
            }
        }
    }

    return false;
}

int main(void)
{
    // Build cycle
    Node node0, node1, node2, node3, node4;

    node0.set_val(0);
    node1.set_val(1);
    node2.set_val(2);
    node3.set_val(3);
    node4.set_val(4);

    node0.add_edge(&node1); // 0->1
    node1.add_edge(&node2); // 1->2
    node2.add_edge(&node3); // 2->3
    node3.add_edge(&node4); // 3->4
    node4.add_edge(&node0); // 4->0

    node0.print_edges();
    node1.print_edges();
    node2.print_edges();
    node3.print_edges();
    node4.print_edges();

    cout << "search for 4: " << node0.dfs(4) << endl;

    return 0;

}