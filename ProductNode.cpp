//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"

struct Product{
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
    void applyDiscount(int insertedAmount){
        if(insertedAmount >= piecesForDiscount){
            price *= discount;
        }
    }
    void overwriteProduct(Product insertedProduct) {
        name = insertedProduct.name;
        size = insertedProduct.size;
        price = insertedProduct.price;
        discount = insertedProduct.discount;
        amount = insertedProduct.amount;
    }
    void overwriteName(string insertedName){
        name = insertedName;
    }
    void overwriteSize(string insertedSize){
        size = insertedSize;
    }
    void overwritePrice(float insertedPrice){
        price = insertedPrice;
    }
    void overwriteDicount(float insertedDiscount){
        insertedDiscount *= 0.01;
        discount = 1 - insertedDiscount;
    }
    void overwritePiecesForDiscount(int insertedPiecesForDiscount){
        piecesForDiscount = insertedPiecesForDiscount;
    }
    void overwriteAmount(int insertedAmount){
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
    void setPrice(float newPrice) {
        price = newPrice;
    }

    float getDiscount(){
        int returnedDiscount = (1 - discount) * 100;
        return returnedDiscount;
    }

    int getPiecesForDiscount(){
        return piecesForDiscount;
    }

    int getAmount(){

        return amount;
    }

};

struct ProductNode{
    Product product;
    int id = rand();

    ProductNode* previous = nullptr;
    ProductNode* next = nullptr;
};