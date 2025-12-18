# User and Book Storage 📚

This project is a **virtual bookshelf application** that allows users to manage their personal book collections. Users can create accounts, log in, and perform full CRUD operations on their books, as well as view reading statistics — all through a graphical interface.

The application was developed entirely in **C++**, using **Qt Creator** for the GUI and **MySQL** for data persistence.

---

## 📑 Table of Contents

- [Features](#-features)
- [Required Software](#-required-software)
- [Required Hardware](#-required-hardware)
- [How It Works](#-how-it-works)
  - [Overview](#overview)
- [Database Structure](#-database-structure)
- [Adding Books](#-adding-books)
- [Removing Books](#-removing-books)
- [Searching Books](#-searching-books)
- [Updating Books](#-updating-books)
- [Viewing Books](#-viewing-books)
- [Viewing Statistics](#-viewing-statistics)
- [Language Note](#-language-note)
- [Notes](#-notes)
- [Demo Account](#-demo-account)
- [Contact](#-contact)

---

## ✨ Features

- User registration and authentication  
- Personal book management per user  
- Add, remove, update, and search books  
- Support for different book formats (physical, ebook, audiobook)  
- Reading progress tracking with status indicators  
- Visual statistics about the user's library  
- Graphical interface built with Qt  

---

## 🧰 Required Software

- A **C++ compiler**
- [Qt Creator](https://www.qt.io/product/development-tools) (Lite version is sufficient)
- MySQL database server

---

## 💻 Required Hardware

- A computer capable of running Qt Creator and compiling C++

---

## 🚀 How It Works

### Overview

When the application is executed for the first time, it automatically creates the required database and tables if they do not already exist. If the database exists, it is simply loaded.

Once initialized, the login screen is displayed. Users may log in using an existing account or create a new one. After authentication, the main interface is shown, allowing access to all available features. An **Exit** button at the bottom of the interface logs the user out safely.

---

## 🗄️ Database Structure

The database consists of **two tables**:

### Users Table
- ID  
- Email  
- Name  
- Password  

User IDs are generated automatically by checking the last registered ID.

### Books Table
- User ID  
- Book ID  
- Title  
- Author  
- Format (physical, ebook, audiobook)  
- Total pages  
- Pages read  

Each book is associated with a user through the user ID, ensuring personal libraries remain private.

---

## ➕ Adding Books

To add a book, the user must provide:
- Title
- Author
- Format
- Total number of pages
- Number of pages read

The user ID is automatically inferred from the logged-in account.  
Validation messages are displayed in case of missing or incorrect data.

---

## ➖ Removing Books

Books can be removed by providing:
- Title
- Author
- Format

If the book is found, it is deleted and a confirmation message is shown.  
If no books exist or the book is not found, an error message is displayed.

---

## 🔍 Searching Books

Users can search for a book by:
- Title
- Author
- Format

If found, the application displays:
- Total pages
- Pages read
- Reading progress bar
- Status (Stopped, In Progress, or Finished)

---

## ✏️ Updating Books

If the book exists, the user may update:
- Total pages
- Pages read

Success or error messages are displayed accordingly.

---

## 📖 Viewing Books

Books are displayed one at a time, showing:
- Book information
- Reading progress bar
- Reading status

Navigation buttons allow browsing through the collection.

---

## 📊 Viewing Statistics

The statistics screen displays:
- Largest book (by number of pages)
- Total number of books
- Number of books read
- Total pages read

---

## 🌍 Language Note

> ⚠️ **Important:**  
> Not all elements of the project are written in English.  
> Some parts of the **source code**, **graphical interface**, and **messages** are in **Portuguese**, as this project was originally developed for an academic course in Brazil.

---

## 📝 Notes

This project was developed in **December 2024** as part of the *Programming Language II* course at the **Faculty of Computer Engineering – UFSC**.

> ⚠️ **Academic integrity notice**  
> If you are a student at UFSC, **do not copy this project**.

Some design choices (such as inheritance and polymorphism in the `Book` class hierarchy) were implemented to meet course requirements.

---

## 🔐 Demo Account

A test account is available with pre-registered books:

- **Login:** `administracao123`
- **Password:** `adm123`

---

## 📬 Contact

If you have any questions or need help, feel free to contact me 💖
