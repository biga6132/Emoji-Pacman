#include <iostream>
#include <vector>
#include "Player.h"
#include "Game.h"

int main(){
    std::cout << "Welcome to Emoji Pacman" << std::endl;
    std::string name;
    std::cout << "What is your Player's name:" << std::endl;
    std::cin >> name;
    Player *p = new Player(name,true);
    Game g = Game();
    std::vector<Player*> enemies;
    g.NewGame(p, enemies, 2);
    std::cout << g << std::endl;
    while (g.IsGameOver(p) == false)
    {
        std::cout << p->Stringify() << std::endl;
        g.TakeTurn(p, enemies);
        std::cout << g << std::endl;
    }
    std::cout << g.GenerateReport(p) << std::endl;
    
}