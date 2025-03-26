//********* kpSolverHeurDP.hpp *********

#pragma once
#include "kpSolverGreedy.hpp"

class  KpSolverHeurDP : public KpSolverGreedy {

protected:

    uint nbSelectedReopt;
    uint nbUnselectedReopt;


    void solveLowerBound(uint lastIndex);

public:
    KpSolverHeurDP(std::string const & filename, uint nbSelectedReopt=100, uint nbUnselectedReopt=200);

    virtual void solve() override;

};

