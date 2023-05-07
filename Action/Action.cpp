#include "Action.h"

UndoAdd::UndoAdd(Repository& repo, const TrenchCoat& t):repo(repo), addedTrenchCoat(t)
{
}

void UndoAdd::doUndo()
{
	repo.removeRepo(addedTrenchCoat);
}

void UndoAdd::doRedo()
{
	repo.addRepo(addedTrenchCoat);
}

UndoRemove::UndoRemove(Repository& repo, const TrenchCoat& t) :repo(repo), removedTrenchCoat(t)
{
}

void UndoRemove::doUndo()
{
	repo.addRepo(removedTrenchCoat);
}

void UndoRemove::doRedo()
{
	repo.removeRepo(removedTrenchCoat);
}

UndoUpdate::UndoUpdate(Repository& repo, const TrenchCoat& oldT, const TrenchCoat& newT): repo(repo), oldTrenchCoat(oldT), newTrenchCoat(newT)
{
}

void UndoUpdate::doUndo()
{
	repo.updateRepo(newTrenchCoat, oldTrenchCoat);
}

void UndoUpdate::doRedo()
{
	repo.updateRepo(oldTrenchCoat, newTrenchCoat);
}
