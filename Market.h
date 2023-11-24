
#pragma once
#include <iostream>
#include <list>
#include "Category.h"
#include "User.h"
#include "Order.h"
//основной класс содержащий категории напитков данные о пользователе, сами товары и цены на них

class Market {
public:
	std::list<Category> Shop;
	std::list<User> Person;
	std::list <Order> Orders;

	bool SavePersons();
	bool SaveOrders();
	bool SaveShop();
	bool LoadPersons();
	bool LoadOrders();
	bool loadShop();
	
};
