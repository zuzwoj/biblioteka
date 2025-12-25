#include "fileManager.h"
#include <windows.h>
#include <shlobj.h> 
#include <iostream>
#include <fstream>

FileManager::FileManager()
{
    wchar_t* appData;
    SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_FORCE_APP_DATA_REDIRECTION, NULL, &appData);
    std::wstring ws(appData);
    rootDirectory = std::string(ws.begin(), ws.end()) + "\\biblioteka";
    shelvesFile = rootDirectory + "\\shelves.json";
    booksDirectory = rootDirectory + "\\books";
    booksFiles = booksDirectory + "\\*.json";
}

void FileManager::loadShelvesFromFile(Library& library)
{
    std::ifstream file(shelvesFile);
    if (file)
    {
        json j;
        file >> j;
        try
        {
            for (const auto& shelf : j["shelves"])
            {
                Shelf s = Shelf(shelf["name"], shelf["ID"]);
                library.addShelf(s);
            }
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON error in loadShelvesFromFile()\n";
        }
    }
}

void FileManager::loadBooksFromFile(Library& library)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(booksFiles.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cerr << "JSON error in loadBooksFromFile()\n";
        return;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            continue;
        }
        std::string filename = findData.cFileName;
        std::string stem = filename.substr(0, filename.size() - 5);
        if (!std::all_of(stem.begin(), stem.end(), ::isdigit))
        {
            continue;
        }
        int fileNumber = std::atoi(stem.c_str());
        std::ifstream file(booksDirectory + "\\" + filename);
        json j;
        file >> j;
        loadBookFromFile(library, j, fileNumber);
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

void FileManager::loadBookFromFile(Library& library, json j, int bookId)
{
    BookData bookData = BookData();
    bookData.title = j["title"];
    bookData.author = j["author"];
    bookData.year = j["year"];
    bookData.pages = j["pages"];
    bookData.shelf = j["shelf"];
    bookData.read = j["read"];
    bookData.note = j["note"];
    Book newBook = Book(bookData, bookId);
    library.getShelves().at(bookData.shelf).addBook(newBook);
}

void FileManager::loadLibraryFromFile(Library& library)
{
	loadShelvesFromFile(library);
	loadBooksFromFile(library);
}

void FileManager::createShelf(Shelf& shelf)
{

}

void FileManager::deleteShelf(Shelf& shelf)
{

}

void FileManager::updateShelf(Shelf& shelf)
{

}

void FileManager::createBook(Book& book)
{

}

void FileManager::deleteBook(Book& book)
{

}
void FileManager::updateBook(Book& book)
{

}
