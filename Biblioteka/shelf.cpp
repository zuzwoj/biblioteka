#include "shelf.h"

Shelf::Shelf(std::string name) : name(name) { }

Shelf::Shelf() : name("") { }

void Shelf::addBook(BookData bookData)
{
	books.push_back(Book(bookData));
}

void Shelf::removeBook(Book& book)
{

}

std::vector<Book>& Shelf::getBooks()
{
	return books;
}
