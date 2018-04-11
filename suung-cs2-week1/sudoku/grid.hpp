# include<string>
using namespace std;
/*
 * @brief A Grid class, representing the game board.
 */ 

class Grid
{
    private: 
        char grid[9][9];
        char grid_o[9][9];

    public:
        Grid();
        ~Grid() {};
        bool loadBoard(string filename);
        void display();
        bool isComplete();
        bool checkValid(int x, int y, char val);
        void writeNum(int x, int y, char val);
        void undoNum(int x, int y);

};
