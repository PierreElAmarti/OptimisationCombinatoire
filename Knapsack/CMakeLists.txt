cmake_minimum_required(VERSION 3.5)

project(Knapsack LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# do not use LTO for debug builds
#if(CMAKE_BUILD_TYPE MATCHES Release)
#    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
#    SET(CMAKE_AR "gcc-ar")
#endif()

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_ARCH_FLAGS} -DDEBUG -O0 -g -ldl -lm -isystem dir -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_ARCH_FLAGS} -O3 -flto=auto -DNDEBUG -ldl -lm -Wall -s -isystem dir -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_ARCH_FLAGS} -O3 -flto=auto -DNDEBUG -ldl -lm -Wall -s -isystem dir -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2")

add_executable(Heur
    testHeur.cpp
    kpSolver.cpp
    kpSolverDPsparseV2.cpp
    kpSolverGreedy.cpp
    kpSolverHeurDP.cpp
)



add_executable(DP
    testDP.cpp
    kpSolver.cpp
    matDP.cpp
    kpSolverDP.cpp
    kpSolverDPsparseV2.cpp
    kpSolverGreedy.cpp
    kpSolverHeurDP.cpp
)

add_executable(BB
    testBB.cpp
    kpSolver.cpp
    kpSolverDPsparseV2.cpp
    nodeBB.cpp
    kpSolverGreedy.cpp
    kpSolverHeurDP.cpp
    nodeManagement.cpp
    kpSolverBB.cpp
)

