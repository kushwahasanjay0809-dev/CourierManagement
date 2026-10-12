#ifndef PARCEL_H
#define PARCEL_H
#include <string>
using namespace std;

class Parcel {
private:
    int parcelId;
    int senderId;          // the customerId of the sender
    string receiverName;
    double weight;         // in kg
public:
    Parcel();
    Parcel(int parcelId, int senderId, string receiverName, double weight);
    ~Parcel();

    int getParcelId() const;
    int getSenderId() const;
    string getReceiverName() const;
    double getWeight() const;
    void setReceiverName(string receiverName);
    void setWeight(double weight);

    double calculateCharge() const;   // Rs. 50 base + Rs. 20 per kg
    void display() const;
    string toLine() const;
};

#endif
