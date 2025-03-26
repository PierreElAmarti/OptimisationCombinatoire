//********* stopBB.hpp *********

#pragma once

#include "kpDefs.hpp"



//TODO: rajouter limite de temps? epagap, eprgap,
class StopCriterionBB{

//protected:
//    KpSolver* kp;

public:
    virtual ~StopCriterionBB();
    virtual bool continueBB(size_t nbNod, size_t nbNodMem)=0;
};

/*
class MemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeInMemory;

public:
    ~MemLim()=default;
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNodMem < nbMaxNodeInMemory ;};
     MemLim(size_t n): nbMaxNodeInMemory(n) {};
};

class NodeLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;

public:
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNod < nbMaxNodeBB ;};
     NodeLim(size_t n): nbMaxNodeBB(n) {};
};
*/
/*
class NodeMemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;
    size_t nbMaxNodeInMemory;
public:
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNod < nbMaxNodeBB && nbNodMem < nbMaxNodeInMemory;};
     NodeMemLim(size_t n1,size_t n2): nbMaxNodeBB(n1),nbMaxNodeInMemory(n2) {};
};
*/
