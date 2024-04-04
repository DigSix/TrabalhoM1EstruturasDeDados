//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#ifndef SALENODE_CPP
#define SALENODE_CPP
#include "commons.cpp"

typedef struct Sale {
private:


public:
    
} Sale;

typedef struct SaleNode {
    Sale sale;
    int id = rand();

    SaleNode* previous = nullptr;
    SaleNode* next = nullptr;

    void setId(int newId) {
        id = newId;
    }
} SaleNode;

#endif
