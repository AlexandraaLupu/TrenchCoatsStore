#pragma once
#include <string>
#include <windows.h>
#include <shellapi.h>
using namespace std;

class TrenchCoat
{
private:
	string size;
	string color;
	double price;
	int quantity;
	string photograph;
public:
	TrenchCoat();	// constructor
	TrenchCoat(const string& size, const string& color, const double& price, const int& quantity, const string& photograph);	// copy constructor

	const string& getSize() const; // getter for size
	const string& getColor() const; // getter for color
	const double& getPrice() const; // getter for price
	const int& getQuantity() const; // getter for quantity
	const string& getPhotograph() const; // getter for photograph

	void setSize(string size);	// setter for size
	void setColor(string color);	//setter for color
	void setPrice(double price);	// setter for price
	void setQuantity(int quantity);	// setter for quantity
	void setPhotograph(string photograph);	//setter for photograph

	void accessPhoto() const;	// opens the link for the photograph

	friend std::istream& operator>>(std::istream& is, TrenchCoat& t);	// operator for ifstream
	friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& t);	// operator for ofstream
};
