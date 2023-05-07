#include "Repository.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
Repository::Repository(string& filename_)
{
	this->filename = filename_;
	this->readRepoFromFile();
}

Repository::~Repository()
{	//destructor
}

void Repository::readRepoFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		throw exception("The file could not be opened!\n");
	TrenchCoat t;
	while (file>>t) {
		this->trenchCoats.push_back(t);
	}
	file.close();
}

void Repository::writeRepoToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw exception("Could not open the file\n");
	for (auto& t : this->trenchCoats)
		file << t;
	file.close();
}

void Repository::addRepo(TrenchCoat& t)
{
	//adds a trench coat to the repository and returns 1 if success; if there is already such trench coat, it returns 0 and it won't add it
	if (findTrenchCoat(t) != -1) {
		string errors;
		errors += string("There is already such trench coat!\n");
		throw RepositoryException(errors);

	}
	this->trenchCoats.push_back(t);
	this->writeRepoToFile();
}

void Repository::removeRepo(TrenchCoat& t)
{
	//removes a trench coat returns 1 if success; if there is not such trench coat, it returns 0 and it won't delete anything
	int position = findTrenchCoat(t);
	if (position == -1)
	{
		string errors;
		errors += string("There is no such trench coat!\n");
		throw RepositoryException(errors);

	}
	vector<TrenchCoat>::iterator it = this->trenchCoats.begin() + position;
	this->trenchCoats.erase(it);
	this->writeRepoToFile();
}

void Repository::updateRepo(TrenchCoat& oldT, TrenchCoat& newT)
{
	//updates a trench coat and returns 1 if success; if there is not such trench coat, it returns 0 and it won't update anything
	int pos = this->findTrenchCoat(oldT);
	if (pos == -1)
	{
		string errors;
		errors += string("There is no such trench coat!\n");
		throw RepositoryException(errors);

	}
	this->trenchCoats[pos].setPrice(newT.getPrice());
	this->trenchCoats[pos].setQuantity(newT.getQuantity());
	this->trenchCoats[pos].setPhotograph(newT.getPhotograph());
	this->writeRepoToFile();
}

int Repository::findTrenchCoat(TrenchCoat& t)
{
	int searchedIndex = 0;
	vector<TrenchCoat>::iterator it = this->trenchCoats.begin();
	while (it != this->trenchCoats.end())
	{	
		TrenchCoat c = *it;
		if (c.getColor() == t.getColor() && c.getSize() == t.getSize())
			return searchedIndex;
		searchedIndex++;
		it = next(it);
	}
	return -1;
}

int Repository::getRepoSize() const
{
	return this->trenchCoats.size();
}

vector<TrenchCoat>& Repository::getAllTrenchCoatsRepo()
{
	return this->trenchCoats;
}

RepositoryException::RepositoryException(std::string& _message):message{_message}
{
}

const char* RepositoryException::what() const noexcept
{
	return message.c_str();
}
