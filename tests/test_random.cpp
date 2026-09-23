#include "TestRunner.hpp"
#include "math/Random.hpp"
#include "nn/Initializers.hpp"
#include <sstream>

void comparaison_matrix(TestRunner &runner, Matrix const &result, Matrix const &expected, std::string const &nom);

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

void test_initializers(TestRunner &runner) {
    runner.section("Test dimensions inchangees");

    Matrix m_dim(3, 2);
    Random gen_dim(42);
    init_weight_Glorot(m_dim, gen_dim);

    runner.check_values(3, m_dim.get_row(), "Test lignes inchangees");
    runner.check_values(2, m_dim.get_column(), "Test colonnes inchangees");

    runner.section("Test reproductibilite");

    Matrix m_rep1(10, 10);
    Matrix m_rep2(10, 10);
    Random gen_rep1(123);
    Random gen_rep2(123);
    init_weight_Glorot(m_rep1, gen_rep1);
    init_weight_Glorot(m_rep2, gen_rep2);

    comparaison_matrix(runner, m_rep1, m_rep2, "Reproductibilite Glorot");

    runner.section("Test non-constance");

    Matrix m_const(10, 10);
    Random gen_const(456);
    init_weight_Glorot(m_const, gen_const);

    bool non_const = false;
    Scalar first_val = m_const.get_value(0, 0);
    for (Index i = 0; i < m_const.get_row(); ++i) {
        for (Index j = 0; j < m_const.get_column(); ++j) {
            if (m_const.get_value(i, j) != first_val) {
                non_const = true;
            }
        }
    }
    runner.check_values(true, non_const, "Au moins deux cases differentes");

    runner.section("Test statistique Glorot");

    Matrix m_stat_g(100, 100);
    Random gen_stat_g(789);
    init_weight_Glorot(m_stat_g, gen_stat_g);

    double sum_g = 0.0;
    Index cases_g = m_stat_g.get_row() * m_stat_g.get_column();
    for (Index i = 0; i < m_stat_g.get_row(); ++i) {
        for (Index j = 0; j < m_stat_g.get_column(); ++j) {
            sum_g += m_stat_g.get_value(i, j);
        }
    }
    double mean_g = sum_g / cases_g;

    double var_sum_g = 0.0;
    for (Index i = 0; i < m_stat_g.get_row(); ++i) {
        for (Index j = 0; j < m_stat_g.get_column(); ++j) {
            var_sum_g += (m_stat_g.get_value(i, j) - mean_g) * (m_stat_g.get_value(i, j) - mean_g);
        }
    }
    double stddev_g = std::sqrt(var_sum_g / cases_g);
    double target_stddev_g = std::sqrt(2.0 / 200.0);

    double tolerance = 0.01;
    bool mean_ok_g = std::abs(mean_g - 0.0) < tolerance;
    bool stddev_ok_g = std::abs(stddev_g - target_stddev_g) < tolerance;

    std::cout << "Glorot - Moyenne calculee : " << mean_g << " (cible : 0.0)" << std::endl;
    std::cout << "Glorot - Ecart-type calcule : " << stddev_g << " (cible : " << target_stddev_g << ")" << std::endl;

    runner.check_values(true, mean_ok_g, "Moyenne empirique Glorot proche de 0");
    runner.check_values(true, stddev_ok_g, "Ecart-type empirique Glorot proche de sqrt(2/200)");

    runner.section("Test statistique He");

    Matrix m_stat_h(100, 100);
    Random gen_stat_h(101112);
    init_weight_He(m_stat_h, gen_stat_h);

    double sum_h = 0.0;
    Index cases_h = m_stat_h.get_row() * m_stat_h.get_column();
    for (Index i = 0; i < m_stat_h.get_row(); ++i) {
        for (Index j = 0; j < m_stat_h.get_column(); ++j) {
            sum_h += m_stat_h.get_value(i, j);
        }
    }
    double mean_h = sum_h / cases_h;

    double var_sum_h = 0.0;
    for (Index i = 0; i < m_stat_h.get_row(); ++i) {
        for (Index j = 0; j < m_stat_h.get_column(); ++j) {
            var_sum_h += (m_stat_h.get_value(i, j) - mean_h) * (m_stat_h.get_value(i, j) - mean_h);
        }
    }
    double stddev_h = std::sqrt(var_sum_h / cases_h);
    double target_stddev_h = std::sqrt(2.0 / 100.0);

    bool mean_ok_h = std::abs(mean_h - 0.0) < tolerance;
    bool stddev_ok_h = std::abs(stddev_h - target_stddev_h) < tolerance;

    std::cout << "He - Moyenne calculee : " << mean_h << " (cible : 0.0)" << std::endl;
    std::cout << "He - Ecart-type calcule : " << stddev_h << " (cible : " << target_stddev_h << ")" << std::endl;

    runner.check_values(true, mean_ok_h, "Moyenne empirique He proche de 0");
    runner.check_values(true, stddev_ok_h, "Ecart-type empirique He proche de sqrt(2/100)");
}