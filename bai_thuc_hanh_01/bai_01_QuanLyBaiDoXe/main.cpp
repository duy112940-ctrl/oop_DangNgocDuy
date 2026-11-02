#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;
    bool isOccupied;

public:
    Vehicle() {
        vehicleID = 0;
        vehicleType = "";
        entryTime = 0;
        parkingDuration = 0;
        parkingFee = 0;
        isOccupied = false;
    }

    Vehicle(int id, const string& type, int entry, int duration) {
        vehicleID = id;
        vehicleType = normalizeType(type);
        entryTime = entry;
        parkingDuration = duration;
        parkingFee = 0;
        isOccupied = true;
        calculateFee();
    }

    static string normalizeType(const string& type) {
        string t = type;
        for (size_t i = 0; i < t.length(); i++) t[i] = tolower(t[i]);
        if (t == "car") return "Car";
        if (t == "motorcycle") return "Motorcycle";
        if (t == "bicycle") return "Bicycle";
        return "";
    }

    int getVehicleID() const { return vehicleID; }
    string getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    int getParkingDuration() const { return parkingDuration; }
    double getParkingFee() const { return parkingFee; }
    bool getIsOccupied() const { return isOccupied; }

    void setVehicleID(int id) { vehicleID = id; }
    void setVehicleType(const string& type) { vehicleType = normalizeType(type); }
    void setEntryTime(int t) { entryTime = t; }
    void setParkingDuration(int d) { parkingDuration = d; }
    void setParkingFee(double f) { parkingFee = f; }
    void setIsOccupied(bool o) { isOccupied = o; }

    void calculateFee() {
        double base = 0;
        if (vehicleType == "Car") base = 6.0;
        else if (vehicleType == "Motorcycle") base = 4.0;
        else if (vehicleType == "Bicycle") base = 2.0;

        bool peak = (entryTime >= 6 && entryTime < 10) ||
                    (entryTime >= 15 && entryTime < 19);

        double total = 0;
        for (int h = 1; h <= parkingDuration; h++) {
            if (h <= 2) {
                if (peak) total += base * 1.30;
                else total += base * 0.95;
            } else {
                total += base * 0.90;
            }
        }
        parkingFee = total;
    }

    void display() const {
        cout << "  - Ma xe: " << vehicleID
             << " | Loai: " << vehicleType
             << " | Gio vao: " << entryTime << "h"
             << " | Thoi gian do: " << parkingDuration << "h"
             << " | Phi: " << fixed << setprecision(2) << parkingFee << endl;
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    Vehicle vehicle1, vehicle2, vehicle3;
    bool hasVehicle1, hasVehicle2, hasVehicle3;

public:
    ParkingLot() {
        parkID = 0;
        size = 'S';
        hasVehicle1 = hasVehicle2 = hasVehicle3 = false;
    }

    ParkingLot(int id, char s) {
        parkID = id;
        size = toupper(s);
        hasVehicle1 = hasVehicle2 = hasVehicle3 = false;
    }

    int getParkID() const { return parkID; }
    char getSize() const { return size; }
    void setParkID(int id) { parkID = id; }
    void setSize(char s) { size = toupper(s); }

    int getCapacity() const {
        if (size == 'S') return 1;
        if (size == 'M') return 2;
        return 3;
    }

    int countVehicles() const {
        int c = 0;
        if (hasVehicle1) c++;
        if (hasVehicle2) c++;
        if (hasVehicle3) c++;
        return c;
    }

    bool isFull() const { return countVehicles() >= getCapacity(); }

    bool hasVehicleID(int vID) const {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) return true;
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) return true;
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) return true;
        return false;
    }

    bool addVehicle(const Vehicle& v) {

        if (!hasVehicle1) {
            vehicle1 = v;
            vehicle1.setIsOccupied(true);
            hasVehicle1 = true;
            return true;
        }

        if (!hasVehicle2 && (size == 'M' || size == 'L')) {
            vehicle2 = v;
            vehicle2.setIsOccupied(true);
            hasVehicle2 = true;
            return true;
        }

        if (!hasVehicle3 && size == 'L') {
            vehicle3 = v;
            vehicle3.setIsOccupied(true);
            hasVehicle3 = true;
            return true;
        }
        return false;
    }

    bool removeVehicle(int vID) {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) {
            vehicle1 = Vehicle();
            hasVehicle1 = false;
            return true;
        }
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) {
            vehicle2 = Vehicle();
            hasVehicle2 = false;
            return true;
        }
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) {
            vehicle3 = Vehicle();
            hasVehicle3 = false;
            return true;
        }
        return false;
    }

    int countByType(const string& type) const {
        int c = 0;
        if (hasVehicle1 && vehicle1.getVehicleType() == type) c++;
        if (hasVehicle2 && vehicle2.getVehicleType() == type) c++;
        if (hasVehicle3 && vehicle3.getVehicleType() == type) c++;
        return c;
    }

    double sumFeeByType(const string& type) const {
        double s = 0;
        if (hasVehicle1 && vehicle1.getVehicleType() == type) s += vehicle1.getParkingFee();
        if (hasVehicle2 && vehicle2.getVehicleType() == type) s += vehicle2.getParkingFee();
        if (hasVehicle3 && vehicle3.getVehicleType() == type) s += vehicle3.getParkingFee();
        return s;
    }

    void displayByType(const string& type) const {
        if (hasVehicle1 && vehicle1.getVehicleType() == type) vehicle1.display();
        if (hasVehicle2 && vehicle2.getVehicleType() == type) vehicle2.display();
        if (hasVehicle3 && vehicle3.getVehicleType() == type) vehicle3.display();
    }

    void displayLotInfo() const {
        cout << "Bai do ID: " << parkID << " | Kich thuoc: " << size
             << " | So xe: " << countVehicles() << "/" << getCapacity() << endl;
        if (countVehicles() == 0) {
            cout << "  (Bai trong)" << endl;
            return;
        }
        if (hasVehicle1) vehicle1.display();
        if (hasVehicle2) vehicle2.display();
        if (hasVehicle3) vehicle3.display();
    }
};

class SystemInterface {
private:
    ParkingLot parkingLot1, parkingLot2, parkingLot3;
    bool hasLot1, hasLot2, hasLot3;

    bool lotExists(int idx) const {
        if (idx == 1) return hasLot1;
        if (idx == 2) return hasLot2;
        return hasLot3;
    }

    ParkingLot& getLot(int idx) {
        if (idx == 1) return parkingLot1;
        if (idx == 2) return parkingLot2;
        return parkingLot3;
    }

    int findLotByID(int id) {
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i) && getLot(i).getParkID() == id) return i;
        }
        return 0;
    }

    int findLotOfVehicle(int vID) {
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i) && getLot(i).hasVehicleID(vID)) return i;
        }
        return 0;
    }

    int countLots() const {
        int c = 0;
        if (hasLot1) c++;
        if (hasLot2) c++;
        if (hasLot3) c++;
        return c;
    }

    int readInt(const string& msg) {
        int x;
        cout << msg;
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai: ";
        }
        return x;
    }

    void createLot() {
        if (countLots() >= 3) {
            cout << "Da du 3 bai do, khong the tao them!" << endl;
            return;
        }
        int id = readInt("Nhap parkID: ");
        if (findLotByID(id) != 0) {
            cout << "parkID da ton tai!" << endl;
            return;
        }
        char s;
        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> s;
        s = toupper(s);
        if (s != 'S' && s != 'M' && s != 'L') {
            cout << "Kich thuoc khong hop le!" << endl;
            return;
        }

        if (!hasLot1) { parkingLot1 = ParkingLot(id, s); hasLot1 = true; }
        else if (!hasLot2) { parkingLot2 = ParkingLot(id, s); hasLot2 = true; }
        else { parkingLot3 = ParkingLot(id, s); hasLot3 = true; }
        cout << "Tao bai do thanh cong!" << endl;
    }

    void addVehicleToLot() {
        if (countLots() == 0) {
            cout << "Chua co bai do nao, hay tao bai truoc!" << endl;
            return;
        }
        int id = readInt("Nhap vehicleID: ");
        if (findLotOfVehicle(id) != 0) {
            cout << "vehicleID da ton tai trong he thong!" << endl;
            return;
        }
        string type;
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> type;
        string t = Vehicle::normalizeType(type);
        if (t == "") {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }
        int entry = readInt("Nhap gio vao (0-23): ");
        if (entry < 0 || entry > 23) {
            cout << "Gio vao khong hop le!" << endl;
            return;
        }
        int dur = readInt("Nhap so gio do (1-23): ");
        if (dur < 1 || dur > 23) {
            cout << "So gio do khong hop le!" << endl;
            return;
        }
        if (entry + dur > 24) {
            cout << "Xe phai ra bai trong cung ngay (gio vao + thoi gian <= 24)!" << endl;
            return;
        }

        Vehicle v(id, t, entry, dur);

        for (int i = 1; i <= 3; i++) {
            if (lotExists(i) && !getLot(i).isFull()) {
                getLot(i).addVehicle(v);
                cout << "Da xep xe " << id << " vao bai " << getLot(i).getParkID()
                     << ". Phi do xe: " << fixed << setprecision(2) << v.getParkingFee() << endl;
                return;
            }
        }
        cout << "Tat ca cac bai da day, khong con cho!" << endl;
    }

    void deleteLot() {
        int id = readInt("Nhap parkID can xoa: ");
        int idx = findLotByID(id);
        if (idx == 0) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        if (idx == 1) { parkingLot1 = ParkingLot(); hasLot1 = false; }
        else if (idx == 2) { parkingLot2 = ParkingLot(); hasLot2 = false; }
        else { parkingLot3 = ParkingLot(); hasLot3 = false; }
        cout << "Da xoa bai do " << id << " (cac xe trong bai cung bi xoa)." << endl;
    }

    void removeVehicleFromLot() {
        int id = readInt("Nhap vehicleID can lay ra: ");
        int idx = findLotOfVehicle(id);
        if (idx == 0) {
            cout << "Khong tim thay xe!" << endl;
            return;
        }
        getLot(idx).removeVehicle(id);
        cout << "Da lay xe " << id << " ra khoi bai." << endl;
    }

    void displayAllLots() {
        if (countLots() == 0) {
            cout << "Chua co bai do nao." << endl;
            return;
        }
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i)) {
                ParkingLot& lot = getLot(i);
                cout << "Bai " << lot.getParkID() << " | Kich thuoc: " << lot.getSize()
                     << " | So xe: " << lot.countVehicles() << "/" << lot.getCapacity() << endl;
            }
        }
    }

    void displayVehiclesInLot() {
        int id = readInt("Nhap parkID: ");
        int idx = findLotByID(id);
        if (idx == 0) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        getLot(idx).displayLotInfo();
    }

    void listByType() {
        string type;
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> type;
        string t = Vehicle::normalizeType(type);
        if (t == "") {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }
        bool found = false;
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i) && getLot(i).countByType(t) > 0) {
                cout << "Bai " << getLot(i).getParkID() << ":" << endl;
                getLot(i).displayByType(t);
                found = true;
            }
        }
        if (!found) cout << "Khong co xe loai " << t << " nao." << endl;
    }

    void printAvgOfType(const string& t) {
        int cnt = 0;
        double sum = 0;
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i)) {
                cnt += getLot(i).countByType(t);
                sum += getLot(i).sumFeeByType(t);
            }
        }
        cout << "  " << t << ": ";
        if (cnt == 0) cout << "chua co xe" << endl;
        else cout << fixed << setprecision(2) << sum / cnt << " (" << cnt << " xe)" << endl;
    }

    void printAvgInLot(ParkingLot& lot, const string& t) {
        int cnt = lot.countByType(t);
        cout << "    " << t << ": ";
        if (cnt == 0) cout << "chua co xe" << endl;
        else cout << fixed << setprecision(2) << lot.sumFeeByType(t) / cnt << " (" << cnt << " xe)" << endl;
    }

    void reportAverageFee() {
        if (countLots() == 0) {
            cout << "Chua co bai do nao." << endl;
            return;
        }
        cout << "=== Phi trung binh toan he thong ===" << endl;
        printAvgOfType("Car");
        printAvgOfType("Motorcycle");
        printAvgOfType("Bicycle");

        cout << "=== Chi tiet theo tung bai ===" << endl;
        for (int i = 1; i <= 3; i++) {
            if (lotExists(i)) {
                cout << "  Bai " << getLot(i).getParkID() << ":" << endl;
                printAvgInLot(getLot(i), "Car");
                printAvgInLot(getLot(i), "Motorcycle");
                printAvgInLot(getLot(i), "Bicycle");
            }
        }
    }

public:
    SystemInterface() {
        hasLot1 = hasLot2 = hasLot3 = false;
    }

    void runMenu() {
        int choice = 0;
        do {
            cout << "\n===== QUAN LY BAI DO XE =====" << endl;
            cout << "1. Tao bai do xe moi" << endl;
            cout << "2. Them xe vao bai do" << endl;
            cout << "3. Xoa mot bai do xe" << endl;
            cout << "4. Lay xe ra khoi bai do" << endl;
            cout << "5. Hien thi danh sach tat ca bai do" << endl;
            cout << "6. Hien thi danh sach xe theo bai" << endl;
            cout << "7. Liet ke xe theo loai phuong tien" << endl;
            cout << "8. Bao cao phi do xe trung binh" << endl;
            cout << "9. Thoat" << endl;
            choice = readInt("Chon chuc nang: ");

            switch (choice) {
                case 1: createLot(); break;
                case 2: addVehicleToLot(); break;
                case 3: deleteLot(); break;
                case 4: removeVehicleFromLot(); break;
                case 5: displayAllLots(); break;
                case 6: displayVehiclesInLot(); break;
                case 7: listByType(); break;
                case 8: reportAverageFee(); break;
                case 9: cout << "Tam biet!" << endl; break;
                default: cout << "Lua chon khong hop le!" << endl;
            }
        } while (choice != 9);
    }
};

int main() {
    SystemInterface system;
    system.runMenu();
    return 0;
}
