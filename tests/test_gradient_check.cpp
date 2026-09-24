#include "TestRunner.hpp"
#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include "nn/DenseLayer.hpp"
#include "nn/Activations.hpp"
#include "nn/Network.hpp"
#include "nn/Losses.hpp"

void comparaison_matrix(TestRunner &runner, Matrix const &result, Matrix const &expected, std::string const &nom);

void test_loss(TestRunner &runner) {
    QuadraLoss loss_fn;

    Matrix predictions(2, 1);
    predictions.get_value(0, 0) = 3;
    predictions.get_value(1, 0) = 5;

    Matrix targets(2, 1);
    targets.get_value(0, 0) = 1;
    targets.get_value(1, 0) = 2;

    runner.section("Test QuadraLoss : Valeur calculee");

    Scalar expected_loss = 3.25;
    Scalar result_loss = loss_fn.calculate_loss(predictions, targets);

    runner.check_values(expected_loss, result_loss, "Valeur de la perte quadratique");

    runner.section("Test QuadraLoss : Gradient calcule");

    Matrix expected_gradient(2, 1);
    expected_gradient.get_value(0, 0) = 2;
    expected_gradient.get_value(1, 0) = 3;

    Matrix result_gradient = loss_fn.calculate_gradients_loss(predictions, targets);

    comparaison_matrix(runner, result_gradient, expected_gradient, "Gradient de la perte quadratique");


    runner.section("Test QuadraLoss : predictions identiques aux cibles");

    Scalar perfect_loss = loss_fn.calculate_loss(targets, targets);
    runner.check_values(0.0, perfect_loss, "Perte parfaite vaut 0");

    Matrix expected_perfect_gradient(2, 1);
    expected_perfect_gradient.get_value(0, 0) = 0;
    expected_perfect_gradient.get_value(1, 0) = 0;

    Matrix perfect_gradient = loss_fn.calculate_gradients_loss(targets, targets);

    comparaison_matrix(runner, perfect_gradient, expected_perfect_gradient, "Gradient parfait");
}

void test_backward(TestRunner &runner) {
    Random gen(42);

    runner.section("Test dimension backward");

    DenseLayer dense(3, 2, gen);

    Matrix input_dense(4, 3);
    for (Index i = 0; i < 4; ++i) {
        for (Index j = 0; j < 3; ++j) {
            input_dense.get_value(i, j) = 1.0;
        }
    }

    Matrix grad_out_dense(4, 2);
    for (Index i = 0; i < 4; ++i) {
        for (Index j = 0; j < 2; ++j) {
            grad_out_dense.get_value(i, j) = 0.5;
        }
    }

    dense.forward(input_dense);
    Matrix grad_in_dense = dense.backward(grad_out_dense);

    runner.check_values(3, dense.get_gradWeight().get_row(), "Lignes gradWeight");
    runner.check_values(2, dense.get_gradWeight().get_column(), "Colonnes gradWeight");

    runner.check_values(1, dense.get_gradBiais().get_row(), "Lignes gradBiais");
    runner.check_values(2, dense.get_gradBiais().get_column(), "Colonnes gradBiais");

    runner.check_values(4, grad_in_dense.get_row(), "Lignes gradient renvoye");
    runner.check_values(3, grad_in_dense.get_column(), "Colonnes gradient renvoye");

    runner.section("Test Tanh Backward ");

    Tanh tanh_layer(3);

    Matrix input_tanh(4, 3);
    Matrix grad_out_tanh(4, 3);
    for (Index i = 0; i < 4; ++i) {
        for (Index j = 0; j < 3; ++j) {
            input_tanh.get_value(i, j) = 0.0;
            grad_out_tanh.get_value(i, j) = 1.0;
        }
    }

    tanh_layer.forward(input_tanh);
    Matrix grad_in_tanh = tanh_layer.backward(grad_out_tanh);

    runner.check_values(4, grad_in_tanh.get_row(), "Lignes gradient renvoye (Tanh)");
    runner.check_values(3, grad_in_tanh.get_column(), "Colonnes gradient renvoye (Tanh)");

    runner.section("Test Identity Backward");

    Identity id_layer(3);
    Matrix input_id(2, 3);
    Matrix grad_out_id(2, 3);

    for (Index i = 0; i < 2; ++i) {
        for (Index j = 0; j < 3; ++j) {
            input_id.get_value(i, j) = i * 10 + j;
            grad_out_id.get_value(i, j) = i + j + 1;
        }
    }

    id_layer.forward(input_id);
    Matrix grad_in_id = id_layer.backward(grad_out_id);

    comparaison_matrix(runner, grad_in_id, grad_out_id, "Gradient Identity == Gradient recu");

    runner.section("Test ReLU : Backward (Valeurs et conditions)");

    ReLU relu_layer(3);
    Matrix input_relu(2, 3);

    input_relu.get_value(0, 0) = 5.0;
    input_relu.get_value(0, 1) = -2.0;
    input_relu.get_value(0, 2) = 0.0;
    input_relu.get_value(1, 0) = -10.0;
    input_relu.get_value(1, 1) = 3.14;
    input_relu.get_value(1, 2) = -0.5;

    Matrix grad_out_relu(2, 3);
    for (Index i = 0; i < 2; ++i) {
        for (Index j = 0; j < 3; ++j) {
            grad_out_relu.get_value(i, j) = 10.0;
        }
    }

    Matrix expected_grad_relu(2, 3);
    expected_grad_relu.get_value(0, 0) = 10.0;
    expected_grad_relu.get_value(0, 1) = 0.0;
    expected_grad_relu.get_value(0, 2) = 0.0;
    expected_grad_relu.get_value(1, 0) = 0.0;
    expected_grad_relu.get_value(1, 1) = 10.0;
    expected_grad_relu.get_value(1, 2) = 0.0;

    relu_layer.forward(input_relu);
    Matrix grad_in_relu = relu_layer.backward(grad_out_relu);

    comparaison_matrix(runner, grad_in_relu, expected_grad_relu, "Application du masque de gradient par ReLU");
}