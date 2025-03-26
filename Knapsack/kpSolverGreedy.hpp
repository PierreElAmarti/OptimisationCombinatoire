//********* kpSolverGreedy.hpp *********

#pragma once

#include "kpSolver.hpp"

class  KpSolverGreedy : public KpSolver {


public:

    pair <pair<uint, uint>,T> solveGreedyUpperBound();
    KpSolverGreedy(std::string const & filename) : KpSolver(filename) {};
    virtual ~KpSolverGreedy()=default;
    virtual void solve() override;

protected:

    void solveGreedyLowerBound ();

};

