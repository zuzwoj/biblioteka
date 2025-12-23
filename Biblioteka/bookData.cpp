#include "book.h"

BookData::BookData(std::string title, std::string author, unsigned int year, std::string note) 
	: title(title), author(author), year(year), note(note) { }

BookData::BookData() : title(""), author(""), year(0), note("") { }
