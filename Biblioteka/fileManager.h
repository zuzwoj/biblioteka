#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"
#include "json.h"

using json = nlohmann::json;

class FileManager
{
private:
	std::string rootDirectory;
	std::string shelvesFile;
	std::string booksDirectory;
	std::string booksFiles;

	void loadShelvesFromFile(Library& library);
	void loadBooksFromFile(Library& library);
	void loadBookFromFile(Library& library, json j, int bookId);

public:
	FileManager();

	void loadLibraryFromFile(Library& library);

	void createShelf(Shelf& shelf);
	void deleteShelf(Shelf& shelf);
	void updateShelf(Shelf& shelf);

	void createBook(Book& book);
	void deleteBook(Book& book);
	void updateBook(Book& book);
};