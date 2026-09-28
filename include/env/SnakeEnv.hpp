#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_SNAKEENV_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_SNAKEENV_HPP
#include "Environment.hpp"
#include <deque>

#include "math/Random.hpp"

struct Point {
    Index x;
    Index y;
    Point(Index i, Index j) : x(i), y(j) {}

};

bool operator==(const Point &p1, const Point &p2);
bool operator!=(const Point &p1, const Point &p2);

class SnakeEnv : public Environment {
public:
    SnakeEnv(Index size, Index limit, std::uint32_t seed = 0) : grid_size(size), food(0,0), limit_step_starving(limit), step_count_starving(0), direction(0), gen(seed), score(0) {}
    Matrix reset() override;
    StepResult step(Index action) override;
    Index get_observation_size() const override;
    Index get_action_count() const override;
    void render() const override;

    Point get_position_head() const;
    Index get_score() const;

private:
    Index grid_size;
    std::deque<Point> snake;
    Point food;
    Index limit_step_starving;
    Index step_count_starving;
    Index direction;
    Random gen;
    Index score;

    void place_food();
    bool is_collision(Point const &position) const;
    Matrix get_observation() const;
    Point get_future_position(Point const &point, Index direct) const;
};

bool is_in_snake(std::deque<Point> const &snake,Point const &p);

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_SNAKEENV_HPP
