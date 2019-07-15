#include <iostream>
#include <string>
using namespace std;

struct Person {
	string name;
	int age;
	string telephoneNumber;
	Person(string inputName, int inputAge, string number) { // constructor
		name = inputName;
		age = inputAge;
		telephoneNumber = number;
	}
	void PrintDetails() {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Telephone Number: " << telephoneNumber << endl;
	}
};

int main() {
	string name;
	int age;
	string telephoneNumber;
	cout << "Please enter your name." << endl;
	getline(cin, name);
	cout << "Please enter your age." << endl;
	cin >> age;
	cin.ignore();
	cout << "Please enter your telephone number." << endl;
	getline(cin, telephoneNumber);
	Person personDetails = Person(name, age, telephoneNumber);
	personDetails.PrintDetails();
	cin.get();
	return 0;
}