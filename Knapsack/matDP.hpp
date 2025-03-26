#pragma once

#include "kpDefs.hpp"
#include <iostream>
//#include <fstream>
#include <vector>


class MatDP {
    
protected:
    uint nbRows;
    uint nbColumns;

    void computeLineDPaux(uint costItem, uint weightItem, T* old, T* temp);

public:

    MatDP(uint nbRow, uint nbCol): nbRows(nbRow), nbColumns(nbCol) {};
    virtual ~MatDP(){};

	virtual T getElement(uint row, uint col)=0;
    virtual void setElement(uint row, uint col, T val)=0;
    virtual T* operator[](uint row)=0;

    virtual void fillFirstLineDP(uint costItem, uint weightItem);
    virtual void computeLineDP(uint row, uint costItem, uint weightItem)=0;
    virtual void createLineDP(uint row){setElement(row,0,0);};
    virtual void display();

};


class MatDPvectVect  : public MatDP  {
private:
    vector<vector<T>> _matrixDP;

public:
    MatDPvectVect(uint nbRow, uint nbCol);
    ~MatDPvectVect() = default;

    T *operator[](uint row) override { return _matrixDP[row].data(); }; //transforme le vecteur en pointeur
    T getElement(uint row, uint col) override { return _matrixDP[row][col]; };
    void setElement(uint row, uint col, T val) override { _matrixDP[row][col] = val; };
    void computeLineDP(uint row, uint costItem, uint weightItem) override;
    void fillFirstLineDP(uint costItem, uint weightItem) override;
    void createLineDP(uint row) override;

};

class MatDPvect : public MatDP  {

private:

    vector<T> _matrixDP;

public:
    MatDPvect(uint nbRow, uint nbCol);
    ~MatDPvect() = default;

    T *operator[](uint row) override { return &_matrixDP[nbColumns * row]; };
    T getElement(uint row, uint col) override { return _matrixDP[nbColumns * row + col]; };
    void setElement(uint row, uint col, T val) override { _matrixDP[nbColumns * row + col] = val; };
    void computeLineDP(uint row, uint costItem, uint weightItem) override;
};

class MatDPtabTab  : public MatDP  {

private:
    T** _matrixDP;

public:
    MatDPtabTab(uint nbRow, uint nbCol);
    ~MatDPtabTab();                     

    T *operator[](uint row) override { return _matrixDP[row]; };
    T getElement(uint row, uint col) override { return _matrixDP[row][col]; };
    void setElement(uint row, uint col, T val) override { _matrixDP[row][col] = val; };
    void computeLineDP(uint row, uint costItem, uint weightItem) override;
};

class MatDPtab : public MatDP  {
private:
    T* _matrixDP;

public:
    MatDPtab(uint nbRow, uint nbCol);
    ~MatDPtab();

    T *operator[](uint row) override { return &_matrixDP[nbColumns * row]; };
    T getElement(uint row, uint col) override { return _matrixDP[nbColumns * row + col]; };
    void setElement(uint row, uint col, T val) override { _matrixDP[nbColumns * row + col] = val; };
    void computeLineDP(uint row, uint costItem, uint weightItem) override;
};
