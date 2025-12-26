#include "book.h"

BookData::BookData(
	std::string title, 
	std::string author, 
	unsigned int year, 
	unsigned int pages,
	unsigned int shelf, 
	std::string note) 
	: title(title), author(author), year(year), pages(pages), shelf(shelf), read(false), note(note) { }

BookData::BookData() { }
