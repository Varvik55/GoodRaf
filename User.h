#pragma once
#include <iostream>
#include "Category.h"
#include "Item.h"

class User {
public:
	unsigned int Id;
	std::string Name;
	std::string Login;
	std::string Password;

	User(unsigned int id, std::string name, std::string login, std::string password) :
		Id{ id }, Name{ name }, Login{ login }, Password{ password } {
	}
	User();

};