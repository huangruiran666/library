#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include <map>
#include <set>
#include <cmath>

using namespace std;

// Language support
enum Language {
    CHINESE,
    ENGLISH
};

Language currentLanguage = CHINESE;  // Default language

// Multi-language text mappings
class LanguageText {
public:
    static string getText(const string& key) {
        static map<string, pair<string, string>> texts = {
            // System messages
            {"welcome", {"欢迎使用专业图书管理系统 v2.0", "Welcome to Professional Library Management System v2.0"}},
            {"goodbye", {"感谢使用专业图书管理系统，再见！", "Thank you for using the system. Goodbye!"}},
            {"loading_data", {"正在加载数据...", "Loading data..."}},
            {"saving_data", {"正在保存数据...", "Saving data..."}},
            {"init_sample", {"初始化示例数据...", "Initializing sample data..."}},
            {"sample_complete", {"示例数据初始化完成！", "Sample data initialization complete!"}},

            // Menu items
            {"menu_title", {"专业图书管理系统 v2.0", "Professional Library Management System v2.0"}},
            {"menu_book_mgmt", {"图书管理", "Book Management"}},
            {"menu_add_book", {"添加图书", "Add Book"}},
            {"menu_del_book", {"删除图书", "Delete Book"}},
            {"menu_update_book", {"修改图书信息", "Update Book Info"}},
            {"menu_view_all", {"查看所有图书", "View All Books"}},
            {"menu_available", {"可借阅图书", "Available Books"}},
            {"menu_rate", {"图书评分", "Rate Book"}},

            {"menu_user_mgmt", {"用户管理", "User Management"}},
            {"menu_add_user", {"添加用户", "Add User"}},
            {"menu_view_user", {"查看用户信息", "View User Info"}},
            {"menu_all_users", {"所有用户列表", "All Users List"}},

            {"menu_borrow_mgmt", {"借阅管理", "Borrowing Management"}},
            {"menu_borrow", {"借阅图书", "Borrow Book"}},
            {"menu_return", {"归还图书", "Return Book"}},
            {"menu_renew", {"续借图书", "Renew Book"}},
            {"menu_current", {"当前借阅", "Current Borrowing"}},
            {"menu_overdue", {"逾期图书", "Overdue Books"}},
            {"menu_history", {"借阅历史", "Borrowing History"}},

            {"menu_search", {"搜索功能", "Search Functions"}},
            {"menu_search_title", {"按标题搜索", "Search by Title"}},
            {"menu_search_author", {"按作者搜索", "Search by Author"}},
            {"menu_search_category", {"按分类搜索", "Search by Category"}},
            {"menu_advanced_search", {"高级搜索", "Advanced Search"}},

            {"menu_statistics", {"统计报表", "Statistics & Reports"}},
            {"menu_system_stats", {"系统统计", "System Statistics"}},
            {"menu_popular", {"热门图书", "Popular Books"}},
            {"menu_category_stats", {"分类统计", "Category Statistics"}},

            {"menu_data_mgmt", {"数据管理", "Data Management"}},
            {"menu_save", {"保存数据", "Save Data"}},
            {"menu_export", {"导出CSV", "Export CSV"}},
            {"menu_import", {"导入CSV", "Import CSV"}},
            {"menu_exit", {"退出系统", "Exit System"}},

            {"menu_prompt", {"请选择操作", "Please select an option"}},
            {"press_enter", {"按回车键继续...", "Press Enter to continue..."}},
            {"invalid_input", {"无效输入，请输入数字！", "Invalid input, please enter a number!"}},
            {"invalid_choice", {"无效选择，请重试。", "Invalid choice, please try again."}},

            // Common prompts
            {"isbn", {"ISBN", "ISBN"}},
            {"title", {"标题", "Title"}},
            {"author", {"作者", "Author"}},
            {"category", {"分类", "Category"}},
            {"publisher", {"出版社", "Publisher"}},
            {"year", {"出版年份", "Publication Year"}},
            {"copies", {"副本数量", "Number of Copies"}},
            {"shelf", {"书架位置", "Shelf Location"}},
            {"description", {"简介", "Description"}},
            {"description_optional", {"简介（可选）", "Description (optional)"}},
            {"rating", {"评分", "Rating"}},

            {"user_id", {"用户ID", "User ID"}},
            {"name", {"姓名", "Name"}},
            {"email", {"邮箱", "Email"}},
            {"phone", {"电话", "Phone"}},
            {"user_type", {"用户类型", "User Type"}},
            {"user_type_prompt", {"用户类型 (student/teacher/admin)", "User Type (student/teacher/admin)"}},

            // Success messages
            {"success", {"成功", "Success"}},
            {"book_added", {"成功添加图书", "Book added successfully"}},
            {"book_deleted", {"已删除图书", "Book deleted"}},
            {"book_updated", {"图书信息已更新！", "Book information updated!"}},
            {"user_added", {"成功添加用户", "User added successfully"}},
            {"borrow_success", {"借阅成功！", "Borrowed successfully!"}},
            {"return_success", {"归还成功！", "Returned successfully!"}},
            {"renew_success", {"续借成功！", "Renewed successfully!"}},
            {"rating_success", {"评分成功！", "Rating submitted successfully!"}},
            {"data_saved", {"数据已保存", "Data saved"}},
            {"export_success", {"成功导出", "Exported successfully"}},
            {"import_success", {"成功导入", "Imported successfully"}},

            // Error messages
            {"error", {"错误", "Error"}},
            {"not_found", {"未找到", "Not found"}},
            {"isbn_exists", {"ISBN 已存在！", "ISBN already exists!"}},
            {"user_id_exists", {"用户ID 已存在！", "User ID already exists!"}},
            {"book_borrowed", {"已被借出，无法删除。", "is borrowed and cannot be deleted."}},
            {"account_disabled", {"用户账户已停用！", "User account is disabled!"}},
            {"limit_reached", {"已达到借阅上限", "Borrowing limit reached"}},
            {"no_copies", {"所有副本已被借出。", "All copies are borrowed."}},
            {"not_borrowed", {"当前未被借出。", "is not currently borrowed."}},
            {"no_record", {"未找到该借阅记录。", "Borrowing record not found."}},
            {"cannot_renew", {"图书已逾期，无法续借！请先归还。", "Book is overdue and cannot be renewed! Please return first."}},
            {"invalid_rating", {"评分必须在0-5之间！", "Rating must be between 0-5!"}},
            {"file_error", {"无法打开文件！", "Cannot open file!"}},
            {"empty_library", {"图书馆为空！", "Library is empty!"}},

            // Display labels
            {"total", {"共", "Total"}},
            {"books", {"本图书", "book(s)"}},
            {"users", {"位用户", "user(s)"}},
            {"records", {"条记录", "record(s)"}},
            {"available", {"可借阅", "Available"}},
            {"borrowed", {"已借出", "Borrowed"}},
            {"status", {"状态", "Status"}},
            {"active", {"正常", "Active"}},
            {"inactive", {"已停用", "Inactive"}},
            {"overdue", {"逾期", "Overdue"}},
            {"days", {"天", "day(s)"}},
            {"fine", {"罚款", "Fine"}},
            {"no_data", {"暂无数据", "No data"}},

            // File operations
            {"books_loaded", {"已加载", "Loaded"}},
            {"users_loaded", {"已加载", "Loaded"}},
            {"records_loaded", {"已加载", "Loaded"}},
            {"books_saved", {"图书数据已保存", "Book data saved"}},
            {"users_saved", {"用户数据已保存", "User data saved"}},
            {"records_saved", {"借阅记录已保存", "Borrow records saved"}},

            // Statistics
            {"book_types", {"图书种类", "Book Types"}},
            {"total_copies", {"图书总数", "Total Copies"}},
            {"available_copies", {"可借阅数", "Available"}},
            {"borrowed_copies", {"已借出数", "Borrowed"}},
            {"registered_users", {"注册用户", "Registered Users"}},
            {"total_records", {"借阅记录", "Total Records"}},
            {"current_borrowing", {"当前在借", "Currently Borrowed"}},
            {"overdue_books", {"逾期图书", "Overdue Books"}},
            {"total_fines", {"累计罚款", "Total Fines"}},
        };

        if (texts.find(key) != texts.end()) {
            return currentLanguage == CHINESE ? texts[key].first : texts[key].second;
        }
        return key;
    }
};

// Forward declarations
struct User;
struct BorrowRecord;

// Book structure with comprehensive information
struct Book {
    string isbn;           // Unique identifier
    string title;          // Book title
    string author;         // Author name
    string category;       // Category (e.g., Programming, Fiction, Science)
    int publicationYear;   // Year of publication
    string publisher;      // Publisher name
    int totalCopies;       // Total number of copies
    int availableCopies;   // Available copies
    string shelf;          // Physical location
    float rating;          // Average rating (0-5)
    int ratingCount;       // Number of ratings
    string description;    // Book description
    vector<string> tags;   // Tags for categorization
    time_t addedDate;      // Date added to system
    Book* next;            // Pointer to next node

    Book() : publicationYear(0), totalCopies(1), availableCopies(1),
             rating(0.0f), ratingCount(0), addedDate(time(nullptr)), next(nullptr) {}
};

// Borrow Record structure
struct BorrowRecord {
    string isbn;
    string userId;
    string bookTitle;
    string userName;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;  // 0 if not returned
    bool isReturned;
    float fine;
    BorrowRecord* next;

    BorrowRecord() : borrowDate(time(nullptr)), dueDate(0), returnDate(0),
                     isReturned(false), fine(0.0f), next(nullptr) {}
};

// User structure
struct User {
    string userId;
    string name;
    string email;
    string phone;
    string userType;    // "student", "teacher", "admin"
    int borrowLimit;    // Max books can borrow
    int currentBorrowed;
    bool isActive;
    time_t registeredDate;
    User* next;

    User() : borrowLimit(5), currentBorrowed(0), isActive(true),
             registeredDate(time(nullptr)), next(nullptr) {}
};


// Library Management System with Advanced Features
class LibrarySystem {
private:
    Book* bookHead;
    User* userHead;
    BorrowRecord* recordHead;
    int totalBooks;
    int totalUsers;
    int totalRecords;
    const string DATA_FILE = "library_books.txt";
    const string USER_FILE = "library_users.txt";
    const string RECORD_FILE = "library_records.txt";
    const int BORROW_DAYS = 30;  // Default borrow period
    const float FINE_PER_DAY = 0.5f;  // Fine per overdue day

    // Helper function to convert string to lowercase
    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    // Get current timestamp string
    string getTimeString(time_t t) {
        if (t == 0) return "N/A";
        char buffer[80];
        struct tm* timeinfo = localtime(&t);
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }

    // Calculate days difference
    int getDaysDifference(time_t from, time_t to) {
        return (int)difftime(to, from) / (24 * 3600);
    }

    // Split string by delimiter
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    LibrarySystem() : bookHead(nullptr), userHead(nullptr), recordHead(nullptr),
                      totalBooks(0), totalUsers(0), totalRecords(0) {
        loadData();
    }

    ~LibrarySystem() {
        saveData();

        // Clean up books
        Book* currentBook = bookHead;
        while (currentBook != nullptr) {
            Book* nextBook = currentBook->next;
            delete currentBook;
            currentBook = nextBook;
        }

        // Clean up users
        User* currentUser = userHead;
        while (currentUser != nullptr) {
            User* nextUser = currentUser->next;
            delete currentUser;
            currentUser = nextUser;
        }

        // Clean up records
        BorrowRecord* currentRecord = recordHead;
        while (currentRecord != nullptr) {
            BorrowRecord* nextRecord = currentRecord->next;
            delete currentRecord;
            currentRecord = nextRecord;
        }
    }

    // ==================== DATA PERSISTENCE ====================

    void saveData() {
        // Save books
        ofstream bookFile(DATA_FILE);
        if (bookFile.is_open()) {
            Book* current = bookHead;
            while (current != nullptr) {
                bookFile << current->isbn << "|"
                        << current->title << "|"
                        << current->author << "|"
                        << current->category << "|"
                        << current->publicationYear << "|"
                        << current->publisher << "|"
                        << current->totalCopies << "|"
                        << current->availableCopies << "|"
                        << current->shelf << "|"
                        << current->rating << "|"
                        << current->ratingCount << "|"
                        << current->description << "|"
                        << current->addedDate << endl;
                current = current->next;
            }
            bookFile.close();
            cout << "✓ 图书数据已保存 (" << totalBooks << " 本)" << endl;
        }

        // Save users
        ofstream userFile(USER_FILE);
        if (userFile.is_open()) {
            User* current = userHead;
            while (current != nullptr) {
                userFile << current->userId << "|"
                        << current->name << "|"
                        << current->email << "|"
                        << current->phone << "|"
                        << current->userType << "|"
                        << current->borrowLimit << "|"
                        << current->currentBorrowed << "|"
                        << current->isActive << "|"
                        << current->registeredDate << endl;
                current = current->next;
            }
            userFile.close();
            cout << "✓ 用户数据已保存 (" << totalUsers << " 位)" << endl;
        }

        // Save borrow records
        ofstream recordFile(RECORD_FILE);
        if (recordFile.is_open()) {
            BorrowRecord* current = recordHead;
            while (current != nullptr) {
                recordFile << current->isbn << "|"
                          << current->userId << "|"
                          << current->bookTitle << "|"
                          << current->userName << "|"
                          << current->borrowDate << "|"
                          << current->dueDate << "|"
                          << current->returnDate << "|"
                          << current->isReturned << "|"
                          << current->fine << endl;
                current = current->next;
            }
            recordFile.close();
            cout << "✓ 借阅记录已保存 (" << totalRecords << " 条)" << endl;
        }
    }

    void loadData() {
        // Load books
        ifstream bookFile(DATA_FILE);
        if (bookFile.is_open()) {
            string line;
            while (getline(bookFile, line)) {
                vector<string> parts = split(line, '|');
                if (parts.size() >= 13) {
                    Book* book = new Book();
                    book->isbn = parts[0];
                    book->title = parts[1];
                    book->author = parts[2];
                    book->category = parts[3];
                    book->publicationYear = stoi(parts[4]);
                    book->publisher = parts[5];
                    book->totalCopies = stoi(parts[6]);
                    book->availableCopies = stoi(parts[7]);
                    book->shelf = parts[8];
                    book->rating = stof(parts[9]);
                    book->ratingCount = stoi(parts[10]);
                    book->description = parts[11];
                    book->addedDate = stoll(parts[12]);
                    book->next = bookHead;
                    bookHead = book;
                    totalBooks++;
                }
            }
            bookFile.close();
            cout << "✓ 已加载 " << totalBooks << " 本图书" << endl;
        }

        // Load users
        ifstream userFile(USER_FILE);
        if (userFile.is_open()) {
            string line;
            while (getline(userFile, line)) {
                vector<string> parts = split(line, '|');
                if (parts.size() >= 9) {
                    User* user = new User();
                    user->userId = parts[0];
                    user->name = parts[1];
                    user->email = parts[2];
                    user->phone = parts[3];
                    user->userType = parts[4];
                    user->borrowLimit = stoi(parts[5]);
                    user->currentBorrowed = stoi(parts[6]);
                    user->isActive = (parts[7] == "1");
                    user->registeredDate = stoll(parts[8]);
                    user->next = userHead;
                    userHead = user;
                    totalUsers++;
                }
            }
            userFile.close();
            cout << "✓ 已加载 " << totalUsers << " 位用户" << endl;
        }

        // Load records
        ifstream recordFile(RECORD_FILE);
        if (recordFile.is_open()) {
            string line;
            while (getline(recordFile, line)) {
                vector<string> parts = split(line, '|');
                if (parts.size() >= 9) {
                    BorrowRecord* record = new BorrowRecord();
                    record->isbn = parts[0];
                    record->userId = parts[1];
                    record->bookTitle = parts[2];
                    record->userName = parts[3];
                    record->borrowDate = stoll(parts[4]);
                    record->dueDate = stoll(parts[5]);
                    record->returnDate = stoll(parts[6]);
                    record->isReturned = (parts[7] == "1");
                    record->fine = stof(parts[8]);
                    record->next = recordHead;
                    recordHead = record;
                    totalRecords++;
                }
            }
            recordFile.close();
            cout << "✓ 已加载 " << totalRecords << " 条借阅记录" << endl;
        }
    }

    // ==================== BOOK MANAGEMENT ====================

    void addBook(const string& isbn, const string& title, const string& author,
                 const string& category, int year, const string& publisher,
                 int copies, const string& shelf, const string& description = "") {
        if (findBookByISBN(isbn) != nullptr) {
            cout << "❌ " << LanguageText::getText("error") << ": " << LanguageText::getText("isbn_exists") << endl;
            return;
        }

        Book* newBook = new Book();
        newBook->isbn = isbn;
        newBook->title = title;
        newBook->author = author;
        newBook->category = category;
        newBook->publicationYear = year;
        newBook->publisher = publisher;
        newBook->totalCopies = copies;
        newBook->availableCopies = copies;
        newBook->shelf = shelf;
        newBook->description = description;
        newBook->next = bookHead;
        bookHead = newBook;
        totalBooks++;

        string msg = LanguageText::getText("book_added") + ": 《" + title + "》";
        if (currentLanguage == ENGLISH) msg = LanguageText::getText("book_added") + ": \"" + title + "\"";
        cout << "✓ " << msg << " (" << LanguageText::getText("total") << " " << copies << " "
             << LanguageText::getText("books") << ")" << endl;
    }

    Book* findBookByISBN(const string& isbn) {
        Book* current = bookHead;
        while (current != nullptr) {
            if (current->isbn == isbn) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void updateBook(const string& isbn) {
        Book* book = findBookByISBN(isbn);
        if (book == nullptr) {
            cout << "❌ 未找到该图书！" << endl;
            return;
        }

        cout << "\n当前信息：" << endl;
        displayBookDetails(book);

        cout << "\n请输入新信息（直接回车保持不变）：" << endl;

        string input;
        cout << "标题 [" << book->title << "]: ";
        getline(cin, input);
        if (!input.empty()) book->title = input;

        cout << "作者 [" << book->author << "]: ";
        getline(cin, input);
        if (!input.empty()) book->author = input;

        cout << "分类 [" << book->category << "]: ";
        getline(cin, input);
        if (!input.empty()) book->category = input;

        cout << "出版社 [" << book->publisher << "]: ";
        getline(cin, input);
        if (!input.empty()) book->publisher = input;

        cout << "书架位置 [" << book->shelf << "]: ";
        getline(cin, input);
        if (!input.empty()) book->shelf = input;

        cout << "简介 [" << book->description << "]: ";
        getline(cin, input);
        if (!input.empty()) book->description = input;

        cout << "✓ 图书信息已更新！" << endl;
    }

    void removeBook(const string& isbn) {
        if (bookHead == nullptr) {
            cout << "❌ 图书馆为空！" << endl;
            return;
        }

        if (bookHead->isbn == isbn) {
            if (bookHead->availableCopies < bookHead->totalCopies) {
                cout << "❌ 错误：《" << bookHead->title << "》 有副本已被借出，无法删除。" << endl;
                return;
            }
            Book* temp = bookHead;
            string title = bookHead->title;
            bookHead = bookHead->next;
            delete temp;
            totalBooks--;
            cout << "✓ 已删除图书：《" << title << "》" << endl;
            return;
        }

        Book* current = bookHead;
        while (current->next != nullptr) {
            if (current->next->isbn == isbn) {
                if (current->next->availableCopies < current->next->totalCopies) {
                    cout << "❌ 错误：《" << current->next->title << "》 有副本已被借出，无法删除。" << endl;
                    return;
                }
                Book* temp = current->next;
                string title = temp->title;
                current->next = current->next->next;
                delete temp;
                totalBooks--;
                cout << "✓ 已删除图书：《" << title << "》" << endl;
                return;
            }
            current = current->next;
        }
        cout << "❌ 错误：未找到ISBN为 " << isbn << " 的图书。" << endl;
    }

    void rateBook(const string& isbn, float rating) {
        if (rating < 0 || rating > 5) {
            cout << "❌ 评分必须在0-5之间！" << endl;
            return;
        }

        Book* book = findBookByISBN(isbn);
        if (book == nullptr) {
            cout << "❌ 未找到该图书！" << endl;
            return;
        }

        float totalRating = book->rating * book->ratingCount + rating;
        book->ratingCount++;
        book->rating = totalRating / book->ratingCount;

        cout << "✓ 评分成功！《" << book->title << "》 当前评分："
             << fixed << setprecision(1) << book->rating
             << " (" << book->ratingCount << "人评价)" << endl;
    }

    // ==================== USER MANAGEMENT ====================

    void addUser(const string& userId, const string& name, const string& email,
                 const string& phone, const string& userType) {
        if (findUserById(userId) != nullptr) {
            cout << "❌ 错误：用户ID " << userId << " 已存在！" << endl;
            return;
        }

        User* newUser = new User();
        newUser->userId = userId;
        newUser->name = name;
        newUser->email = email;
        newUser->phone = phone;
        newUser->userType = userType;

        // Set borrow limit based on user type
        if (userType == "teacher" || userType == "admin") {
            newUser->borrowLimit = 10;
        } else {
            newUser->borrowLimit = 5;
        }

        newUser->next = userHead;
        userHead = newUser;
        totalUsers++;

        cout << "✓ 成功添加用户：" << name << " (ID: " << userId << ")" << endl;
    }

    User* findUserById(const string& userId) {
        User* current = userHead;
        while (current != nullptr) {
            if (current->userId == userId) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayUserInfo(const string& userId) {
        User* user = findUserById(userId);
        if (user == nullptr) {
            cout << "❌ 未找到该用户！" << endl;
            return;
        }

        cout << "\n👤 用户信息：" << endl;
        cout << string(60, '=') << endl;
        cout << "用户ID：" << user->userId << endl;
        cout << "姓名：" << user->name << endl;
        cout << "邮箱：" << user->email << endl;
        cout << "电话：" << user->phone << endl;
        cout << "类型：" << user->userType << endl;
        cout << "借阅限额：" << user->borrowLimit << " 本" << endl;
        cout << "当前已借：" << user->currentBorrowed << " 本" << endl;
        cout << "账户状态：" << (user->isActive ? "✓ 正常" : "❌ 已停用") << endl;
        cout << "注册日期：" << getTimeString(user->registeredDate) << endl;
        cout << string(60, '=') << endl;

        // Show user's borrow history
        displayUserBorrowHistory(userId);
    }

    void displayAllUsers() {
        if (userHead == nullptr) {
            cout << "\n暂无注册用户。" << endl;
            return;
        }

        cout << "\n👥 所有用户列表：" << endl;
        cout << string(120, '=') << endl;
        cout << left << setw(15) << "用户ID"
             << setw(20) << "姓名"
             << setw(30) << "邮箱"
             << setw(15) << "电话"
             << setw(12) << "类型"
             << setw(10) << "已借/限额"
             << "状态" << endl;
        cout << string(120, '-') << endl;

        User* current = userHead;
        while (current != nullptr) {
            cout << left << setw(15) << current->userId
                 << setw(20) << current->name
                 << setw(30) << current->email
                 << setw(15) << current->phone
                 << setw(12) << current->userType
                 << setw(10) << (to_string(current->currentBorrowed) + "/" + to_string(current->borrowLimit))
                 << (current->isActive ? "正常" : "停用") << endl;
            current = current->next;
        }
        cout << string(120, '=') << endl;
        cout << "共 " << totalUsers << " 位用户" << endl;
    }

    // ==================== BORROW & RETURN ====================

    void borrowBook(const string& isbn, const string& userId) {
        Book* book = findBookByISBN(isbn);
        if (book == nullptr) {
            cout << "❌ 错误：未找到ISBN为 " << isbn << " 的图书。" << endl;
            return;
        }

        User* user = findUserById(userId);
        if (user == nullptr) {
            cout << "❌ 错误：未找到用户ID " << userId << endl;
            return;
        }

        if (!user->isActive) {
            cout << "❌ 错误：用户账户已停用！" << endl;
            return;
        }

        if (user->currentBorrowed >= user->borrowLimit) {
            cout << "❌ 错误：已达到借阅上限（" << user->borrowLimit << "本）！" << endl;
            return;
        }

        if (book->availableCopies <= 0) {
            cout << "❌ 错误：《" << book->title << "》 所有副本已被借出。" << endl;
            return;
        }

        // Create borrow record
        BorrowRecord* record = new BorrowRecord();
        record->isbn = isbn;
        record->userId = userId;
        record->bookTitle = book->title;
        record->userName = user->name;
        record->borrowDate = time(nullptr);
        record->dueDate = record->borrowDate + (BORROW_DAYS * 24 * 3600);
        record->next = recordHead;
        recordHead = record;
        totalRecords++;

        book->availableCopies--;
        user->currentBorrowed++;

        cout << "✓ 借阅成功！" << endl;
        cout << "图书：《" << book->title << "》" << endl;
        cout << "借阅人：" << user->name << endl;
        cout << "借阅日期：" << getTimeString(record->borrowDate) << endl;
        cout << "应还日期：" << getTimeString(record->dueDate) << endl;
    }

    void returnBook(const string& isbn, const string& userId) {
        Book* book = findBookByISBN(isbn);
        if (book == nullptr) {
            cout << "❌ 错误：未找到ISBN为 " << isbn << " 的图书。" << endl;
            return;
        }

        User* user = findUserById(userId);
        if (user == nullptr) {
            cout << "❌ 错误：未找到用户ID " << userId << endl;
            return;
        }

        // Find active borrow record
        BorrowRecord* current = recordHead;
        while (current != nullptr) {
            if (current->isbn == isbn && current->userId == userId && !current->isReturned) {
                current->isReturned = true;
                current->returnDate = time(nullptr);

                // Calculate fine if overdue
                if (current->returnDate > current->dueDate) {
                    int overdueDays = getDaysDifference(current->dueDate, current->returnDate);
                    current->fine = overdueDays * FINE_PER_DAY;
                }

                book->availableCopies++;
                user->currentBorrowed--;

                cout << "✓ 归还成功！" << endl;
                cout << "图书：《" << book->title << "》" << endl;
                cout << "归还人：" << user->name << endl;
                cout << "归还日期：" << getTimeString(current->returnDate) << endl;

                if (current->fine > 0) {
                    int overdueDays = getDaysDifference(current->dueDate, current->returnDate);
                    cout << "⚠️  逾期 " << overdueDays << " 天，罚款：￥"
                         << fixed << setprecision(2) << current->fine << endl;
                } else {
                    cout << "✓ 按时归还，无罚款" << endl;
                }
                return;
            }
            current = current->next;
        }

        cout << "❌ 错误：未找到该用户借阅此书的记录。" << endl;
    }

    void renewBook(const string& isbn, const string& userId) {
        BorrowRecord* current = recordHead;
        while (current != nullptr) {
            if (current->isbn == isbn && current->userId == userId && !current->isReturned) {
                time_t now = time(nullptr);
                if (now > current->dueDate) {
                    cout << "❌ 错误：图书已逾期，无法续借！请先归还。" << endl;
                    return;
                }

                current->dueDate += (BORROW_DAYS * 24 * 3600);
                cout << "✓ 续借成功！新的应还日期：" << getTimeString(current->dueDate) << endl;
                return;
            }
            current = current->next;
        }
        cout << "❌ 错误：未找到该借阅记录。" << endl;
    }

    // ==================== SEARCH FUNCTIONS ====================

    void searchByTitle(const string& title) {
        string searchTerm = toLower(title);
        Book* current = bookHead;
        vector<Book*> results;

        while (current != nullptr) {
            if (toLower(current->title).find(searchTerm) != string::npos) {
                results.push_back(current);
            }
            current = current->next;
        }

        cout << "\n🔍 搜索结果（标题包含 \"" << title << "\"）：" << endl;
        cout << string(100, '=') << endl;

        if (results.empty()) {
            cout << "未找到匹配的图书。" << endl;
        } else {
            for (Book* book : results) {
                displayBookDetails(book);
            }
            cout << "\n共找到 " << results.size() << " 本图书。" << endl;
        }
        cout << string(100, '=') << endl;
    }

    void searchByAuthor(const string& author) {
        string searchTerm = toLower(author);
        Book* current = bookHead;
        vector<Book*> results;

        while (current != nullptr) {
            if (toLower(current->author).find(searchTerm) != string::npos) {
                results.push_back(current);
            }
            current = current->next;
        }

        cout << "\n🔍 搜索结果（作者包含 \"" << author << "\"）：" << endl;
        cout << string(100, '=') << endl;

        if (results.empty()) {
            cout << "未找到该作者的图书。" << endl;
        } else {
            for (Book* book : results) {
                displayBookDetails(book);
            }
            cout << "\n共找到 " << results.size() << " 本图书。" << endl;
        }
        cout << string(100, '=') << endl;
    }

    void searchByCategory(const string& category) {
        string searchTerm = toLower(category);
        Book* current = bookHead;
        vector<Book*> results;

        while (current != nullptr) {
            if (toLower(current->category).find(searchTerm) != string::npos) {
                results.push_back(current);
            }
            current = current->next;
        }

        cout << "\n🔍 搜索结果（分类：" << category << "）：" << endl;
        cout << string(100, '=') << endl;

        if (results.empty()) {
            cout << "该分类下没有图书。" << endl;
        } else {
            for (Book* book : results) {
                displayBookDetails(book);
            }
            cout << "\n共找到 " << results.size() << " 本图书。" << endl;
        }
        cout << string(100, '=') << endl;
    }

    void advancedSearch() {
        cout << "\n🔍 高级搜索" << endl;
        cout << string(60, '=') << endl;

        string title, author, category, publisher;
        int yearFrom = 0, yearTo = 9999;
        float minRating = 0;

        cout << "标题关键词（回车跳过）: ";
        getline(cin, title);
        cout << "作者关键词（回车跳过）: ";
        getline(cin, author);
        cout << "分类关键词（回车跳过）: ";
        getline(cin, category);
        cout << "出版社关键词（回车跳过）: ";
        getline(cin, publisher);

        string input;
        cout << "最低评分（0-5，回车跳过）: ";
        getline(cin, input);
        if (!input.empty()) minRating = stof(input);

        cout << "出版年份范围（如: 2000 2020，回车跳过）: ";
        getline(cin, input);
        if (!input.empty()) {
            istringstream iss(input);
            iss >> yearFrom >> yearTo;
        }

        vector<Book*> results;
        Book* current = bookHead;

        while (current != nullptr) {
            bool match = true;

            if (!title.empty() && toLower(current->title).find(toLower(title)) == string::npos)
                match = false;
            if (!author.empty() && toLower(current->author).find(toLower(author)) == string::npos)
                match = false;
            if (!category.empty() && toLower(current->category).find(toLower(category)) == string::npos)
                match = false;
            if (!publisher.empty() && toLower(current->publisher).find(toLower(publisher)) == string::npos)
                match = false;
            if (current->rating < minRating)
                match = false;
            if (current->publicationYear < yearFrom || current->publicationYear > yearTo)
                match = false;

            if (match) results.push_back(current);
            current = current->next;
        }

        cout << "\n搜索结果：" << endl;
        cout << string(100, '=') << endl;

        if (results.empty()) {
            cout << "未找到符合条件的图书。" << endl;
        } else {
            for (Book* book : results) {
                displayBookDetails(book);
            }
            cout << "\n共找到 " << results.size() << " 本图书。" << endl;
        }
        cout << string(100, '=') << endl;
    }

    // ==================== DISPLAY FUNCTIONS ====================

    void displayBookDetails(Book* book) {
        cout << "📖 ISBN: " << book->isbn << endl;
        cout << "   标题: " << book->title << endl;
        cout << "   作者: " << book->author << endl;
        cout << "   分类: " << book->category << endl;
        cout << "   出版社: " << book->publisher << endl;
        cout << "   出版年份: " << book->publicationYear << endl;
        cout << "   书架位置: " << book->shelf << endl;
        cout << "   藏书量: " << book->totalCopies << " 本 (可借: " << book->availableCopies << " 本)" << endl;
        if (book->ratingCount > 0) {
            cout << "   评分: " << fixed << setprecision(1) << book->rating
                 << " ⭐ (" << book->ratingCount << "人评价)" << endl;
        } else {
            cout << "   评分: 暂无评分" << endl;
        }
        if (!book->description.empty()) {
            cout << "   简介: " << book->description << endl;
        }
        cout << "   入库时间: " << getTimeString(book->addedDate) << endl;
        cout << endl;
    }

    void displayAllBooks() {
        if (bookHead == nullptr) {
            cout << "\n📚 图书馆当前没有图书。\n" << endl;
            return;
        }

        cout << "\n📚 图书馆所有图书（共 " << totalBooks << " 本）：" << endl;
        cout << string(100, '=') << endl;

        Book* current = bookHead;
        while (current != nullptr) {
            displayBookDetails(current);
            current = current->next;
        }
        cout << string(100, '=') << endl;
    }

    void displayAvailableBooks() {
        Book* current = bookHead;
        int count = 0;

        cout << "\n📗 可借阅图书：" << endl;
        cout << string(100, '=') << endl;

        while (current != nullptr) {
            if (current->availableCopies > 0) {
                displayBookDetails(current);
                count++;
            }
            current = current->next;
        }

        if (count == 0) {
            cout << "当前没有可借阅的图书。" << endl;
        } else {
            cout << "\n共 " << count << " 本可借阅图书。" << endl;
        }
        cout << string(100, '=') << endl;
    }

    void displayBorrowedBooks() {
        BorrowRecord* current = recordHead;
        int count = 0;

        cout << "\n📕 当前借阅中的图书：" << endl;
        cout << string(120, '=') << endl;
        cout << left << setw(20) << "图书标题"
             << setw(15) << "借阅人"
             << setw(12) << "用户ID"
             << setw(22) << "借阅日期"
             << setw(22) << "应还日期"
             << "状态" << endl;
        cout << string(120, '-') << endl;

        time_t now = time(nullptr);
        while (current != nullptr) {
            if (!current->isReturned) {
                cout << left << setw(20) << current->bookTitle.substr(0, 18)
                     << setw(15) << current->userName.substr(0, 13)
                     << setw(12) << current->userId
                     << setw(22) << getTimeString(current->borrowDate).substr(0, 20)
                     << setw(22) << getTimeString(current->dueDate).substr(0, 20);

                if (now > current->dueDate) {
                    int overdueDays = getDaysDifference(current->dueDate, now);
                    cout << "⚠️ 逾期" << overdueDays << "天";
                } else {
                    int remainingDays = getDaysDifference(now, current->dueDate);
                    cout << "✓ 还有" << remainingDays << "天";
                }
                cout << endl;
                count++;
            }
            current = current->next;
        }

        if (count == 0) {
            cout << "当前没有借出的图书。" << endl;
        } else {
            cout << string(120, '=') << endl;
            cout << "共 " << count << " 本图书在借。" << endl;
        }
    }

    void displayUserBorrowHistory(const string& userId) {
        BorrowRecord* current = recordHead;
        vector<BorrowRecord*> userRecords;

        while (current != nullptr) {
            if (current->userId == userId) {
                userRecords.push_back(current);
            }
            current = current->next;
        }

        if (userRecords.empty()) {
            cout << "\n暂无借阅记录。" << endl;
            return;
        }

        cout << "\n📚 借阅历史：" << endl;
        cout << string(120, '=') << endl;
        cout << left << setw(22) << "图书标题"
             << setw(22) << "借阅日期"
             << setw(22) << "应还日期"
             << setw(22) << "实际归还日期"
             << setw(10) << "罚款"
             << "状态" << endl;
        cout << string(120, '-') << endl;

        for (BorrowRecord* rec : userRecords) {
            cout << left << setw(22) << rec->bookTitle.substr(0, 20)
                 << setw(22) << getTimeString(rec->borrowDate).substr(0, 20)
                 << setw(22) << getTimeString(rec->dueDate).substr(0, 20)
                 << setw(22) << getTimeString(rec->returnDate).substr(0, 20);

            if (rec->fine > 0) {
                cout << setw(10) << ("￥" + to_string((int)rec->fine));
            } else {
                cout << setw(10) << "-";
            }

            cout << (rec->isReturned ? "已归还" : "借阅中") << endl;
        }
        cout << string(120, '=') << endl;
        cout << "共 " << userRecords.size() << " 条记录" << endl;
    }

    void displayOverdueBooks() {
        BorrowRecord* current = recordHead;
        vector<BorrowRecord*> overdueRecords;
        time_t now = time(nullptr);

        while (current != nullptr) {
            if (!current->isReturned && now > current->dueDate) {
                overdueRecords.push_back(current);
            }
            current = current->next;
        }

        cout << "\n⚠️  逾期图书列表：" << endl;
        cout << string(120, '=') << endl;

        if (overdueRecords.empty()) {
            cout << "✓ 当前没有逾期图书。" << endl;
        } else {
            cout << left << setw(22) << "图书标题"
                 << setw(15) << "借阅人"
                 << setw(12) << "用户ID"
                 << setw(22) << "应还日期"
                 << setw(12) << "逾期天数"
                 << "预计罚款" << endl;
            cout << string(120, '-') << endl;

            for (BorrowRecord* rec : overdueRecords) {
                int overdueDays = getDaysDifference(rec->dueDate, now);
                float estimatedFine = overdueDays * FINE_PER_DAY;

                cout << left << setw(22) << rec->bookTitle.substr(0, 20)
                     << setw(15) << rec->userName.substr(0, 13)
                     << setw(12) << rec->userId
                     << setw(22) << getTimeString(rec->dueDate).substr(0, 20)
                     << setw(12) << (to_string(overdueDays) + "天")
                     << "￥" << fixed << setprecision(2) << estimatedFine << endl;
            }
            cout << string(120, '=') << endl;
            cout << "共 " << overdueRecords.size() << " 本逾期图书" << endl;
        }
    }

    // ==================== STATISTICS & REPORTS ====================

    void displayStatistics() {
        int borrowedCount = 0;
        int overdueCount = 0;
        float totalFines = 0;
        time_t now = time(nullptr);

        BorrowRecord* current = recordHead;
        while (current != nullptr) {
            if (!current->isReturned) {
                borrowedCount++;
                if (now > current->dueDate) {
                    overdueCount++;
                }
            }
            totalFines += current->fine;
            current = current->next;
        }

        int totalCopies = 0;
        int availableCopies = 0;
        Book* bookCurrent = bookHead;
        while (bookCurrent != nullptr) {
            totalCopies += bookCurrent->totalCopies;
            availableCopies += bookCurrent->availableCopies;
            bookCurrent = bookCurrent->next;
        }

        cout << "\n📊 图书馆统计信息：" << endl;
        cout << string(60, '=') << endl;
        cout << "📚 图书统计：" << endl;
        cout << "   图书种类：" << totalBooks << " 种" << endl;
        cout << "   图书总数：" << totalCopies << " 本" << endl;
        cout << "   可借阅数：" << availableCopies << " 本" << endl;
        cout << "   已借出数：" << (totalCopies - availableCopies) << " 本" << endl;
        cout << "\n👥 用户统计：" << endl;
        cout << "   注册用户：" << totalUsers << " 位" << endl;
        cout << "\n📋 借阅统计：" << endl;
        cout << "   借阅记录：" << totalRecords << " 条" << endl;
        cout << "   当前在借：" << borrowedCount << " 本" << endl;
        cout << "   逾期图书：" << overdueCount << " 本" << endl;
        cout << "   累计罚款：￥" << fixed << setprecision(2) << totalFines << endl;
        cout << string(60, '=') << endl;
    }

    void displayPopularBooks() {
        // Count borrow times for each book
        map<string, int> borrowCount;
        BorrowRecord* current = recordHead;

        while (current != nullptr) {
            borrowCount[current->isbn]++;
            current = current->next;
        }

        // Create vector of pairs for sorting
        vector<pair<string, int>> sortedBooks(borrowCount.begin(), borrowCount.end());
        sort(sortedBooks.begin(), sortedBooks.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second > b.second;
             });

        cout << "\n🔥 热门图书排行榜（按借阅次数）：" << endl;
        cout << string(100, '=') << endl;
        cout << left << setw(8) << "排名"
             << setw(35) << "书名"
             << setw(20) << "作者"
             << setw(12) << "借阅次数"
             << "评分" << endl;
        cout << string(100, '-') << endl;

        int rank = 1;
        for (const auto& pair : sortedBooks) {
            if (rank > 10) break;  // Top 10

            Book* book = findBookByISBN(pair.first);
            if (book != nullptr) {
                cout << left << setw(8) << rank
                     << setw(35) << book->title.substr(0, 33)
                     << setw(20) << book->author.substr(0, 18)
                     << setw(12) << pair.second;

                if (book->ratingCount > 0) {
                    cout << fixed << setprecision(1) << book->rating << " ⭐";
                } else {
                    cout << "暂无";
                }
                cout << endl;
                rank++;
            }
        }
        cout << string(100, '=') << endl;
    }

    void displayCategoryStatistics() {
        map<string, int> categoryCount;
        map<string, int> categoryBorrowed;

        Book* current = bookHead;
        while (current != nullptr) {
            categoryCount[current->category] += current->totalCopies;
            categoryBorrowed[current->category] += (current->totalCopies - current->availableCopies);
            current = current->next;
        }

        cout << "\n📊 分类统计：" << endl;
        cout << string(80, '=') << endl;
        cout << left << setw(20) << "分类"
             << setw(15) << "图书总数"
             << setw(15) << "已借出"
             << setw(15) << "可借阅"
             << "借出率" << endl;
        cout << string(80, '-') << endl;

        for (const auto& pair : categoryCount) {
            int total = pair.second;
            int borrowed = categoryBorrowed[pair.first];
            int available = total - borrowed;
            float borrowRate = (total > 0) ? (borrowed * 100.0f / total) : 0;

            cout << left << setw(20) << pair.first
                 << setw(15) << total
                 << setw(15) << borrowed
                 << setw(15) << available
                 << fixed << setprecision(1) << borrowRate << "%" << endl;
        }
        cout << string(80, '=') << endl;
    }

    // ==================== DATA IMPORT/EXPORT ====================

    void exportToCSV() {
        string filename;
        cout << "请输入导出文件名（如: books.csv）: ";
        getline(cin, filename);

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "❌ 无法创建文件！" << endl;
            return;
        }

        // CSV Header
        file << "ISBN,标题,作者,分类,出版年份,出版社,总数,可借,书架,评分,评价数" << endl;

        Book* current = bookHead;
        while (current != nullptr) {
            file << current->isbn << ","
                 << current->title << ","
                 << current->author << ","
                 << current->category << ","
                 << current->publicationYear << ","
                 << current->publisher << ","
                 << current->totalCopies << ","
                 << current->availableCopies << ","
                 << current->shelf << ","
                 << fixed << setprecision(2) << current->rating << ","
                 << current->ratingCount << endl;
            current = current->next;
        }

        file.close();
        cout << "✓ 成功导出 " << totalBooks << " 本图书到 " << filename << endl;
    }

    void importFromCSV() {
        string filename;
        cout << "请输入导入文件名（如: books.csv）: ";
        getline(cin, filename);

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "❌ 无法打开文件！" << endl;
            return;
        }

        string line;
        getline(file, line);  // Skip header

        int importCount = 0;
        while (getline(file, line)) {
            vector<string> parts = split(line, ',');
            if (parts.size() >= 9) {
                if (findBookByISBN(parts[0]) == nullptr) {
                    addBook(parts[0], parts[1], parts[2], parts[3],
                           stoi(parts[4]), parts[5], stoi(parts[6]), parts[8]);
                    importCount++;
                }
            }
        }

        file.close();
        cout << "✓ 成功导入 " << importCount << " 本图书" << endl;
    }
};


// Display main menu
void displayMenu() {
    string border = currentLanguage == CHINESE ? "═" : "=";
    string corner1 = "╔", corner2 = "╗", corner3 = "╚", corner4 = "╝";
    string line = "║", split = "╠╣";

    cout << "\n" << corner1 << string(60, border[0]) << corner2 << endl;
    cout << line << "           📚 " << LanguageText::getText("menu_title") << " 📚                      " << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  📖 " << LanguageText::getText("menu_book_mgmt") << string(currentLanguage == CHINESE ? 47 : 34, ' ') << line << endl;
    cout << line << "    1. " << LanguageText::getText("menu_add_book")
         << string(10, ' ') << "2. " << LanguageText::getText("menu_del_book")
         << string(6, ' ') << "3. " << LanguageText::getText("menu_update_book")
         << string(currentLanguage == CHINESE ? 2 : 0, ' ') << line << endl;
    cout << line << "    4. " << LanguageText::getText("menu_view_all")
         << string(6, ' ') << "5. " << LanguageText::getText("menu_available")
         << string(currentLanguage == CHINESE ? 4 : 1, ' ') << "6. " << LanguageText::getText("menu_rate")
         << string(currentLanguage == CHINESE ? 6 : 8, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  👥 " << LanguageText::getText("menu_user_mgmt") << string(currentLanguage == CHINESE ? 47 : 35, ' ') << line << endl;
    cout << line << "    7. " << LanguageText::getText("menu_add_user")
         << string(10, ' ') << "8. " << LanguageText::getText("menu_view_user")
         << string(currentLanguage == CHINESE ? 2 : 0, ' ') << "9. " << LanguageText::getText("menu_all_users")
         << string(currentLanguage == CHINESE ? 2 : 0, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  📋 " << LanguageText::getText("menu_borrow_mgmt") << string(currentLanguage == CHINESE ? 43 : 27, ' ') << line << endl;
    cout << line << "   10. " << LanguageText::getText("menu_borrow")
         << string(9, ' ') << "11. " << LanguageText::getText("menu_return")
         << string(currentLanguage == CHINESE ? 5 : 2, ' ') << "12. " << LanguageText::getText("menu_renew")
         << string(currentLanguage == CHINESE ? 5 : 3, ' ') << line << endl;
    cout << line << "   13. " << LanguageText::getText("menu_current")
         << string(9, ' ') << "14. " << LanguageText::getText("menu_overdue")
         << string(currentLanguage == CHINESE ? 5 : 2, ' ') << "15. " << LanguageText::getText("menu_history")
         << string(currentLanguage == CHINESE ? 5 : 0, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  🔍 " << LanguageText::getText("menu_search") << string(currentLanguage == CHINESE ? 47 : 32, ' ') << line << endl;
    cout << line << "   16. " << LanguageText::getText("menu_search_title")
         << string(currentLanguage == CHINESE ? 7 : 0, ' ') << "17. " << LanguageText::getText("menu_search_author")
         << string(currentLanguage == CHINESE ? 3 : 0, ' ') << "18. " << LanguageText::getText("menu_search_category")
         << string(currentLanguage == CHINESE ? 3 : 0, ' ') << line << endl;
    cout << line << "   19. " << LanguageText::getText("menu_advanced_search") << string(currentLanguage == CHINESE ? 51 : 33, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  📊 " << LanguageText::getText("menu_statistics") << string(currentLanguage == CHINESE ? 43 : 25, ' ') << line << endl;
    cout << line << "   20. " << LanguageText::getText("menu_system_stats")
         << string(currentLanguage == CHINESE ? 8 : 1, ' ') << "21. " << LanguageText::getText("menu_popular")
         << string(currentLanguage == CHINESE ? 5 : 2, ' ') << "22. " << LanguageText::getText("menu_category_stats")
         << string(currentLanguage == CHINESE ? 5 : 0, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "  💾 " << LanguageText::getText("menu_data_mgmt") << string(currentLanguage == CHINESE ? 47 : 35, ' ') << line << endl;
    cout << line << "   23. " << LanguageText::getText("menu_save")
         << string(currentLanguage == CHINESE ? 9 : 3, ' ') << "24. " << LanguageText::getText("menu_export")
         << string(currentLanguage == CHINESE ? 6 : 2, ' ') << "25. " << LanguageText::getText("menu_import")
         << string(currentLanguage == CHINESE ? 6 : 3, ' ') << line << endl;
    cout << split[0] << string(60, border[0]) << split[1] << endl;
    cout << line << "   0. " << LanguageText::getText("menu_exit") << string(currentLanguage == CHINESE ? 52 : 38, ' ') << line << endl;
    cout << corner3 << string(60, border[0]) << corner4 << endl;
    cout << LanguageText::getText("menu_prompt") << " (0-25): ";
}

int main() {
    // Language selection
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║    📚 Professional Library Management System v2.0    ║" << endl;
    cout << "║         专业图书管理系统 v2.0                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << "\nPlease select your language / 请选择语言:" << endl;
    cout << "1. 中文 (Chinese)" << endl;
    cout << "2. English" << endl;
    cout << "Choice / 选择 (1-2): ";

    int langChoice;
    if (!(cin >> langChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        langChoice = 1;  // Default to Chinese
    }
    cin.ignore();

    currentLanguage = (langChoice == 2) ? ENGLISH : CHINESE;

    LibrarySystem library;
    int choice;
    string isbn, title, author, category, shelf, publisher, description;
    string userId, userName, email, phone, userType;
    int year, copies;
    float rating;

    cout << "\n════════════════════════════════════════════════════════" << endl;
    cout << "🎉 " << LanguageText::getText("welcome") << endl;
    cout << "════════════════════════════════════════════════════════" << endl;

    // Add some sample books if database is empty
    if (library.findBookByISBN("978-0-13-110362-7") == nullptr) {
        cout << "\n" << LanguageText::getText("init_sample") << endl;

        if (currentLanguage == CHINESE) {
            library.addBook("978-0-13-110362-7", "C程序设计语言", "Kernighan & Ritchie",
                           "编程", 1988, "机械工业出版社", 3, "A1",
                           "C语言的权威指南，由语言设计者编写。");
            library.addBook("978-0-13-235088-4", "代码整洁之道", "Robert C. Martin",
                           "编程", 2008, "人民邮电出版社", 5, "A2",
                           "软件工程经典之作，讲述如何编写高质量代码。");
            library.addBook("978-0-20163-361-0", "设计模式", "Gamma等",
                           "编程", 1994, "机械工业出版社", 2, "A3",
                           "面向对象设计的经典著作，GoF四人帮力作。");
            library.addBook("978-7-11-545800-5", "三体", "刘慈欣",
                           "科幻小说", 2008, "重庆出版社", 10, "B1",
                           "中国科幻巨著，雨果奖获奖作品。");
            library.addBook("978-0-45-152493-5", "指环王", "J.R.R. Tolkien",
                           "奇幻小说", 1954, "译林出版社", 8, "B2",
                           "史诗级奇幻小说，现代奇幻文学的奠基之作。");
            library.addBook("978-0-13-468599-1", "深入理解计算机系统", "Randal E. Bryant",
                           "计算机科学", 2015, "机械工业出版社", 4, "A4",
                           "计算机系统经典教材，深入讲解计算机底层原理。");
            library.addBook("978-7-115-42848-3", "Python编程：从入门到实践", "Eric Matthes",
                           "编程", 2016, "人民邮电出版社", 6, "A5",
                           "Python入门经典教材，适合初学者。");
            library.addBook("978-0-596-52068-7", "算法导论", "Thomas H. Cormen",
                           "计算机科学", 2009, "机械工业出版社", 3, "A6",
                           "算法领域的权威著作，MIT经典教材。");
        } else {
            library.addBook("978-0-13-110362-7", "The C Programming Language", "Kernighan & Ritchie",
                           "Programming", 1988, "Prentice Hall", 3, "A1",
                           "The authoritative guide to C, written by the language designers.");
            library.addBook("978-0-13-235088-4", "Clean Code", "Robert C. Martin",
                           "Programming", 2008, "Prentice Hall", 5, "A2",
                           "A handbook of agile software craftsmanship.");
            library.addBook("978-0-20163-361-0", "Design Patterns", "Gamma et al.",
                           "Programming", 1994, "Addison-Wesley", 2, "A3",
                           "Elements of reusable object-oriented software.");
            library.addBook("978-7-11-545800-5", "The Three-Body Problem", "Liu Cixin",
                           "Science Fiction", 2008, "Tor Books", 10, "B1",
                           "Hugo Award-winning Chinese science fiction masterpiece.");
            library.addBook("978-0-45-152493-5", "The Lord of the Rings", "J.R.R. Tolkien",
                           "Fantasy", 1954, "Allen & Unwin", 8, "B2",
                           "Epic high-fantasy novel, foundation of modern fantasy literature.");
            library.addBook("978-0-13-468599-1", "Computer Systems: A Programmer's Perspective", "Randal E. Bryant",
                           "Computer Science", 2015, "Pearson", 4, "A4",
                           "Classic textbook on computer systems.");
            library.addBook("978-7-115-42848-3", "Python Crash Course", "Eric Matthes",
                           "Programming", 2016, "No Starch Press", 6, "A5",
                           "A hands-on, project-based introduction to programming.");
            library.addBook("978-0-596-52068-7", "Introduction to Algorithms", "Thomas H. Cormen",
                           "Computer Science", 2009, "MIT Press", 3, "A6",
                           "Comprehensive introduction to algorithms.");
        }

        // Add sample users
        if (currentLanguage == CHINESE) {
            library.addUser("U001", "张三", "zhangsan@example.com", "13800138000", "student");
            library.addUser("U002", "李四", "lisi@example.com", "13800138001", "teacher");
            library.addUser("U003", "王五", "wangwu@example.com", "13800138002", "student");
            library.addUser("ADMIN", "管理员", "admin@library.com", "13900000000", "admin");
        } else {
            library.addUser("U001", "John Smith", "john@example.com", "1-800-111-0001", "student");
            library.addUser("U002", "Mary Johnson", "mary@example.com", "1-800-111-0002", "teacher");
            library.addUser("U003", "Bob Williams", "bob@example.com", "1-800-111-0003", "student");
            library.addUser("ADMIN", "Administrator", "admin@library.com", "1-800-111-9999", "admin");
        }

        cout << "✓ " << LanguageText::getText("sample_complete") << endl;
    }

    while (true) {
        displayMenu();

        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ " << LanguageText::getText("invalid_input") << endl;
            continue;
        }
        cin.ignore();

        switch (choice) {
            // ==================== BOOK MANAGEMENT ====================
            case 1: { // Add book
                cout << "\n╔══════════ " << LanguageText::getText("menu_add_book") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                cout << LanguageText::getText("title") << ": ";
                getline(cin, title);
                cout << LanguageText::getText("author") << ": ";
                getline(cin, author);
                cout << LanguageText::getText("category") << ": ";
                getline(cin, category);
                cout << LanguageText::getText("year") << ": ";
                cin >> year;
                cin.ignore();
                cout << LanguageText::getText("publisher") << ": ";
                getline(cin, publisher);
                cout << LanguageText::getText("copies") << ": ";
                cin >> copies;
                cin.ignore();
                cout << LanguageText::getText("shelf") << ": ";
                getline(cin, shelf);
                cout << LanguageText::getText("description_optional") << ": ";
                getline(cin, description);
                library.addBook(isbn, title, author, category, year, publisher, copies, shelf, description);
                break;
            }
            case 2: { // Remove book
                cout << "\n╔══════════ " << LanguageText::getText("menu_del_book") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                library.removeBook(isbn);
                break;
            }
            case 3: { // Update book
                cout << "\n╔══════════ " << LanguageText::getText("menu_update_book") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                library.updateBook(isbn);
                break;
            }
            case 4: { // Display all books
                library.displayAllBooks();
                break;
            }
            case 5: { // Display available books
                library.displayAvailableBooks();
                break;
            }
            case 6: { // Rate book
                cout << "\n╔══════════ " << LanguageText::getText("menu_rate") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                cout << LanguageText::getText("rating") << " (0-5): ";
                cin >> rating;
                cin.ignore();
                library.rateBook(isbn, rating);
                break;
            }

            // ==================== USER MANAGEMENT ====================
            case 7: { // Add user
                cout << "\n╔══════════ " << LanguageText::getText("menu_add_user") << " ══════════╗" << endl;
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                cout << LanguageText::getText("name") << ": ";
                getline(cin, userName);
                cout << LanguageText::getText("email") << ": ";
                getline(cin, email);
                cout << LanguageText::getText("phone") << ": ";
                getline(cin, phone);
                cout << LanguageText::getText("user_type_prompt") << ": ";
                getline(cin, userType);
                library.addUser(userId, userName, email, phone, userType);
                break;
            }
            case 8: { // Display user info
                cout << "\n╔══════════ " << LanguageText::getText("menu_view_user") << " ══════════╗" << endl;
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                library.displayUserInfo(userId);
                break;
            }
            case 9: { // Display all users
                library.displayAllUsers();
                break;
            }

            // ==================== BORROW MANAGEMENT ====================
            case 10: { // Borrow book
                cout << "\n╔══════════ " << LanguageText::getText("menu_borrow") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                library.borrowBook(isbn, userId);
                break;
            }
            case 11: { // Return book
                cout << "\n╔══════════ " << LanguageText::getText("menu_return") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                library.returnBook(isbn, userId);
                break;
            }
            case 12: { // Renew book
                cout << "\n╔══════════ " << LanguageText::getText("menu_renew") << " ══════════╗" << endl;
                cout << LanguageText::getText("isbn") << ": ";
                getline(cin, isbn);
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                library.renewBook(isbn, userId);
                break;
            }
            case 13: { // Display borrowed books
                library.displayBorrowedBooks();
                break;
            }
            case 14: { // Display overdue books
                library.displayOverdueBooks();
                break;
            }
            case 15: { // Display borrow history
                cout << "\n╔══════════ " << LanguageText::getText("menu_history") << " ══════════╗" << endl;
                cout << LanguageText::getText("user_id") << ": ";
                getline(cin, userId);
                library.displayUserBorrowHistory(userId);
                break;
            }

            // ==================== SEARCH FUNCTIONS ====================
            case 16: { // Search by title
                cout << "\n╔══════════ " << LanguageText::getText("menu_search_title") << " ══════════╗" << endl;
                cout << LanguageText::getText("title") << ": ";
                getline(cin, title);
                library.searchByTitle(title);
                break;
            }
            case 17: { // Search by author
                cout << "\n╔══════════ " << LanguageText::getText("menu_search_author") << " ══════════╗" << endl;
                cout << LanguageText::getText("author") << ": ";
                getline(cin, author);
                library.searchByAuthor(author);
                break;
            }
            case 18: { // Search by category
                cout << "\n╔══════════ " << LanguageText::getText("menu_search_category") << " ══════════╗" << endl;
                cout << LanguageText::getText("category") << ": ";
                getline(cin, category);
                library.searchByCategory(category);
                break;
            }
            case 19: { // Advanced search
                library.advancedSearch();
                break;
            }

            // ==================== STATISTICS ====================
            case 20: { // Display statistics
                library.displayStatistics();
                break;
            }
            case 21: { // Display popular books
                library.displayPopularBooks();
                break;
            }
            case 22: { // Display category statistics
                library.displayCategoryStatistics();
                break;
            }

            // ==================== DATA MANAGEMENT ====================
            case 23: { // Save data
                cout << "\n" << LanguageText::getText("saving_data") << endl;
                library.saveData();
                break;
            }
            case 24: { // Export to CSV
                library.exportToCSV();
                break;
            }
            case 25: { // Import from CSV
                library.importFromCSV();
                break;
            }

            case 0: { // Exit
                cout << "\n" << LanguageText::getText("saving_data") << endl;
                library.saveData();
                cout << "\n════════════════════════════════════════════════════════" << endl;
                cout << "👋 " << LanguageText::getText("goodbye") << endl;
                cout << "════════════════════════════════════════════════════════" << endl;
                return 0;
            }

            default:
                cout << "❌ " << LanguageText::getText("invalid_choice") << endl;
        }

        // Pause for user to read output
        cout << "\n" << LanguageText::getText("press_enter");
        cin.get();
    }

    return 0;
}
