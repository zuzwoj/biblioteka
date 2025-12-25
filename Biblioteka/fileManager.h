#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"

class FileManager
{
public:
	void loadLibraryFromFile(Library& library);

	void createShelf(Shelf& shelf);
	void deleteShelf(Shelf& shelf);
	void updateShelf(Shelf& shelf);

	void createBook(Book& book);
	void deleteBook(Book& book);
	void updateBook(Book& book);
};