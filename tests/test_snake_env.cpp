#include "TestRunner.hpp"
#include "env/SnakeEnv.hpp"

void test_snake_env(TestRunner &runner) {
    SnakeEnv env(10,12,7);

    runner.section("Test dimension");

    runner.check_values(11,env.get_observation_size(),"Dimension observation");
    runner.check_values(4,env.get_action_count(), "Nombre d'actions");

    runner.section("Test matrice observation après reset");
    Matrix obs = env.reset();
    runner.check_values(1,obs.get_row(),"Nombre de lignes");
    runner.check_values(11,obs.get_column(),"Nombre de colonnes");
    bool direction_init = obs.get_value(0,3) == 1 && obs.get_value(0,4) == 0 && obs.get_value(0,5) == 0 && obs.get_value(0,6) == 0;
    runner.check_values(true,direction_init,"Direction initiale");

    runner.section("Test deplacement (sans demi-tour)");
    Point p1 = env.get_position_head();
    env.step(0);
    Point p2 = env.get_position_head();

    runner.check_values(true ,p1 != p2, "Déplacement");

    StepResult result(Matrix(1,11),0,false);
    runner.section("Test mort par le mur");
    for (int i = 0; i < 5; i++) {
        result = env.step(0);
    }

    runner.check_values(true, result.end_step, "Game over");
    runner.check_values(true, result.reward <= 0, "Récompenses négative");

    runner.section("Test demi-tour refusé");
    obs = env.reset();
    p1 = env.get_position_head();
    result = env.step(2);
    p2 = env.get_position_head();

    runner.check_values(true ,(p1.x == p2.x) && (p1.y-1 == p2.y), "Demi-tour refusé");
    runner.check_values(false, result.end_step, "Serpent toujours en vie");

    runner.section("Fin de boucle infini");
    obs = env.reset();

    for (int i = 0; i < 3; i++) {
        result = env.step(0);
    }
    for (int i = 0; i < 3; i++) {
        result = env.step(1);
    }
    for (int i = 0; i < 3; i++) {
        result = env.step(2);
    }
    for (int i = 0; i < 3; i++) {
        result = env.step(3);
    }
    result = env.step(0);

    runner.check_values(true, result.end_step, "Limite de pas dépassé");

}