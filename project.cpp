#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ============================================================
// BOOK CLASS
// ============================================================
class Book {
private:
    int bookID;
    string title;
    string author;
    double price;
    bool issued;

public:
    // Default constructor
    Book() {
        bookID = 0;
        title = "";
        author = "";
        price = 0.0;
        issued = false;
    }
    // Parameterized constructor
    Book(int id, string t, string a, double p, bool status = false) {
        bookID = id;
        title = t;
        author = a;
        price = p;
        issued = status;
    }
    // Getter functions

    int getBookID() {
        return bookID;
    }
    string getTitle() {
        return title;
    }
    string getAuthor() {
        return author;
    }
    double getPrice() {
        return price;
    }
    bool isIssued() {
        return issued;
    }
    // Issue book
    void issueBook() {

        if (!issued) {

            issued = true;

            cout << "\nBook issued successfully!\n";
        }
        else {

            cout << "\nBook is already issued.\n";
        }
    }
    // Return book
    void returnBook() {

        if (issued) {

            issued = false;

            cout << "\nBook returned successfully!\n";
        }
        else {

            cout << "\nBook is already available.\n";
        }
    }
    // Display book information
    void displayBook() {

        cout << "\n-----------------------------------\n";

        cout << "Book ID: " << bookID << endl;

        cout << "Title: " << title << endl;

        cout << "Author: " << author << endl;

        cout << "Price: Rs. " << price << endl;

        if (issued) {

            cout << "Status: Issued" << endl;
        }
        else {

            cout << "Status: Available" << endl;
        }

        cout << "-----------------------------------\n";
    }
    // Save book information to file
    void saveToFile(ofstream &file) {

        file << bookID << "|"
             << title << "|"
             << author << "|"
             << price << "|"
             << issued << endl;
    }
};
// ============================================================
// LOGIN SYSTEM CLASS
// ============================================================

class LoginSystem {

private:
    string username;
    string password;

public:

    // Constructor
    LoginSystem() {

        username = "admin";
        password = "1234";
    }
    // Create users.txt if it does not exist
    void createUserFile() {

        ifstream checkFile("users.txt");

        if (!checkFile) {

            ofstream file("users.txt");
            if (file) {
                file << username << endl;
                file << password << endl;

                file.close();
            }
        }

        checkFile.close();
    }
    // Login function
    bool login() {

        string enteredUsername;
        string enteredPassword;
        string savedUsername;
        string savedPassword;
        ifstream file("users.txt");
        if (!file) {

            cout << "\nUnable to open users.txt\n";

            return false;
        }
        getline(file, savedUsername);

        getline(file, savedPassword);

        file.close();
        cout << "\n====================================\n";
        cout << "          LIBRARY LOGIN\n";
        cout << "====================================\n";
        cout << "Username: ";
        cin >> enteredUsername;
        cout << "Password: ";
        cin >> enteredPassword;
        if (enteredUsername == savedUsername &&
            enteredPassword == savedPassword) {

            cout << "\nLogin successful!\n";

            cout << "Welcome, " << enteredUsername << "!\n";

            return true;
        }
        cout << "\nInvalid username or password!\n";

        return false;
    }
};
// ============================================================
// LIBRARY CLASS
// ============================================================

class Library {

private:

    vector<Book> books;

public:

    // ========================================================
    // LOAD BOOKS FROM FILE
    // ========================================================

    void loadBooks() {

        ifstream file("books.txt");

        // If file doesn't exist, simply return
        if (!file) {

            return;
        }
        string line;
        while (getline(file, line)) {

            if (line.empty()) {

                continue;
            }

            int id;

            string title;
            string author;
            double price;
            bool issued;
            // Find separators
            size_t pos1 = line.find('|');

            size_t pos2 = line.find('|', pos1 + 1);

            size_t pos3 = line.find('|', pos2 + 1);

            size_t pos4 = line.find('|', pos3 + 1);
            // Make sure all separators exist
            if (pos1 == string::npos ||
                pos2 == string::npos ||
                pos3 == string::npos ||
                pos4 == string::npos) {

                continue;
            }
            try {

                // Book ID
                id = stoi(
                    line.substr(0, pos1)
                );

                // Book title
                title = line.substr(
                    pos1 + 1,
                    pos2 - pos1 - 1
                );
                // Author
                author = line.substr(
                    pos2 + 1,
                    pos3 - pos2 - 1
                );
                // Price
                price = stod(
                    line.substr(
                        pos3 + 1,
                        pos4 - pos3 - 1
                    )
                );
                // Issued status
                issued = stoi(
                    line.substr(pos4 + 1)
                );
                // Add book to vector
                books.push_back(
                    Book(
                        id,
                        title,
                        author,
                        price,
                        issued
                    )
                );
            }
            catch (...) {

                cout << "\nError reading book data.\n";
            }
        }

        file.close();
    }
    // ========================================================
    // SAVE BOOKS TO FILE
    // ========================================================

    void saveBooks() {

        ofstream file("books.txt");

        if (!file) {

            cout << "\nError opening books.txt for saving.\n";

            return;
        }

        for (Book &book : books) {

            book.saveToFile(file);
        }


        file.close();
    }
    // ========================================================
    // ADD BOOK
    // ========================================================

    void addBook() {

        int id;
        string title;
        string author;
        double price;
        cout << "\n====================================\n";
        cout << "             ADD BOOK\n";
        cout << "====================================\n";
        cout << "Enter Book ID: ";
        cin >> id;
        // Check for duplicate ID
        for (Book &book : books) {

            if (book.getBookID() == id) {

                cout << "\nBook ID already exists!\n";

                return;
            }
        }

        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        cout << "Enter Book Price: Rs. ";
        cin >> price;
        // Validate price
        if (price < 0) {
            cout << "\nPrice cannot be negative.\n";
            return;
        }
        // Create and add book
        books.push_back(
            Book(
                id,
                title,
                author,
                price
            )
        );
        // Save to file
        saveBooks();

        cout << "\nBook added successfully!\n";
    }
    // ========================================================
    // DISPLAY ALL BOOKS
    // ========================================================

    void displayAllBooks() {

        if (books.empty()) {

            cout << "\nNo books available in the library.\n";

            return;
        }
        cout << "\n====================================\n";
        cout << "             ALL BOOKS\n";
        cout << "====================================\n";
        for (Book &book : books) {

            book.displayBook();
        }
    }
    // ========================================================
    // SEARCH BOOK
    // ========================================================

    void searchBook() {

        int id;
        cout << "\nEnter Book ID to search: ";
        cin >> id;
        for (Book &book : books) {

            if (book.getBookID() == id) {

                cout << "\nBook found!\n";

                book.displayBook();

                return;
            }
        }
        cout << "\nBook not found.\n";
    }
    // ========================================================
    // ISSUE BOOK
    // ========================================================

    void issueBook() {

        int id;
        cout << "\nEnter Book ID to issue: ";
        cin >> id;
        for (Book &book : books) {

            if (book.getBookID() == id) {

                book.issueBook();
                // Save updated status
                saveBooks();
                return;
            }
        }
        cout << "\nBook not found.\n";
    }
    // ========================================================
    // RETURN BOOK
    // ========================================================

    void returnBook() {

        int id;
        cout << "\nEnter Book ID to return: ";
        cin >> id;
        for (Book &book : books) {

            if (book.getBookID() == id) {

                book.returnBook();
                // Save updated status
                saveBooks();
                return;
            }
        }
        cout << "\nBook not found.\n";
    }
    // ========================================================
    // DELETE BOOK
    // ========================================================

    void deleteBook() {

        int id;
        cout << "\nEnter Book ID to delete: ";
        cin >> id;
        for (
            vector<Book>::iterator it = books.begin();
            it != books.end();
            ++it
        ) {

            if (it->getBookID() == id) {
                // Don't delete an issued book
                if (it->isIssued()) {

                    cout << "\nCannot delete an issued book.\n";

                    return;
                }
                books.erase(it);
                // Save changes
                saveBooks();
                cout << "\nBook deleted successfully!\n";

                return;
            }
        }

        cout << "\nBook not found.\n";
    }
};
// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {
    // ========================================================
    // LOGIN
    // ========================================================

    LoginSystem loginSystem;
    // Create users.txt if it doesn't exist
    loginSystem.createUserFile();
    // Ask user to login
    if (!loginSystem.login()) {

        cout << "\nAccess denied.\n";
        cout << "Program terminated.\n";

        return 0;
    }

    // ========================================================
    // LIBRARY
    // ========================================================
    Library library;
    // Load previously saved books
    library.loadBooks();

    int choice;
    // ========================================================
    // MAIN MENU
    // ========================================================

    do {
        cout << "\n\n";
        cout << "====================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Logout / Exit\n";

        cout << "====================================\n";

        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {

            case 1:

                library.addBook();

                break;

            case 2:

                library.displayAllBooks();

                break;

            case 3:

                library.searchBook();

                break;

            case 4:

                library.issueBook();

                break;

            case 5:

                library.returnBook();

                break;

            case 6:

                library.deleteBook();

                break;

            case 7:

                cout << "\nLogging out...\n";

                cout << "Thank you for using the Library Management System!\n";

                break;

            default:

                cout << "\nInvalid choice!\n";

                cout << "Please enter a number from 1 to 7.\n";
        }
    } while (choice != 7);
    return 0;
}