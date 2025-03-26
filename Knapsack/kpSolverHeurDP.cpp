//********* knapsackheurDP.cpp *********

#include "kpSolverHeurDP.hpp"
#include "kpSolverDPsparseV2.hpp"

KpSolverHeurDP::KpSolverHeurDP(std::string const & filename, uint nbSelect, uint nbUnselect):
    KpSolverGreedy(filename),
    //heurParams(HeuristicParameters(Heuristics::KernelSearch,nbSelect,nbUnselect))
    nbSelectedReopt(nbSelect),
    nbUnselectedReopt(nbUnselect)

{

}


void KpSolverHeurDP::solveLowerBound(uint lastIndex) {

    uint idMax(std::min(nbItems-1,lastIndex + nbUnselectedReopt));
    uint idMin(0);
    if (lastIndex > nbSelectedReopt)
        idMin =lastIndex - nbSelectedReopt;

    //cout << "neighborhood defined by indexes : " << idMin << "  " << idMax << endl;

    //extraire vecteurs poids et prix correspodnant


    uint  fixedBound(0);
    T  fixedCost(0);


    for (uint i(0); i < idMin; i++){
        fixedBound += weights[i];
        fixedCost += values[i];
        //solution.push_back(true);
        //cout << "selection of item " << i << endl;
    }

    //cout << "knapsack neighborhood fixing cost " << fixedCost << endl;
    //cout << "knapsack neighborhood fixing weight " << fixedBound << endl;


    kpSolverDPsparseV2 kp(this);
    kp.extractSubInstance(idMin, idMax, knapsackBound - fixedBound);
    kp.solve();

    // se ramener aux solutions du probleme initial

    costSolution = kp.getSolutionCost() + fixedCost;
    if ((idMin==0) &&idMax==nbItems-1)
        upperBoundOPT=static_cast<double>(costSolution);

    solution.clear();
    solution.reserve(nbItems);
    solution.resize(idMin,true);

    for (uint i(idMin); i <= idMax; i++){
        solution.push_back(kp.isSelected(i-idMin));
    }
    solution.resize(nbItems,false);


}


void KpSolverHeurDP::solve() {

    std::pair<std::pair<uint, uint>, T> p(solveGreedyUpperBound());
    uint i(p.first.first);
    upperBoundOPT = static_cast<double>(p.second) +
    static_cast<double>(values[i]*p.first.second)   /  (static_cast<double>(weights[i]));
    solveLowerBound(i);

}


