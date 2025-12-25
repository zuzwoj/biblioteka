#pragma once
#include "book.h"
#include <vector>
#include <string>

class Shelf
{
private:
	std::vector<Book> books = std::vector<Book>();

public:
	std::string name;

	void addBook(BookData bookData);
	void removeBook(Book& book);
	std::vector<Book>& getBooks();

	Shelf(std::string name);
	Shelf();

	friend bool operator== (const Shelf& s1, const Shelf& s2);
	friend bool operator!= (const Shelf& s1, const Shelf& s2);
};
