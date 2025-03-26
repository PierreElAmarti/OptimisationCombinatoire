#include "matDP.hpp"

void MatDP::fillFirstLineDP(uint costItem, uint weightItem) {

    for(uint m = 0; m < weightItem; m++) setElement(0,m,0);
    for(uint m = weightItem; m < nbColumns; m++) setElement(0,m,costItem);

}


void MatDP::computeLineDPaux(uint costItem, uint weightItem, T* old , T* temp)
{
    for (uint m = 0; m < nbColumns; ++m) temp[m] = old[m];

    uint lb = weightItem;
    if (lb==0) lb=1;

    for (uint m = nbColumns-1; m >= lb; --m) {

        if (temp[m-weightItem] + costItem > temp[m]) {
            temp[m] = temp[m-weightItem] + costItem;
        }
    }


}


MatDPtabTab::MatDPtabTab(uint nbRow, uint nbCol): MatDP(nbRow, nbCol) {
    _matrixDP = new T* [nbRow];
    _matrixDP[0] = new T [nbCol];
    for(uint i = 1; i < nbRow; i++){
        _matrixDP[i] = new T [nbCol];
	}
}

MatDPtabTab::~MatDPtabTab(){
    for(uint i = 0; i < nbRows; i++){
		delete [] _matrixDP[i];
	}
	delete [] _matrixDP;
}


MatDPtab::MatDPtab(uint nbRow, uint nbCol): MatDP(nbRow, nbCol){
    _matrixDP=new T[nbRow*nbCol];
}

MatDPtab::~MatDPtab(){
    delete[] _matrixDP;
}


/*
void MatDP::computeLineDP(uint row, uint costItem, uint weightItem){

    setElement(row,0,0);

    for (uint m = 1; m < nbColumns; ++m)
        setElement(row,m,getElement(row-1,m));

    for (uint m = nbColumns-1; m >= 1; --m) {
        T aux = getElement(row, m-weightItem) + costItem;

        if (m >= weightItem && aux > getElement(row, m)) {
            setElement(row,m,aux);
        }
    }
}
*/
void MatDP::display()
{
    cout << "print DP matrix : " << endl;

    for(uint i = 0; i < nbRows; i++){
        for(uint j = 0; j < nbColumns; j++)
            cout <<  getElement(i,j) << " "  ;
        cout << endl;
    }
}



/*
MatDPvectVect::MatDPvectVect(uint nbRow, uint nbCol)
    : MatDP(nbRow,nbCol), _matrixDP(nbRow, vector<T>(nbCol, 0))
{
}*/

MatDPvectVect::MatDPvectVect(uint nbRow, uint nbCol)
    : MatDP(nbRow,nbCol), _matrixDP(nbRow)
{
    _matrixDP.shrink_to_fit();

}

void MatDPvectVect::fillFirstLineDP(uint costItem, uint weightItem)
{
    _matrixDP[0].clear();
    _matrixDP[0].resize(weightItem,0);
    _matrixDP[0].resize(nbColumns,costItem);
    _matrixDP[0].shrink_to_fit();

}


void MatDPvectVect::createLineDP(uint row)
{
    _matrixDP[row].resize(nbColumns,0);
    _matrixDP[row].shrink_to_fit();
}

void MatDPvectVect::computeLineDP(uint row, uint costItem, uint weightItem){

    _matrixDP[row] = _matrixDP[row-1];
    T* temp = _matrixDP[row].data();

    uint lb = weightItem;
    if (lb==0) lb=1;

    for (uint m = nbColumns-1; m >= lb; --m) {
        if (temp[m-weightItem] + costItem > temp[m]) {
            temp[m] = temp[m-weightItem] + costItem;
        }
    }

}

void MatDPtabTab::computeLineDP(uint row, uint costItem, uint weightItem) {

    T* temp = _matrixDP[row];
    T* old = _matrixDP[row-1];
    computeLineDPaux(costItem,weightItem, old , temp);
}

void MatDPtab::computeLineDP(uint row, uint costItem, uint weightItem){
    T* temp = &_matrixDP[nbColumns * row];
    T* old = &_matrixDP[nbColumns * (row-1)];
    computeLineDPaux(costItem,weightItem, old , temp);

}

void MatDPvect::computeLineDP(uint row, uint costItem, uint weightItem)
{
    T* temp = &_matrixDP[nbColumns * row];
    T* old = &_matrixDP[nbColumns * (row-1)];
    computeLineDPaux(costItem,weightItem, old , temp);
}


MatDPvect::MatDPvect(uint nbRow, uint nbCol) : MatDP(nbRow,nbCol), _matrixDP(nbCol*nbRow, 0)
{
    _matrixDP.shrink_to_fit();
}


