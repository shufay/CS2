#include "grid.hpp"

/*
 * @brief A Game class, holding the game state.
 */

class Game
{
    public:
        int moves;
        Grid myGrid;

        Game();
        ~Game() {};
        void getMove();
        void Run();

};

