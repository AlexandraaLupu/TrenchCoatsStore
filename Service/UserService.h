#pragma once
#include "../Repository/UserRepository.h"
#include "../Repository/Repository.h"

class UserService {
private:
	Repository& repository;
	UserRepository& userRepository;
public:
	UserService(Repository& _repository, UserRepository& _userRepository);
	//explicit UserService(Repository& _repository);
	vector<TrenchCoat> filterBySize(string& size);
	void addTrenchToBasketService(TrenchCoat& t);
	vector<TrenchCoat> getTrenchCoats();
	vector<TrenchCoat> getBasket();
	double getBasketPrice();
	void setBasket(string type);
	//void openFile();
	~UserService();

};