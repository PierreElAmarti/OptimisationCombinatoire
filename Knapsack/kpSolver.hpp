//********* kpSolver.hpp *********

#pragma once
#include "kpDefs.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class KpSolver {

private:

    void sortKnapsack();        
    void importInstance(const string& fileName); // Reads instance data.
    bool checkFeasibilitySolution(const vector<bool> & sol);
    T checkSolutionCost(const vector<bool> & sol);

protected:
    // Items and knapsack properties.
    uint nbItems; // Number of items.
    uint  knapsackBound;     // Knapsack bound
    vector<uint> weights; //weights of items
    vector<uint> values; //values of items

    // Solution (items in the knapsack).
    vector<bool> solution;
    T costSolution;
    double upperBoundOPT;

    bool isOptimal();




public:

    KpSolver(std::string const & filename) : costSolution(0) {importInstance(filename);}
    KpSolver(KpSolver * kp);

    virtual ~KpSolver()=default;

    virtual void solve()=0;


    void importSolution(const vector<bool> & sol, T cost);
    void extractSubInstance(uint idMin, uint idMax, uint newBound);


    //std::pair <std::pair<uint, double>,double> greedyUB();
    void printKnapsackInstance();
    std::string printKnapsackSolution(bool printSol,std::string s);
    //void reindexMemo(bool sortMode);

    double getUpperBound(){return upperBoundOPT;};
    T getSolutionCost(){return costSolution;};
    bool isSelected(uint item){return solution[item];};

	//void exportSubInstance(string& fileName, int id1, int id2, float propFactor);
    uint getNbItems() const {return nbItems;	};
    uint getKnapsackBound() const {return knapsackBound;	};
    uint getWeight(uint i){return weights[i];};
    uint getValue(uint i){return values[i];};

};
