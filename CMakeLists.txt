cmake_minimum_required(VERSION 3.10)
project(ds_ex1)

set(CMAKE_CXX_STANDARD 11)
set(MySourcesList car_dealership_manager.cpp
        car_dealership_manager.h
        library.cpp
        library.h
        btree_23.h
        car_node.h
        car_node.cpp
        grade_node.h
        grade_node.cpp
        zero_grade_type_node.cpp
        zero_grade_type_node.h
        sells_node.cpp
        sells_node.h
        model_data.h
        shared_pointer.h
        tree_node.h
        vector.h)

add_executable(main_tests main1.cpp ${MySourcesList})

add_executable(more_tests more_tests.cpp ${MySourcesList})

find_package(GTest CONFIG REQUIRED)
add_executable(tests tests.cpp)
target_link_libraries(tests gtest gtest_main rt pthread)
add_test(tests tests)