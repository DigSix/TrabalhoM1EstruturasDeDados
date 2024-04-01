//Integrantes do grupo: Diogo Morgado Viana e Gabriel Schaldach Morgado

#include "commons.cpp"

struct User{
	private:
	string name;
	string password;
	bool permissions[3] = {false, false, false}; // 0 = admin, 1 = seller, 2 = buyer;

	public:
	void createAdmin(string newName,string newPassword) {
		name = newName;
		password = newPassword;
		permissions[0] = true;
	}

	void createSeller(string newName, string newPassword) {
		name = newName;
		password = newPassword;
		permissions[1] = true;
	}

	void createBuyer(string newName, string newPassword) {
		name = newName;
		password = newPassword;
		permissions[2] = true;
	}

	string getName() {
		return name;
	}

	string getPassword() {
		return password;
	}

	bool isAdmin() {
		if (permissions[0]) return true;
		return false;
	}

	bool isSeller() {
		if (permissions[1]) return true;
		return false;
	}

	bool isBuyer() {
		if (permissions[2]) return true;
		return false;
	}

	bool checkLogin(string insertedName, string insertedPassword) {
		if (name == insertedName && password == insertedPassword) return true;
		return false;
	}
};

struct UserNode {
	User user;
    int id = rand();

	UserNode* next = nullptr;
};

struct UserList {
	UserNode* startNode = nullptr;
	UserNode* endNode = nullptr;

    bool insertUser(User newUser) {
        UserNode* newNode = new UserNode;
        if (newNode == nullptr) return false;

        newNode->user = newUser;

        if (endNode == nullptr) {
            startNode = newNode;
            endNode = newNode;
        }

        else {
            endNode->next = newNode;
            endNode = newNode;
        }

        return true;
    }

    void getFromFile(string insertedPath) {
        ifstream file;
        file.open(insertedPath);

        if (file.is_open()) {
            string readedLine;
            string name;
			string password;
            string permission;

            while (getline(file, readedLine)) {
                name = readedLine;
                getline(file, readedLine);
                password = readedLine;
                getline(file, readedLine);
                permission = readedLine;
                User user;
                if (permission == "admin") user.createAdmin(name, password);
                if (permission == "seller") user.createSeller(name, password);
                if (permission == "buyer") user.createBuyer(name, password);
                this->insertUser(user);
            }
            file.close();
        }
        else {
            cout << "ERROR. System can't load user list :C";
        }
    }

    void saveInFile(string insertedPath) {
        ofstream file;
        file.open(insertedPath);

        if (file.is_open()) {
            UserNode* currentNode = startNode;
            while (currentNode != nullptr) {
                file << currentNode->user.getName() << "\n";
                file << currentNode->user.getPassword() << "\n";
                if(currentNode->user.isAdmin()) file << "admin\n";
                if(currentNode->user.isSeller()) file << "seller\n";
                if(currentNode->user.isBuyer()) file << "buyer\n";
                currentNode = currentNode->next;
            }
            file.close();
            cout << "User list saved :3";
        }
        else {
            cout << "ERROR. System can't save user list :C";
        }
    }

    User login(string insertedName, string insertedPassword){
        UserNode* currentNode = startNode;
        while (currentNode != nullptr){
            if(currentNode->user.checkLogin(insertedName, insertedPassword)){
                return currentNode->user;
            }
            currentNode = currentNode->next;
        }
        
    }
};