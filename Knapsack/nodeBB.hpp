//********* nodeBB.hpp *********

#pragma once

#include "kpSolverGreedy.hpp"
//using namespace std;
//#include <vector>

class  NodeBB {

private:
    vector<bool> isFixed;
    vector<bool> isRemoved;

    T fixedValue;
    T localUpperBoundInt;

    uint criticalIndex;
    //unsigned long localLowerBound;
    uint fixedWeight;
    uint remainingToInt;

    KpSolverGreedy * solver;

public:
    NodeBB(KpSolverGreedy * instance, const std::pair <std::pair <uint,uint>,T> & p);

    //void primalHeuristic(KpSolver * instance);
    void solveUpperBound();

    void fixVariable0(){isRemoved[criticalIndex]=true;};
    void fixVariable1();

    double getNodeUpperBound() const;

    void printNode();

    //void copyPrimalSolution(vector<bool> *sol) {sol->clear();*sol = primalSolution;}
    void recoverPrimalSolution();//, double epsilon);
    uint getCriticalIndex() const {return criticalIndex;};
    uint getfixedWeight() const {return fixedWeight;};
    bool isIntegral() const {return remainingToInt==0;};
    bool isNotOptimal() const {return getNodeUpperBound()< static_cast<double>(solver->getSolutionCost() + 1);};

    T getLocalUpperBoundInt() const;
};

