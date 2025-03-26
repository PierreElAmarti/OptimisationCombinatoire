//********* kpSolver.cpp *********

#include "kpSolver.hpp"
#include <math.h>

#include <sstream>

void KpSolver::importInstance(const string& fileName) {
    ifstream infile;
    infile.exceptions(ifstream::failbit | ifstream::badbit);
    infile.open(fileName.c_str());
    infile >> nbItems;
    weights.resize(nbItems);
    for (uint i = 0; i < nbItems; i++) infile >> weights[i];
    values.resize(nbItems);
    for (uint i = 0; i < nbItems; i++) infile >> values[i];    
    infile >> knapsackBound;
    solution.resize(nbItems);
    sortKnapsack();
}

void KpSolver::importSolution(const vector<bool> &sol, T cost)
{
    if (cost>costSolution)
        {solution=sol; costSolution=cost;};
}


bool KpSolver::checkFeasibilitySolution(const vector<bool> & sol){
    uint computedWeight(0);
    for (uint i(0); i<nbItems ; i++){
        if (sol[i]){
            computedWeight += weights[i];
            if (computedWeight> knapsackBound) return false;
        }
    }
    return true;
}

T KpSolver::checkSolutionCost(const vector<bool> & sol){
    T computedCost(0);
    for (uint i(0); i<nbItems ; i++){
        if (sol[i]){
            computedCost += values[i];
        }
    }
    return computedCost;
}

bool KpSolver::isOptimal()
{
    return static_cast<T>(floor(upperBoundOPT)) <= costSolution;
}

KpSolver::KpSolver(KpSolver *kp):
    nbItems(kp->nbItems),
    knapsackBound(kp->knapsackBound),
    weights(kp->weights),
    values(kp->values),
    solution(kp->nbItems),
    costSolution(0),
    upperBoundOPT(0)
{

}

void KpSolver::sortKnapsack() {

    vector<std::pair<uint,uint>> newStruct;

    std::pair <uint,uint> item;

    for (uint i = 0; i < nbItems; i++){
        item = make_pair (weights[i],values[i]);
        newStruct.push_back(item);
    }

    std::sort(newStruct.begin(), newStruct.end(),
            [](pair<uint,uint> i, pair<uint,uint> j)
            {return
                static_cast<float>(i.second) / ( static_cast<float>(i.first))
                > static_cast<float>(j.second) / ( static_cast<float>(j.first));}
    );

    for (uint i = 0; i < nbItems; i++){
        weights[i] = newStruct[i].first;
        values[i] = newStruct[i].second;
    }
    newStruct.clear();
}



void KpSolver::printKnapsackInstance() {

	cout << "Max capacity knapsack : " << knapsackBound  << endl;

	for (uint i = 0; i < nbItems; i++){
            cout << "Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " Marginal Cost : " << static_cast<float>(values[i]) / static_cast<float>(weights[i])  << endl;
	}
	 cout << endl;	
 }
 

std::string KpSolver::printKnapsackSolution(bool printSol, std::string s) {

    std::stringstream ss;
    ss << s;

    ss << costSolution << ";";
	cout << "solution cost : " << costSolution << endl;

    ss << upperBoundOPT << ";";
	cout << "proven upper bound  : " << upperBoundOPT << endl;

    T rounded(static_cast<T> (floor(upperBoundOPT)));
    ss << rounded << ";";
    cout << "proven upper bound  after rounding: " << rounded << endl;

    ss << (floor(upperBoundOPT)- static_cast<double>(costSolution)) /( 0.01 * static_cast<double>(costSolution))  << ";";
    cout << "gap : " << (floor(upperBoundOPT)- static_cast<double>(costSolution)) /( 0.01 * static_cast<double>(costSolution)) << "%" << endl;

	if (printSol){
	cout << "knapsack composition  : ";
	for (std::vector<bool>::iterator it = solution.begin() ; it != solution.end(); ++it)
		    std::cout << ' ' << *it;
	cout  << endl;
	}

    return ss.str();
}




void KpSolver::extractSubInstance(uint idMin, uint idMax, uint newBound) {

    for (uint i(idMin); i<= idMax; i++){
        weights[i-idMin] = weights[i];
        values[i-idMin] = values[i];
	}
    knapsackBound = newBound;
    nbItems = idMax - idMin+1;
    weights.resize(nbItems);
    values.resize(nbItems);
}
/*
void KpSolver::exportSubInstance(string& fileName, int id1, int id2, float propFactor) {
	fileName.substr(0,fileName.size()-2);
	fileName+= "_";
	fileName+= id1;
	fileName+= "_";
	fileName+= id2;
	fileName+= "_";
	fileName+= propFactor;
	fileName+= ".in";

    ofstream outfile;
    outfile.exceptions(ofstream::failbit | ofstream::badbit);
    outfile.open(fileName.c_str());

    int newNbItems;
    long partialWeight=0;
    long totalWeight=0;

    id1=max(0,min(id1,nbItems-1));
    id2=min(max(0,id2),nbItems-1);

    outfile << id2-id1+1 << endl;
    for (unsigned int i = id1; i <= id2; ++i) {
    	partialWeight += weights[i];
    	outfile << weights[i] << " ";

    }

	for (std::vector<int>::iterator it = weights.begin() ; it != weights.end(); ++it)
		totalWeight += *it;


    outfile << endl;
    for (unsigned int i = id1; i <= id2; ++i) outfile << values[i] << " ";
    outfile << endl;
    outfile << (long) (propFactor * ((double) partialWeight)/((double) totalWeight));
}
*/


/*
void KpSolver::reindexMemo(bool sortMode) {

	vector<std::pair<std::pair<int,int>,float>> newStruct;

	std::pair <int,int> item;
	std::pair<std::pair<int,int>,float> itemCost;

	for (uint i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		itemCost = make_pair(item,(float) weights[i] / ((float) values[i]) );
	        newStruct.push_back(itemCost);
	}

	if (sortMode) 	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) { return i.first.first < j.first.first;  }
	);
	else std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) { return i.first.first > j.first.first;  });

	for (uint i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first.first;
		values[i] = newStruct[i].first.second;
	}
	newStruct.clear();
}
*/
