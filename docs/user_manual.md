# Library Management System – User Manual

## Introduction
This system helps librarians manage books, members, and borrowing records. It runs in a text‑based menu and saves all data to files (`books.txt`, `members.txt`, `borrowings.txt`).

## Getting Started
1. Compile all `.c` files together (e.g., using GCC) and run the executable.
2. At login, enter:
   - **Username:** `admin`
   - **Password:** `admin`
3. After successful login, the main menu appears.

## Main Menu Options

### 1. Display all books
Shows a table of all books with ID, title, author, genre, year, and quantity.

### 2. Search book by title
Enter a full or partial title. All books whose title contains the text will be displayed.

### 3. Search book by author
Enter a full or partial author name. All matching books are displayed.

### 4. Add new book
Prompts for title, author, genre, year published, and quantity. The system automatically assigns a new book ID. After adding, data is saved to `books.txt`.

### 5. Update book quantity
Enter a book ID, see the current quantity, then enter a new quantity. The change is saved immediately.

### 6. Remove book
Enter a book ID. The book is deleted from the system and the file is updated.

### 7. Member Management
Opens a sub‑menu with three options:
- **Register new member:** Enter name, email, phone. System assigns a member ID.
- **View all members:** Shows a table of all registered members.
- **Update member info:** Enter a member ID, then optionally change name, email, or phone. Press Enter to keep existing value.

### 8. Borrowing Management
Opens a sub‑menu:
- **Issue book to member:** Enter a book ID and a member ID. If the book is available and the member does not already have it, you are asked for a borrow date (format YYYY-MM-DD). The book’s quantity decreases and a borrowing record is created.
- **Return book:** Enter the book ID and member ID. Then enter the return date. The book’s quantity increases and the borrowing record is marked as returned.
- **View borrowing history:** Shows all borrowing records with borrow and return dates. “Not yet” means the book is still out.

### 9. Generate Inventory Report
Creates a text file `inventory_report.txt` listing every book with details and availability status. The file is saved in the same folder as the program.

### 0. Exit
Saves all data (books, members, borrowings) to their respective `.txt` files and terminates the program.

## Data Files
- `books.txt` – stores book records in comma‑separated format.
- `members.txt` – stores member records.
- `borrowings.txt` – stores borrowing records (return date `NULL` indicates active).
- `inventory_report.txt` – generated report (not read by the program).

**Note:** If a data file is missing when the program starts, it is created automatically when you add or modify data.

## Example Workflow
1. Login with admin/admin.
2. Add a book: “The Hobbit” by J.R.R. Tolkien, genre Fantasy, year 1937, quantity 3.
3. Register a member: John Doe, john@example.com, 123456789.
4. Issue the book to John: enter book ID and member ID, give borrow date 2026-05-21.
5. View borrowing history to confirm.
6. Later, return the book: enter same IDs, return date 2026-06-01.
7. Generate inventory report to see updated quantity.
8. Exit – data is saved.

## Troubleshooting
- **Login fails:** Use exact credentials `admin` / `admin`.
- **“Book limit reached”:** You can increase `MAX_BOOKS` in `config.h` and recompile.
- **File not found warnings on first run:** Ignore – the program will create files when you add data.
- **Invalid dates:** The system does not validate dates; always use `YYYY-MM-DD` format for consistency.

For further help, contact your system administrator.
