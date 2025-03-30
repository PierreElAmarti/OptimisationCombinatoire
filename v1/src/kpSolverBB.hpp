//********* kpSolverBB.hpp *********

#ifndef KPSOLVERBB_HPP
#define KPSOLVERBB_HPP

#include "kpSolver.hpp"
#include "nodeBB.hpp"
#include <deque>


enum BranchingStrategies { BestBound,  DFS10, DFS01, BFS, Random,End};



class  KpSolverBB : public KpSolver {

private:
    deque<NodeBB*> nodes;
    int nbNodes;
    int nbMaxNodeBB;
    bool withPrimalHeuristics;
    bool verboseMode;
    bool withDPinitPrimalHeuristic;
    int sizeDPheur;

    BranchingStrategies branchingStrategy;
/*
    bool modeBranchBFS;
    bool modeBranchDFS;
    bool modeBranchBestBound;
    bool modeBranchOBefore1;
*/
    void solveUpperBound();
    void printStatus();
    void removeNodes();

    double getUpperBound();

    NodeBB* selectNode();
    NodeBB* selectNodeRandom();/*
    NodeBB* selectNodeBestBound();
    NodeBB* selectNodeBFS();
    NodeBB* selectNodeDFS();*/

    void insertNode(NodeBB* nod);
    void insertNodes(NodeBB* nod1, NodeBB* nod2);

    void insertNodesBestBound(NodeBB* nod1, NodeBB* nod2);
    void insertNodesBFS(NodeBB* nod1, NodeBB* nod2);
    void insertNodesDFS(NodeBB* nod1, NodeBB* nod2);

    void init();

public:

    void solve();
/*
    void setModeBFS(){modeBranchBestBound =false; modeBranchBFS =true; modeBranchDFS =false;};
    void setModeDFS(){modeBranchBestBound =false; modeBranchBFS =false; modeBranchDFS =true;};
    void setModeBestBound(){modeBranchBestBound =true; modeBranchBFS =false; modeBranchDFS =false;};
*/
    void solveRecursiveDFS();

	void setNbMaxNodeBb(int nbMaxNodeBb) {	nbMaxNodeBB = nbMaxNodeBb;};
	void setVerboseMode(bool vMode){verboseMode = vMode;};
	void setWithPrimalHeuristics(bool withHeuristics) {withPrimalHeuristics = withHeuristics;};
	void setWithDPinitPrimalHeuristic(bool withHeuristic) {withDPinitPrimalHeuristic = withHeuristic;};
	void setSizeDPheur(int siz) {sizeDPheur = siz;};
	void setBranchingStrategy(BranchingStrategies bStrategy) {branchingStrategy = bStrategy;};
	int getNbNodes() const {return nbNodes;};


};



#endif
