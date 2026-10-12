// CourierSystem.h - the "brain". It owns all the data (dynamic arrays) and does all the operations.
#ifndef COURIERSYSTEM_H
#define COURIERSYSTEM_H
#include <string>
#include "Customer.h"
#include "Courier.h"
#include "Parcel.h"
#include "Delivery.h"
using namespace std;

class CourierSystem {
private:
    static const int CAPACITY = 100;      // maximum records of each kind

    Customer* customers;                  // dynamic arrays - created with new[] in the constructor
    Courier*  couriers;
    Parcel*   parcels;
    Delivery* deliveries;

    int customerCount, courierCount, parcelCount, deliveryCount;           // how many are used
    int nextCustomerId, nextCourierId, nextParcelId, nextDeliveryId;       // IDs are given automatically

    int findCustomer(int id) const;       // each returns the array index, or -1 if not found
    int findCourier(int id) const;
    int findParcel(int id) const;
    int findDeliveryOfParcel(int parcelId) const;

    friend class FileManager;             // lets FileManager fill the arrays when loading
public:
    CourierSystem();
    ~CourierSystem();

    // 1. Add
    int addCustomer(string name, string phone);
    int addCourier(string name, string phone);
    int bookParcel(int senderId, string receiverName, double weight, string date);   // also creates a Delivery
    // 2. Display
    void displayCustomers() const;
    void displayCouriers() const;
    void displayParcels() const;
    void displayDeliveries() const;
    void displayAllPeople() const;        // polymorphism demo
    // 3. Search (by ID)
    void searchCustomer(int id) const;
    void searchCourier(int id) const;
    void searchParcel(int id) const;
    // 4. Update
    void updateCustomer(int id, string name, string phone);
    void updateCourier(int id, string name, string phone);
    void updateParcel(int id, string receiverName, double weight);
    // 5. Delete
    void deleteCustomer(int id);
    void deleteCourier(int id);
    void deleteParcel(int id);
    // 6. Main transaction
    void assignCourier(int parcelId, int courierId, string date);
    void updateStatus(int parcelId, string newStatus, string date);
    void trackParcel(int parcelId) const;
    // 7. Report
    void report() const;
};

#endif
