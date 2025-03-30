//********* nodeBB.hpp *********

#ifndef NODEBB_HPP
#define NODEBB_HPP

//#include "kpSolver.hpp"
#include <vector>
//#include "kpSolverBB.hpp"

using namespace std;

class  NodeBB {

private:
    vector<bool> isFixed;
    vector<bool> isRemoved;
    vector<bool> primalSolution;
    int criticalIndex;
    float fractionalVariable;
    double localUpperBound;
    long localLowerBound;
    bool overCapacitated;

public:

    bool canBeRemoved();

    void primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);
    void solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);
    void init(int size);
    void updateAfterbranching0(int id);
    void updateAfterbranching1(NodeBB* nod, int id);

    void clearSolution(){primalSolution.clear();};
    void fixVariable(int id, bool val){if (val) {isFixed[id]=true;} else {isRemoved[id]=true;}};
    double getNodeUpperBound(){return localUpperBound;};
    long getNodePrimalBound(){return localLowerBound;};
    void copyPrimalSolution(vector<bool> *sol) {sol->clear();*sol = primalSolution;}
    int getCriticalIndex() const {return criticalIndex;};
    float getFractionalVariable() const {return fractionalVariable;};

};

#endif
