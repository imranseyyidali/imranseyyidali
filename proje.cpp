#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
using namespace std;

struct ayakkabi {
    string brand;
    string model;
    int yil;
    double pricePerDay;
    bool isRented;
};

class ayakkabiRentalSystem {
private:
    vector<ayakkabi> ayakkabis;

    
    void loadFromFile(const string& filename) {
        ifstream file(filename.c_str());

        if (file.is_open()) {
            ayakkabi ayakkabi;
            while (file >> ayakkabi.brand >> ayakkabi.model >> ayakkabi.yil >> ayakkabi.pricePerDay >> ayakkabi.isRented) {
                ayakkabis.push_back(ayakkabi);
            }
            file.close();
            cout << "Dosyadan ayakkabi verileri yüklendi." << endl;
        } else {
            cout << "Dosya açilamadi, yeni bir sistem baslatiliyor." << endl;
        }
    }

    
void saveToFile(const string& filename) const {
    ofstream file(filename.c_str());

    if (file.is_open()) {
        for (size_t i = 0; i < ayakkabis.size(); ++i) {
            const ayakkabi& ayakkabi = ayakkabis[i];
            if (ayakkabi.isRented) { 
                file << ayakkabi.brand << " " << ayakkabi.model << " " << ayakkabi.yil << " "
                     << ayakkabi.pricePerDay << " " << ayakkabi.isRented << endl;
            }
        }
        file.close();
        cout << "Ayakkabi verileri dosyaya kaydedildi." << endl;
    } else {
        cout << "Dosya açilamadi!" << endl;
    }
}


public:
    ayakkabiRentalSystem(const string& filename) {
        loadFromFile(filename); 
    }

    ~ayakkabiRentalSystem() {
        saveToFile("ayakkabis.txt"); 
    }

    void addayakkabi(const ayakkabi& ayakkabi) {
        ayakkabis.push_back(ayakkabi);
        cout << "Ayakkabi eklendi: " << ayakkabi.brand << " " << ayakkabi.model << endl;
    }

    void displayayakkabis() const {
        if (ayakkabis.empty()) {
            cout << "Sistemde kayitli ayakkabi yok." << endl;
            return;
        }

        cout << "Mevcut ayakkabilar:" << endl;
        for (size_t i = 0; i < ayakkabis.size(); ++i) {
            cout << i << ": " << ayakkabis[i].brand << " " << ayakkabis[i].model 
                 << " (" << ayakkabis[i].yil << "), Günlük Fiyat: " 
                 << ayakkabis[i].pricePerDay << " TL, "
                 << (ayakkabis[i].isRented ? "Kirada" : "Uygun") << endl;
        }
    }

    void rentayakkabi(int index) {
        if (index >= 0 && index < ayakkabis.size()) {
            if (!ayakkabis[index].isRented) {
                ayakkabis[index].isRented = true;
                cout << "Ayakkabi kiralandi: " << ayakkabis[index].brand << " " << ayakkabis[index].model << endl;
            } else {
                cout << "Ayakkabi zaten kirada!" << endl;
            }
        } else {
            cout << "Geçersiz ayakkabi indeksi!" << endl;
        }
    }

    void returnayakkabi(int index) {
        if (index >= 0 && index < ayakkabis.size()) {
            if (ayakkabis[index].isRented) {
                ayakkabis[index].isRented = false;
                cout << "Ayakkabi teslim alindi: " << ayakkabis[index].brand << " " << ayakkabis[index].model << endl;
            } else {
                cout << "Ayakkabi zaten teslim edilmis durumda!" << endl;
            }
        } else {
            cout << "Geçersiz ayakkabi indeksi!" << endl;
        }
    }
};

int main() {
    ayakkabiRentalSystem system("ayakkabis.txt");
    string command;

    while (true) {
        cout << "\nBir komut girin (ekle, goster, kirala, teslim, exit): ";
        cin >> command;

        if (command == "ekle") {
            ayakkabi newayakkabi;
            cout << "Marka: ";
            cin >> newayakkabi.brand;
            cout << "Model: ";
            cin >> newayakkabi.model;
            cout << "Yil: ";
            cin >> newayakkabi.yil;
            cout << "Günlük Fiyat: ";
            cin >> newayakkabi.pricePerDay;
            newayakkabi.isRented = false; 

            system.addayakkabi(newayakkabi);
        } else if (command == "goster") {
            system.displayayakkabis();
        } else if (command == "kirala") {
            int index;
            cout << "Kiralanacak araç indeksi: ";
            cin >> index;
            system.rentayakkabi(index);
        } else if (command == "teslim") {
            int index;
            cout << "Teslim alýnacak araç indeksi: ";
            cin >> index;
            system.returnayakkabi(index);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Geçersiz komut!" << endl;
        }
    }

    return 0;
}

