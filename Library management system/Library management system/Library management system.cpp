#include<iostream>
#include<string>
#include<iomanip>
#include <fstream>
using namespace std;

//page
#define new_page system("cls")

//globalvariable
const int capacity = 1000;
int numofbooks = 5;
string* Author = new string[capacity];
string* Title = new string[capacity];
int* ID = new int[capacity];
bool* Status = new bool[capacity];

//save the updated data
void save_to_file() {
    ofstream MyFile("library_data.txt");

    if (MyFile.is_open()) {
        MyFile << numofbooks << endl;

        for (int i = 0; i < numofbooks; i++) {
            MyFile << ID[i] << "\t" << Title[i] << "\t" << Author[i] << "\t" << boolalpha << Status[i] << endl;
        }
        MyFile.close();
    }
}

//read the recent data
void load_from_file() {
    ifstream MyReadFile("library_data.txt");

    if (MyReadFile.is_open()) {
        MyReadFile >> numofbooks;

        for (int i = 0; i < numofbooks; i++) {
            MyReadFile >> ID[i];
            MyReadFile.ignore();
            getline(MyReadFile, Title[i]);
            getline(MyReadFile, Author[i]);
            MyReadFile >> boolalpha >> Status[i];
        }
        MyReadFile.close();
    }
}

//search
int search(int id) {

    for (int i = 0; i < numofbooks; i++)
    {
        if (ID[i] == id)
            return i;
    }
    return -1;
}

//enter id when required
int read_id() {
    int id;
    cout << "\nEnter book ID : ";
    cin >> id;
    int find = search(id);
    return find;
}

//confirm 
int choose;
void confirm(int id) {
    cout << "\n-book-\nauthor: " << Author[id]
        << "\ntitle: " << Title[id]
        << "\nid: " << ID[id];
    cout << "\n\nDo you want to confirm\n";
    cout << "1-confirm  2-retreat\n";
    cout << "your choice: ";
    cin >> choose;
    cout << endl;
}

//add book
void add_book() {
    if (numofbooks >= 1000) {
        cout << "\nError: Library storage is full!\n";
        return;
    }

    do {
        new_page;
        cout << "\t\t\t\t-Add book-\n";
        ID[numofbooks] = ID[numofbooks - 1] + 1;
        cout << "Please enter author : ";
        cin.ignore();
        getline(cin, Author[numofbooks]);
        cout << "Please enter title : ";
        getline(cin, Title[numofbooks]);

        confirm(numofbooks);
    } while (choose != 1);

    Status[numofbooks] = true;
    numofbooks++;
    save_to_file();
    cout << "\nBook added successfully!";
    cout << "\nBook added successfully! Current library size: " << numofbooks << endl;
}

//borrow book
void borrow_book() {
    cout << "\t\t\t\t - BORROW BOOK -\n";
rewrite_borrow:
    int find = read_id();
    if (find != -1) {
        if (Status[find])
        {
            confirm(find);
            if (choose == 2)
                goto rewrite_borrow;
            cout << "\nBook borrowed successfully!\n";
            Status[find] = false;
            save_to_file();
        }
        else
            cout << "\nSorry: This book is already borrowed.\n";
    }
    else
        cout << "Error: Book not found in the library !\n";
}

//return book
void return_book() {
    cout << "\t\t\t\t ----- Return BOOK -----\n";
rewrite_return:
    int find = read_id();
    if (find != -1) {
        if (Status[find]) {
            cout << "\nError: Wrong ID ; Book is already exist.\n";
            goto rewrite_return;
        }
        else {
            confirm(find);
            if (choose == 2)
                goto rewrite_return;
            cout << "\nBook returned successfully!\n";
            Status[find] = true;
            save_to_file();
        }
    }
    else
        cout << "\nError: Invalid ID!\n";
}

//remove book
void remove_book() {
    cout << "\t\t\t\t ----- REMOVE BOOK -----\n";
rewrite_remove:
    int find = read_id();
    if (find != -1) {
        confirm(find);
        if (choose == 1) {
            for (int i = find; i < numofbooks - 1; i++) {
                ID[i] = ID[i + 1];
                Author[i] = Author[i + 1];
                Title[i] = Title[i + 1];
                Status[i] = Status[i + 1];
            }
            numofbooks--;
            save_to_file();
            cout << "\nBook removed successfully from system\n";
        }
        else
            goto rewrite_remove;
    }
    else
        cout << "\nError: Invalid ID!\n";
}

//update book
void update_book() {
    cout << "\t\t\t\t ----- UPDATE BOOK -----\n";
rewrite_update:
    int find = read_id();
    if (find != -1) {
        confirm(find);
        if (choose == 1) {
            int num;
            cout << "Update:\n 1-Author\n 2-Title\n 3-both";
            cout << "\nEnter a choice: ";
            cin >> num;
            switch (num) {
            case 1:
                cout << "\nEnter new Author: ";
                cin.ignore();
                getline(cin, Author[find]);
                cout << "\nBook updated successfully!\n";
                save_to_file();
                break;
            case 2:
                cout << "\nEnter new Title: ";
                cin.ignore();
                getline(cin, Title[find]);
                cout << "\nBook updated successfully!\n";
                save_to_file();
                break;
            case 3:
                cout << "\nEnter new Author: ";
                cin.ignore();
                getline(cin, Author[find]);
                cout << "\nEnter new Title: ";
                getline(cin, Title[find]);
                cout << "\nBook updated successfully!\n";
                save_to_file();
                break;
            default:
                cout << "\nError: Invalid choice\n";
            }
        }
    }
    else
        cout << "\nError: Invalid ID!\n";
}

//all books
void display_all_books() {
    cout << "\t\t\t\t ------- ALL BOOKS ------\n";
    if (numofbooks == 0) {
        cout << "\nSorry:The library is empty\n";
        return;
    }
    cout << endl;
    cout << left << setw(8) << "ID" << setw(25) << "Title" << setw(20) << "Author" <<setw(15) <<"Status" << endl;
    cout << "-------------------------------------------------------------------\n";
    for (int i = 0; i < numofbooks; i++) {
        cout << left << setw(8) << ID[i]
            << setw(25) << Title[i]
            << setw(20) << Author[i]
            << setw(15) << (Status[i] ? "Available" : "Borrowed") << endl;
    }
}

//available books
void display_available_books() {
    cout << "\t\t\t\t ------ AVAILABLE BOOKS ------\n";
    int check = 0;
    cout << endl;
    cout << left << setw(8) << "ID" << setw(25) << "Title" << setw(20) << "Author" << endl;
    cout << "---------------------------------------------------\n";
    for (int i = 0; i < numofbooks; i++) {
        if (Status[i]) {
            cout << left << setw(8) << ID[i]
                << setw(25) << Title[i]
                << setw(20) << Author[i];
            cout << endl;
            check++;
        }
    }
    if (check == 0)
        cout << "\nSorry:All books were borrowed.\n";
}

//Admin
void admin()
{
    new_page;
    cout << "\t\t\t\t ---- Admin Access Granted ----\n";
    int choice;
    do {
        cout << "\nWhat do you want : \n";
        cout << "1-Display all books\n";
        cout << "2-Display available books\n";
        cout << "3-Add book\n";
        cout << "4-Remove book\n";
        cout << "5-Update book\n";
        cout << "6-Exist\n";
        cout << "Enter a choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            new_page;
            display_all_books();
            break;
        case 2:
            new_page;
            display_available_books();
            break;
        case 3:
            add_book();
            break;
        case 4:
            remove_book();
            break;
        case 5:
            update_book();
            break;
        case 6:
            new_page;
            cout << "\nExisting system....\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);
}

//user
void user() {
    new_page;
    cout << "\t\t\t\t---- User Access Granted ----\n";
    int choice;
    do {
        cout << "\nWhat do you want : \n";
        cout << "1-Display all books\n";
        cout << "2-Display available books\n";
        cout << "3-Add book\n";
        cout << "4-Borrow book\n";
        cout << "5-Return book\n";
        cout << "6-Exist\n";
        cout << "Enter a choice: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
        case 1:
            new_page;
            display_all_books();
            break;
        case 2:
            new_page;
            display_available_books();
            break;
        case 3:
            add_book();
            break;
        case 4:
            borrow_book();
            break;
        case 5:
            return_book();
            break;
        case 6:
            new_page;
            cout << "\nExisting system....\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);
}

//main
int main() {

    //load ancient data
    load_from_file();

    //initialize_Variables
    string titles[] = {
            "Clean Code",
            "Effective C++",
            "Grokking Algorithms",
            "Don't Make Me Think",
            "A Tour of C++"
    };

    string authors[] = {
            "Robert C. Martin",
            "Scott Meyers",
            "Aditya Bhargava",
            "Steve Krug",
            "Bjarne Stroustrup"
    };

    ID[0] = 1000;

    for (int i = 0; i < 5; i++) {
        ID[i + 1] = ID[i] + 1;
        Status[i] = true;
        Title[i] = titles[i];
        Author[i] = authors[i];
    }

    cout << "\t\t\t\t\t----AMOOR library----\n";

    //who 
    int choice_who;
    cout << "\nYou are :\n 1-Admin \n 2-User\n";
    cout << "Please enter a choice : ";
    cin >> choice_who;
    cout << endl;

    const int password = 1234;
    switch (choice_who)
    {
    case 1:
        int pass;
        new_page;
		cout << "\t\t\t\t---- Admin Access Required ----\n";
        cout << "\nPlease enter password : ";
        cin >> pass;
        if (pass == password) {
            admin();
        }
        else {
            cout << "Wrong!!\n";
        }
        break;
    case 2:
        user();
        break;
    default:
        cout << "\nInvalid choice.\n";
    }
    cout << "\n< Thanks a lot for your time , hope our service has been satisfactory to you. >\n";

    //free_memory
    delete[]Author;
    delete[]Title;
    delete[]Status;
    delete[]ID;

    return 0;
}
