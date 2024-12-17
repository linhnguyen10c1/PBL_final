#include "prescription.h"
#include <sstream>
#include <stdexcept>


// Hàm thiết lập dữ liệu
void Prescription::set_data(long long ID_checking, long long ID_medicine, int quantity, const string& instruction, LinkedList<Medicine>& medicine_list) {
    this->ID_checking = ID_checking;
    this->ID_medicine = ID_medicine;
    this->quantity = quantity;
    this->instruction = instruction;

    Node<Medicine>* current = medicine_list.get_head();
    while (current != nullptr) {
        if (current->data.get_id() == ID_medicine) {
            // Giảm số lượng thuốc trong danh sách
            if (current->data.get_quantity() >= quantity) {
                current->data.decrease_quantity(quantity);
                write_data_to_file(medicine_list, "medicines.txt");
                this->price = current->data.get_price();
                this->function = current->data.get_function();
            }
            else {
                throw runtime_error("Not enough medicine in stock.");
            }
            break;
        }
        current = current->next;
    }

    if (current == nullptr) {
        throw runtime_error("Medicine ID not found.");
    }
}

// Hàm hiển thị thông tin
void Prescription::display() const {
    cout << "ID Checking: " << ID_checking
        << ", ID Medicine: " << ID_medicine
        << ", Quantity: " << quantity
        << ", Price: " << price
        << ", Instruction: " << instruction
        << ", Function: " << function << endl;
}

// Hàm đọc một đối tượng từ file
void Prescription::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;
    getline(ss, item, ',');
    ID_checking = stoll(item);
    getline(ss, item, ',');
    ID_medicine = stoll(item);
    getline(ss, item, ',');
    quantity = stoi(item);
    getline(ss, item, ',');
    price = stod(item);
    getline(ss, instruction, ',');
    getline(ss, function, ',');
}

// Hàm ghi một đối tượng vào file
void Prescription::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << ID_checking << ","
            << ID_medicine << ","
            << quantity << ","
            << price << ","
            << instruction << ","
            << function << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}

