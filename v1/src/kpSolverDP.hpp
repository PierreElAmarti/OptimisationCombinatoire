//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "kpSolver.hpp"

class  KpSolverDP : public KpSolver {

private:

    int** matrixDP;

    bool memoizedVersion;
    bool parallelizedVersion;
    bool verboseMode;


    void solveIterSeq();
    //void solveIterParallel();
    int solveMemoized(int i , int m);

    void backtrack();

    void createMatrixDP();
    void deleteMatrixDP();
    void printMatrixDP();

    void fillFirstColumnDP();

public:
    


    void solve();


    //KpSolverDP(vector<int> & newWeights, vector<int> & newValues );

    void updateKpSolverDP(vector<int> & newWeights, vector<int> & newValues, int newBound);

	void setMemoizedVersion(bool memoizedVersion);
	void setParallelizedVersion(bool parallelVersion);
	void setVerboseMode(bool verbosemode);

};

#endif

