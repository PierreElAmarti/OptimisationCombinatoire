//********* kpSolverDP.hpp *********

#pragma once
#include "kpSolver.hpp"
#include "matDP.hpp"
#include <memory>
#include <string>

enum class MatDPType { 
    MatDPvectVect, 
    MatDPvect, 
    MatDPtabTab,
    MatDPtab    
};

string tostring(MatDPType);

class  KpSolverDP : public KpSolver {

protected:    

    std::unique_ptr<MatDP> _matDP;
    MatDPType _type;

    void backtrack();

public:
    virtual ~KpSolverDP(){};

    //virtual void solve() =0;


    //affichage de la matrice de prog dynamique
    void printMatrixDP(); 

    KpSolverDP(std::string const & filenaKpSolverDP2me,  MatDPType type= MatDPType::MatDPvect);
    KpSolverDP(KpSolver * kp):KpSolver(kp){_matDP= std::make_unique<MatDPtab>(nbItems, knapsackBound+1); };


};


class  KpSolverDPv0 : public KpSolverDP {
public:
    KpSolverDPv0(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};

class  KpSolverDPv1 : public KpSolverDP {
public:
    KpSolverDPv1(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};

class  KpSolverDPv1bis : public KpSolverDP {
public:
    KpSolverDPv1bis(std::string const & filename,  MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};

    void solve() override;
};


class  KpSolverDPv2 : public KpSolverDP {
public:
    KpSolverDPv2(std::string const & filename, MatDPType type = MatDPType::MatDPvect)
        : KpSolverDP(filename, type){};
    //KpSolverDPv2(vector<uint>  w, vector<uint>  c, uint kpBound, MatDPType type = MatDPType::MatDPvect);
    KpSolverDPv2(KpSolver * kp):KpSolverDP(kp){};

    void solve() override;
};

