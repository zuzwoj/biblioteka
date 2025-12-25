#include "book.h"

BookData::BookData(std::string title, std::string author, unsigned int year, std::string note) 
	: title(title), author(author), year(year), note(note) { }

BookData::BookData() : title(""), author(""), year(0), note("") { }

bool operator== (const BookData& b1, const BookData& b2)
{
	return b1.title == b2.title && b1.author == b2.author && b1.year == b2.year && b1.note == b2.note;
}

bool operator!= (const BookData& b1, const BookData& b2)
{
	return !(b1 == b2);
}
