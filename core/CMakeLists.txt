# Define the core static library target
add_library(mmgym_core INTERFACE)

target_include_directories(mmgym_core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mmgym_core INTERFACE
    Eigen3::Eigen
    pinocchio::pinocchio
    spdlog::spdlog
)