#include "TestRunner.hpp"
#include "env/CorridorEnv.hpp"

void test_corridor(TestRunner &runner) {
    CorridorEnv corridor(5,50);
    corridor.reset();
    runner.section("Test chemin parfait");

    StepResult result = corridor.step(1);
    runner.check_values(0.0,result.reward,"Récompense étape 1");
    runner.check_values(false,result.end_step,"Condition de fin étape 1");

    result = corridor.step(1);
    runner.check_values(0.0,result.reward,"Récompense étape 2");
    runner.check_values(false,result.end_step,"Condition de fin étape 2");

    result = corridor.step(1);
    runner.check_values(0.0,result.reward,"Récompense étape 3");
    runner.check_values(false,result.end_step,"Condition de fin étape 3");

    result = corridor.step(1);
    runner.check_values(1.0,result.reward,"Récompense étape 4");
    runner.check_values(true,result.end_step,"Condition de fin étape 4");

    runner.section("Test reset");
    Matrix pos =  corridor.reset();
    runner.check_values(0.0,pos.get_value(0,0),"Position après reset");

    runner.section("Test mur gauche");
    corridor.reset();
    result = corridor.step(0);
    runner.check_values(0.0,result.observation.get_value(0,0),"Position après mur gauche");
    runner.check_values(0.0,result.reward,"Récompense après mur gauche");
    runner.check_values(false,result.end_step,"Condition de fin après mur gauche");

    runner.section("Test fin par limite de pas");
    CorridorEnv corridor2(10,2);
    corridor2.reset();
    corridor2.step(1);
    result = corridor2.step(1);
    runner.check_values(true,result.end_step,"Fin prématuré");

    runner.section("Test méthode get");
    runner.check_values(1,corridor.get_observation_size(),"Observation size");
    runner.check_values(2,corridor.get_action_count(),"Action count");



}