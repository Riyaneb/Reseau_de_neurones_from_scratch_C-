#include "TestRunner.hpp"
#include "rl/ReplayBuffer.hpp"

void test_replay_buffer(TestRunner &runner) {
    Matrix s(1, 1);
    s.get_value(0, 0) = 0.0;

    ReplayBuffer buffer(5, 42);

    runner.section("Test remplissage et seuil");
    
    buffer.add_transition(Transition(s, 0, 1.0, s, false));
    buffer.add_transition(Transition(s, 0, 2.0, s, false));
    buffer.add_transition(Transition(s, 0, 3.0, s, false));

    runner.check_values(3, buffer.get_size(), "Taille après 3 ajouts");
    runner.check_values(false, buffer.is_enough(5), "Seuil insuffisant");
    runner.check_values(true, buffer.is_enough(2), "Seuil suffisant");

    runner.section("Test plafonnement");
    
    buffer.add_transition(Transition(s, 0, 4.0, s, false));
    buffer.add_transition(Transition(s, 0, 5.0, s, false));
    buffer.add_transition(Transition(s, 0, 6.0, s, false));
    buffer.add_transition(Transition(s, 0, 7.0, s, false));
    buffer.add_transition(Transition(s, 0, 8.0, s, false));

    runner.check_values(5, buffer.get_size(), "Taille plafonnée");

    runner.section("Test écrasement");
    
    bool overwrite_ok = true;
    for (Index i = 0; i < 20; ++i) {
        std::vector<Transition> batch_ecrasement = buffer.get_transitions(5);
        for (Index j = 0; j < (Index)batch_ecrasement.size(); ++j) {
            if (batch_ecrasement[j].reward < 4.0) {
                overwrite_ok = false;
            }
        }
    }
    runner.check_values(true, overwrite_ok, "Anciennes transitions écrasées");

    runner.section("Test taille du lot");
    
    std::vector<Transition> batch_taille = buffer.get_transitions(3);
    runner.check_values(3, (Index)batch_taille.size(), "Taille du lot renvoyé");

    runner.section("Test reproductibilité");
    
    ReplayBuffer buffer1(5, 123);
    ReplayBuffer buffer2(5, 123);

    for (Index i = 1; i <= 5; ++i) {
        buffer1.add_transition(Transition(s, 0, (Scalar)i, s, false));
        buffer2.add_transition(Transition(s, 0, (Scalar)i, s, false));
    }

    std::vector<Transition> batch1 = buffer1.get_transitions(4);
    std::vector<Transition> batch2 = buffer2.get_transitions(4);

    bool repro_ok = true;
    for (Index i = 0; i < 4; ++i) {
        if (batch1[i].reward != batch2[i].reward) {
            repro_ok = false;
        }
    }
    runner.check_values(true, repro_ok, "Reproductibilité avec même graine");
}