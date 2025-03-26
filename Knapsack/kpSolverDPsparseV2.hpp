//********* kpSolverDPsparse.hpp *********

#pragma once

#include "kpSolver.hpp"

class  kpSolverDPsparseV2 : public KpSolver {

    struct LineDP {
        T lastVal;
        uint beginIndex;
        uint endIndex;
        T* beginTab=nullptr;
    };

private:

    LineDP* lines;

    void deleteLine(uint id);
    void backtrack();
    void printMatrixDP();

    T getElement(uint id, uint m);

    bool initDP();


public:
    
    kpSolverDPsparseV2(std::string const & filename):KpSolver(filename){};
    kpSolverDPsparseV2(KpSolver * kp):KpSolver(kp){};

    void solve() override;


};


