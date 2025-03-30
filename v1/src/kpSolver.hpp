//********* kpSolver.hpp *********

#ifndef KPSOLVER_HPP
#define KPSOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class KpSolver {

private:
    void sortKnapsack();


protected:

    // Items and knapsack properties.
    int nbItems; // Number of items.
    vector<int> weights; //weights of items
    vector<int> values; //values of items
    int knapsackBound;     // Knapsack bound

    // Solution (items in the knapsack).
    vector<bool> solution;
    long costSolution;
    double upperBoundOPT;




public:
    

    // Reads instance data. 
    void importInstance(const string& fileName);
    void printKnapsackInstance();
    void printKnapsackSolution(bool printSol);
    void reindexMemo(bool sortMode);

	int getUpperBound(){return upperBoundOPT;};
	int getSolutionCost(){return costSolution;};
	bool isSelected(int item){return solution[item];};

	//void exportSubInstance(string& fileName, int id1, int id2, float propFactor);
	void extractSubInstance(int idMin, int idMax);

    void clearInstance();

	int getNbItems() const {return nbItems;	};
};

#endif

