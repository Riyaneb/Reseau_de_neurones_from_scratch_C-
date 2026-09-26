#include "TestRunner.hpp"
#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include <sstream>

void test_indexation(TestRunner &runner, Matrix &matrix);
void test_matrice(TestRunner& runner);

void test_random(TestRunner &runner);
void test_initializers(TestRunner &runner);

void test_layer(TestRunner& runner);

void test_loss(TestRunner &runner);
void test_backward(TestRunner &runner);
void test_gradient_check_network(TestRunner &runner);
void test_gradient_check_complet(TestRunner &runner);

void test_clone(TestRunner& runner);

int main() {
    TestRunner runner;
    test_matrice(runner);
    test_random(runner);
    test_initializers(runner);
    test_layer(runner);
    test_loss(runner);
    test_backward(runner);
    test_gradient_check_network(runner);
    test_gradient_check_complet(runner);
    test_clone(runner);
    runner.bilan();
    return runner.return_test();
}