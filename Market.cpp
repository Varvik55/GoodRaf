
#include <iostream>
#include <fstream>
#include "Market.h"
#include <string>




bool Market::LoadPersons() {
	return false;
};

bool Market::LoadOrders() {
	return false;
};

bool Market::loadShop() {
	std::ifstream inFile;
	inFile.open("shop.csv");
	std::string input;
	//перебираем до точки с запятой
	std::string str[3];
	if (inFile.is_open()) {
		//убрали : записали каждое слово в массив
		while (std::getline(inFile, input)) {
			std::string ch = "";
			std::string str[3];
			int i = 0;
			int j = 0;
			while (j<input.length())
			{
				ch = input[j];
				if (ch==";")
				{
					i++;
				}
				else
				{
					str[i] += input[j];
				}
				j++;
			}
			Item item;
			item.Title = str[1];
			item.Price = atoi(str[2].c_str());
			bool isFind = false;
			std::list<Category>::iterator cat = Shop.begin();
			for (; cat != Shop.end();cat++)
			{
				if (cat->Title==str[0]) {
					cat->Items.push_back(item);
					isFind = true;
					break;
				}
			}
			if (!isFind) {
				Category cat;
				cat.Title = str[0];
				cat.Items.push_back(item);
				Shop.push_back(cat);
			}

			
		}

		

	}
	inFile.close();
	return true;

};

bool Market::SavePersons() {
	return false;
};

bool Market::SaveOrders() {
	return false;
};

bool Market::SaveShop() {
	//сохранение фссортимента магазина
	// категоря; товар;цена формат csv

	std::ofstream outFile;// открываем файл (файловая переменная)
	outFile.open("shop.csv");
	for (auto const& category : Shop) {
		for (auto const& item : category.Items) {
			outFile << category.Title << ": " << item.Title << ": " << item.Price << std::endl;
		}
	}

	outFile.close();
	return true;
	
};

