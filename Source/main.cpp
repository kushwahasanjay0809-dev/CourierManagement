// main.cpp - creates the system, shows the menu and calls CourierSystem functions.
#include <iostream>
#include <string>
#include <stdexcept>
#include "CourierSystem.h"
#include "FileManager.h"
using namespace std;

class InputEnded {};      // thrown if the input stream closes (for example Ctrl+D)

// ---- small input helpers ----
string readText(string message) {
    cout << message;
    string text;
    if (!getline(cin, text)) throw InputEnded();
    return text;
}
int readInt(string message) {
    string text = readText(message);
    try { return stoi(text); }
    catch (exception& e) { throw runtime_error("Please enter a whole number."); }
}
double readDouble(string message) {
    string text = readText(message);
    try { return stod(text); }
    catch (exception& e) { throw runtime_error("Please enter a number."); }
}

// ---- menus ----
void showMenu() {
    cout << "\n===== COURIER MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Display Records" << endl;
    cout << "3. Search Record" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Main Transaction / Process" << endl;
    cout << "7. Report" << endl;
    cout << "8. Save / Load" << endl;
    cout << "9. Exit" << endl;
}

void bookParcelMenu(CourierSystem& sys) {
    int senderId = readInt("Sender customer ID: ");
    string receiver = readText("Receiver name: ");
    double weight = readDouble("Weight in kg: ");
    string date = readText("Date (DD-MM-YYYY): ");
    int id = sys.bookParcel(senderId, receiver, weight, date);
    cout << "Parcel booked. Parcel ID = " << id << endl;
    sys.trackParcel(id);
}

void addMenu(CourierSystem& sys) {
    cout << "1. Customer  2. Courier  3. Parcel (book)" << endl;
    int choice = readInt("Add which? ");
    if (choice == 1) {
        string name = readText("Name: ");
        string phone = readText("Phone (10 digits): ");
        cout << "Customer added. ID = " << sys.addCustomer(name, phone) << endl;
    } else if (choice == 2) {
        string name = readText("Name: ");
        string phone = readText("Phone (10 digits): ");
        cout << "Courier added. ID = " << sys.addCourier(name, phone) << endl;
    } else if (choice == 3) {
        bookParcelMenu(sys);
    } else {
        cout << "Invalid choice." << endl;
    }
}

void displayMenu(CourierSystem& sys) {
    cout << "1. Customers  2. Couriers  3. Parcels  4. Deliveries  5. All people (polymorphism)" << endl;
    int choice = readInt("Display which? ");
    if (choice == 1) sys.displayCustomers();
    else if (choice == 2) sys.displayCouriers();
    else if (choice == 3) sys.displayParcels();
    else if (choice == 4) sys.displayDeliveries();
    else if (choice == 5) sys.displayAllPeople();
    else cout << "Invalid choice." << endl;
}

void searchMenu(CourierSystem& sys) {
    cout << "1. Customer  2. Courier  3. Parcel" << endl;
    int choice = readInt("Search which? ");
    if (choice < 1 || choice > 3) { cout << "Invalid choice." << endl; return; }
    int id = readInt("Enter ID: ");
    if (choice == 1) sys.searchCustomer(id);
    else if (choice == 2) sys.searchCourier(id);
    else sys.searchParcel(id);
}

void updateMenu(CourierSystem& sys) {
    cout << "1. Customer  2. Courier  3. Parcel" << endl;
    int choice = readInt("Update which? ");
    if (choice < 1 || choice > 3) { cout << "Invalid choice." << endl; return; }
    int id = readInt("Enter ID: ");
    if (choice == 3) {
        string receiver = readText("New receiver name: ");
        double weight = readDouble("New weight in kg: ");
        sys.updateParcel(id, receiver, weight);
    } else {
        string name = readText("New name: ");
        string phone = readText("New phone: ");
        if (choice == 1) sys.updateCustomer(id, name, phone);
        else sys.updateCourier(id, name, phone);
    }
    cout << "Record updated." << endl;
}

void deleteMenu(CourierSystem& sys) {
    cout << "1. Customer  2. Courier  3. Parcel" << endl;
    int choice = readInt("Delete which? ");
    if (choice < 1 || choice > 3) { cout << "Invalid choice." << endl; return; }
    int id = readInt("Enter ID: ");
    if (choice == 1) sys.deleteCustomer(id);
    else if (choice == 2) sys.deleteCourier(id);
    else sys.deleteParcel(id);
    cout << "Record deleted." << endl;
}

void transactionMenu(CourierSystem& sys) {
    cout << "1. Book parcel  2. Assign courier  3. Update delivery status  4. Track parcel" << endl;
    int choice = readInt("Choose: ");
    if (choice == 1) {
        bookParcelMenu(sys);
    } else if (choice == 2) {
        int parcelId = readInt("Parcel ID: ");
        int courierId = readInt("Courier ID: ");
        string date = readText("Date (DD-MM-YYYY): ");
        sys.assignCourier(parcelId, courierId, date);
        sys.trackParcel(parcelId);
    } else if (choice == 3) {
        int parcelId = readInt("Parcel ID: ");
        int s = readInt("New status (1 = In Transit, 2 = Delivered): ");
        string date = readText("Date (DD-MM-YYYY): ");
        if (s == 1) sys.updateStatus(parcelId, "In Transit", date);
        else if (s == 2) sys.updateStatus(parcelId, "Delivered", date);
        else throw runtime_error("Status must be 1 or 2.");
        sys.trackParcel(parcelId);
    } else if (choice == 4) {
        sys.trackParcel(readInt("Parcel ID: "));
    } else {
        cout << "Invalid choice." << endl;
    }
}

int main() {
    CourierSystem sys;        // the system object
    FileManager fm;

    fm.load(sys);             // START -> load existing records
    cout << "Old records loaded from the Data folder (if any)." << endl;

    while (true) {
        try {
            showMenu();
            int choice = readInt("Enter choice: ");
            if (choice == 1) addMenu(sys);
            else if (choice == 2) displayMenu(sys);
            else if (choice == 3) searchMenu(sys);
            else if (choice == 4) updateMenu(sys);
            else if (choice == 5) deleteMenu(sys);
            else if (choice == 6) transactionMenu(sys);
            else if (choice == 7) sys.report();
            else if (choice == 8) {
                cout << "1. Save  2. Load" << endl;
                int c = readInt("Choose: ");
                if (c == 1) { fm.save(sys); cout << "Saved." << endl; }
                else if (c == 2) { fm.load(sys); cout << "Loaded." << endl; }
                else cout << "Invalid choice." << endl;
            }
            else if (choice == 9) {
                fm.save(sys);          // save updated records -> EXIT
                cout << "Data saved. Goodbye!" << endl;
                break;
            }
            else cout << "Please choose a number from 1 to 9." << endl;
        }
        catch (InputEnded&) {
            fm.save(sys);
            cout << "\nInput closed. Data saved." << endl;
            break;
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << endl;      // validation / rule errors land here
        }
    }
    return 0;
}
