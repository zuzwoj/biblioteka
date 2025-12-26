#include "shelf.h"

unsigned int Shelf::currentID = 0;

Shelf::Shelf(std::string name) : name(name), ID(currentID)
{ 
	++currentID;
}

Shelf::Shelf(std::string name, unsigned int ID) : name(name), ID(ID)
{
	if (ID >= currentID)
	{
		currentID = ID + 1;
	}
}

void Shelf::addBook(BookData bookData)
{
	bookData.shelf = ID;
	books.push_back(Book(bookData));
}

void Shelf::addBook(Book& book)
{
	book.bookData.shelf = ID;
	books.push_back(book);
}

void Shelf::removeBook(Book& book)
{
	books.erase(std::remove(books.begin(), books.end(), book), books.end());
}

std::list<Book>& Shelf::getBooks()
{
	return books;
}

bool operator== (const Shelf& s1, const Shelf& s2)
{
	return s1.ID == s2.ID;
}

bool operator!= (const Shelf& s1, const Shelf& s2)
{
	return !(s1 == s2);
}
