#include "Delivery.h"
#include "Validation.h"
#include <iostream>
#include <stdexcept>

Delivery::Delivery() {
    deliveryId = 0;
    parcelId = 0;
    courierId = 0;
    status = "Booked";
    date = "01-01-2000";
}

Delivery::Delivery(int deliveryId, int parcelId, int courierId, string status, string date) {
    checkDate(date);
    this->deliveryId = deliveryId;
    this->parcelId = parcelId;
    this->courierId = courierId;
    this->status = status;
    this->date = date;
}

Delivery::~Delivery() {}

void Delivery::assign(int courierId, string date) {
    checkDate(date);
    if (status != "Booked" && status != "Assigned")
        throw runtime_error("A courier can only be assigned while the parcel is Booked or Assigned.");
    this->courierId = courierId;
    this->status = "Assigned";
    this->date = date;
}

void Delivery::updateStatus(string newStatus, string date) {
    checkDate(date);
    if (newStatus == "In Transit") {
        if (status != "Assigned")
            throw runtime_error("Parcel must be Assigned before it can be In Transit.");
    } else if (newStatus == "Delivered") {
        if (status != "In Transit")
            throw runtime_error("Parcel must be In Transit before it can be Delivered.");
    } else {
        throw runtime_error("Unknown status.");
    }
    status = newStatus;
    this->date = date;
}

int Delivery::getDeliveryId() const { return deliveryId; }
int Delivery::getParcelId() const { return parcelId; }
int Delivery::getCourierId() const { return courierId; }
string Delivery::getStatus() const { return status; }
string Delivery::getDate() const { return date; }

void Delivery::display() const {
    cout << "  Delivery | ID: " << deliveryId << " | Parcel: " << parcelId << " | Courier: ";
    if (courierId == 0) cout << "none";
    else cout << courierId;
    cout << " | Status: " << status << " | Date: " << date << endl;
}

string Delivery::toLine() const {
    return to_string(deliveryId) + "|" + to_string(parcelId) + "|" + to_string(courierId) + "|" + status + "|" + date;
}
