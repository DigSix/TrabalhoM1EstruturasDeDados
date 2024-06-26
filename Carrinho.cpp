//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#ifndef CARRINHO_CPP
#define CARRINHO_CPP
#include "commons.cpp"
#include "ProductNode.cpp"

struct ProductCart {
    ProductNode* startNode = nullptr;
    ProductNode* endNode = nullptr;
    int length = 0;

    bool insertProduct(Product insertedProduct, int id, int amount){
        ProductNode* newNode = new ProductNode;
        if(newNode == nullptr) return false;

        newNode->product.overwriteProduct(insertedProduct);
        newNode->product.setAmount(amount);
        newNode->setId(id);

        if(startNode == nullptr){
            startNode = newNode;
            endNode = newNode;
            length++;
            return true;
        }
        if(newNode->product.getName() < startNode->product.getName()){
            startNode->previous = newNode;
            newNode->next = startNode;
            startNode = newNode;
            length++;
            return true;
        }
        if(newNode->product.getName() > endNode->product.getName()){
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            length++;
            return true;
        }

        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->product.getName() >= newNode->product.getName()){
                newNode->next = targetNode;
                newNode->previous = targetNode->previous;
                targetNode->previous = newNode;
                newNode->previous ->next = newNode;
                length++;
                return true;
            }
            targetNode = targetNode->next;
        }
        return false;
    }

    bool removeProduct(int insertedId){
        ProductNode* targetNode;

        if(startNode->id == insertedId && endNode == startNode){
            targetNode = startNode;
            startNode = nullptr;
            endNode = nullptr;
            delete targetNode;
            length--;
            return true;
        }
        if(startNode->id == insertedId){
            targetNode = startNode;
            startNode = targetNode->next;
            startNode->previous = nullptr;
            delete targetNode;
            length--;
            return true;
        }
        if(endNode->id == insertedId){
            targetNode = endNode;
            endNode = targetNode->previous;
            endNode->next = nullptr;
            delete targetNode;
            length--;
            return true;
        }

        targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->id == insertedId){
                targetNode->next->previous = targetNode->previous;
                targetNode->previous->next = targetNode->next;
                delete targetNode;
                length--;
                return true;
            }
        targetNode = targetNode->next;
        }
        return false;
    }

    void emptyCart() {
        while (length) {
            removeProduct(endNode->id);
        }
    }

    void showProduct(ProductNode* insertedNode) {
        cout << insertedNode->id << " - [ Nome do produto: " << insertedNode->product.getName() << " ]";
        cout << "[ Tamanho do produto: " << insertedNode->product.getSize() << " ]";
        cout << "[ Preco do produto: " << insertedNode->product.getPrice() << " ]";
        cout << "[ Quantidade: " << insertedNode->product.getAmount() << " ]\n";
    }

    void showProductAndPrice(ProductNode* insertedNode) {
        cout << insertedNode->id << " - [ Nome do produto: " << insertedNode->product.getName() << " ]";
        cout << "[ Tamanho do produto: " << insertedNode->product.getSize() << " ]";
        cout << "[ Preco do produto: " << insertedNode->product.getPrice() << " ]";
        cout << "[ Quantidade: " << insertedNode->product.getAmount() << " ]";
        cout << " = " << getProductPrice(insertedNode) << "\n";
    }

    void showByNameAZ() {
        ProductNode* targetNode;
        targetNode = startNode;
        while (targetNode != nullptr) {
            showProduct(targetNode);
            targetNode = targetNode->next;
        }
        cout << "\n";
    }

    void showByNameAZAndPrice() {
        ProductNode* targetNode;
        targetNode = startNode;
        while (targetNode != nullptr) {
            showProductAndPrice(targetNode);
            targetNode = targetNode->next;
        }
        cout << "\n";
    }

    ProductNode* getProductNodeById(int productId) {
        ProductNode* targetNode = startNode;

        while (targetNode != nullptr) {
            if (productId == targetNode->id) {
                return targetNode;
            }
            targetNode = targetNode->next;
        }
    }

    float getProductTotalPrice(ProductNode* productNode) {
        float productPrice = productNode->product.getPrice() * productNode->product.getAmount();
        return productPrice;
    }

    float getProductPrice(ProductNode* productNode) {
        float productPrice = productNode->product.getPrice() * productNode->product.getAmount();
        if (productNode->product.getAmount() >= productNode->product.getPiecesForDiscount()) {
            productPrice *= productNode->product.getDiscount();
        }

        return productPrice;
    }

    float getCartPrice() {
        float totalPrice = 0;
        ProductNode* targetNode;
        targetNode = startNode;
        while (targetNode != nullptr) {
            float productPrice = getProductPrice(targetNode);
            totalPrice += productPrice;
            targetNode = targetNode->next;
        }
        return totalPrice;
    }

    float getCartTotalPrice() {
        float totalPrice = 0;
        ProductNode* targetNode;
        targetNode = startNode;
        while (targetNode != nullptr) {
            float productPrice = getProductTotalPrice(targetNode);
            totalPrice += productPrice;
            targetNode = targetNode->next;
        }
        return totalPrice;
    }

};
#endif
