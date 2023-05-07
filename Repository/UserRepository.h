#pragma once
#include "../Domain/Domain.h"
#include <vector>

class UserRepository {
private:
	vector<TrenchCoat>shoppingBasket;
public:
	UserRepository();	// constructor
	vector<TrenchCoat> getBasket();	// returns the trench coat in the basket
	int findTrenchCoatInBasket(const TrenchCoat& t);	// finds a trench coat in the basket
	void addTrenchToBasket(const TrenchCoat& t);
	double getBasketPrice();
	//void writeToFile();
	//void openFile();
	~UserRepository() = default;
};

//class CSVShoppingBasket : public UserRepository
//{
//private:
//	string filename = "shoppingbasket.csv";
//public:
//	CSVShoppingBasket() = default;
//	void addTrenchToBasket(TrenchCoat& t) override;
//	void writeToFile() override;
//	void openFile() override;
//	~CSVShoppingBasket() = default;
//};
//
//class HTMLShoppingBasket : public UserRepository
//{
//private:
//	string filename = "shoppingbasket.html";
//
//public:
//	HTMLShoppingBasket() = default;
//	void addTrenchToBasket(TrenchCoat& t) override;
//	void writeToFile() override;
//	void openFile() override;
//	~HTMLShoppingBasket() = default;
//};

class UserRepositoryException : public std::exception {
private:
	std::string message;
public:
	UserRepositoryException(std::string& _message);	// constructor

	const char* what() const noexcept override;
};
