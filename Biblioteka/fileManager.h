#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"
#include "json.h"

using json = nlohmann::json;

class FileManager
{
private:
	Library& library;

	std::string rootDirectory;
	std::string shelvesFile;
	std::string booksDirectory;
	std::string discardedDirectory;
	std::string booksFiles;

	void loadShelvesFromFile();
	void loadBooksFromFile();
	void loadBookFromFile(json j, int bookId);

	int getBookId(std::string filename);

public:
	FileManager(Library& library);

	void loadLibraryFromFile();

	void persistShelves();

	void persistBook(Book& book);
	void deleteBook(Book& book);
};