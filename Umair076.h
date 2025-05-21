
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "app.cpp"

using namespace std;

app::app()
{
    choice = 0;
    head = nullptr;

    ifstream in("books/AllBooks.txt");

  
    Node *current = nullptr;

    string line;
    while (getline(in, line))
    {
        Node *newNode = new Node(line);

        if (head == nullptr)
        {
            head = newNode;
            current = head;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }
    }
    in.close();
}
app::~app()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}
bool app::init()
{
    menu();
    if (choice == 1)
    {
        DisplayBooks();
    }
    else if (choice == 2)
    {
        
    }
    else if (choice == 3)
    {
        system("cls");
        exit(0);
    }
    return true;
}

void app::menu()
{
    system("cls");

    while (choice != 1 && choice != 2 && choice != 3)
    {
        cout << "*************** E-Book Reader ***************" << endl
             << endl;

        if (choice == 0)
        {
            cout << "              Choose your option" << endl
                 << endl;
        }
        else if (choice != 1 && choice != 2 && choice != 3)
        {
            cout << "              Invalid option!" << endl
                 << endl;
        }

        cout << "1. Display All Books" << endl;
        cout << "2. Exit" << endl
             << endl;

        cout << "Enter your choice: ";
        cin >> choice;
    }
}

void app::DisplayBooks()
{
    system("cls");
    int count = 1;

    string st;
    cout << "*************** E-Book Reader ***************" << endl
         << endl;

    ifstream in("books/AllBooks.txt");
    while (getline(in, st))
    {
        cout << count << "." << st << endl;
        count++;
    }

    cout << "Choose : " << endl;
    cin >> BookChoice;

    bookname = searchBook(head, BookChoice);
    readBook(bookname);
}

string app::searchBook(Node *head, int index)
{
    Node *current = head;
    int count = 0;

    while (current != nullptr)
    {
        if (count + 1 == index)
        {
            return current->Names;
        }
        current = current->next;
        count++;
    }
    return "Book not found"; // If the index is out of range
}

void app::readBook(string bookname)
{

    if (bookname == "Book not found")
    {
        cout << "Invalid book selection. Returning to menu..." << endl;
        menu();
        return;
    }
    string name = bookname;

    string line;
    int pageNo = 1; // Start at page 1
    int choice;
    bool stillReading = true;

    while (stillReading)
    {
        string filePath = "books/" + name + "/page" + to_string(pageNo) + ".txt";
        ifstream in(filePath);

        if (!in.is_open())
        {
            cout << "Error: Could not open " << filePath << endl;
            break; // Exit the loop if the file cannot be opened
        }

        system("cls");
        cout << "*************** E-Book Reader ***************" << endl;
        cout << "               Page " << pageNo<< endl
             << endl;

        // Read and display the contents of the page
        while (getline(in, line))
        {
            cout << line << endl;
        }

        in.close();

        // Navigation options
        cout << endl
             << "Options:" << endl
             << "1. Next Page" << endl
             << "2. Previous Page" << endl
             << "0. Exit" << endl
             << "Enter your choice: ";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1: // Next page
            pageNo++;
            break;
        case 2: // Previous page
            if (pageNo > 1)
            {
                pageNo--;
            }
            else
            {
                cout << "You are already on the first page!" << endl;
            }
            break;
        case 0: // Exit
            stillReading = false;
            menu();
            break;
        default: // Invalid input
            cout << "Invalid choice. Try again." << endl;
        }
    }
}
