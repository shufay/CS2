/**
 * Linked list with function to check if there is a loop in the list.
 *
 * Member function List::loop() is the function checking for a loop.
 * List::make_loop() makes a loop in the list.
 *
 * To run: 
 * Type 'g++ --std=c++11 -o loop loop.cpp' in terminal and then type
 * './loop'. 
 *
 * main() creates a list and runs loop() on it. 
 * A loop is the created with make_loop(). 
 * loop() is ran on the list again. 
 *
 * All results are printed to the terminal.
 *
 */

#include <iostream>

using namespace std;

/**
 * A class defining the shell of a linked list data structure.
 */
class List
{

/**
 * Public methods accessible by external code.
 */
public:
    List();
    ~List();
    void insert(int item);
    void printList();
    bool loop();
    void make_loop();

/**
 * Private data, including structure definition and class variables.
 */
private:
    struct Node
    {
        int data;
        Node *next;

        /**
         * Constructor for a node structure.
         */
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int num_elements;
};

/**
 * List constructor.
 */
List::List()
{
    head = nullptr;
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List()
{
    // TODO: Write the destructor so that this code does not leak memory!
    Node *temp = head;

    for (int i = 0; i < num_elements; ++i)
    {
        delete temp;
        temp = temp->next;
    }
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }

    else
    {
        head = new Node(item, nullptr);
        num_elements++;
    }

    return;
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

/* 
 * loop		Checks if list is a loop. Returns 0 if there is no loop, 
 *          1 if there is.
 *
 * Algorithm has a time complexity of O(n) because it loops through
 * the list, checking if there exists a Node with its 'next' as a 
 * nullptr. Space complexity is O(1) since it only stores one 
 * variable temp.
 */
bool List::loop()
{
	Node *temp = head;

	for (int i = 0; i < num_elements; i++)
	{
		temp = temp->next;

		if (temp == nullptr)
		{
			return false;
		}
	}

	// If no nullptr found, then there is a loop.
	return true;
}


/*
 * make_loop()		Makes a loop in list.
 */
void List::make_loop()
{
	// Set up a pointer to get to end of current list
    Node *temp = head;

    for (int i = 0; i < num_elements - 1; ++i)
    {
        temp = temp->next;
    }
    // temp now points to node at end of list

    // Let last node point to first node.
    temp->next = head;
}

int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 1; i < 10; ++i)
    {
        lst.insert(i);
    }

    cout << "Original List:" << endl;
    lst.printList();

    cout << endl;
    cout << "Loop: " << lst.loop() << endl;

    cout << "Making Loop..." << endl;
    cout << endl;
    lst.make_loop();
    cout << "Loop: " << lst.loop() << endl;

    return 0;
}
