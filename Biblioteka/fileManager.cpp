#include "fileManager.h"
#include <windows.h>
#include <shlobj.h> 
#include <iostream>
#include <fstream>
#include <chrono>

FileManager::FileManager(Library& library) : library(library)
{
    wchar_t* appData;
    SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_FORCE_APP_DATA_REDIRECTION, NULL, &appData);
    std::wstring ws(appData);
    rootDirectory = std::string(ws.begin(), ws.end()) + "\\Biblioteka";
    shelvesFile = rootDirectory + "\\shelves.json";
    booksDirectory = rootDirectory + "\\books";
    discardedDirectory = rootDirectory + "\\discarded";
    booksFiles = booksDirectory + "\\*.json";

    if (CreateDirectoryA(rootDirectory.c_str(), nullptr))
    {
        CreateDirectoryA(booksDirectory.c_str(), nullptr);
        CreateDirectoryA(discardedDirectory.c_str(), nullptr);
        CreateFileA(shelvesFile.c_str(), FILE_READ_DATA, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
        persistShelves();
    }
}

void FileManager::loadShelvesFromFile()
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

void FileManager::loadBooksFromFile()
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(booksFiles.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cerr << "JSON error in loadBooksFromFile() or no books persisted\n";
        return;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            continue;
        }
        std::string filename = findData.cFileName;
        int bookId = getBookId(filename);
        if (bookId < 0)
        {
            continue;
        }
        std::ifstream file(booksDirectory + "\\" + filename);
        json j;
        file >> j;
        loadBookFromFile(j, bookId);
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

int FileManager::getBookId(std::string filename)
{
    std::string stem = filename.substr(0, filename.size() - 5);
    if (!std::all_of(stem.begin(), stem.end(), ::isdigit))
    {
        return -1;
    }
    return std::atoi(stem.c_str());
}

void FileManager::loadBookFromFile(json j, int bookId)
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

void FileManager::loadLibraryFromFile()
{
	loadShelvesFromFile();
	loadBooksFromFile();
}

void FileManager::persistShelves()
{
    json result;
    result["shelves"] = json::array();
    for (auto& s : library.getShelves())
    {
        json shelfJson;
        shelfJson["name"] = s.second.name;
        shelfJson["ID"] = s.first;

        result["shelves"].push_back(shelfJson);
    }
    std::ofstream file(shelvesFile);
    if (file)
    {
        try
        {
            file << result.dump();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON error in persistShelves()\n";
        }
    }
}

void FileManager::persistBook(Book& book)
{
    json result;
    result["title"] = book.bookData.title;
    result["author"] = book.bookData.author;
    result["year"] = book.bookData.year;
    result["pages"] = book.bookData.pages;
    result["shelf"] = book.bookData.shelf;
    result["read"] = book.bookData.read;
    result["note"] = book.bookData.note;
    std::ofstream file(booksDirectory + "\\" + std::to_string(book.getID()) + ".json");
    if (file)
    {
        try
        {
            file << result.dump();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON error in persistShelves()\n";
        }
    }
}

void FileManager::deleteBook(Book& book)
{
    int timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    std::string suffix = std::to_string(book.getID()) + ".json";
    std::string src = booksDirectory + "\\" + suffix;
    std::string dst = discardedDirectory + "\\" + std::to_string(timestamp) + "-" + suffix;
    if (!MoveFileExA(src.c_str(), dst.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING)) {
        std::cerr << "Error in deleteBook()\n";
    }
}
