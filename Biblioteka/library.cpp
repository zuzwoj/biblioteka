#include "library.h"

int unsigned Library::addShelf(std::string name)
{
	Shelf newShelf = Shelf(name);
	shelves.emplace(newShelf.getID(), newShelf);
	return newShelf.getID();
}

void Library::addShelf(Shelf& shelf)
{
	shelves.emplace(shelf.getID(), shelf);
}

void Library::removeShelf(Shelf& shelf)
{
	shelves.erase(shelf.getID());
}

std::map<unsigned int, Shelf>& Library::getShelves()
{
	return shelves;
}
