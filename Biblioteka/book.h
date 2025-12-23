#pragma once
#include <string>

struct BookData
{
	std::string title;
	std::string author;
	unsigned int year;
	std::string note;

	BookData(std::string title, std::string author, unsigned int year, std::string note);
	BookData();
};

class Book
{
public:
	BookData bookData;

	Book(BookData bookData);
	Book();
};
