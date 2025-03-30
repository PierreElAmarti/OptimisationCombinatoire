//********* kpSolver.cpp *********

#include "kpSolver.hpp"
#include <math.h>
#include <sstream>

void KpSolver::importInstance(const string& fileName) {

	clearInstance();

    ifstream infile;
    infile.exceptions(ifstream::failbit | ifstream::badbit);
    infile.open(fileName.c_str());

    infile >> nbItems;

    weights.resize(nbItems);
    for (int i = 0; i < nbItems; i++) infile >> weights[i];

    values.resize(nbItems);
    for (int i = 0; i < nbItems; i++) infile >> values[i];
    
    infile >> knapsackBound;

    sortKnapsack();


 }



void KpSolver::sortKnapsack() {

	vector<std::pair<std::pair<int,int>,float>> newStruct;

	std::pair <int,int> item;
	std::pair<std::pair<int,int>,float> itemCost;

	for (int i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		itemCost = make_pair(item,(float) values[i] / ((float) weights[i]) );
	        newStruct.push_back(itemCost);
	}	

	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) {return i.second > j.second;}
	);

	for (int i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first.first;
		values[i] = newStruct[i].first.second;		
	}
	newStruct.clear();
}

void KpSolver::clearInstance() {
	values.clear();
	weights.clear();
	nbItems = -1;

	solution.clear();
	costSolution=0;
	upperBoundOPT=0;
}

void KpSolver::printKnapsackInstance() {

	cout << "Max capacity knapsack : " << knapsackBound  << endl;

	for (int i = 0; i < nbItems; i++){
	        cout << "Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " Marginal Cost : " << (float) values[i] / ((float) weights[i])  << endl;
	}
	 cout << endl;	
 }

std::string KpSolver::printKnapsackSolution(bool printSol) {

	std::stringstream ss;
	

	cout << "solution cost : " << costSolution << endl;
	ss << costSolution << ";";

	cout << "proven upper bound  : " << upperBoundOPT << endl;
	ss << upperBoundOPT << ";";

	cout << "proven upper bound  after rounding: " << floor(upperBoundOPT) << endl;
	ss<<floor(upperBoundOPT)<<";";

	cout << "gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;
	ss<< (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100<<";";

	if (printSol){
	cout << "knapsack composition  : ";
	for (std::vector<bool>::iterator it = solution.begin() ; it != solution.end(); ++it)
		    std::cout << ' ' << *it;
	cout  << endl;
	}

	return ss.str();

}




void KpSolver::extractSubInstance(int idMin, int idMax) {

    idMin= max(0,idMin);
    idMax= min(nbItems,idMax);

	float numerator = 0;
	for (int i = idMin; i< idMax; i++){
		numerator += weights[i];
	}
	float denominator = 0 ;
	for (int i = 0; i < nbItems ; i++){
		denominator += weights[i];
	}
	knapsackBound =  (int) (((float) knapsackBound) * numerator / denominator) ;

	nbItems = idMax - idMin;
	vector<int> oldweights = weights ;
	vector <int> oldvalues = values ;

    weights.resize(nbItems);
    values.resize(nbItems);

	for (int i = 0; i<nbItems; i++){
		weights[i] = oldweights[i+idMin];
		values[i] = oldvalues[i+idMin];
	}
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
}/*
*/



void KpSolver::reindexMemo(bool sortMode) {

	vector<std::pair<std::pair<int,int>,float>> newStruct;

	std::pair <int,int> item;
	std::pair<std::pair<int,int>,float> itemCost;

	for (int i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		itemCost = make_pair(item,(float) weights[i] / ((float) values[i]) );
	        newStruct.push_back(itemCost);
	}

	if (sortMode) 	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) { return i.first.first < j.first.first;  }
	);
	else std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) { return i.first.first > j.first.first;  });

	for (int i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first.first;
		values[i] = newStruct[i].first.second;
	}
	newStruct.clear();
}

