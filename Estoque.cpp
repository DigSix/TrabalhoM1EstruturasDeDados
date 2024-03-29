//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "ProductNode.cpp"

struct Storage{
    private:
    ProductNode* startNode = nullptr;
    ProductNode* endNode = nullptr;
    int length = 0;

    private:
    void showProduct(ProductNode* insertedNode) {
        cout << insertedNode->id << " - [ Nome do produto: " << insertedNode->product.getName() << " ]";
        cout << "[ Tamanho do produto: " << insertedNode->product.getSize() << " ]";
        cout << "[ Preco do produto: " << insertedNode->product.getPrice() << " ]\n";
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

    void showAZ(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr){
            showProduct(targetNode);
            targetNode = targetNode->next;
        }
    cout << "\n";
    }

    void showZA(){
        ProductNode* targetNode = endNode;
        while(targetNode != nullptr){
            showProduct(targetNode);
            targetNode = targetNode->previous;
        }
    cout << "\n";
    }

    bool isOrdenedByName(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;
            if(nextNode->product.getName() < targetNode->product.getName()){
                return false;
            }      
            targetNode = nextNode;
        }
        return true;
    }

    bool isOrdenedBySize(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;
            if(nextNode->product.getSize() < targetNode->product.getSize()){
                return false;
            }      
            targetNode = nextNode;
        }
        return true;
    }

    bool isOrdenedByPrice(){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;
            if(nextNode->product.getPrice() < targetNode->product.getPrice()){
                return false;
            }      
            targetNode = nextNode;
        }
        return true;
    }

    void sortByName(){
        while(!this->isOrdenedByName()){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;

                if(nextNode->product.getName() < targetNode->product.getName()){
                    if(targetNode->previous != nullptr){
                        targetNode->previous->next = nextNode;
                    }
                    if(nextNode->next != nullptr){
                        nextNode->next->previous = targetNode;
                    }
            
                    targetNode->next = nextNode->next;
                    nextNode->next = targetNode;
                    nextNode->previous = targetNode->previous;
                    targetNode->previous = nextNode;

                    if(targetNode == startNode){
                        startNode = nextNode;
                    }
                    if(nextNode == endNode){
                        endNode = targetNode;
                    }
                }
                else{
                    targetNode = nextNode;
                }
            }
        }
    }

    void sortBySize(){
        while(!this->isOrdenedBySize()){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;

                if(nextNode->product.getSize() < targetNode->product.getSize()){
                    if(targetNode->previous != nullptr){
                        targetNode->previous->next = nextNode;
                    }
                    if(nextNode->next != nullptr){
                        nextNode->next->previous = targetNode;
                    }
            
                    targetNode->next = nextNode->next;
                    nextNode->next = targetNode;
                    nextNode->previous = targetNode->previous;
                    targetNode->previous = nextNode;

                    if(targetNode == startNode){
                        startNode = nextNode;
                    }
                    if(nextNode == endNode){
                        endNode = targetNode;
                    }
                }
                else{
                    targetNode = nextNode;
                }
            }
        }
    }

    void sortByPrice(){
        while(!this->isOrdenedByPrice()){
        ProductNode* targetNode = startNode;
        while(targetNode != nullptr && targetNode->next != nullptr){
            ProductNode* nextNode = targetNode->next;

                if(nextNode->product.getPrice() < targetNode->product.getPrice()){
                    if(targetNode->previous != nullptr){
                        targetNode->previous->next = nextNode;
                    }
                    if(nextNode->next != nullptr){
                        nextNode->next->previous = targetNode;
                    }
            
                    targetNode->next = nextNode->next;
                    nextNode->next = targetNode;
                    nextNode->previous = targetNode->previous;
                    targetNode->previous = nextNode;

                    if(targetNode == startNode){
                        startNode = nextNode;
                    }
                    if(nextNode == endNode){
                        endNode = targetNode;
                    }
                }
                else{
                    targetNode = nextNode;
                }
            }
        }
    }

    public:
    int getLength(){
        return length;
    }

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
        sortByName();
        showAZ();
    }

    void showByNameZA(){
        sortByName();
        showZA();
    }

    void showBySizeAZ(){
        sortBySize();
        showAZ();
        sortByName();
    }

    void showBySizeZA(){
        sortBySize();
        showZA();
        sortByName();
    }

    void showByPriceInc(){
        sortByPrice();
        showAZ();
        sortByName();
    }

    void showByPriceDec(){
        sortByPrice();
        showZA();
        sortByName();
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

    void searchProductByName(string insertedName){
        ProductNode* targetNode = startNode;

        while (targetNode != nullptr){
            if(insertedName == targetNode->product.getName()){
                showProduct(targetNode);
            }
            targetNode = targetNode->next;
        }
    }

    void searchProductBySize(string insertedSize){
        ProductNode* targetNode = startNode;

        while (targetNode != nullptr){
            if(insertedSize == targetNode->product.getSize()){
                showProduct(targetNode);
            }
            targetNode = targetNode->next;
        }
    }

    void searchProductByPrice(float insertedPrice){
        ProductNode* targetNode = startNode;

        while (targetNode != nullptr){
            if(insertedPrice == targetNode->product.getPrice()){
                showProduct(targetNode);
            }
            targetNode = targetNode->next;
        }
    }

    void getFromFile(string insertedPath){
        ifstream file;
        file.open(insertedPath);

        if(file.is_open()){
            string readedLine;
            string name;
            string size;
            float price;
            float discount;
            int piecesForDiscount;
            int ammount;
            Product product;
            
            while(getline(file, readedLine)){
                name = readedLine;
                getline(file, readedLine);
                size = readedLine;
                getline(file, readedLine);
                price = stof(readedLine);
                getline(file, readedLine);
                discount = stof(readedLine);
                getline(file, readedLine);
                piecesForDiscount = stoi(readedLine);
                getline(file, readedLine);
                ammount = stoi(readedLine);
                product.create(name, size, price, discount, piecesForDiscount, ammount);
                this->insertProduct(product);
            }
        }
    }

    void saveInFile(string insertedPath){
        ofstream file;
        file.open(insertedPath);

        if (file.is_open()) {
            ProductNode* currentNode = startNode;
            while (currentNode != nullptr) {
                file << currentNode->product.getName() << "\n";
                file << currentNode->product.getSize() << "\n";
                file << currentNode->product.getPrice() << "\n";
                file << currentNode->product.getDiscount() << "\n";
                file << currentNode->product.getPiecesForDiscount() << "\n";
                file << currentNode->product.getAmmount() << "\n";
                currentNode = currentNode->next;
            }
            file.close();
            cout << "File saved :3";
        }
        else{
            cout << "ERROR.";
        }
    }
};