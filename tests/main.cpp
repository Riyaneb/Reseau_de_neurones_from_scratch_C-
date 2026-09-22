#include "TestRunner.hpp"
#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include <sstream>

void test_indexation(TestRunner &runner, Matrix &matrix);
void test_matrice(TestRunner& runner);

void test_random(TestRunner &runner) {
    runner.section("Test de reproductibilite (meme graine)");

    Random rng1(42);
    Random rng2(42);
    bool identical = true;
    for (int i = 0; i < 10; ++i) {
        Scalar val1 = rng1.randomizeUniform(0, 100);
        Scalar val2 = rng2.randomizeUniform(0, 100);
        std::ostringstream nom;
        nom << "Valeur " << i << " identique";
        runner.check_values(val1, val2, nom.str());
        if (val1 != val2) {
            identical = false;
        }
    }
    runner.check_values(true, identical, "La suite de 10 valeurs est strictement identique");

    runner.section("Test de graines differentes");

    Random rng3(42);
    Random rng4(84);
    bool at_least_one_different = false;
    for (int i = 0; i < 10; ++i) {
        Scalar val3 = rng3.randomizeUniform(0, 100);
        Scalar val4 = rng4.randomizeUniform(0, 100);
        if (val3 != val4) {
            at_least_one_different = true;
        }
    }
    runner.check_values(true, at_least_one_different, "Au moins une valeur differe entre les deux generateurs");

    runner.section("Test des bornes de la loi uniforme");

    Random rng5(123);
    int a = 5;
    int b = 15;
    bool out_of_bounds = false;
    for (int i = 0; i < 1000; ++i) {
        Scalar val_bounds = rng5.randomizeUniform(a, b);
        if (val_bounds < a || val_bounds > b) {
            out_of_bounds = true;
            break;
        }
    }
    runner.check_values(false, out_of_bounds, "Aucune valeur ne sort de l'intervalle [5, 15]");

    runner.section("Test de reinitialisation de la graine");

    Random rng7(99);
    Scalar v1 = rng7.randomizeUniform(0, 1000);
    Scalar v2 = rng7.randomizeUniform(0, 1000);

    rng7.changeSeed(999);

    rng7.changeSeed(99);
    Scalar v1_reset = rng7.randomizeUniform(0, 1000);
    Scalar v2_reset = rng7.randomizeUniform(0, 1000);

    runner.check_values(v1, v1_reset, "La premiere valeur apres reset est identique");
    runner.check_values(v2, v2_reset, "La seconde valeur apres reset est identique");
}

int main() {
    TestRunner runner;
    test_matrice(runner);
    test_random(runner);
    runner.bilan();
    return runner.return_test();
}