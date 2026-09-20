#include "TestRunner.hpp"
#include "math/Matrix.hpp"

void test_indexation(TestRunner &runner, Matrix &matrix);
void test_matrice(TestRunner& runner);

int main()
{
    TestRunner runner;
    test_matrice(runner);
    runner.bilan();
    return runner.return_test();
}