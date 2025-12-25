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

	friend bool operator== (const BookData& b1, const BookData& b2);
	friend bool operator!= (const BookData& b1, const BookData& b2);
};

class Book
{
public:
	BookData bookData;

	Book(BookData bookData);
	Book();

	friend bool operator== (const Book& b1, const Book& b2);
	friend bool operator!= (const Book& b1, const Book& b2);
};
