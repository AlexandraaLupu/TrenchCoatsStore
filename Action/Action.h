#pragma once
#include "../Domain/Domain.h"
#include "../Repository/Repository.h"

class Action {
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual ~Action() {}
};

class UndoAdd : public Action {
private:
	TrenchCoat addedTrenchCoat;
	Repository& repo;
public:
	UndoAdd(Repository& repo, const TrenchCoat& t);

	void doUndo() override;
	void doRedo() override;
};

class UndoRemove : public Action {
private:
	TrenchCoat removedTrenchCoat;
	Repository& repo;
public:
	UndoRemove(Repository& repo, const TrenchCoat& t);

	void doUndo() override;
	void doRedo() override;
};

class UndoUpdate : public Action {
private:
	TrenchCoat oldTrenchCoat, newTrenchCoat;
	Repository& repo;
public:
	UndoUpdate(Repository& repo, const TrenchCoat& oldT, const TrenchCoat& newT);

	void doUndo() override;
	void doRedo() override;
};