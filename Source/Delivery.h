#ifndef DELIVERY_H
#define DELIVERY_H
#include <string>
using namespace std;

// Status flow:  Booked -> Assigned -> In Transit -> Delivered
class Delivery {
private:
    int deliveryId;
    int parcelId;
    int courierId;        // 0 means "no courier yet"
    string status;
    string date;          // date of the last change, DD-MM-YYYY
public:
    Delivery();
    Delivery(int deliveryId, int parcelId, int courierId, string status, string date);
    ~Delivery();

    void assign(int courierId, string date);        // Booked/Assigned -> Assigned
    void updateStatus(string newStatus, string date); // "In Transit" or "Delivered"

    int getDeliveryId() const;
    int getParcelId() const;
    int getCourierId() const;
    string getStatus() const;
    string getDate() const;
    void display() const;
    string toLine() const;
};

#endif
