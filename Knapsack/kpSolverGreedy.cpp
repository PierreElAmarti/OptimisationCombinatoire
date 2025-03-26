//********* knapsackGreedy.cpp *********

#include "kpSolverGreedy.hpp"


std::pair<std::pair<uint, uint>, T> KpSolverGreedy::solveGreedyUpperBound()
{


    T intValue(0);
    uint remaining(knapsackBound);
    uint id(0);


    while(id < nbItems){
        if (weights[id] > remaining) break;
            remaining -= weights[id];
            intValue += values[id];
            id++;

    }
    std::pair<std::pair<uint, uint>, T> p;
    p.first.first = id;
    p.first.second = remaining;
    p.second = intValue;
    return p;
}

/*
void KpSolverGreedy::solveGreedyUpperBound() {

	upperBoundOPT=0;
    float remaining = knapsackBound;
    int id = 0;
    bool b = true;

    while(b &&remaining >0 && id < nbItems){
    	//cout << " Item: " << id << " Weight : " << weights[id]  << " Value : " << values[id] << " remaining : "<< remaining << endl;
    	if (weights[id] <= remaining) {
    		remaining -= weights[id];
    		upperBoundOPT += values[id];
    		id++;
    	}
    	else b = false;

	}

    if (id< nbItems && (!b)) upperBoundOPT += ((float) values[id])  * remaining /  ((float) weights[id]);

    //if (id< nbItems)  cout << " additional cost : " << ((float) values[id])  * remaining /  ((float) weights[id]) << endl;

 }
*/
void KpSolverGreedy::solveGreedyLowerBound() {

    costSolution=0;
    uint remaining = knapsackBound;

    for (uint i = 0; i < nbItems; i++){
		if (weights[i] <= remaining){
			remaining -= weights[i];
			costSolution += values[i];
			solution[i]=true;
		}
	}
 }

void KpSolverGreedy::solve() {
    std::pair<std::pair<uint, uint>, T> p(solveGreedyUpperBound());
    uint i(p.first.first);
    upperBoundOPT = static_cast<double>(p.second) +
    static_cast<double>(values[i]*p.first.second)   /  (static_cast<double>(weights[i]));
    solveGreedyLowerBound();
}
