#include "TestRunner.hpp"
#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include <sstream>

void test_indexation(TestRunner &runner, Matrix &matrix);
void test_matrice(TestRunner& runner);

void test_random(TestRunner &runner);
void test_initializers(TestRunner &runner);

void test_layer(TestRunner& runner);

int main() {
    TestRunner runner;
    test_matrice(runner);
    test_random(runner);
    test_initializers(runner);
    test_layer(runner);
    runner.bilan();
    return runner.return_test();
}