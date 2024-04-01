//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"
#include "Usuario.cpp"

#define savedStorage "savedStorage.txt"
#define savedUsers "savedUsers.txt"



int main() {
	srand(time(NULL));

	UserList usersList;
	usersList.getFromFile(savedUsers);

	string loginName, loginPassword;

	cout << "Realizar Login\nNome: ";
	cin >> loginName;
	system("cls");
	cout << "Realizar Login\nSenha: ";
	cin >> loginPassword;
	system("cls");

	User currentUser;
	currentUser = usersList.login(loginName, loginPassword);

	Storage storage;
	storage.getFromFile(savedStorage);
	storage.showByNameAZ();

	storage.showByNameAZ();

	if (currentUser.isAdmin()) {
		cout << "Insira respectivamente o id e o novo preco do produto que deseja alterar." << "\n";
		int productID;
		float newPrice;
		cin >> productID;
		cin >> newPrice;

		storage.editProductPrice(productID, newPrice);

		system("cls");

		storage.showByNameAZ();

		storage.removeProduct(productID);

		storage.showByNameAZ();
	}
	
	return 0;
}