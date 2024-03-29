//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "ProductNode.cpp"

struct Storage{
    ProductNode* startNode = nullptr;
    ProductNode* endNode = nullptr;
    int length = 0;

    private:
    void showProduct(ProductNode* insertedNode) {
        cout << insertedNode->id << " - [ Nome do produto: " << insertedNode->product.name << " ]";
        cout << "[ Tamanho do produto: " << insertedNode->product.size << " ]";
        cout << "[ Preco do produto: " << insertedNode->product.price << " ]\n";
    }

    void subtractID(int insertedID) {
        ProductNode* targetNode = startNode;
        while (targetNode != nullptr) {
            if (targetNode->id > insertedID) {
                targetNode->id--;
            }
            targetNode = targetNode->next;
        }
    }

    public:
    bool insertProduct(Product insertedProduct){
        ProductNode* newNode = new ProductNode;
        if(newNode == nullptr) return false;
        newNode->product = insertedProduct;
        newNode->id = length;

        if(startNode == nullptr){
            startNode = newNode;
            endNode = newNode;
            length++;
            return true;
        }
        if(insertedProduct.name < startNode->product.name){
            startNode->previous = newNode;
            newNode->next = startNode;
            startNode = newNode;
            length++;
            return true;
        }
        if(insertedProduct.name > endNode->product.name){
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            length++;
            return true;
        }

        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->product.name >= insertedProduct.name){
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

    public:
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
            subtractID(startNode->id);
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
            endNode->id--;
            length--;
            return true;
        }

        targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->id == insertedId){
                targetNode->next->previous = targetNode->previous;
                targetNode->previous->next = targetNode->next;
                subtractID(targetNode->id);
                delete targetNode;
                length--;
                return true;
            }
        targetNode = targetNode->next;
        }
        return false;
    }

    void showByNameAZ(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            showProduct(targetNode);
            targetNode = targetNode->next;
        }
    cout << "\n";
    }

    void showByNameZA(){
        ProductNode* targetNode = endNode;
        while(targetNode != nullptr){
            showProduct(targetNode);
            targetNode = targetNode->previous;
        }
    cout << "\n";
    }

    void showById(){
        ProductNode* targetNode;
        for(int i = 0; i <= length; i++){
            targetNode = startNode;
            while(targetNode != nullptr){
                if(targetNode->id == i){
                    showProduct(targetNode);
                }
                targetNode = targetNode->next;
            }
        }
    cout << "\n";
    }

    //searchProductByName(){}

    //searchProductBySize(){}

    //searchProductByPrice(){}

    //getFromFile(){}

    //save(){}
};