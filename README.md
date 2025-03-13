# User and book storage

This project consists of registering the books that each user wants, in other words, it's a virtual bookshelf. This allows new users to register and existing ones to log in. In addition to registering books, each user can remove, update and search for books, as well as view statistics about them. It is entirely made in C++, in QtCreator, using the MySQL database.

***

## Required Software

- C++ compiler;
- To be able to use the project and visualize all the graphical interfaces, you need to use [QtCreator](https://www.qt.io/product/development-tools) (the lite version is great).

## Required Hardware

- Just a computer that runs QtCreator and compiles C++.

***

## How it works

### A simple description:

When you run the program for the first time, the database that registers users and books will be created, since it probably doesn't exist yet. If it does exist, it will be opened. If this is OK, the login screen will be shown and you can log in with the administrator account (explained below) or create a new one. After logging in, you will be shown the main interface where you can perform all operations. At the bottom, you can see an “Exit” button which will log you out.

***

### The database:

The database is divided into two tables: users and books. The users table has the following items: ID, e-mail, name and password. All are added using C++, and the ID is added based on the last ID added (the last one registered is searched for using a query and, if there isn't one, it's 1). The book table, on the other hand, has: user ID, book ID (also added based on the last book ID added and, if there isn't one, it's 1), title, author, format (physical, ebook or audiobook), number of total pages and number of pages read.

***

### To add books

To add a book, you need to enter the title, author, format (which is already predefined), number of total pages and number of pages read. The user ID is generated automatically from the e-mail address used to log in (it is “saved” because it is passed on as a parameter for each screen). If any information is missing or misspelled, an error message is displayed. If all is well, a confirmation message appears. You can add the same books in different formats.

***

### To remove books

To remove a book, you need to enter the book's title, author and format. If it is found, it will be removed and a message will be displayed. If not, an error message will be displayed. If there are no books registered, a message is displayed indicating this and asking for books to be registered.

***

### To research books

To search for a book, you need to enter its title, author and format. If the book is found, it will show the number of pages, the number of pages read and a progress bar indicating the reading progress, along with the book's status (Stopped, In progress or Finished). If it is not found, an error message is displayed. If there are no books registered, a message is displayed indicating this and asking for books to be registered.

***

### Update books

To update a book, you need to enter the title, author and format. If the book is found, you can update the number of total pages and the number of pages read. If the change is completed, a completion message is displayed and if not, an error message is displayed. If there are no books registered, a message is displayed indicating this and asking for books to be registered.

***

### Show books

Showing the books will display the public information for each book along with the progress bar and the status of the book. One book is shown at a time and there is a “Next” button in the bottom right-hand corner of the page, as well as a “Back” button in the bottom left-hand corner. If there are no more books registered, a screen indicating this is shown and only the back button is present. If there are no books registered, a message is displayed indicating this and asking for books to be registered.

***

### Show statistics

This option shows the largest book on the shelf (by number of pages), the number of books on the shelf and the number of books and pages read. If there are no books registered, a message is displayed indicating this and asking for books to be registered.

***

## Notes

This was a project done for the “Linguagem de Programação II” course, in December 2024, at the Faculty of Computer Engineering - UFSC. So, if you're a student there, DO NOT COPY IT. This addendum explains why the project uses a “books” class with inheritance and polymorphism, when it wouldn't be necessary: it's a requirement of the project, it's possible to do without.

There is already an account registered with some books, in case you want to access it. It is:
- Login: administracao123
- Password: adm123
- 
***

#### if you need any help, please contact me <3

***
