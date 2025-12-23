#include "library.h"

void Library::addShelf(std::string name)
{
	shelves.push_back(Shelf(name));
}

void Library::removeShelf(Shelf& shelf)
{

}

std::vector<Shelf>& Library::getShelves()
{
	return shelves;
}
