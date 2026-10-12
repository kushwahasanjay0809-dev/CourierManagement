#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

FileManager::FileManager() {
    folder = "Data";
}

vector<string> FileManager::splitLine(const string& line) {
    vector<string> parts;
    stringstream ss(line);
    string piece;
    while (getline(ss, piece, '|')) parts.push_back(piece);
    return parts;
}

void FileManager::save(CourierSystem& s) {
    ofstream cf(folder + "/customers.txt");
    ofstream kf(folder + "/couriers.txt");
    ofstream pf(folder + "/parcels.txt");
    ofstream df(folder + "/deliveries.txt");
    if (!cf || !kf || !pf || !df)
        throw runtime_error("Could not open the files. Make sure a folder named Data exists next to the program.");

    for (int i = 0; i < s.customerCount; i++) cf << s.customers[i].toLine() << endl;
    for (int i = 0; i < s.courierCount; i++)  kf << s.couriers[i].toLine() << endl;
    for (int i = 0; i < s.parcelCount; i++)   pf << s.parcels[i].toLine() << endl;
    for (int i = 0; i < s.deliveryCount; i++) df << s.deliveries[i].toLine() << endl;
}

void FileManager::load(CourierSystem& s) {
    // Start from empty (the arrays already exist, we just reset the counters).
    s.customerCount = s.courierCount = s.parcelCount = s.deliveryCount = 0;
    s.nextCustomerId = s.nextCourierId = s.nextParcelId = s.nextDeliveryId = 1;

    string line;
    ifstream cf(folder + "/customers.txt");      // if the file does not exist (first run) the loop simply does nothing
    while (getline(cf, line)) {
        try {
            vector<string> p = splitLine(line);
            Customer c(stoi(p.at(0)), p.at(1), p.at(2));
            s.customers[s.customerCount++] = c;
            s.nextCustomerId = max(s.nextCustomerId, c.getId() + 1);
        } catch (exception& e) { /* skip a damaged line */ }
    }

    ifstream kf(folder + "/couriers.txt");
    while (getline(kf, line)) {
        try {
            vector<string> p = splitLine(line);
            Courier c(stoi(p.at(0)), p.at(1), p.at(2));
            s.couriers[s.courierCount++] = c;
            s.nextCourierId = max(s.nextCourierId, c.getId() + 1);
        } catch (exception& e) { }
    }

    ifstream pf(folder + "/parcels.txt");
    while (getline(pf, line)) {
        try {
            vector<string> p = splitLine(line);
            Parcel x(stoi(p.at(0)), stoi(p.at(1)), p.at(2), stod(p.at(3)));
            s.parcels[s.parcelCount++] = x;
            s.nextParcelId = max(s.nextParcelId, x.getParcelId() + 1);
        } catch (exception& e) { }
    }

    ifstream df(folder + "/deliveries.txt");
    while (getline(df, line)) {
        try {
            vector<string> p = splitLine(line);
            Delivery d(stoi(p.at(0)), stoi(p.at(1)), stoi(p.at(2)), p.at(3), p.at(4));
            s.deliveries[s.deliveryCount++] = d;
            s.nextDeliveryId = max(s.nextDeliveryId, d.getDeliveryId() + 1);
        } catch (exception& e) { }
    }
}
