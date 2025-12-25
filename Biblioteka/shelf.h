#pragma once
#include "book.h"
#include <list>
#include <string>

class Shelf
{
private:
	static unsigned int currentID;
	unsigned int ID;
	std::list<Book> books = std::list<Book>();

public:
	std::string name;

	Shelf(std::string name);

	void addBook(BookData bookData);
	void addBook(Book& book);
	void removeBook(Book& book);
	std::list<Book>& getBooks();

	unsigned int getID() { return ID; }

	friend bool operator== (const Shelf& s1, const Shelf& s2);
	friend bool operator!= (const Shelf& s1, const Shelf& s2);
};
