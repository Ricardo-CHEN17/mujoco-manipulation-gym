# Define the core static library target
add_library(mmgym_core STATIC)

target_include_directories(mmgym_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mmgym_core PUBLIC
    Eigen3::Eigen
    pinocchio::pinocchio
    spdlog::spdlog
)