#include "env/SnakeEnv.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

bool operator==(const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}
bool operator!=(const Point &p1, const Point &p2) {
    return p1.x != p2.x || p1.y != p2.y;
}

Index SnakeEnv::get_action_count() const {
    return 4;
}

Point SnakeEnv::get_future_position(Point const &point, Index direct) const {
    switch (direct) {
        case 0:
            return Point(point.x,point.y-1);
        case 1:
            return Point(point.x+1,point.y);
        case 2:
            return Point(point.x, point.y+1);
        case 3:
            return Point(point.x-1,point.y);
    }
    return point;
}

Index SnakeEnv::get_observation_size() const {
    return 11;
}

Matrix SnakeEnv::get_observation() const {
    Matrix observation(1,11,0);

    if (is_collision(get_future_position(snake[0],direction))) {
        observation.get_value(0,0) = 1;
    }

    if (is_collision(get_future_position(snake[0],( direction+1) % 4 ))) {
        observation.get_value(0,1) = 1;
    }

    if (is_collision(get_future_position(snake[0],(direction+3) % 4 ))) {
        observation.get_value(0,2) = 1;
    }


    observation.get_value(0,3+direction) = 1;

    if (food.y > snake[0].y) {
        observation.get_value(0,7) = 1;
    }

    if (food.y < snake[0].y) {
        observation.get_value(0,8) = 1;
    }

    if (food.x > snake[0].x) {
        observation.get_value(0,9) = 1;
    }

    if (food.x < snake[0].x) {
        observation.get_value(0,10) = 1;
    }

    return observation;
}

Point SnakeEnv::get_position_head() const {
    return snake.front();
}

Index SnakeEnv::get_score() const {
    return score;
}

void SnakeEnv::place_food() {
    assert((Index)snake.size() < (grid_size*grid_size) && "Erreur : Le serpent fait déjà toute la grille");
    std::deque<Point>::const_iterator it;
    bool collision = false;
    do {
        collision = false;
        Index rand1 = gen.randomizeInt(0,grid_size-1);
        Index rand2 = gen.randomizeInt(0,grid_size-1);
        food = Point(rand1,rand2);
        for (it = snake.begin(); it != snake.end(); ++it) {
            if (food == *it) {
                collision = true;
            }
        }
    }while (collision);
}

Matrix SnakeEnv::reset() {
    snake.clear();
    Index center = grid_size/2;
    snake.push_back(Point(center,center));
    snake.push_back(Point(center,center+1));
    snake.push_back(Point(center,center+2));
    direction = 0;
    step_count_starving = 0;
    score = 0;
    place_food();
    return get_observation();
}

bool SnakeEnv::is_collision(Point const &position) const {
    bool result = (position.x >= grid_size) || (position.y >= grid_size) || (position.x < 0) || (position.y < 0);
    if (result) {
        return true;
    }
    std::deque<Point>::const_iterator it;
    for (it = snake.begin(); it != snake.end(); ++it) {
        if (position == *it) {
            return true;
        }
    }
    return false;
}


StepResult SnakeEnv::step(Index action) {
    assert((action >= 0 && action < get_action_count()) && "Erreur : L'action est invalide");
    Index direct = action;
    Scalar reward = 0;
    if (std::abs(action - direction) == 2) {
        direct = direction;
    }
    direction = direct;
    Point future_head = get_future_position(snake[0],direct);
    step_count_starving++;
    if (future_head != food) {
        snake.pop_back();
        if (is_collision(future_head)) {
            reward = -10;
            return StepResult(get_observation(),reward,true);
        }
        snake.push_front(future_head);
    }
    else {
        snake.push_front(future_head);
        reward = 5;
        score += 1;
        step_count_starving = 0;
        place_food();
    }

    reward -= 0.05;
    if (step_count_starving > limit_step_starving) {
        reward = 0;
        return StepResult(get_observation(),reward,true);
    }
    return StepResult(get_observation(),reward,false);

}

bool is_in_snake(std::deque<Point> const &snake,Point const &p) {
    std::deque<Point>::const_iterator it;
    for (it = snake.begin(); it != snake.end(); ++it) {
        if (p == *it) {
            return true;
        }
    }
    return false;
}

void SnakeEnv::render() const {
    for (Index i = 0; i < grid_size+2; i++) {
        std::cout << "#";
    }
    for (Index j = 0; j < grid_size; j++) {
        std::cout << std::endl << "#";
        for (Index i = 0; i < grid_size; i++) {
            if (food == Point(i,j)) {
                std::cout << "\033[31m*\033[0m";
            }
            else if (is_in_snake(snake,Point(i,j))) {
                if (Point(i,j) == snake[0]) {
                    std::cout << "\033[92m@\033[0m";
                }
                else {
                    std::cout << "\033[32mo\033[0m";
                }
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "#";
    }
    std::cout << std::endl;
    for (Index i = 0; i < grid_size+2; i++) {
        std::cout << "#";
    }
    std::cout << "\n Score : " << score << "\n\n" << std::endl;
}
