#include "shelf.h"

Shelf::Shelf(std::string name) : name(name) { }

Shelf::Shelf() : name("") { }

void Shelf::addBook(BookData bookData)
{
	books.push_back(Book(bookData));
}

void Shelf::removeBook(Book& book)
{
	books.erase(std::remove(books.begin(), books.end(), book), books.end());
}

std::vector<Book>& Shelf::getBooks()
{
	return books;
}

bool operator== (const Shelf& s1, const Shelf& s2)
{
	return s1.name == s2.name;
}

bool operator!= (const Shelf& s1, const Shelf& s2)
{
	return !(s1 == s2);
}
