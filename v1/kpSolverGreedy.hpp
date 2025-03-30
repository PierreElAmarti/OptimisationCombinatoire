//********* kpSolverGreedy.hpp *********

#ifndef KPSOLVERGREEDY_HPP
#define KPSOLVERGREEDY_HPP

#include "kpSolver.hpp"

class  KpSolverGreedy : public KpSolver {


public:

    void solveLowerBound();
    void solveUpperBound();
    void solve();


};


#endif
