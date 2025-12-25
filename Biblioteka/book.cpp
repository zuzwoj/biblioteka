#include "book.h"

Book::Book(BookData bookData) : bookData(bookData) { }

Book::Book() { }

bool operator== (const Book& b1, const Book& b2)
{
	return b1.bookData == b2.bookData;
}

bool operator!= (const Book& b1, const Book& b2)
{
	return !(b1 == b2);
}
