#pragma once
#include "book.h"
#include <vector>
#include <string>

class Shelf
{
private:
	std::vector<Book> books = std::vector<Book>();

public:
	void addBook(BookData bookData);
	void removeBook(Book& book);
	std::vector<Book> getBooks();
};
