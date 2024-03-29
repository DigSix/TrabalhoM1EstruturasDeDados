//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"

struct Product{
    string name;
    string size;
    float price = 0.0;
    float discount = 0.95;
    int piecesForDiscount = 3;

    void create(string insertedName, string insertedSize, float insertedPrice, float insertedDiscount, int insertedAmount){
        name = insertedName; size = insertedSize; price = insertedPrice; piecesForDiscount = insertedAmount;

        insertedDiscount *= 0.01;
        discount = 1 - insertedDiscount;
    }
    void applyDiscount(int insertedAmount){
        if(insertedAmount >= piecesForDiscount){
            price *= discount;
        }
    }
};

struct ProductNode{
    Product product;
    int id = 0;

    ProductNode* previous = nullptr;
    ProductNode* next = nullptr;
};