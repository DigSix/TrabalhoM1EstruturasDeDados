//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#ifndef SALENODE_CPP
#define SALENODE_CPP
#include "commons.cpp"
#include "ProductNode.cpp"

typedef struct Sale {
private:
    float totalPrice = 0.0;
    float discountedPrice = 0.0;
    string paymentOptions[3] = {
        "Débito",
        "Crédito",
        "Físico"
    };
    int paymentOption;
    string sellerOptions[5] = {
        "Márcio",
        "Maurício",
        "Marco",
        "Márcia",
        "Mariana"
    };
    int seller;

public:
    void create(float insertedTotalPrice, float insertedDiscountedPrice, int insertedPaymentOption, int insertedSeller) {
        totalPrice = insertedTotalPrice; discountedPrice = insertedDiscountedPrice; seller = insertedSeller; paymentOption = insertedPaymentOption;
    }

    float getTotalPrice() {
        return totalPrice;
    }

    float getDiscountedPrice() {
        return discountedPrice;
    }

    string getPaymentOption() {
        return paymentOptions[paymentOption];
    }

    int getPaymentOptionInt() {
        return paymentOption;
    }

    string getSeller() {
        return sellerOptions[seller];
    }

    int getSellerInt() {
        return seller;
    }

} Sale;

typedef struct SaleNode {
    Sale sale;
    int id = rand();

    SaleNode* previous = nullptr;
    SaleNode* next = nullptr;
} SaleNode;

#endif
