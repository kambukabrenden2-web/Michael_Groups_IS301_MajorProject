Detailed pseudocode for each module
# Library Management System – Pseudocode

## 1. Authentication Module (`auth.c`, `auth.h`)

### Function `login()`
BEGIN login
DISPLAY "======= LIBRARY MANAGEMENT SYSTEM ======="
DISPLAY "Administrator Login"
PROMPT "Username: " → read username
PROMPT "Password: " → read password
IF username == "admin" AND password == "admin" THEN
DISPLAY "Login successful!"
RETURN true
ELSE
DISPLAY "Invalid credentials. Access denied."
RETURN false
END IF
END

## 2. Book Management (`books.c`)

### Helper `stristr(haystack, needle)`
BEGIN stristr
IF needle is empty THEN RETURN haystack
FOR each character in haystack:
IF case‑insensitive match of needle starting at current position THEN
RETURN pointer to current position
RETURN NULL
END

### Helper `getNextBookId(books, count)`
BEGIN getNextBookId
maxId = 0
FOR i = 0 to count-1:
IF books[i].id > maxId THEN maxId = books[i].id
RETURN maxId + 1
END

### `addBook(books, *count)`
BEGIN addBook
IF *count >= MAX_BOOKS THEN
DISPLAY "Error: Book limit reached."
RETURN
newBook.id = getNextBookId(books, *count)
PROMPT "Enter Title: " → read newBook.title (trim newline)
PROMPT "Enter Author: " → read newBook.author
PROMPT "Enter Genre: " → read newBook.genre
PROMPT "Enter Year Published: " → read newBook.year
PROMPT "Enter Quantity: " → read newBook.quantity
IF newBook.quantity < 0 THEN newBook.quantity = 0
books[*count] = newBook
(*count)++
DISPLAY "Book added successfully! ID: " + newBook.id
END

### `removeBook(books, *count)`
BEGIN removeBook
PROMPT "Enter Book ID to remove: " → read id
idx = findBookIndexById(books, *count, id)
IF idx == -1 THEN
DISPLAY "Book ID not found."
RETURN
FOR i = idx to (*count)-2:
books[i] = books[i+1]
(*count)--
DISPLAY "Book removed successfully."
END

### `updateBookQuantity(books, count)`
BEGIN updateBookQuantity
PROMPT "Enter Book ID to update quantity: " → read id
idx = findBookIndexById(books, count, id)
IF idx == -1 THEN
DISPLAY "Book ID not found."
RETURN
DISPLAY "Current quantity: " + books[idx].quantity
PROMPT "Enter new quantity: " → read newQty
IF newQty < 0 THEN newQty = 0
books[idx].quantity = newQty
DISPLAY "Quantity updated."
END

### `searchBookByTitle(books, count)`
BEGIN searchBookByTitle
PROMPT "Enter title (or partial): " → read title
found = FALSE
FOR i = 0 to count-1:
IF stristr(books[i].title, title) != NULL THEN
CALL displayBook(books[i])
found = TRUE
IF NOT found THEN DISPLAY "No books found with title containing ..."
END

### `searchBookByAuthor(books, count)`
BEGIN searchBookByAuthor
PROMPT "Enter author name (or partial): " → read author
found = FALSE
FOR each book:
IF stristr(book.author, author) != NULL THEN
displayBook(book)
found = TRUE
IF NOT found THEN DISPLAY "No books found by author ..."
END

### `displayAllBooks(books, count)`
BEGIN displayAllBooks
IF count == 0 THEN DISPLAY "No books in the library."; RETURN
DISPLAY table header (ID, Title, Author, Genre, Year, Qty)
FOR each book:
DISPLAY book.id, title, author, genre, year, quantity
END

### `findBookIndexById(books, count, id)`
BEGIN findBookIndexById
FOR i = 0 to count-1:
IF books[i].id == id THEN RETURN i
RETURN -1
END

### `displayBook(book)`
BEGIN displayBook
DISPLAY "ID: X | Title: ... | Author: ... | Genre: ... | Year: ... | Qty: ..."
END

## 3. Member Management (`members.c`)

### Helper `getNextMemberId(members, count)`
BEGIN getNextMemberId
maxId = 0
FOR i = 0 to count-1:
IF members[i].id > maxId THEN maxId = members[i].id
RETURN maxId + 1
END

### `registerMember(members, *count)`
BEGIN registerMember
IF count >= MAX_MEMBERS THEN
DISPLAY "Error: Member limit reached."
RETURN
newMember.id = getNextMemberId(members, count)
PROMPT "Enter full name: " → read newMember.name
PROMPT "Enter email: " → read newMember.email
PROMPT "Enter phone: " → read newMember.phone
members[count] = newMember
(count)++
DISPLAY "Member registered successfully! ID: " + newMember.id
END

### `viewAllMembers(members, count)`
BEGIN viewAllMembers
IF count == 0 THEN DISPLAY "No members registered."; RETURN
DISPLAY table (ID, Name, Email, Phone)
FOR each member:
DISPLAY member.id, name, email, phone
END

### `updateMember(members, count)`
BEGIN updateMember
PROMPT "Enter Member ID to update: " → read id
idx = findMemberIndexById(members, count, id)
IF idx == -1 THEN
DISPLAY "Member ID not found."
RETURN
DISPLAY "Updating member: " + members[idx].name
PROMPT "New name (enter to keep current): " → read newName
IF newName not empty THEN copy to members[idx].name
PROMPT "New email (enter to keep): " → read newEmail
IF newEmail not empty THEN copy to members[idx].email
PROMPT "New phone (enter to keep): " → read newPhone
IF newPhone not empty THEN copy to members[idx].phone
DISPLAY "Member information updated."
END

### `findMemberIndexById(members, count, id)`
BEGIN findMemberIndexById
FOR i = 0 to count-1:
IF members[i].id == id THEN RETURN i
RETURN -1
END

### `displayMember(member)`
BEGIN displayMember
DISPLAY "ID: ... | Name: ... | Email: ... | Phone: ..."
END

## 4. Borrowing Management (`borrowing.c`)

### Helper `getNextBorrowId(borrowings, count)`
BEGIN getNextBorrowId
maxId = 0
FOR i = 0 to count-1:
IF borrowings[i].borrowId > maxId THEN maxId = borrowings[i].borrowId
RETURN maxId + 1
END

### `issueBook(borrowings, *borrowCount, books, bookCount, members, memberCount)`
BEGIN issueBook
PROMPT "Enter Book ID: " → read bookId
PROMPT "Enter Member ID: " → read memberId
bookIdx = findBookIndexById(books, bookCount, bookId)
IF bookIdx == -1 THEN
DISPLAY "Book ID not found."; RETURN
IF books[bookIdx].quantity <= 0 THEN
DISPLAY "Book not available."; RETURN
memberIdx = findMemberIndexById(members, memberCount, memberId)
IF memberIdx == -1 THEN
DISPLAY "Member ID not found."; RETURN
// Check if member already has this book active
FOR each borrowing record:
IF borrowing.bookId == bookId AND borrowing.memberId == memberId AND borrowing.returnDate empty THEN
DISPLAY "Member already has this book borrowed and not returned."; RETURN
IF borrowCount >= MAX_BORROWINGS THEN
DISPLAY "Borrowing limit reached."; RETURN
newBorrow.borrowId = getNextBorrowId(borrowings, borrowCount)
newBorrow.bookId = bookId
newBorrow.memberId = memberId
PROMPT "Enter borrow date (YYYY-MM-DD): " → read newBorrow.borrowDate
newBorrow.returnDate = empty string
borrowings[borrowCount] = newBorrow
(borrowCount)++
books[bookIdx].quantity-- // decrease available quantity
DISPLAY "Book issued successfully. Borrow ID: " + newBorrow.borrowId
END

### `returnBook(borrowings, borrowCount, books, bookCount)`
BEGIN returnBook
PROMPT "Enter Book ID: " → read bookId
PROMPT "Enter Member ID: " → read memberId
Find active borrowing record where bookId and memberId match and returnDate empty → borrowIdx
IF borrowIdx == -1 THEN
DISPLAY "No active borrowing record found."; RETURN
PROMPT "Enter return date (YYYY-MM-DD): " → read retDate
Copy retDate to borrowings[borrowIdx].returnDate
bookIdx = findBookIndexById(books, bookCount, bookId)
IF bookIdx != -1 THEN
books[bookIdx].quantity++ // increase available quantity
DISPLAY "Book returned successfully."
END

### `viewBorrowingHistory(borrowings, borrowCount, members, memberCount, books, bookCount)`
BEGIN viewBorrowingHistory
IF borrowCount == 0 THEN
DISPLAY "No borrowing records."; RETURN
DISPLAY table header (BorrowID, BookID, MemberID, BorrowDate, ReturnDate)
FOR each borrowing record:
returnDisplay = (returnDate empty) ? "Not yet" : returnDate
DISPLAY borrowId, bookId, memberId, borrowDate, returnDisplay
END

### `findActiveBorrowing(borrowings, count, bookId, memberId)`
BEGIN findActiveBorrowing
FOR i = 0 to count-1:
IF borrowings[i].bookId == bookId AND borrowings[i].memberId == memberId AND borrowings[i].returnDate empty THEN
RETURN i
RETURN -1
END

## 5. File Handling (`filehandling.c`)

### `loadBooksFromFile(filename, books, *count)`
BEGIN loadBooksFromFile
Open file for reading
IF file not open THEN
DISPLAY "Warning: file not found. Starting empty."
*count = 0; RETURN
*count = 0
WHILE read line from file AND count < MAX_BOOKS:
Parse line: id,title,author,genre,year,quantity
IF parsed 6 fields THEN
Add book to array; (count)++
Close file
END

### `saveBooksToFile(filename, books, count)`
BEGIN saveBooksToFile
Open file for writing
IF error THEN DISPLAY error and RETURN
FOR i = 0 to count-1:
Write: id,title,author,genre,year,quantity (comma‑separated)
Close file
END

### `loadMembersFromFile(filename, members, *count)`
BEGIN loadMembersFromFile
Open file; if fails, *count=0; RETURN
*count=0
WHILE read line AND count<MAX_MEMBERS:
Parse: id,name,email,phone
If 4 fields → add to array; (count)++
Close file
END

### `saveMembersToFile(filename, members, count)`
BEGIN saveMembersToFile
Open file for writing
FOR each member: write id,name,email,phone
Close file
END

### `loadBorrowingsFromFile(filename, borrowings, *count)`
BEGIN loadBorrowingsFromFile
Open file; if fails, *count=0; RETURN
*count=0
WHILE read line AND count<MAX_BORROWINGS:
Parse: borrowId,bookId,memberId,borrowDate,returnDate
If 5 fields → add to array; (count)++
Close file
END

### `saveBorrowingsToFile(filename, borrowings, count)`
BEGIN saveBorrowingsToFile
Open file for writing
FOR each borrowing:
returnStr = (returnDate empty) ? "NULL" : returnDate
Write: borrowId,bookId,memberId,borrowDate,returnStr
Close file
END

### `generateInventoryReport(filename, books, count)`
BEGIN generateInventoryReport
Open file for writing
FOR each book:
Write: BookID, Title, Author, Genre, Year Published, Quantity, Availability Status
Write separator line
Close file
DISPLAY "Inventory report saved to " + filename
END

## 6. Menu & Main (`menu.c`, `main.c`)

### `main()` (in `main.c`)
BEGIN main
IF NOT login() THEN
DISPLAY "Exiting system."; RETURN 1
CALL runMainMenu()
RETURN 0
END

### `runMainMenu()` (in `menu.c`)
BEGIN runMainMenu
// Load data from files
loadBooksFromFile("books.txt", books, &bookCount)
loadMembersFromFile("members.txt", members, &memberCount)
loadBorrowingsFromFile("borrowings.txt", borrowings, &borrowCount)

choice = -1
WHILE choice != 0:
DISPLAY main menu options
PROMPT "Choice: " → read choice

SWITCH choice:
CASE 1: displayAllBooks(books, bookCount)
CASE 2: searchBookByTitle(books, bookCount)
CASE 3: searchBookByAuthor(books, bookCount)
CASE 4: addBook(books, &bookCount); saveBooksToFile(...)
CASE 5: updateBookQuantity(books, bookCount); saveBooksToFile(...)
CASE 6: removeBook(books, &bookCount); saveBooksToFile(...)
CASE 7: // Member Management sub‑menu
DO:
DISPLAY member sub‑menu
read mchoice
SWITCH mchoice:
1: registerMember(members, &memberCount); saveMembersToFile(...)
2: viewAllMembers(members, memberCount)
3: updateMember(members, memberCount); saveMembersToFile(...)
WHILE mchoice != 0
CASE 8: // Borrowing Management sub‑menu
DO:
DISPLAY borrowing sub‑menu
read bchoice
SWITCH bchoice:
1: issueBook(..., books, bookCount, members, memberCount); saveBooksToFile(...); saveBorrowingsToFile(...)
2: returnBook(..., books, bookCount); saveBooksToFile(...); saveBorrowingsToFile(...)
3: viewBorrowingHistory(...)
WHILE bchoice != 0
CASE 9: generateInventoryReport("inventory_report.txt", books, bookCount)
CASE 0: saveAllData(); DISPLAY "Exiting..."
END SWITCH
END WHILE
END

