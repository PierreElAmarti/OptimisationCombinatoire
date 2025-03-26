//********* kpSolverDP.hpp *********

#include "kpSolverDPsparseV2.hpp"

//#include <omp.h>

void kpSolverDPsparseV2::deleteLine(uint id)
{
    if (lines[id].beginTab != nullptr)
        delete[] lines[id].beginTab;
}

T kpSolverDPsparseV2::getElement(uint id, uint m)
{
    LineDP* l (&lines[id]);
    if (m>l->endIndex) return l->lastVal;
    if (m<l->beginIndex) return 0;
    return l->beginTab[m-l->beginIndex];
}

void kpSolverDPsparseV2::backtrack(){
    solution.clear();
    solution.resize(nbItems, false);
    uint m(knapsackBound);
    for (uint i(nbItems-1); i >=1 ; i--){
        if (getElement(i-1,m) != getElement(i,m)){
            solution[i]=true;
            m -= weights[i];
            if (m==0) return;
        }
    }
    if (m >= weights[0]) solution[0]=true;
}


bool kpSolverDPsparseV2::initDP()
{

    //auto l = std::min_element(weights.begin(), weights.end());
    uint minWeight=*std::min_element(weights.begin(), weights.end());
    if (minWeight==0) minWeight=1;
    if (knapsackBound<minWeight){
        solution.clear();
        solution.resize(nbItems,false);
        costSolution = 0;
        upperBoundOPT = 0 ;
        return false;

    }
    lines = new LineDP[nbItems];
    lines[0].lastVal = values[0];
    lines[0].beginIndex = 1;//weights[0];
    lines[0].endIndex = weights[0];

    for (uint i(1); i< nbItems; i++){
        lines[i].endIndex=min(weights[i]+lines[i-1].endIndex,knapsackBound);
        lines[i].lastVal = values[i] + lines[i-1].lastVal;
        }

    if (lines[nbItems-1].endIndex<knapsackBound){
        solution.clear();
        solution.resize(nbItems,true);
        costSolution = lines[nbItems-1].lastVal;
        upperBoundOPT = costSolution ;
        return false;

    }
    lines[nbItems-1].beginIndex = knapsackBound;

    for(uint i(nbItems-2); i > 0 ; i--) {
        if (lines[i+1].beginIndex > weights[i+1] )
        lines[i].beginIndex= lines[i+1].beginIndex - weights[i+1];
        else lines[i].beginIndex =1;
        //cout << "valeur borne id : " << i << " : " << lowerBoundId[i] << endl;
        //if (indexLines[i].first ==1 )        break;
    }

    lines[0].beginTab = new T[weights[0]];
    for (uint i(0); i<weights[0]-1; i++)
        lines[0].beginTab[i]=0;
    lines[0].beginTab[weights[0]-1]=values[0];
/*
    for (uint i(1); i<nbItems; i++)
        lines[i].beginTab = new T[lines[i].endIndex - lines[i].beginIndex +1];
*/
   return true;
}

void kpSolverDPsparseV2::solve() {

    if (!initDP()) return;
/*
    for(auto lgn : lines){
        cout << "indices ligne : " << lgn.beginIndex << " ";
        cout << lgn.endIndex << " " << endl;
    }
*/
    LineDP* l(&lines[0]);
    LineDP* previousLine;

    for (uint i (1); i <nbItems ; i++) {
        lines[i].beginTab = new T[lines[i].endIndex - lines[i].beginIndex +1];

        previousLine = l;
        l = &lines[i];
        uint shift(previousLine->beginIndex);
        T* tab(previousLine->beginTab);
        T* tab_new(l->beginTab);
        uint shift_new(l->beginIndex);

        for (uint m (l->beginIndex); m <= previousLine->endIndex; m++) {
            tab_new[m-shift_new] =(tab[m-shift]);
        }
        for (uint m (previousLine->endIndex +1); m <= l->endIndex; m++) {
            tab_new[m-shift_new] =(previousLine->lastVal);
        }
        //matrixDP.push_back(l->lastVal);

        T* tab2 (l->beginTab);
        uint shift2(l->beginIndex);
        //T* tab0(previousLine->beginTab);


        for (uint m (max(weights[i],shift2)); m <= l->endIndex; m++) {
            uint temp (getElement(i-1,m-weights[i])+values[i]);
            //uint temp (tab[m-weights[i]-shift]+values[i]);

            if(tab2[m-shift2]< temp) tab2[m-shift2]= temp;
        }

    }
/*
    cout << "\n Affiche DP matrix complete " << endl;
    printMatrixDP();

    cout << "\n Affiche lignes DP matrix " << endl;

    for (uint i(0); i<nbItems; i++){


    //for(auto lgn : lines){
        cout << lines[i].beginIndex << " ";
        cout << lines[i].endIndex << " " << endl;
        for (uint m (lines[i].beginIndex); m <= lines[i].endIndex; m++) {
            cout << lines[i].beginTab[m-lines[i].beginIndex] << " ";
            }
        cout << " fin ligne " << endl;

    }

    */
    //costSolution = l->beginTab[l->endIndex-l->beginIndex]; //matrixDP.back();
    costSolution = l->beginTab[0];


//	if (verboseMode) cout << " DP matrix filled: " << endl;
	upperBoundOPT = costSolution ;
//	if (verboseMode) cout << "backtrack operations:" << endl;

    //solution.resize(nbItems);

    backtrack();

    for (uint i(0); i<nbItems; i++)
        deleteLine(i);

    /*
    solution.clear();
    solution.resize(nbItems, false);
    uint m (knapsackBound);
    for (uint i(nbItems-1); i >=1 ; i--){
        if (getElement(i-1,m) != getElement(i,m)){
            solution[i]=true;
            m -= weights[i];
            if (m==0) return;
        }
    }
    if (m >= weights[0]) solution[0]=true;
*/

    //matrixDP.clear();
}

void kpSolverDPsparseV2::printMatrixDP() {

    //uint M = knapsackBound+1;
	cout << "print DP matrix : " << endl;

    for(uint i (0); i < nbItems; i++){
        for(uint j(0); j <= knapsackBound; j++)
            cout <<  getElement(i,j) << " "  ;
		cout << endl;
	}
}


