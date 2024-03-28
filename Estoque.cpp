//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "ProductNode.cpp"

struct Storage{
    ProductNode* startNode = nullptr;
    ProductNode* endNode = nullptr;
    int lenght = 0;

    bool insertProduct(Product insertedProduct){
        ProductNode* newNode = new ProductNode;
        if(newNode == nullptr) return false;
        newNode->product = insertedProduct;
        newNode->id = lenght;

        if(startNode == nullptr){
            startNode = newNode;
            endNode = newNode;
            lenght++;
            return true;
        }
        if(insertedProduct.name < startNode->product.name){
            startNode->previous = newNode;
            newNode->next = startNode;
            startNode = newNode;
            lenght++;
            return true;
        }
        if(insertedProduct.name > endNode->product.name){
            endNode->next = newNode;
            newNode->previous = endNode;
            endNode = newNode;
            lenght++;
            return true;
        }

        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->product.name >= insertedProduct.name){
                newNode->next = targetNode;
                newNode->previous = targetNode->previous;
                targetNode->previous = newNode;
                newNode->previous ->next = newNode;
                lenght++;
                return true;
            }
            targetNode = targetNode->next;
        }
        return false;
    }

    private:
    void subtractID(ProductNode* insertedNode){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->id > insertedNode->id){
                targetNode->id--;
            }
            targetNode = targetNode->next;
        }
    }

    public:
    bool removeProduct(int insertedId){
        ProductNode* targetNode;

        if(startNode->id == insertedId & endNode == startNode){
            targetNode = startNode;
            startNode = nullptr;
            endNode = nullptr;
            delete targetNode;
            lenght--;
            return true;
        }
        if(startNode->id == insertedId){
            subtractID(startNode);
            targetNode = startNode;
            startNode = targetNode->next;
            startNode->previous = nullptr;
            delete targetNode;
            lenght--;
            return true;
        }
        if(endNode->id == insertedId){
            targetNode = endNode;
            endNode = targetNode->previous;
            endNode->next = nullptr;
            delete targetNode;
            endNode->id--;
            lenght--;
            return true;
        }

        targetNode = startNode;
        while(targetNode != nullptr){
            if(targetNode->id == insertedId){
                targetNode->next->previous = targetNode->previous;
                targetNode->previous->next = targetNode->next;
                subtractID(targetNode);
                delete targetNode;
                lenght--;
                return true;
            }
        targetNode = targetNode->next;
        }
        return false;
    }

    void showAZ(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            cout << targetNode->id << " - [ Nome do produto: " << targetNode->product.name << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.size << " ]";
            cout << "[ Preco do produto: " << targetNode->product.price << " ]\n";
            targetNode = targetNode->next;
        }
    cout << "\n";
    }

    void showZA(){
        ProductNode* targetNode = endNode;
        while(targetNode != nullptr){
            cout << targetNode->id << " - [ Nome do produto: " << targetNode->product.name << " ]";
            cout << "[ Tamanho do produto: " << targetNode->product.size << " ]";
            cout << "[ Preco do produto: " << targetNode->product.price << " ]\n";
            targetNode = targetNode->previous;
        }
    cout << "\n";
    }

    void showById(){
        ProductNode* targetNode;
        for(int i = 0; i <= lenght; i++){
            targetNode = startNode;
            while(targetNode != nullptr){
                if(targetNode->id == i){
                    cout << targetNode->id << " - [ Nome do produto: " << targetNode->product.name << " ]";
                    cout << "[ Tamanho do produto: " << targetNode->product.size << " ]";
                    cout << "[ Preco do produto: " << targetNode->product.price << " ]\n";
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