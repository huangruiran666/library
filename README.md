# Professional Library Management System

A bilingual Chinese/English command-line library management system written in C++.

## Features

- Book catalog management with ISBN, category, publisher, shelf, and rating fields
- User management for students, teachers, and admins
- Borrow, return, renew, overdue tracking, and fine calculation
- Search by title, author, and category, plus advanced search flows
- CSV import/export and persistent local storage
- Switchable Chinese and English interface text

## Project Layout

- `main.cpp`: main application entry point and core system logic
- `library_books.txt`: generated local book data
- `library_users.txt`: generated local user data
- `library_records.txt`: generated borrow history data

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

## Notes

- Sample data is initialized automatically when the local database is empty.
- Runtime data files are created in the project root during save/export operations.
- CSV export/import is intended for local data exchange and backup workflows.

## License

MIT
