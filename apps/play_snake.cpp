#include <iostream>
#include <ostream>

#include "env/SnakeEnv.hpp"
#include "utils/Logger.hpp"

int main()
{
    SnakeEnv env(10,1000);
    bool game = true;
    env.reset();
    while (game) {
        Index choice = 0;
        std::cout << "Score : " << env.get_score() << std::endl;
        env.render();
        do {
            std::cout << "\nChoisissez votre prochaine action (0 : haut ; 1 : droite ; 2 : bas ; 3 : gauche) : ";
            std::cin >> choice;
            if (choice < 0 || choice > 3) {
                std::cout << "Erreur dans la saisie de l'action\n" << std::endl;
            }
        }while(choice < 0 || choice > 3);
        StepResult result = env.step(choice);
        game = !(result.end_step);
        if (game) {
            clear();
        }
    }
    std::cout << "Vous avez perdu avec un score de : " << env.get_score() << std::endl;
    return 0;
}
