#include "Parcel.h"
#include "Validation.h"
#include <iostream>

Parcel::Parcel() {
    parcelId = 0;
    senderId = 0;
    receiverName = "None";
    weight = 0;
}

Parcel::Parcel(int parcelId, int senderId, string receiverName, double weight) {
    checkId(parcelId);
    checkId(senderId);
    this->parcelId = parcelId;
    this->senderId = senderId;
    setReceiverName(receiverName);
    setWeight(weight);
}

Parcel::~Parcel() {}

int Parcel::getParcelId() const { return parcelId; }
int Parcel::getSenderId() const { return senderId; }
string Parcel::getReceiverName() const { return receiverName; }
double Parcel::getWeight() const { return weight; }

void Parcel::setReceiverName(string receiverName) {
    checkName(receiverName);
    this->receiverName = receiverName;
}

void Parcel::setWeight(double weight) {
    checkWeight(weight);
    this->weight = weight;
}

double Parcel::calculateCharge() const {
    return 50 + 20 * weight;
}

void Parcel::display() const {
    cout << "  Parcel | ID: " << parcelId << " | Sender ID: " << senderId
         << " | Receiver: " << receiverName << " | Weight: " << weight
         << " kg | Charge: Rs." << calculateCharge() << endl;
}

string Parcel::toLine() const {
    return to_string(parcelId) + "|" + to_string(senderId) + "|" + receiverName + "|" + to_string(weight);
}
