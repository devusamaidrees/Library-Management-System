# Library Management System
This program is a simple implementation of a library management system with four main options:

**1.Book_Issue()**: Allows a student to borrow a book from the library.

**2.Deposit_Book()**: Allows a student to return a book to the library.

**3.Admin_Menu():** Displays the admin menu with further options.

**4.Exit()**: Exits the program.
# Admin Menu
The `Admin_Menu()` option displays further 11 options for the library admin:

**1.CREATE STUDENT RECORD**: Allows the admin to add a new student record to the library database. The student record contains a unique ID, name, and contact information.

**2.DISPLAY ALL STUDENTS RECORD**: Displays all the student records currently available in the library database.

**3.DISPLAY SPECIFIC STUDENT RECORD: **Allows the admin to search for a specific student record in the library database using the unique student ID and displays its details.

**4.MODIFY STUDENT RECORD**: Allows the admin to modify an existing student record in the library database using the unique student ID.

**5.DELETE STUDENT RECORD**: Allows the admin to delete a student record from the library database using the unique student ID.

**6.CREATE BOOK**: Allows the admin to add a new book to the library. The book record contains a unique ID, title, author, and availability status.

**7.DISPLAY ALL BOOKS**: Displays all the books currently available in the library.

**8.DISPLAY SPECIFIC BOOK**: Allows the admin to search for a specific book in the library using the unique book ID and displays its details.

**9.MODIFY BOOK**: Allows the admin to modify an existing book in the library using the unique book ID.

**10.DELETE BOOK**: Allows the admin to delete a book from the library using the unique book ID.

**11.Main menu**: Returns to the main menu.
# Usage
To use the library management system, simply run the program and choose one of the four main options:

If you choose **Book_Issue()**, you will be prompted to enter the student's unique ID and the book's unique ID. If the book is available and the student does not have any other books issued, the book will be issued to the student and the database will be updated accordingly.

If you choose **Deposit_Book()**, you will be prompted to enter the student's unique ID and the book's unique ID. If the book is valid and issued to the student, it will be returned to the library and the database will be updated accordingly.

If you choose **Admin_Menu()**, you will be prompted to enter the admin password. Once authenticated, you can choose one of the 11 options listed above.If you choose `Exit()`, the program will exit.
