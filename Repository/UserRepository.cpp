#include "UserRepository.h"
#include <fstream>


UserRepository::UserRepository()
{
}

vector<TrenchCoat> UserRepository::getBasket()
{
	return this->shoppingBasket;
}

int UserRepository::findTrenchCoatInBasket(const TrenchCoat& t)
{
	string t_size = t.getSize();
	string t_color = t.getColor();

	int searchedIndex = 0;
	vector<TrenchCoat>::iterator it = this->shoppingBasket.begin();
	while (it != this->shoppingBasket.end())
	{
		TrenchCoat c = *it;
		if (t_color == c.getColor() && t_size == c.getSize())
			return searchedIndex;
		searchedIndex++;
		it = next(it);
	}
	return -1;
}

void UserRepository::addTrenchToBasket(const TrenchCoat& t)
{
		if (findTrenchCoatInBasket(t) == -1)
	{
			this->shoppingBasket.push_back(t);
	}
	else {
		string error = "Already added\n";
		throw UserRepositoryException(error);
	}
}

double UserRepository::getBasketPrice()
{
	double price = 0;
	for (auto t : this->shoppingBasket)
		price += t.getPrice();
	return price;

}


UserRepositoryException::UserRepositoryException(std::string& _message) :message{ _message }
{
}

const char* UserRepositoryException::what() const noexcept
{
	return message.c_str();
}
