#include "library.h"

int Library::addShelf(std::string name)
{
	shelves.push_back(Shelf(name));
	return shelves.size() - 1;
}

void Library::removeShelf(Shelf& shelf)
{
	shelves.erase(std::remove(shelves.begin(), shelves.end(), shelf), shelves.end());
}

std::vector<Shelf>& Library::getShelves()
{
	return shelves;
}
