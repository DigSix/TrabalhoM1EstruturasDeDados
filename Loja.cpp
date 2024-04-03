//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"
#include "Usuario.cpp"
#include "Carrinho.cpp"

#define savedStorage "savedStorage.txt"
#define savedUsers "savedUsers.txt"

struct Controls{
	HANDLE out;
	COORD coord;
	char key;
	int menu_select = 0;
	int menu_length = 0;

	void init() {
		CONSOLE_CURSOR_INFO     cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(out, &cursorInfo);

		out = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(out, 15);

		short int CX = 0, CY = 0;
		coord.X = CX;
		coord.Y = CY;
	}
	void clearConsole() {
		system("cls");
	}
	void drawMenu(string menu_options[]) {
		for (int i = 0; i < menu_length; i++) {
			if (menu_select == i) {
				cout << "-> ";
			}
			else {
				cout << "   ";
			}
			cout << menu_options[i];
			cout << "\n";
		}
	}
	void resetCursor() {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
};

void admin_loop(Controls controls, UserList usersList, Storage storage);
void editProductPriceLoop(Controls controls, UserList usersList, Storage storage) {
	controls.clearConsole();
	cout << "Insira respectivamente o id e o novo preco do produto que deseja alterar." << "\n";
	int productID;
	float newPrice;
	cin >> productID;
	cin >> newPrice;

	storage.editProductPrice(productID, newPrice);
}

void editProductAmountLoop(Controls controls, UserList usersList, Storage storage) {
	controls.clearConsole();
	cout << "Insira respectivamente o id e a nova quantidade do produto que deseja alterar." << "\n";
	int productID;
	int newAmount;
	cin >> productID;
	cin >> newAmount;

	storage.editProductAmount(productID, newAmount);
}

void client_loop(Controls controls, UserList usersList, Storage storage, ProductCart cart) {
	controls.menu_select = 0;
	controls.menu_length = 4;
	static string menu_options[4] = {
		"Adicionar no carrinho",
		"Remover do carrinho",
		"Finalizar compra",
		"Voltar",
	};

	controls.clearConsole();
	controls.drawMenu(menu_options);
	storage.showByNameAZ();


}

void admin_loop(Controls controls, UserList usersList, Storage storage) {
	controls.menu_select = 0;
	controls.menu_length = 4;
	static string menu_options[4] = {
		"Editar preço",
		"Editar quantidade",
		"Salvar",
		"Voltar",
	};

	controls.clearConsole();
	controls.drawMenu(menu_options);
	storage.showByNameAZ();

	while (true) {
		if (_kbhit()) {
			controls.key = _getch();
			switch (controls.key) {
			case ' ':
				switch (controls.menu_select) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				}
				controls.clearConsole();
				break;
			case 72: case 'w':
				if (controls.menu_select > 0) controls.menu_select--;
				break;
			case 80: case 's':
				if (controls.menu_select < controls.menu_length-1) controls.menu_select++;
				break;
			}
		controls.resetCursor();
		controls.drawMenu(menu_options);
		storage.showByNameAZ();
		}
	}
}

void login_loop(Controls controls, UserList usersList, Storage storage, ProductCart cart) {
	controls.clearConsole();
	string loginName, loginPassword;

	cout << "Realizar Login\nNome: ";
	cin >> loginName;
	cout << "\nRealizar Login\nSenha: ";
	cin >> loginPassword;

	User currentUser;
	currentUser = usersList.login(loginName, loginPassword);

	if (currentUser.isAdmin()) {
		admin_loop(controls, usersList, storage);
	}
	if (currentUser.isBuyer()) {
		client_loop(controls, usersList, storage, cart);
	}
}

int main() {
	srand(time(NULL));

	Controls controls;
	controls.init();

	UserList usersList;
	usersList.getFromFile(savedUsers);

	Storage storage;
	storage.getFromFile(savedStorage);

	ProductCart cart;

	login_loop(controls, usersList, storage, cart);
	
	return 0;
}