cmake_minimum_required(VERSION 3.22)

project(ReseauDeNeuroneFromScratch LANGUAGES CXX)

set(CORE_SOURCE
        src/env/CorridorEnv.cpp
        src/env/Environment.cpp
        src/env/SnakeEnv.cpp
        src/io/Serializer.cpp
        src/math/Matrix.cpp
        src/math/Random.cpp
        src/math/Types.cpp
        src/nn/ActivationLayer.cpp
        src/nn/Activations.cpp
        src/nn/DenseLayer.cpp
        src/nn/Initializers.cpp
        src/nn/Layer.cpp
        src/nn/Loss.cpp
        src/nn/Losses.cpp
        src/nn/Network.cpp
        src/nn/Optimizer.cpp
        src/nn/Optimizers.cpp
        src/rl/DQNAgent.cpp
        src/rl/EpsilonSchedule.cpp
        src/rl/ReplayBuffer.cpp
        src/rl/Transition.cpp
        src/utils/Logger.cpp
        src/utils/Timer.cpp
)

set(TEST
        tests/main.cpp
        tests/test_gradient_check.cpp
        tests/test_layers.cpp
        tests/test_matrix.cpp
        tests/test_optimizers.cpp
        tests/test_replay_buffer.cpp
        tests/test_snake_env.cpp
        tests/test_xor.cpp
)

add_library(libNeurone ${CORE_SOURCE})
target_include_directories(libNeurone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(play_snake apps/play_snake.cpp)
target_link_libraries(play_snake PRIVATE libNeurone)
target_compile_features(play_snake PRIVATE cxx_std_17)
set_target_properties(play_snake PROPERTIES CXX_EXTENSIONS OFF)

add_executable(train_snake apps/train_snake.cpp)
target_link_libraries(train_snake PRIVATE libNeurone)
target_compile_features(train_snake PRIVATE cxx_std_17)
set_target_properties(train_snake PROPERTIES CXX_EXTENSIONS OFF)

add_executable(train_xor apps/train_xor.cpp)
target_link_libraries(train_xor PRIVATE libNeurone)
target_compile_features(train_xor PRIVATE cxx_std_17)
set_target_properties(train_xor PROPERTIES CXX_EXTENSIONS OFF)

add_executable(test_module ${TEST})
target_include_directories(test_module PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(test_module PRIVATE libNeurone)
target_compile_features(test_module PRIVATE cxx_std_17)
set_target_properties(test_module PROPERTIES CXX_EXTENSIONS OFF)


if(MSVC)
    target_compile_options(libNeurone PUBLIC /W4 /WX)
else()
    target_compile_options(libNeurone PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()