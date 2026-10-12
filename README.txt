============================================================
              COURIER MANAGEMENT SYSTEM
============================================================

Project Code     : [YOUR PROJECT CODE]
Enrollment No.   : [YOUR ENROLLMENT NUMBER]
Student Name     : [YOUR FULL NAME]
Project Name     : Courier Management System
Language         : C++
Development Tool : Visual Studio Code
Compiler         : GNU G++ (MSYS2 UCRT64)


1. PROJECT DESCRIPTION
------------------------------------------------------------

Courier Management System is a console-based C++ application
developed to manage a courier business: customers, couriers,
parcels and their deliveries.

The system allows the user to add, display, search, update and
delete records. It also provides a main transaction (book a
parcel, assign a courier, update the delivery status and track
the parcel), report generation, data validation and file-based
data persistence.


2. MAIN FEATURES
------------------------------------------------------------

1. Add Customer / Courier / Parcel (Book Parcel)
2. Display Customers / Couriers / Parcels / Deliveries
3. Search Customer / Courier / Parcel by ID
4. Update Customer / Courier / Parcel
5. Delete Customer / Courier / Parcel
6. Main Transaction: Book Parcel, Assign Courier,
   Update Delivery Status, Track Parcel
7. Generate Report
8. Save Data
9. Load Data
10. Automatic Save Before Exit


3. CLASSES USED
------------------------------------------------------------

The project is divided into multiple classes and files.

Person
------
Base class. Stores ID, name and phone number. Has a virtual
function display().

Customer
--------
Derived from Person. Represents a customer who sends parcels.

Courier
-------
Derived from Person. Represents a courier who delivers parcels.

Parcel
------
Stores parcel ID, sender ID, receiver name and weight.
calculateCharge() returns Rs. 50 + Rs. 20 per kg.

Delivery
--------
Stores delivery ID, parcel ID, courier ID, status and date.
assign() gives the parcel to a courier and updateStatus()
moves it through the status flow:
Booked -> Assigned -> In Transit -> Delivered.

CourierSystem
-------------
Main system class. Owns the dynamic arrays of customers,
couriers, parcels and deliveries and performs all operations
(add, display, search, update, delete, bookParcel,
assignCourier, updateStatus, trackParcel, report).

FileManager
-----------
Responsible for saving and loading all records using text
files in the Data folder.

Validation
----------
Provides validation functions for names, phone numbers,
weights, dates and IDs.


4. OOP CONCEPTS USED
------------------------------------------------------------

The following Object-Oriented Programming concepts are used:

1. Classes and Objects
2. Encapsulation
3. Default and Parameterized Constructors
4. Destructors
5. Inheritance
6. Runtime Polymorphism
7. Dynamic Memory Allocation
8. File Handling
9. Validation
10. Exception Handling
11. Access Specifiers


5. INHERITANCE AND POLYMORPHISM
------------------------------------------------------------

Person is used as the base class.

Customer and Courier are derived classes.

The function display() is virtual in Person and is overridden
in Customer and Courier.

CourierSystem::displayAllPeople() stores both customers and
couriers in one array of Person pointers and calls display()
through each pointer. The correct version (Customer or
Courier) is chosen at run time. This demonstrates runtime
polymorphism.


6. DYNAMIC MEMORY
------------------------------------------------------------

CourierSystem dynamically creates arrays of objects in its
constructor.

Example:

customers  = new Customer[CAPACITY];
couriers   = new Courier[CAPACITY];
parcels    = new Parcel[CAPACITY];
deliveries = new Delivery[CAPACITY];

The allocated memory is released in the destructor using:

delete[] customers;
delete[] couriers;
delete[] parcels;
delete[] deliveries;

CAPACITY is 100 records for each kind of record.


7. FILE HANDLING
------------------------------------------------------------

The project uses file handling to store records permanently.

Data is stored in the Data folder:

Data/customers.txt
Data/couriers.txt
Data/parcels.txt
Data/deliveries.txt

Records are stored one per line, with fields separated by |

The FileManager class provides functions to:

- save() : write all records to the files
- load() : read all records from the files

When the program starts, previously saved records are loaded.

Before the program exits, the current records are
automatically saved.


8. VALIDATION AND EXCEPTION HANDLING
------------------------------------------------------------

The Validation functions check user input.

The following validations are performed:

- IDs must be greater than zero.
- Names must be 1 to 30 characters and must not contain |
- Phone numbers must be exactly 10 digits.
- Weight must be more than 0 and at most 50 kg.
- Dates must be in DD-MM-YYYY format.
- Sender must be an existing customer.
- Status must follow Booked > Assigned > In Transit > Delivered.
- Customers with parcels, couriers with deliveries in progress
  and parcels in progress cannot be deleted.

Invalid input is handled using exception handling
(throw runtime_error and try-catch blocks in main).
This prevents invalid data from being added or updated.


9. HOW TO COMPILE
------------------------------------------------------------

Open the terminal in the project folder and use:

g++ Source/*.cpp -o CourierManagement.exe

If your terminal does not expand *.cpp, use:

g++ Source/main.cpp Source/Person.cpp Source/Customer.cpp Source/Courier.cpp Source/Parcel.cpp Source/Delivery.cpp Source/CourierSystem.cpp Source/FileManager.cpp Source/Validation.cpp -o CourierManagement.exe


10. HOW TO RUN
------------------------------------------------------------

After successful compilation, run from the project root:

.\CourierManagement.exe

Important: run the program from the project root folder so
that the Data folder is found.


11. MAIN MENU
------------------------------------------------------------

The main menu contains:

1. Add Record
2. Display Records
3. Search Record
4. Update Record
5. Delete Record
6. Main Transaction / Process
7. Report
8. Save / Load
9. Exit


12. DATA PERSISTENCE
------------------------------------------------------------

The program loads previously saved records when it starts.

The user can also manually save or load data using the
Save / Load menu.

The program automatically saves the current records before
exiting.

Therefore, saved records remain available when the program is
opened again.


13. FOLDER STRUCTURE
------------------------------------------------------------

CourierManagement_Project
|
|-- Source
|   |-- main.cpp
|   |-- Person.h
|   |-- Person.cpp
|   |-- Customer.h
|   |-- Customer.cpp
|   |-- Courier.h
|   |-- Courier.cpp
|   |-- Parcel.h
|   |-- Parcel.cpp
|   |-- Delivery.h
|   |-- Delivery.cpp
|   |-- CourierSystem.h
|   |-- CourierSystem.cpp
|   |-- FileManager.h
|   |-- FileManager.cpp
|   |-- Validation.h
|   |-- Validation.cpp
|
|-- Data
|   |-- customers.txt
|   |-- couriers.txt
|   |-- parcels.txt
|   |-- deliveries.txt
|
|-- Diagrams
|   |-- UseCaseDiagram.png
|   |-- ClassDiagram.png
|   |-- SequenceDiagram1.png
|   |-- SequenceDiagram2.png
|
|-- Screenshots
|   |-- 01_MainMenu.png ... 10_Persistence.png
|
|-- Executable
|   |-- CourierManagement.exe
|
|-- CourierManagement.exe
|
|-- README.txt
|
|-- ProjectReport.pdf
|
|-- ProjectReport.docx


14. SYSTEM REQUIREMENTS
------------------------------------------------------------

Hardware:
- Basic computer or laptop
- Minimum 4 GB RAM recommended

Software:
- Windows operating system
- Visual Studio Code
- GNU G++ compiler
- MSYS2 UCRT64 environment


15. PROJECT PURPOSE
------------------------------------------------------------

The purpose of this project is to demonstrate the use of
Object-Oriented Programming concepts in C++ by developing a
console-based Courier Management System.

The project also demonstrates file handling, dynamic memory,
inheritance, runtime polymorphism, validation and exception
handling.


16. PROJECT STATUS
------------------------------------------------------------

The core Courier Management application has been implemented
and tested.

The project includes:

- Modular C++ source files
- Customer, courier, parcel and delivery management
- Parcel booking, courier assignment and status tracking
- Dynamic memory allocation
- File handling and persistence
- Input validation
- Exception handling
- Report generation
- Executable program


============================================================
                    END OF README
============================================================
