#pragma once
#include <string>

struct BookData
{
	std::string title;
	std::string author;
	unsigned int year;
	std::string note;

	BookData(std::string title, std::string author, unsigned int year, std::string note);
};

class Book
{
private:
	BookData bookData;

public:
	Book(BookData bookData);
};
