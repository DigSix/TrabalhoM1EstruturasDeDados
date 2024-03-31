//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "ProductNode.cpp"

/*struct ProductCart {
    ProductNode* start;
    ProductNode* end;

    bool insertProduct(Product insertedProduct){
        ProductNode* newNode = new ProductNode;
        if(newNode == nullptr) return false;
        newNode->product = insertedProduct;

        if(startNode == nullptr){
            startNode = newNode;
            endNode = newNode;
            length++;
            return true;
        }
        if(insertedProduct.getName() < startNode->product.getName()){
            startNode->previous = newNode;
            newNode->next = startNode;
            startNode = newNode;
            length++;
            return true;
        }
        if(insertedProduct.getName() > endNode->product.getName()){
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            length++;
            return true;
        }

        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->product.getName() >= insertedProduct.getName()){
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

    searchProductByName(){

    }

    searchProductBySize(){

    }

    searchProductByPrice(){
        
    }

};*/