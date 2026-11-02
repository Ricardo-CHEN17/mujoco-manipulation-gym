enable_testing()

add_executable(test_math_types test_math_types.cpp)

target_link_libraries(test_math_types PRIVATE
    mmgym_core
    Catch2::Catch2WithMain
)

add_test(NAME testMathTypes COMMAND test_math_types)