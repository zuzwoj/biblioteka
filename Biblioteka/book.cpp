#include "book.h"

unsigned int Book::currentID = 0;

Book::Book(BookData bookData) : bookData(bookData), ID(currentID)
{
	++currentID;
}

Book::Book() : ID(currentID)
{ 
	++currentID;
}

bool operator== (const Book& b1, const Book& b2)
{
	return b1.ID == b2.ID;
}

bool operator!= (const Book& b1, const Book& b2)
{
	return !(b1 == b2);
}
