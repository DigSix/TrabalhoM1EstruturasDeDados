#include "commons.cpp"
#include "Estoque.cpp"

int main() {

	Product teste;
	teste.name = "Este é o nome! :3";
	teste.size = "Este é o tamanho! :3";
	teste.price = 01.10;

	Product teste1;
	teste1.name = "Este é o nome2! :3";
	teste1.size = "Este é o tamanho2! :3";
	teste1.price = 100.00;

	Storage storage;
	storage.insertProduct(teste);
	storage.insertProduct(teste1);
	storage.showAZ();
	storage.showZA();

	return 0;
}