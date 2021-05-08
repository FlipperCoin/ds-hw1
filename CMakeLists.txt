cmake_minimum_required(VERSION 3.10)
project(ds_ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ds_ex1 main.cpp
        car_dealership_manager.cpp
        car_dealership_manager.h
        btree_23.h
        car_node.h
        grade_node.h
        list_node.h
        model_data.h
        model_node.h
        shared_pointer.h
        tree_node.h
        vector.h
        )

find_package(GTest CONFIG REQUIRED)
add_executable(tests tests.cpp)
target_link_libraries(tests gtest gtest_main rt pthread)
add_test(tests tests)