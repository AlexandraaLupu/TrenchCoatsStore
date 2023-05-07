#include "Domain.h"
#include <string>
#include <utility>
#include <iostream> 

TrenchCoat::TrenchCoat()
{
	this->size = "default";
	this->color = "default";
	this->price = 0;
	this->quantity = 0;
	this->photograph = "default";
}

TrenchCoat::TrenchCoat(const string& size, const string& color, const double& price, const int& quantity, const string& photograph)
{
	this->size = size;
	this->color = color;
	this->price = price;
	this->quantity = quantity;
	this->photograph = photograph;
}

const string& TrenchCoat::getSize() const
{
	return this->size;
}

const string& TrenchCoat::getColor() const
{
	return this->color;
}

const double& TrenchCoat::getPrice() const
{
	return ceil(this->price * 100.0) / 100.0;
}

const int& TrenchCoat::getQuantity() const
{
	return this->quantity;
}

const string& TrenchCoat::getPhotograph() const
{
	return this->photograph;
}

void TrenchCoat::setSize(string size)
{
	this->size = size;
}

void TrenchCoat::setColor(string color)
{
	this->color = color;
}

void TrenchCoat::setPrice(double price)
{
	this->price = price;
}

void TrenchCoat::setQuantity(int quantity)
{
	this->quantity = quantity;

}

void TrenchCoat::setPhotograph(string photograph)
{
	this->photograph = photograph;
}

void TrenchCoat::accessPhoto() const
{
	ShellExecuteA(0, 0, "chrome.exe", getPhotograph().c_str(), 0, SW_SHOWMAXIMIZED);
}

istream& operator>>(istream& is, TrenchCoat& t)
{

		string size, color, price, quantity, photograph;
		getline(is, size, ',');
		if (size.empty())
			return is;
		getline(is, color, ',');
		getline(is, price, ',');
		getline(is, quantity, ',');
		getline(is, photograph, '\n');
		t.setSize(size);
		t.setColor(color);
		t.setPrice(stod(price));
		t.setQuantity(stoi(quantity));
		t.setPhotograph(photograph);
	return is;
}

ostream& operator<<(ostream& os, const TrenchCoat& t) {
	os << t.getSize() << "," << t.getColor() << "," << to_string(t.getPrice()) << "," << to_string(t.getQuantity()) << "," << t.getPhotograph() << "\n";
	return os;
}