//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"
#include "Estoque.cpp"
#include "Usuario.cpp"
#include "Carrinho.cpp"
#include "ListaVendas.cpp"

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

void login_loop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales);
void admin_loop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales);
void client_loop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales);
void editProductPriceInput(Controls& controls, UserList& usersList, Storage& storage) {
	controls.clearConsole();
	storage.showByNameAZ();

	cout << "Insira respectivamente o id e o novo preco do produto que deseja alterar." << "\n";

	int productID;
	float newPrice;
	cin >> productID;
	cin >> newPrice;

	storage.editProductPrice(productID, newPrice);
}

void editProductAmountInput(Controls& controls, UserList& usersList, Storage& storage) {
	controls.clearConsole();
	storage.showByNameAZ();

	cout << "Insira respectivamente o id e a nova quantidade do produto que deseja alterar." << "\n";
	int productID;
	int newAmount;
	cin >> productID;
	cin >> newAmount;

	storage.editProductAmount(productID, newAmount);
}

void addCartProductInput(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.clearConsole();
	storage.showByNameAZ();

	cout << "Insira respectivamente o id do produto a ser adicionado e a quantidade." << "\n";
	int productId, productAmount;
	cin >> productId;
	cin >> productAmount;

	ProductNode* storageProduct = storage.getProductNodeById(productId);
	if(productAmount > storageProduct->product.getAmount()){
		return;
	}

	storageProduct->product.setAmount(storageProduct->product.getAmount() - productAmount);
	cart.insertProduct(storageProduct->product, storageProduct->id, productAmount);
}

void removeCartProductInput(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.clearConsole();
	cart.showByNameAZ();

	cout << "Insira o id do produto a ser removido." << "\n";
	int productId;
	cin >> productId;

	ProductNode* cartProduct = cart.getProductNodeById(productId);
	ProductNode* storageProduct = storage.getProductNodeById(productId);

	int newAmount = cartProduct->product.getAmount() + storageProduct->product.getAmount();
	storage.editProductAmount(productId, newAmount);
	cart.removeProduct(productId);
}

void endClientSale(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.clearConsole();
	cart.showByNameAZAndPrice();
	cout << "Preço total = " << cart.getCartPrice() << "\n";

	cout << "Insira o vendedor do seu atendimento e a opção de pagamento." << "\n";
	int paymentOption;
	int seller;
	cout << "Vendedor(a) do atendimento (0 para Márcio, 1 para Maurício, 2 para Marco, 3 para Márcia, 4 para Mariana): ";
	cin >> seller;
	cout << "Opção de pagamento (0 para débito, 1 para crédito, 2 para dinheiro físico): ";
	cin >> paymentOption;

	sales.insertSale(cart.getCartTotalPrice(), cart.getCartPrice(), paymentOption, seller);
	cart.emptyCart();
	storage.saveInFile(savedStorage);
}

void statisticsLoop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.menu_select = 0;
	controls.menu_length = 3;

	static string menu_options[3] = {
		// Adicionar opções de filtros diferentes paras as vendas e passar a opção selecionada como parâmetro para sales.showByNameAZ();
		"Vendas totais",
		"Vendas por vendedor",
		"Vendas por método de pagamento"
	};

	controls.clearConsole();
	cout << "Aperte Espaço para voltar\n";
	controls.drawMenu(menu_options);
	sales.showSales();

	while (true) {
		if (_kbhit()) {
			controls.key = _getch();
			switch (controls.key) {
			case ' ':
				admin_loop(controls, usersList, storage, cart, sales);
				return;
			case 72: case 'w':
				if (controls.menu_select > 0) controls.menu_select--;
				break;
			case 80: case 's':
				if (controls.menu_select < controls.menu_length - 1) controls.menu_select++;
				break;
			}
			controls.clearConsole();
			cout << "Aperte Espaço para voltar\n";
			controls.drawMenu(menu_options);
			switch (controls.menu_select) {
			case 0:
				sales.showSales();
				break;
			case 1:
				sales.showSalesBySeller();
				break;
			case 2:
				sales.showSalesByPaymentOption();
				break;
			}
			
		}
	}
}

void cashRegisterLoop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.menu_select = 0;
	controls.menu_length = 2;

	static string menu_options[2] = {
		"Finalizar compra",
		"Voltar",
	};

	controls.clearConsole();
	controls.drawMenu(menu_options);
	cart.showByNameAZAndPrice();
	cout << "Preço total = " << cart.getCartPrice() << "\n";

	while (true) {
		if (_kbhit()) {
			controls.key = _getch();
			switch (controls.key) {
			case ' ':
				switch (controls.menu_select) {
				case 0:
					endClientSale(controls, usersList, storage, cart, sales);
					client_loop(controls, usersList, storage, cart, sales);
					return;
				case 1:
					client_loop(controls, usersList, storage, cart, sales);
					return;
				}
				controls.clearConsole();
				break;
			case 72: case 'w':
				if (controls.menu_select > 0) controls.menu_select--;
				break;
			case 80: case 's':
				if (controls.menu_select < controls.menu_length - 1) controls.menu_select++;
				break;
			}
			controls.resetCursor();
			controls.drawMenu(menu_options);
			cart.showByNameAZAndPrice();
			cout << "Preço total = " << cart.getCartPrice() << "\n";
		}
	}
}

void client_loop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.menu_select = 0;
	controls.menu_length = 4;
	static string menu_options[4] = {
		"Adicionar no carrinho",
		"Remover do carrinho",
		"Ir para o caixa",
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
					addCartProductInput(controls, usersList, storage, cart, sales);
					break;
				case 1:
					removeCartProductInput(controls, usersList, storage, cart, sales);
					break;
				case 2:
					cashRegisterLoop(controls, usersList, storage, cart, sales);
					break;
				case 3:
					login_loop(controls, usersList, storage, cart, sales);
					return;
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

void admin_loop(Controls& controls, UserList &usersList, Storage &storage, ProductCart &cart, SaleList& sales) {
	controls.menu_select = 0;
	controls.menu_length = 5;
	static string menu_options[5] = {
		"Editar pre�o",
		"Editar quantidade",
		"Salvar",
		"Ver estatísticas",
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
					editProductPriceInput(controls, usersList, storage);
					break;
				case 1:
					editProductAmountInput(controls, usersList, storage);
					break;
				case 2:
					storage.saveInFile(savedStorage);
					break;
				case 3:
					statisticsLoop(controls, usersList, storage, cart, sales);
					return;
				case 4:
					login_loop(controls, usersList, storage, cart, sales);
					return;
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

void login_loop(Controls& controls, UserList& usersList, Storage& storage, ProductCart& cart, SaleList& sales) {
	controls.clearConsole();
	string loginName, loginPassword;

	cout << "Realizar Login\nNome: ";
	cin >> loginName;
	cout << "\nRealizar Login\nSenha: ";
	cin >> loginPassword;

	User currentUser;
	currentUser = usersList.login(loginName, loginPassword);

	if (currentUser.isAdmin()) {
		admin_loop(controls, usersList, storage, cart, sales);
	}
	if (currentUser.isBuyer()) {
		client_loop(controls, usersList, storage, cart, sales);
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

	SaleList sales;

	login_loop(controls, usersList, storage, cart, sales);

	return 0;
}
