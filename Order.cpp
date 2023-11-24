#include "Order.h"


int Order::GetTotalSum() {
	int sum = 0;
	for (auto const& item : Items)
	{
		sum += item.Price;
	}
	TotalSum = sum;
	return sum;
}
void Order::Clear() {
	Items.clear();
	Status = "";
	Person = "";
	DateTime = 0;
}
bool Order::SaveOrder() {
	std::ofstream out;
	out.open("orders/"+std::to_string(DateTime) + ".dat");
	out << DateTime << "\n";
	out << GetTotalSum() << "\n";
	out << Status << "\n";
	out << Person << "\n";
	for (auto const& item : Items) {
		out << item.Title << ";" << item.Price << "\n";
	}
	out.close();
	return true;
}