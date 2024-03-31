//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"

#define savedStorage "savedStorage.txt"



int main() {
	srand(time(NULL));

	Storage storage;
	storage.getFromFile(savedStorage);
	storage.showByNameAZ();

	ProductNode* product = storage.getProductByIndex(0);
	storage.editProductPrice(product->id, 30.5);
	storage.showByNameAZ();

	ProductNode* product2 = storage.getProductByIndex(1);
	storage.removeProduct(product2->id);
	storage.showByNameAZ();
	
	return 0;
}