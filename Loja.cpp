//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"

#define savedStorage "savedStorage.txt"

int main() {

	Storage storage;
	storage.getFromFile(savedStorage);
	storage.showByNameAZ();
	
	return 0;
}