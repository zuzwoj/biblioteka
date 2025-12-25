#pragma once
#include <string>

struct BookData
{
	std::string title;
	std::string author;
	unsigned int year;
	unsigned int pages;
	unsigned int shelf;
	bool read;
	std::string note;

	BookData(
		std::string title, 
		std::string author, 
		unsigned int year, 
		unsigned int pages, 
		unsigned int shelf, 
		std::string note);
	BookData();
};

class Book
{
private:
	static unsigned int currentID;
	unsigned int ID;

public:
	BookData bookData;

	Book(BookData bookData);
	Book();

	friend bool operator== (const Book& b1, const Book& b2);
	friend bool operator!= (const Book& b1, const Book& b2);
};
