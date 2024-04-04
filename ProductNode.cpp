//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#ifndef PRODUCTNODE_C++
#define PRODUCTNODE_C++
#include "commons.cpp"

typedef struct Product{
    private:
    string name;
    string size;
    float price = 0.0;
    float discount = 0.95;
    int piecesForDiscount = 3;
    int amount = 0;

    public:
    void create(string insertedName, string insertedSize, float insertedPrice, float insertedDiscount,int insertedPiecesForDiscount, int insertedAmount){
        name = insertedName; size = insertedSize; price = insertedPrice; piecesForDiscount = insertedPiecesForDiscount; amount = insertedAmount;

        insertedDiscount *= 0.01;
        discount = 1 - insertedDiscount;
    }
    void overwriteProduct(Product insertedProduct) {
        name = insertedProduct.name;
        size = insertedProduct.size;
        price = insertedProduct.price;
        discount = insertedProduct.discount;
        amount = insertedProduct.amount;
    }
    void setName(string insertedName){
        name = insertedName;
    }
    void setSize(string insertedSize){
        size = insertedSize;
    }
    void setPrice(float insertedPrice){
        price = insertedPrice;
    }
    void setDiscount(float insertedDiscount){
        insertedDiscount *= 0.01;
        discount = 1 - insertedDiscount;
    }
    void setPiecesForDiscount(int insertedPiecesForDiscount){
        piecesForDiscount = insertedPiecesForDiscount;
    }
    void setAmount(int insertedAmount){
        amount = insertedAmount;
    }

    string getName(){
        return name;
    }

    string getSize(){
        return size;
    }

    float getPrice(){
        return price;
    }

    float getDiscount(){
        return discount;
    }

    int getPiecesForDiscount(){
        return piecesForDiscount;
    }

    int getAmount(){

        return amount;
    }

} Product;

typedef struct ProductNode{
    Product product;
    int id = rand();

    ProductNode* previous = nullptr;
    ProductNode* next = nullptr;

    void setId(int newId) {
        id = newId;
    }
} ProductNode;

#endif
