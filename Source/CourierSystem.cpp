#include "CourierSystem.h"
#include "Validation.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// ---------- constructor / destructor (dynamic memory) ----------
CourierSystem::CourierSystem() {
    // We do not know how many records the user will have, so the arrays are made on the heap with new[].
    customers  = new Customer[CAPACITY];
    couriers   = new Courier[CAPACITY];
    parcels    = new Parcel[CAPACITY];
    deliveries = new Delivery[CAPACITY];
    customerCount = courierCount = parcelCount = deliveryCount = 0;
    nextCustomerId = nextCourierId = nextParcelId = nextDeliveryId = 1;
}

CourierSystem::~CourierSystem() {
    // Every new[] must have a matching delete[], otherwise memory leaks.
    delete[] customers;
    delete[] couriers;
    delete[] parcels;
    delete[] deliveries;
}

// ---------- find helpers ----------
int CourierSystem::findCustomer(int id) const {
    for (int i = 0; i < customerCount; i++)
        if (customers[i].getId() == id) return i;
    return -1;
}
int CourierSystem::findCourier(int id) const {
    for (int i = 0; i < courierCount; i++)
        if (couriers[i].getId() == id) return i;
    return -1;
}
int CourierSystem::findParcel(int id) const {
    for (int i = 0; i < parcelCount; i++)
        if (parcels[i].getParcelId() == id) return i;
    return -1;
}
int CourierSystem::findDeliveryOfParcel(int parcelId) const {
    for (int i = 0; i < deliveryCount; i++)
        if (deliveries[i].getParcelId() == parcelId) return i;
    return -1;
}

// ---------- 1. Add ----------
int CourierSystem::addCustomer(string name, string phone) {
    if (customerCount == CAPACITY) throw runtime_error("Customer list is full.");
    Customer c(nextCustomerId, name, phone);   // the constructor validates name and phone
    customers[customerCount] = c;
    customerCount++;
    return nextCustomerId++;
}

int CourierSystem::addCourier(string name, string phone) {
    if (courierCount == CAPACITY) throw runtime_error("Courier list is full.");
    Courier c(nextCourierId, name, phone);
    couriers[courierCount] = c;
    courierCount++;
    return nextCourierId++;
}

int CourierSystem::bookParcel(int senderId, string receiverName, double weight, string date) {
    if (parcelCount == CAPACITY) throw runtime_error("Parcel list is full.");
    if (findCustomer(senderId) == -1) throw runtime_error("Sender (customer) ID not found.");

    Parcel p(nextParcelId, senderId, receiverName, weight);        // validates receiver and weight
    Delivery d(nextDeliveryId, nextParcelId, 0, "Booked", date);   // validates date
    parcels[parcelCount] = p;
    parcelCount++;
    deliveries[deliveryCount] = d;
    deliveryCount++;
    nextDeliveryId++;
    return nextParcelId++;
}

// ---------- 2. Display ----------
void CourierSystem::displayCustomers() const {
    cout << "--- Customers (" << customerCount << ") ---" << endl;
    for (int i = 0; i < customerCount; i++) customers[i].display();
}
void CourierSystem::displayCouriers() const {
    cout << "--- Couriers (" << courierCount << ") ---" << endl;
    for (int i = 0; i < courierCount; i++) couriers[i].display();
}
void CourierSystem::displayParcels() const {
    cout << "--- Parcels (" << parcelCount << ") ---" << endl;
    for (int i = 0; i < parcelCount; i++) parcels[i].display();
}
void CourierSystem::displayDeliveries() const {
    cout << "--- Deliveries (" << deliveryCount << ") ---" << endl;
    for (int i = 0; i < deliveryCount; i++) deliveries[i].display();
}

void CourierSystem::displayAllPeople() const {
    // RUNTIME POLYMORPHISM: one array of Person pointers holds both Customers and Couriers.
    // When we call display(), C++ picks Customer::display() or Courier::display() while the program runs.
    Person* people[2 * CAPACITY];
    int n = 0;
    for (int i = 0; i < customerCount; i++) { people[n] = &customers[i]; n++; }
    for (int i = 0; i < courierCount; i++)  { people[n] = &couriers[i];  n++; }

    cout << "--- All people ---" << endl;
    for (int i = 0; i < n; i++) people[i]->display();
}

// ---------- 3. Search ----------
void CourierSystem::searchCustomer(int id) const {
    int i = findCustomer(id);
    if (i == -1) cout << "  Customer not found." << endl;
    else customers[i].display();
}
void CourierSystem::searchCourier(int id) const {
    int i = findCourier(id);
    if (i == -1) cout << "  Courier not found." << endl;
    else couriers[i].display();
}
void CourierSystem::searchParcel(int id) const {
    int i = findParcel(id);
    if (i == -1) cout << "  Parcel not found." << endl;
    else parcels[i].display();
}

// ---------- 4. Update ----------
void CourierSystem::updateCustomer(int id, string name, string phone) {
    int i = findCustomer(id);
    if (i == -1) throw runtime_error("Customer ID not found.");
    checkName(name);       // check both first so we never half-update a record
    checkPhone(phone);
    customers[i].setName(name);
    customers[i].setPhone(phone);
}
void CourierSystem::updateCourier(int id, string name, string phone) {
    int i = findCourier(id);
    if (i == -1) throw runtime_error("Courier ID not found.");
    checkName(name);
    checkPhone(phone);
    couriers[i].setName(name);
    couriers[i].setPhone(phone);
}
void CourierSystem::updateParcel(int id, string receiverName, double weight) {
    int i = findParcel(id);
    if (i == -1) throw runtime_error("Parcel ID not found.");
    int d = findDeliveryOfParcel(id);
    if (deliveries[d].getStatus() != "Booked")
        throw runtime_error("Only parcels with status Booked can be updated.");
    checkName(receiverName);
    checkWeight(weight);
    parcels[i].setReceiverName(receiverName);
    parcels[i].setWeight(weight);
}

// ---------- 5. Delete (shift the remaining records one step left) ----------
void CourierSystem::deleteCustomer(int id) {
    int i = findCustomer(id);
    if (i == -1) throw runtime_error("Customer ID not found.");
    for (int j = 0; j < parcelCount; j++)
        if (parcels[j].getSenderId() == id)
            throw runtime_error("Cannot delete: this customer still has parcels.");
    for (int j = i; j < customerCount - 1; j++) customers[j] = customers[j + 1];
    customerCount--;
}

void CourierSystem::deleteCourier(int id) {
    int i = findCourier(id);
    if (i == -1) throw runtime_error("Courier ID not found.");
    for (int j = 0; j < deliveryCount; j++) {
        string s = deliveries[j].getStatus();
        if (deliveries[j].getCourierId() == id && (s == "Assigned" || s == "In Transit"))
            throw runtime_error("Cannot delete: this courier has deliveries in progress.");
    }
    for (int j = i; j < courierCount - 1; j++) couriers[j] = couriers[j + 1];
    courierCount--;
}

void CourierSystem::deleteParcel(int id) {
    int i = findParcel(id);
    if (i == -1) throw runtime_error("Parcel ID not found.");
    int d = findDeliveryOfParcel(id);
    string s = deliveries[d].getStatus();
    if (s == "Assigned" || s == "In Transit")
        throw runtime_error("Cannot delete: this parcel is in progress.");
    for (int j = i; j < parcelCount - 1; j++) parcels[j] = parcels[j + 1];
    parcelCount--;
    for (int j = d; j < deliveryCount - 1; j++) deliveries[j] = deliveries[j + 1];
    deliveryCount--;
}

// ---------- 6. Main transaction ----------
void CourierSystem::assignCourier(int parcelId, int courierId, string date) {
    if (findParcel(parcelId) == -1) throw runtime_error("Parcel ID not found.");
    if (findCourier(courierId) == -1) throw runtime_error("Courier ID not found.");
    int d = findDeliveryOfParcel(parcelId);
    deliveries[d].assign(courierId, date);
}

void CourierSystem::updateStatus(int parcelId, string newStatus, string date) {
    if (findParcel(parcelId) == -1) throw runtime_error("Parcel ID not found.");
    int d = findDeliveryOfParcel(parcelId);
    deliveries[d].updateStatus(newStatus, date);
}

void CourierSystem::trackParcel(int parcelId) const {
    int p = findParcel(parcelId);
    if (p == -1) throw runtime_error("Parcel ID not found.");
    int d = findDeliveryOfParcel(parcelId);
    int s = findCustomer(parcels[p].getSenderId());
    int c = findCourier(deliveries[d].getCourierId());

    cout << "--- Tracking parcel " << parcelId << " ---" << endl;
    parcels[p].display();
    cout << "  Sender : " << (s == -1 ? "(deleted)" : customers[s].getName()) << endl;
    if (deliveries[d].getCourierId() == 0) cout << "  Courier: not assigned yet" << endl;
    else cout << "  Courier: " << (c == -1 ? "(deleted)" : couriers[c].getName()) << endl;
    cout << "  Status : " << deliveries[d].getStatus() << " (on " << deliveries[d].getDate() << ")" << endl;
}

// ---------- 7. Report ----------
void CourierSystem::report() const {
    int booked = 0, assigned = 0, transit = 0, delivered = 0;
    double totalCharge = 0, deliveredCharge = 0;

    for (int i = 0; i < deliveryCount; i++) {
        string s = deliveries[i].getStatus();
        int p = findParcel(deliveries[i].getParcelId());
        double charge = parcels[p].calculateCharge();
        totalCharge += charge;
        if (s == "Booked") booked++;
        else if (s == "Assigned") assigned++;
        else if (s == "In Transit") transit++;
        else if (s == "Delivered") { delivered++; deliveredCharge += charge; }
    }

    cout << "========== REPORT ==========" << endl;
    cout << "Customers: " << customerCount << endl;
    cout << "Couriers : " << courierCount << endl;
    cout << "Parcels  : " << parcelCount << endl;
    cout << "Booked: " << booked << " | Assigned: " << assigned
         << " | In Transit: " << transit << " | Delivered: " << delivered << endl;
    cout << "Total charges of all parcels : Rs." << totalCharge << endl;
    cout << "Charges of delivered parcels : Rs." << deliveredCharge << endl;
    cout << "============================" << endl;
}
