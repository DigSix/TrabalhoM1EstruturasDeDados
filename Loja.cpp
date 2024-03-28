//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"

int main() {

	Product teste, teste1, teste2, teste3, teste4, teste5;

	teste.create("ItemA", "M", 100, 5, 3);
	teste1.create("ItemE", "GG", 250, 25, 2);
	teste2.create("ItemD", "G", 300, 5, 1);
	teste3.create("ItemC", "P", 125, 5, 3);
	teste4.create("ItemB", "GG", 175, 25, 2);
	teste5.create("ItemF", "GG", 175, 25, 2);


	Storage storage;
	storage.insertProduct(teste);
	storage.insertProduct(teste1);
	storage.insertProduct(teste2);
	storage.insertProduct(teste3);
	storage.insertProduct(teste4);
	//storage.insertProduct(teste5);
	storage.showAZ();
	storage.showById();
	storage.removeProduct(2);
	storage.showById();
	
	return 0;
}