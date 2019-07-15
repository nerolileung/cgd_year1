#include "Cat.h"

Cat::Cat(int initialAge) {
	age = initialAge;
}

Cat::~Cat() {

}

int Cat::GetAge() {
	return age;
}

void Cat::SetAge(int age) {
	age = age;
}