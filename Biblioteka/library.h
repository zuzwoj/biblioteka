#pragma once
#include "shelf.h"
#include <map>
#include <string>

class Library
{
private:
	std::map<unsigned int, Shelf> shelves = std::map<unsigned int, Shelf>();

public:
	int addShelf(std::string name);
	void removeShelf(Shelf& shelf);
	std::map<unsigned int, Shelf>& getShelves();};
