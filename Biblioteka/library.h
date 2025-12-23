#pragma once
#include "shelf.h"
#include <vector>
#include <string>

class Library
{
private:
	std::vector<Shelf> shelves = std::vector<Shelf>();

public:
	void addShelf(std::string name);
	void removeShelf(Shelf& shelf);
	std::vector<Shelf>& getShelves();
};
