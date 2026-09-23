#include "TestRunner.hpp"
#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include "nn/DenseLayer.hpp"
#include "nn/Activations.hpp"

void comparaison_matrix(TestRunner &runner, Matrix const &result, Matrix const &expected, std::string const &nom);

void test_DenseLayer(TestRunner &runner) {
    Random gen(33);
    DenseLayer dl(3,2,gen);
    runner.section("Test dimension DenseLayer");
    runner.check_values(3,dl.nInput(),"Verification du nombre d'entrée");
    runner.check_values(2,dl.nOutput(),"Vérification du nombre de sortie");

    Matrix weight(3, 2);
    weight.get_value(0, 0) = 1;
    weight.get_value(0, 1) = 4;
    weight.get_value(1, 0) = 2;
    weight.get_value(1, 1) = 5;
    weight.get_value(2, 0) = 3;
    weight.get_value(2, 1) = 6;

    Matrix biais(1, 2);
    biais.get_value(0, 0) = 10;
    biais.get_value(0, 1) = 20;

    Matrix input1(1, 3);
    input1.get_value(0, 0) = 1;
    input1.get_value(0, 1) = 1;
    input1.get_value(0, 2) = 1;

    Matrix expected1(1, 2);
    expected1.get_value(0, 0) = 16;
    expected1.get_value(0, 1) = 35;


    dl.set_weight(weight);
    dl.set_biais(biais);
    Matrix copieWeight(dl.get_weight());
    Matrix copieBiais(dl.get_biais());
    Matrix result1 = dl.forward(input1);
    comparaison_matrix(runner,result1,expected1,"Test echantillon 1");

    Matrix input2(2, 3);
    input2.get_value(0, 0) = 1;
    input2.get_value(0, 1) = 1;
    input2.get_value(0, 2) = 1;
    input2.get_value(1, 0) = 1;
    input2.get_value(1, 1) = 0;
    input2.get_value(1, 2) = 0;

    Matrix expected2(2, 2);
    expected2.get_value(0, 0) = 16;
    expected2.get_value(0, 1) = 35;
    expected2.get_value(1, 0) = 11;
    expected2.get_value(1, 1) = 24;

    Matrix result2 = dl.forward(input2);
    comparaison_matrix(runner,result2,expected2,"Test echantillon 2");


    Random gen1(33);
    Random gen2(33);

    DenseLayer dl1(3,2,gen1);
    DenseLayer dl2(3,2,gen2);
    comparaison_matrix(runner,dl1.forward(input2),dl2.forward(input2),"Test reproductibilité");

    comparaison_matrix(runner,dl.get_weight(),copieWeight,"Test intégrité de weight");
    comparaison_matrix(runner,dl.get_biais(),copieBiais,"test intégrité biais");

}

void test_activations(TestRunner &runner) {
    Matrix input(2, 3);
    input.get_value(0, 0) = -3;
    input.get_value(0, 1) = 0;
    input.get_value(0, 2) = 5;
    input.get_value(1, 0) = -1;
    input.get_value(1, 1) = 2;
    input.get_value(1, 2) = -7;

    runner.section("Test ReLU");

    Matrix expected_relu(2, 3);
    expected_relu.get_value(0, 0) = 0;
    expected_relu.get_value(0, 1) = 0;
    expected_relu.get_value(0, 2) = 5;
    expected_relu.get_value(1, 0) = 0;
    expected_relu.get_value(1, 1) = 2;
    expected_relu.get_value(1, 2) = 0;

    ReLU relu(3);
    Matrix out_relu = relu.forward(input);
    comparaison_matrix(runner, out_relu, expected_relu, "Test sortie ReLU");
    runner.check_values(3, relu.nInput(), "Dimensions accesseur 1 ReLU");
    runner.check_values(3, relu.nOutput(), "Dimensions accesseur 2 ReLU");
    runner.check_values(2, out_relu.get_row(), "Lignes sortie ReLU");
    runner.check_values(3, out_relu.get_column(), "Colonnes sortie ReLU");

    runner.section("Test Identite");

    Identity identite(3);
    Matrix out_id = identite.forward(input);
    comparaison_matrix(runner, out_id, input, "Test sortie Identite");
    runner.check_values(3, identite.nInput(), "Dimensions accesseur 1 Identite");
    runner.check_values(3, identite.nOutput(), "Dimensions accesseur 2 Identite");
    runner.check_values(2, out_id.get_row(), "Lignes sortie Identite");
    runner.check_values(3, out_id.get_column(), "Colonnes sortie Identite");

    runner.section("Test Sigmoide");

    Sigmoide sigmoide(3);
    Matrix input_zero(1, 1);
    input_zero.get_value(0, 0) = 0;

    Sigmoide sigmoide_1(1);
    Matrix out_sig_zero = sigmoide_1.forward(input_zero);
    runner.check_values(0.5, out_sig_zero.get_value(0, 0), "Point remarquable Sigmoide en 0");

    Matrix out_sig = sigmoide.forward(input);
    bool sig_bounds_ok = true;
    for (Index i = 0; i < out_sig.get_row(); ++i) {
        for (Index j = 0; j < out_sig.get_column(); ++j) {
            if (out_sig.get_value(i, j) <= 0.0 || out_sig.get_value(i, j) >= 1.0) {
                sig_bounds_ok = false;
            }
        }
    }
    runner.check_values(true, sig_bounds_ok, "Propriete bornes Sigmoide entre 0 et 1");
    runner.check_values(3, sigmoide.nInput(), "Dimensions accesseur 1 Sigmoide");
    runner.check_values(3, sigmoide.nOutput(), "Dimensions accesseur 2 Sigmoide");
    runner.check_values(2, out_sig.get_row(), "Lignes sortie Sigmoide");
    runner.check_values(3, out_sig.get_column(), "Colonnes sortie Sigmoide");

    runner.section("Test Tanh");

    Tanh tanh_act(3);
    Tanh tanh_act_1(1);
    Matrix out_tanh_zero = tanh_act_1.forward(input_zero);
    runner.check_values(0.0, out_tanh_zero.get_value(0, 0), "Point remarquable Tanh en 0");

    Matrix out_tanh = tanh_act.forward(input);
    bool tanh_bounds_ok = true;
    for (Index i = 0; i < out_tanh.get_row(); ++i) {
        for (Index j = 0; j < out_tanh.get_column(); ++j) {
            if (out_tanh.get_value(i, j) <= -1.0 || out_tanh.get_value(i, j) >= 1.0) {
                tanh_bounds_ok = false;
            }
        }
    }
    runner.check_values(true, tanh_bounds_ok, "Propriete bornes Tanh entre -1 et 1");
    runner.check_values(3, tanh_act.nInput(), "Dimensions accesseur 1 Tanh");
    runner.check_values(3, tanh_act.nOutput(), "Dimensions accesseur 2 Tanh");
    runner.check_values(2, out_tanh.get_row(), "Lignes sortie Tanh");
    runner.check_values(3, out_tanh.get_column(), "Colonnes sortie Tanh");
}

void test_enchainement(TestRunner &runner) {
    Random gen1(7);
    DenseLayer dl1(2,4,gen1);

    Matrix weight1(2, 4);
    weight1.get_value(0, 0) = 1;
    weight1.get_value(0, 1) = 0.5;
    weight1.get_value(0, 2) = 1;
    weight1.get_value(0, 3) = 2;
    weight1.get_value(1, 0) = 1;
    weight1.get_value(1, 1) = 0;
    weight1.get_value(1, 2) = 2;
    weight1.get_value(1, 3) = 1;

    Matrix biais1(1, 4);
    biais1.get_value(0, 0) = 0;
    biais1.get_value(0, 1) = 0;
    biais1.get_value(0, 2) = 0.5;
    biais1.get_value(0, 3) = -1;

    Matrix input1(1, 2);
    input1.get_value(0, 0) = 1;
    input1.get_value(0, 1) = -1;

    Matrix expected(1, 4);
    expected.get_value(0, 0) = 0;
    expected.get_value(0, 1) = 0.5;
    expected.get_value(0, 2) = 0;
    expected.get_value(0, 3) = 0;

    dl1.set_weight(weight1);
    dl1.set_biais(biais1);

    Matrix outDense1 = dl1.forward(input1);
    ReLU relu1(4);
    Matrix outFinal1 = relu1.forward(outDense1);

    comparaison_matrix(runner, outFinal1, expected,"Verification enchainement 1");


    Random gen2(42);
    DenseLayer dl2(4, 2, gen2);

    Matrix weight2(4, 2);
    weight2.get_value(0, 0) = 1;
    weight2.get_value(0, 1) = -1;
    weight2.get_value(1, 0) = 0.5;
    weight2.get_value(1, 1) = 2;
    weight2.get_value(2, 0) = -1;
    weight2.get_value(2, 1) = 0;
    weight2.get_value(3, 0) = 1;
    weight2.get_value(3, 1) = 1;

    Matrix biais2(1, 2);
    biais2.get_value(0, 0) = -0.5;
    biais2.get_value(0, 1) = 1;

    Matrix input2(3, 4);

    input2.get_value(0, 0) = 2;
    input2.get_value(0, 1) = 0;
    input2.get_value(0, 2) = -2;
    input2.get_value(0, 3) = 1;

    input2.get_value(1, 0) = 0;
    input2.get_value(1, 1) = 1;
    input2.get_value(1, 2) = 0;
    input2.get_value(1, 3) = -1;

    input2.get_value(2, 0) = 1;
    input2.get_value(2, 1) = 1;
    input2.get_value(2, 2) = 1;
    input2.get_value(2, 3) = 1;

    Matrix expected2(3, 2);

    expected2.get_value(0, 0) = 4.5;
    expected2.get_value(0, 1) = 0;

    expected2.get_value(1, 0) = 0;
    expected2.get_value(1, 1) = 2;

    expected2.get_value(2, 0) = 1;
    expected2.get_value(2, 1) = 3;


    dl2.set_weight(weight2);
    dl2.set_biais(biais2);

    Matrix outDense2 = dl2.forward(input2);
    ReLU relu2(2);
    Matrix outFinal2 = relu2.forward(outDense2);

    comparaison_matrix(runner, outFinal2, expected2, "Verification enchainement 2 avec entrees multiples (3x4)");

}

void test_layer(TestRunner& runner) {

    runner.section("Test de la classe DenseLayer");
    test_DenseLayer(runner);

    runner.section("Test fonction d'activation");
    test_activations(runner);

    runner.section("Test enchainement couche dense -> activation");
    test_enchainement(runner);

}