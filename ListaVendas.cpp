//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#ifndef LISTAVENDAS_CPP
#define LISTAVENDAS_CPP
#include "commons.cpp"
#include "SaleNode.cpp"

struct SaleList {
    SaleNode* startNode = nullptr;
    SaleNode* endNode = nullptr;
    int length = 0;

    bool insertSale(float insertedTotalPrice, float insertedPayedPrice, int paymentOption, int insertedSeller) {
        SaleNode* newNode = new SaleNode;
        if (newNode == nullptr) return false;

        newNode->sale.create( insertedTotalPrice, insertedPayedPrice, paymentOption, insertedSeller);

        if (startNode == nullptr) {
            startNode = newNode;
            endNode = newNode;
            length++;
            return true;
        }
        if (newNode->sale.getDiscountedPrice() < startNode->sale.getDiscountedPrice()) {
            startNode->previous = newNode;
            newNode->next = startNode;
            startNode = newNode;
            length++;
            return true;
        }
        if (newNode->sale.getDiscountedPrice() > endNode->sale.getDiscountedPrice()) {
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            length++;
            return true;
        }

        SaleNode* targetNode = startNode;
        while (targetNode != nullptr) {
            if (targetNode->sale.getDiscountedPrice() >= newNode->sale.getDiscountedPrice()) {
                newNode->next = targetNode;
                newNode->previous = targetNode->previous;
                targetNode->previous = newNode;
                newNode->previous->next = newNode;
                length++;
                return true;
            }
            targetNode = targetNode->next;
        }
        return false;
    }

    void showSales() {
        SaleNode* targetNode = startNode;
        while (targetNode != nullptr) {
            showSale(targetNode);
            targetNode = targetNode->next;
        }
        cout << "\n";
    }

    void showSale(SaleNode* targetNode) {
        cout << targetNode->id << " - [ Preço total: " << targetNode->sale.getTotalPrice() << " ]";
        cout << "[ Preço com descontos: " << targetNode->sale.getDiscountedPrice() << " ]";
        cout << "[ Opção de pagamento: " << targetNode->sale.getPaymentOption() << " ]";
        cout << "[ Vendedor: " << targetNode->sale.getSeller() << " ]\n";
    }

    void showSalesByPaymentOption() {
        SaleNode* targetNode = startNode;
        string paymentOptions[3] = {
            "Débito",
            "Crédito",
            "Físico"
        };
        float paymentOptionsValue[3] = {0,0,0};
        while (targetNode != nullptr) {
            paymentOptionsValue[targetNode->sale.getPaymentOptionInt()] += targetNode->sale.getDiscountedPrice();
            targetNode = targetNode->next;
        }
        for (int i = 0; i < 3; i++) {
            cout << "Vendas em " << paymentOptions[i] << " = " << paymentOptionsValue[i] << "\n";
        }

        cout << "\n";
    }

    void showSalesBySeller() {
        SaleNode* targetNode = startNode;
        string sellerOptions[5] = {
            "Márcio",
            "Maurício",
            "Marco",
            "Márcia",
            "Mariana"
        };
        float sellerValue[5] = {0,0,0,0,0};
        while (targetNode != nullptr) {
            sellerValue[targetNode->sale.getSellerInt()] += targetNode->sale.getDiscountedPrice();
            targetNode = targetNode->next;
        }
        for (int i = 0; i < 5; i++) {
            cout << "Vendas feitas por " << sellerOptions[i] << " = " << sellerValue[i] << "\n";
        }
        cout << "\n";
    }

};
#endif
