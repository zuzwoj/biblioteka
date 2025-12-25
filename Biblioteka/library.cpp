#include "library.h"

int Library::addShelf(std::string name)
{
	Shelf newShelf = Shelf(name);
	shelves.emplace(newShelf.getID(), newShelf);
	return (int)shelves.size() - 1;
}

void Library::removeShelf(Shelf& shelf)
{
	shelves.erase(shelf.getID());
}

std::map<unsigned int, Shelf>& Library::getShelves()
{
	return shelves;
}
