#include "UserService.h"
#include <algorithm>
#include <iterator>

UserService::UserService(Repository& _repository, UserRepository& _userRepository): repository{_repository}, userRepository{_userRepository}
{
}

vector<TrenchCoat> UserService::filterBySize(string& size)
{
	vector<TrenchCoat> result;
	vector<TrenchCoat> trenchCoats;
	if (size == "null")
		return this->getTrenchCoats();
	trenchCoats = this->getTrenchCoats();
	copy_if(trenchCoats.begin(), trenchCoats.end(), back_inserter(result), [size](TrenchCoat& t) {return t.getSize() == size; });
	return result;
}

void UserService::addTrenchToBasketService(TrenchCoat& t)
{
	this->userRepository.addTrenchToBasket(t);
	if (t.getQuantity() == 0)
		this->repository.removeRepo(t);
}

vector<TrenchCoat> UserService::getTrenchCoats()
{
	return this->repository.getAllTrenchCoatsRepo();
}

vector<TrenchCoat> UserService::getBasket()
{
	return this->userRepository.getBasket();
}

double UserService::getBasketPrice()
{
	return this->userRepository.getBasketPrice();
}

UserService::~UserService()
{
	//delete this->userRepository;
}
