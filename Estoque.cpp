#include "commons.cpp"
#include "ProductNode.cpp"

struct Storage{
    ProductNode* startNode = nullptr;
    ProductNode* endNode = nullptr;

    bool insertProduct(Product insertedProduct){
        ProductNode* newNode = new ProductNode;
        if(newNode == nullptr) return false;
        newNode->product = insertedProduct;

        if(startNode == nullptr){
            startNode = newNode;
            endNode = newNode;
            return true;
        }
        if(insertedProduct.name < startNode->product.name){
            newNode->next = startNode;
            startNode->previous = newNode;
            startNode = newNode;
            return true;
        }
        if(insertedProduct.name > endNode->product.name){
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            return true;
        }

        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->product.name < insertedProduct.name && insertedProduct.name < targetNode->next->product.name){
                newNode->previous = targetNode;
                newNode->next = targetNode->next;
                targetNode->next = newNode;
                newNode->next->previous = newNode;
                return true;
            }
            targetNode = targetNode->next;
        }
        return false;
    }

    //removeProduct(){}

    void showAZ(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            cout << "[ Nome do produto: " << targetNode->product.name << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.size << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.price << " ]\n";
            targetNode = targetNode->next;
        }
    cout << "\n";
    }

    void showZA(){
        ProductNode* targetNode = endNode;
        while(targetNode != nullptr){
            cout << "[ Nome do produto: " << targetNode->product.name << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.size << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.price << " ]\n";
            targetNode = targetNode->previous;
        }
    cout << "\n";
    }

    //searchProductByName(){}

    //searchProductBySize(){}

    //searchProductByPrice(){}

    //getFromFile(){}

    //save(){}
};