#ifndef SHOESTORE_H
#define SHOESTORE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Shoe {
    string brand;
    string model;
    int size;
    double price;
};

class ShoeStore {
private:
    vector<Shoe> inventory;

public:
    void addShoe(const Shoe& shoe);
    void removeShoe(int index);
    void displayInventory() const;
};

#endif // SHOESTORE_H


void ShoeStore::addShoe(const Shoe& shoe) {
    inventory.push_back(shoe);
    cout << "Ayakkabý eklendi: " << shoe.brand << " " << shoe.model << endl;
}

void ShoeStore::removeShoe(int index) {
    if (index >= 0 && index < inventory.size()) {
        cout << "Ayakkabý silindi: " << inventory[index].brand << " " << inventory[index].model << endl;
        inventory.erase(inventory.begin() + index);
    } else {
        cout << "Geçersiz ayakkabý indeksi!" << endl;
    }
}

void ShoeStore::displayInventory() const {
    if (inventory.empty()) {
        cout << "Stokta ayakkabý yok." << endl;
        return;
    }
    
    cout << "Stokta bulunan ayakkabýlar:" << endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i << ": " << inventory[i].brand << " " << inventory[i].model << ", Boyut: " 
                  << inventory[i].size << ", Fiyat: " << inventory[i].price << " TL" << endl;
    }
}


int main() {
    ShoeStore store;
    string command;

    while (true) {
        cout << "Bir komut girin (ekle, sil, goster, exit): ";
        cin >> command;

        if (command == "ekle") {
            Shoe newShoe;
            cout << "Marka: ";
            cin >> newShoe.brand;
            cout << "Model: ";
            cin >> newShoe.model;
            cout << "Boyut: ";
            cin >> newShoe.size;
            cout << "Fiyat: ";
            cin >> newShoe.price;

            store.addShoe(newShoe);
        } else if (command == "sil") {
            int index;
            cout << "Silinecek ayakkabý indeksi: ";
            cin >> index;
            store.removeShoe(index);
        } else if (command == "goster") {
            store.displayInventory();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Geçersiz komut." << endl;
        }
    }

    return 0;
}

