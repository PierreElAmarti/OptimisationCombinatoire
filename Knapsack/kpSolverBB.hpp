//********* kpSolverBB.hpp *********

#pragma once

#include "kpSolverHeurDP.hpp"
#include "nodeManagement.hpp"
#include "stopBB.hpp"
#include <memory>


enum class BranchingStrategies { BestBound,  DFS10, DFS01,// BFS,
    Random};

/*
enum class TerminationStatus { Optimal,  Feasible, NoSolutionFound};

class OptimStatus{
    private:
    TerminationStatus termStatus;
    uint nbNodes;

public:
    OptimStatus( TerminationStatus s = TerminationStatus::NoSolutionFound, uint nbNod=0);

    TerminationStatus getTerminationStatus() const {return termStatus;};
    uint getNbNodes() const {return nbNodes;};
    void incrNbNodes()  {nbNodes++;};

};
*/

enum class Heuristics { None,  Greedy, KernelSearch};

struct HeuristicParameters{
    Heuristics heurRootNode =Heuristics::Greedy;//Greedy;//KernelSearch;//None;
    uint nbSelectedReopt=20;
    uint nbUnselectedReopt=60;

    //HeuristicParameters(Heuristics hRootNod=Heuristics::KernelSearch, uint nbSelect=100, uint nbUnselect=200):
    //        heurRootNode(hRootNod),nbSelectedReopt(nbSelect), nbUnselectedReopt(nbUnselect){};
};



struct BBparameters{
    //uint warmStart=1;
    uint verboseMode=0;
    //uint nbMaxNodeBB;
    //uint nbMaxNodeInMemory;
    //double epsilon = 0.000001;
    vector<unique_ptr<StopCriterionBB>> term;
};


class  KpSolverBB : public KpSolverHeurDP {

private:

    std::unique_ptr<NodeManagement> nodes;
    BBparameters bbParams;
    HeuristicParameters heurParams;
    size_t nbNodes;

    //OptimStatus status;

    void printStatus();

    void init();
    double getUpperBound();

    bool continueBB(size_t nbNod, size_t nbNodMem);




public:
    KpSolverBB(std::string const & filename,
               BranchingStrategies b = BranchingStrategies::BestBound
            //BestBound, DFS01
            ):KpSolverHeurDP(filename), bbParams(), heurParams(), nbNodes(0){

        switch(b){
        case BranchingStrategies::BestBound:
            nodes = std::make_unique<BestBoundVector>();
                    break;
        case BranchingStrategies::Random:
            nodes = std::make_unique<Random>();
                    break;
        case BranchingStrategies::DFS10:
            nodes = std::make_unique<DFS10>();
                    break;
        case BranchingStrategies::DFS01:
            nodes = std::make_unique<DFS01>();
                    break;/*
        case BranchingStrategies::BFS:
            nodes = std::make_unique<BFSdeque>();
                    break;*/
    }
    };
    //KpSolverBB(KpSolver * kp):KpSolver(kp){};


    void solve() override;


    void setInitialHeur(Heuristics h){heurParams.heurRootNode = h;};
    void setVerboseMode(uint i){bbParams.verboseMode = i;};
    //void setWarmstartMode(uint i){bbParams.warmStart = i;};
    size_t getNbNodes() const {return nbNodes;};



    //void solveRecursiveDFS();

};



