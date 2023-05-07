#pragma once
#include <vector>
#include "../Domain/Domain.h"

using namespace std;

class Repository {
private:
	vector<TrenchCoat> trenchCoats;
	string filename;

public:
	Repository(string& filename_);	// constructor
	~Repository();	// destructor

	void readRepoFromFile();	// reads the trench coats from a text file
	void writeRepoToFile();		// writes the trench coats toa file


	// adds a trench coat to the repo
	// throws exception if the trench coat is already in the repo
	void addRepo(TrenchCoat& t);	

	// deletes a trench coat from the repo
	// throws exception if the trench coat is not in the repo
	void removeRepo(TrenchCoat& t);	

	// updates a trench coat from the repo
	// throws exception if the trench coat is not in the repo
	void updateRepo(TrenchCoat& oldT, TrenchCoat& newT);

	// returns the position of the given trench coat in the repo vector
	//returns -1 if there is no such trench coat
	int findTrenchCoat(TrenchCoat& t);

	int getRepoSize() const;	// return the number of trench coats

	vector<TrenchCoat>& getAllTrenchCoatsRepo();	// returns the vector where the trench coats are store
};


class RepositoryException : public std::exception {
private:
	std::string message;
public:
	RepositoryException(std::string& _message);	// constructor

	const char* what() const noexcept override;
};

