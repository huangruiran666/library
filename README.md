# Professional Library Management System

[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Interface](https://img.shields.io/badge/Interface-Bilingual-0ea5e9.svg)](.)

Bilingual Chinese/English command-line library management system built as a single-file C++ application with local persistence, borrowing workflows, and CSV import/export support.

## Features

- Book records with ISBN, category, publisher, shelf, and rating fields
- User management for students, teachers, and admins
- Borrow, return, renew, overdue tracking, and fine calculation
- Search by title, author, and category
- CSV import/export helpers
- Automatic local data persistence
- Switchable Chinese and English interface text

## Build

### macOS / Linux

```bash
g++ -std=c++17 -O2 main.cpp -o library-system
./library-system
```

### Windows

```bash
g++ -std=c++17 -O2 main.cpp -o library-system.exe
library-system.exe
```

## Runtime Files

The application creates local data files in the project root:

- `library_books.txt`
- `library_users.txt`
- `library_records.txt`
- exported `*.csv` files

These generated files are intentionally ignored by Git.

## Repository Layout

```text
library/
├── main.cpp
├── README.md
├── LICENSE
└── .gitignore
```

## Notes

- Sample data is initialized automatically when the local database is empty.
- The repo is intentionally compact and centered around one readable source file.

## License

MIT
