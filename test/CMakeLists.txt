include_directories(${THIRDPARTY_DIR})
set(TEST_INCLUDE ${THIRDPARTY_DIR}/catch.hpp)

add_executable(test_dfs 
	${SOLVER_HEADERS} ${TEST_INCLUDE} test_dfs.cpp test_main.cpp)
add_test(test_dfs test_dfs)
