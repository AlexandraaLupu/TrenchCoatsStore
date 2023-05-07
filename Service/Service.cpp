#include "Service.h"
#include <assert.h>
#include <algorithm>
#include <iterator>
#include <string>

Service::Service(Repository& _repo, TrenchCoatValidator& _validator): repo{_repo}, validator{_validator}
{
	
}

void Service::addService(string& size, string& color, string& price, string& quantity, string& photograph)
{
	TrenchCoat t;
	t.setSize(size);
	t.setColor(color);
	t.setPrice(stod(price));
	t.setQuantity(stoi(quantity));
	t.setPhotograph(photograph);
	this->validator.validate(t);
	this->repo.addRepo(t);
	this->undoActions.push_back(make_unique<UndoAdd>(this->repo, t));
	this->redoActions.clear();

}

void Service::deleteService(TrenchCoat& t)
{
	this->validator.validate(t);
	this->repo.removeRepo(t);
	this->undoActions.push_back(make_unique<UndoRemove>(this->repo, t));
	this->redoActions.clear();
}

void Service::updateService(TrenchCoat& t, string& price, string& quantity, string& photograph)
{
	TrenchCoat oldT = this->getAllTrenchCoats()[this->repo.findTrenchCoat(t)];
	TrenchCoat newT{ t.getSize(), t.getColor(), stod(price), stoi(quantity), photograph };
	this->validator.validate(newT);
	this->repo.updateRepo(t, newT);
	this->undoActions.push_back(make_unique<UndoUpdate>(this->repo, oldT, newT));
	this->redoActions.clear();
}

vector<TrenchCoat>& Service::getAllTrenchCoats()
{
	return this->repo.getAllTrenchCoatsRepo();
}

void Service::undo()
{
	if (undoActions.empty()) {
		string str = "There is nothing to undo";
		throw RepositoryException(str);
	}
	unique_ptr<Action>last = move(this->undoActions.back());
	last->doUndo();
	this->undoActions.pop_back();
	this->redoActions.push_back(move(last));
}

void Service::redo()
{
	if (redoActions.empty()) {
		string str = "There is nothing to redo";
		throw RepositoryException(str);
	}
	unique_ptr<Action>last = move(this->redoActions.back());
	last->doRedo();
	this->redoActions.pop_back();
	this->undoActions.push_back(move(last));
}

Service::~Service()
{
}

