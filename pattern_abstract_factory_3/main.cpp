#include "gen.h"
#include "MazeGame.h"
#include "BombedMazeGame.h"
#include "MazeFactory.h"
#include <ctime>
#include <cstdlib>w
using namespace std;

int main() 
{

    MazeGame* m_MazeGame = new MazeGame();
    MazeFactory* m_MazeFactory = new MazeFactory();
    // Maze* m_Maze[5];
    std::vector<Maze*> m_Maze(5);

    // seed rand
    srand(time(NULL));
    // create 5 mazes
    for (int i = 0; i < 5; i++) 
    {
        m_Maze[i] = m_MazeGame->CreateMaze(*m_MazeFactory);
        // m_Maze.push_back() m_MazeGame->CreateMaze(*m_MazeFactory);
        m_Maze[i]->PrintId();
    }
    
    system("PAUSE");
    return 0;
}
