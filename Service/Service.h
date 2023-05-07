#pragma once
#include "../Repository/Repository.h"
#include "../Validator/Validator.h"
#include "../Action/Action.h"
#include <memory>

class Service {

private:
	Repository& repo;
	TrenchCoatValidator& validator;
	vector<unique_ptr<Action>> undoActions;
	vector<unique_ptr<Action>> redoActions;
public:
	Service(Repository& _repo, TrenchCoatValidator& _validator);	// constructor

	//validates the given data and adds trench coat
	void addService(string& size, string& color, string& price, string& quantity, string& photograph);

	//validates the given data and deletes trench coat
	void deleteService(TrenchCoat& t);

	//validates the given data and updates trench coat
	void updateService(TrenchCoat& t, string& price, string& quantity, string& photograph);

	vector<TrenchCoat>& getAllTrenchCoats();	// returns the trench coats

	void undo();
	
	void redo();
	~Service();	// destructor
};
//void testService();
