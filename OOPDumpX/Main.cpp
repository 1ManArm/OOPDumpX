#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Person {
private:
	std::string _name;
	unsigned int _age;
public:
	Person(std::string name, int age) : _name(name), _age(age) {

	}
	std::string setName(std::string name) {
		return _name;
	}
	int setAge(int age) {
		return _age;
	}
	void showData() {
		std::cout << "________________________________" << std::endl;
		std::cout << "Имя:     |" << _name << std::endl;
		std::cout << "Возраст: |" << _age << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << std::endl;
	}
};

class Pupil {
private:
	std::string _name;
	unsigned int _age;
	std::vector <double>_marks;
public:
	Pupil(std::string name, int age, double marks) : _name(name), _age(age), _marks(marks) {

	}
	std::string setName(std::string name) {
		_name = name;
	}
	int setAge(int age) {
		_age = age;
	}
	void setMarks(unsigned int a, unsigned int b, unsigned int c) {
		_marks.push_back(a);
		_marks.push_back(b);
		_marks.push_back(c);
	}
	void showData() {
		std::cout << "________________________________" << std::endl;
		std::cout << "Имя:     |" << _name << std::endl;
		std::cout << "Возраст: |" << _age << std::endl;
		std::cout << "Оценки:  |";
		for (int i{}; i < _marks.size(); i++)
			std::cout << _marks.at(i) << " ";
		std::cout << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << std::endl;
	}
};

class Professor {
private:
	std::string _name;
	std::string _degree;
public:
	Professor(std::string name, std::string degree) : _name(name), _degree(degree) {

	}
	std::string setName(std::string name) {
		_name = name;
	}
	std::string setDegree(std::string degree) {
		_degree = degree;
	}
	void showData() {
		std::cout << "________________________________" << std::endl;
		std::cout << "Имя:         |" << _name << std::endl;
		std::cout << "Уч. степень: |" << _degree << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << std::endl;
	}
};

class Client {
private:
	std::string _name;
	int _age;
	long long _bill;
public:
	Client(std::string name, int age, long long bill) {
		_name = name;
		_age = age;
		_bill = bill;
	}
	void showData() {
		std::cout << "________________________________" << std::endl;
		std::cout << "Client's name: |" << _name << '\n';
		std::cout << "Client's age:  |" << _age << '\n';
		std::cout << "Client's bill: |" << _bill << '\n';
	}
};

class Bank {
private:
	std::vector<Client*>_clients;
public:

	void addClient(Client* client) {
		_clients.push_back(client);
	}

	void showClients() {
		/*std::vector<Client*>::iterator it;
		for (it = _clients.begin(); it != _clients.end(); ++it)
			(*it)->showData();*/

		for (const auto& it : _clients)
			it->showData();
	}

	void showClient(int index) {
		if (index > _clients.size())
			return;

		_clients.at(index - 1)->showData();
	}
};

class Implement {
public:
	virtual ~Implement(){}
	virtual std::string OperationImplement() const = 0;
};

class SpecificImplementA : public Implement {
public:
	std::string OperationImplement() const override {
		return "SpecificImplementA: Результат платформы A: \n";
	}
};

class SpecificImplementB : public Implement {
public:
	std::string OperationImplement() const override {
		return "SpecificImplementB: Результат платформы B: \n";
	}
};

class Abstraction {
protected:
	Implement* implement_;

public:
	Abstraction(Implement* implement) : implement_(implement){}

	virtual ~Abstraction(){}

	virtual std::string Operation() const {
		return "Abstraction: Операция над: \n" +
			this->implement_->OperationImplement();
	}
};

class ExAbstraction : public Abstraction {
public:
	ExAbstraction(Implement* implement) : Abstraction(implement){}
	std::string Operation() const override {
		return "ExAbstraction: Расширенная операция над: \n" +
			this->implement_->OperationImplement();
	}
};

void ClientCode(const Abstraction& abstraction) {

	std::cout << abstraction.Operation();

}

int main() {
	setlocale(LC_ALL, "Russian");

	Person person1("Иван", 41);
	person1.showData();

	Pupil pupil1("Марк", 14, 4.9);
	pupil1.setMarks(5, 4, 3);
	pupil1.showData();

	Professor professor1("Константин Романенков", "Доцент");
	professor1.showData();

	Bank* bank = new Bank();
	Client* client1 = new Client("Bob", 20, 6541631631);
	Client* client2 = new Client("Alex", 25, 695665631);
	Client* client3 = new Client("Monica", 40, 658466769921);
	Client* client4 = new Client("Jacob", 70, 4755);
	Client* client5 = new Client("Richard", 20, 69245245656);
	Client* client6 = new Client("Alisa", 18, 446464646448);
	bank->addClient(client1);
	bank->addClient(client2);
	bank->addClient(client3);
	bank->addClient(client4);
	bank->addClient(client5);
	bank->addClient(client6);
	bank->showClients();
	bank->showClient(2);

	std::cout << std::endl;

	Implement* implement = new SpecificImplementA;
	Abstraction* abstraction = new Abstraction(implement);
	ClientCode(*abstraction);
	std::cout << std::endl;
	delete implement;
	delete abstraction;

	implement = new SpecificImplementB;
	abstraction = new ExAbstraction(implement);
	ClientCode(*abstraction);

	delete implement;
	delete abstraction;
	return 0;
}