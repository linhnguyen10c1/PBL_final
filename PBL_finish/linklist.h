#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "admin.h"
#include <SFML/Graphics.hpp> 
#include "button.h"
#include"support.h"
//#include "testing.h"
using namespace std;

// Cấu trúc Node cho danh sách liên kết
template <typename T>
struct Node {
    T data;
    Node* next;
};

// Lớp cơ bản cho các thao tác danh sách liên kết
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}



    /////////////////////////////////////////////////////////////////////////

    int size() {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Lấy phần tử tại một vị trí cụ thể (ở đây là bằng cách lặp)  
    Node<T>* get_node(int index) {
        Node<T>* current = head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }
        return current;
    }

    template <typename T>
    void setcolum(sf::RenderWindow& window, const string& filename, Node<T>* current) {
        sf::Font font;
        if (!font.loadFromFile("consola.ttf")) {
            ErrorWindow("Cannot load font file!");
        }
        sf::Text header;
        header.setFont(font);
        header.setString(current->data.setheader());
        header.setFillColor(sf::Color::Blue);
        header.setCharacterSize(15.5);
        header.setPosition(50, 270); // Căn chỉnh vị trí của tiêu đề
        window.draw(header);
    }
    ///////////////////////////////////////////////////////////////////////////////
    Node<T>* get_head() const { return head; }
    int check_id_password(long long id, string& password);
    void add(const T& item);
    long long get_id_from_file();
    void display_list(bool& textboarderflag, sf::RenderWindow& window, sf::Event& event, LinkedList<T>& list, const string& filename) const; // SFML
    //int search_check_update_delete_recover_by_id(sf::RenderWindow& window, sf::Event& event, long long ID, const string& function);
    int search_check_update_delete_recover_by_id(long long ID,const string &function);



    // DOCTOR interact list RECORD, TESTING
    // to add a object has 2 foreign key
    void add_for_test(const T& item);
    // display result of testing for general Doctor update final result
    void display_result_testing(long long ID) const;
    // check a record has a attribute testing_or_not and update result for a record by general doctor, after watching result testing
    int checkExist_updateResult_for_record(long long ID, const string& function);
    // kiểm tra xem bác sĩ có ID _checking đó trong record không
    int check_a_doctor_has_ID_checking(long long ID_checking, long long ID_doctor, const string& function);
    int count_patients(long long ID_doctor, const string& function, int priority = 100);
    // display in order, to doctor can call patient in room to check
    void display_list_waiting(std::string typedoctor, bool& clickflag, int& flag, long long ID_doctor, LinkedList<T>& list, sf::RenderWindow& window, sf::Event& event) const;
    int check_doctor_updated_result(long long ID_checking);
    int check_test_having_another_test(long long ID_checking, long long ID_doctor);
};


template <typename T>
int LinkedList<T>::check_id_password(long long id, string& password) {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "Danh sách rỗng." << endl;
        return 0;
    }
    while (current) {
        if (current->data.get_id() == id
            && current->data.get_password() == password
            && current->data.get_is_deleted() == false) {
            current->data.display();
            return 1;
        }
        current = current->next;
    }
    ErrorWindow("      Uncorrect account");
    return 0;
}

template <typename T>
void LinkedList<T>::add(const T& item) {
    Node<T>* newNode = new Node<T>{ item, nullptr };
    newNode->next = nullptr;
    if (!head) {
        head = newNode;
        return;
    }
    Node<T>* temp = head;
    while (temp->next) {
        if (temp->data.get_id() == item.get_id()) {
            cout << temp->data.get_id() << ":" << item.get_id() << endl;
            ErrorWindow("phan tu da ton tai trong list");
            return;
        }
        temp = temp->next;
    }
    temp->next = newNode;
}

template <typename T>
long long LinkedList<T>::get_id_from_file() {
    Node<T>* current = head;
    if (current == nullptr) {
        return T::set_id;
    }
    while (current->next) {
        current = current->next;
    }
    return (current->data.get_id()) + 1;
}

template <typename T>
void LinkedList<T>::display_list(bool& textboarderflag, sf::RenderWindow& window, sf::Event& event, LinkedList<T>& list, const string& filename) const {

    int itemHeight = 20;
    int visibleItems = 15;
    int totalItems = list.size();
    static float posittionY;


    static long long ID;
    static int searchflag = 0;
    static int scrollOffset = 0;
    static Node<T>* ChoseNode;
    int temp;

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        ErrorWindow("Cannot load font file!");
    }

    Node<T>* forlenght = list.get_head();
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(float((forlenght->data.setheader()).size()) * 8, itemHeight));
    box.setFillColor(sf::Color(170, 220, 245));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color(170, 220, 245));



    Button update("Update", 400, 195, 80, 50, sf::Color(100, 180, 220), sf::Color::White);
    Button updatepass("Update password", 510, 195, 150, 50, sf::Color(100, 180, 220), sf::Color::White);
    Button Delete("Delete", 690, 195, 80, 50, sf::Color(100, 180, 220), sf::Color::White);
    Button recover("Recover", 810, 195, 80, 50, sf::Color(100, 180, 220), sf::Color::White);
    Button expand("Expand", 930, 195, 80, 50, sf::Color(100, 180, 220), sf::Color::White);


    Button Search("Search", 1670, 195, 80, 50, sf::Color(135, 206, 235), sf::Color::Black);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (Search.isClicked(mousePos)) {
            searchscreen(ID, searchflag);
        }
    }
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {

            scrollOffset = std::max(scrollOffset - 1, 0);
        }
        else if (event.mouseWheelScroll.delta < 0) {

            scrollOffset = std::min(scrollOffset + 1, totalItems - visibleItems);
        }
    }

    //search neu nhan nut serch searchflag=1 khi do doan ma sau se tim scrolloffset cua node can tim
    Node<T>* current1 = list.get_head();
    temp = scrollOffset;
    if (searchflag == 1) {
        scrollOffset = 0;
        while (current1 && current1->data.get_id() != ID) {
            scrollOffset++;
            current1 = current1->next;
        }
        if (!current1) { ErrorWindow("       Don't exist ID"); scrollOffset = temp; }
        if (current1) ChoseNode = current1;
        searchflag = 0;
    }
    //ve khung mau xanhblue
    Node<T>* current = list.get_node(scrollOffset);
    list.setcolum(window, filename, current);
    for (int i = 0; i < visibleItems; i++) {

        if (current) {
            if (!textboarderflag) box.setPosition(50, 300 + i * (itemHeight));
            if (textboarderflag) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Kiểm tra click vào text
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (!(filename == "records.txt") && update.isClicked(mousePos)) {
                        int forcallfunction = 1;
                        sf::RenderWindow window1(sf::VideoMode(800, 600), "Update");
                        ChoseNode->data.update_info(window1, event, forcallfunction);
                        if (forcallfunction != 2) write_data_to_file(list, filename);
                        //if (forcallfunction != 2) searchflag = 1;

                    }
                    if (!(filename == "medicines.txt") && !(filename == "records.txt") && updatepass.isClicked(mousePos)) {
                        ChoseNode->data.update_data();
                        write_data_to_file(list, filename);
                        //searchflag = 1;

                    }
                    if (Delete.isClicked(mousePos)) {
                        ChoseNode->data.update_is_deleted();
                        write_data_to_file(list, filename);
                        //searchflag = 1;

                    }
                    if (recover.isClicked(mousePos)) {
                        ChoseNode->data.update_is_recovered();
                        write_data_to_file(list, filename);
                        //searchflag = 1;
                    }
                    if (filename == "records.txt" && expand.isClicked(mousePos)) {
                        ChoseNode->data.display();
                        //write_data_to_file(list, filename);
                        //searchflag = 1;
                    }
                }

                //////////
                Delete.draw(window);
                if (filename == "records.txt") {
                    update.setButtonColor(sf::Color::Red);
                    updatepass.setButtonColor(sf::Color::Red);
                }
                if (filename != "records.txt") expand.setButtonColor(sf::Color::Red);
                expand.draw(window);
                update.draw(window);
                if (filename == "medicines.txt") {
                    updatepass.setButtonColor(sf::Color::Red);
                }
                updatepass.draw(window);
                recover.draw(window);
                box.setPosition(50, posittionY);
            }

            if (!textboarderflag && event.type == sf::Event::MouseButtonPressed) {
                // Kiểm tra click vào ô
                if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    ChoseNode = current;
                    ID = current->data.get_id();
                    posittionY = 300 + i * (itemHeight);
                    textboarderflag = true;
                }
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (textboarderflag && event.type == sf::Event::MouseButtonPressed) {
                // Kiểm tra click vào ô
                if (!box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !Delete.isClicked(mousePos)
                    && !update.isClicked(mousePos) && !updatepass.isClicked(mousePos) && !recover.isClicked(mousePos)) {
                    posittionY = 0;
                    textboarderflag = false;
                }
            }
            if (textboarderflag) {
                window.draw(box);
            }
            current = current->next;
        }
        else {
            break;
        }
    }
    // ve bang
    current = list.get_node(scrollOffset);
    for (int i = 0; i < visibleItems; i++) {

        if (current) {

            sf::Text text;
            text.setFont(font);
            text.setString(current->data.toString());
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(15.5);
            text.setPosition(50, 300 + i * (itemHeight));
            window.draw(text);
            current = current->next;
        }
        else {
            break;
        }
    }
    Search.draw(window);

}



template <typename T>
void LinkedList<T>::add_for_test(const T& item) {
    Node<T>* newNode = new Node<T>{ item, nullptr };
    if (!head) {
        head = newNode;
        return;
    }
    else {
        Node<T>* temp = head;
        while (temp->next) {
            if (temp->data.get_id() == item.get_id() && temp->data.get_id_doctor() == item.get_id_doctor()) {
                cout << "Item existed" << endl;
                return;
            }
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void testscreen(long long ID_checking, long long ID_doctor);
void search_record_patient(long long ID_patient, sf::RenderWindow& window1, sf::Event& event1);
template <typename T>
void checkingscreen(long long ID_checking, long long ID_doctor, LinkedList<T>& record_list, sf::RenderWindow& window1, sf::Event& event1);


template <typename T>
void LinkedList<T>::display_list_waiting(std::string typedoctor, bool& clickflag, int& flag, long long ID_doctor, LinkedList<T>& list, sf::RenderWindow& window, sf::Event& event) const {

    int itemHeight = 20;
    int visibleItems = 3;
    int totalItems = list.size();
    static float posittionY = 0;
    static int scrollOffset = 0;
    static bool textboarderflag = false;
    LinkedList<T> temp_list;
    static int loop = 0;

    string typestatus;
    typestatus = "waiting";
    //if (typedoctor == "detail") typestatus = "processing";

    Node<T>* temp = list.get_head();
    while (temp) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() &&
            temp->data.get_status_checking() == typestatus && temp->data.get_priority() == 1) {
            T needadd = temp->data;
            temp_list.add(needadd);
        }
        temp = temp->next;
    }
    temp = list.get_head();
    while (temp) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() &&
            temp->data.get_status_checking() == typestatus && temp->data.get_priority() == 2) {
            T needadd = temp->data;
            temp_list.add(needadd);
        }
        temp = temp->next;
    }
    temp = list.get_head();
    while (temp) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() &&
            temp->data.get_status_checking() == typestatus && temp->data.get_priority() == 3) {
            T needadd = temp->data;
            temp_list.add(needadd);
        }
        temp = temp->next;
    }
    temp = list.get_head();
    while (temp) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() &&
            temp->data.get_status_checking() == "processing") {
            T needadd = temp->data;
            temp_list.add(needadd);
        }
        temp = temp->next;
    }



    static Node<T>* ChoseNode;
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        ErrorWindow("Cannot load font file!");
    }

    Node<T>* forlenght = list.get_head();

    sf::RectangleShape box;
    box.setSize(sf::Vector2f(float((forlenght->data.setheader()).size()) * 8, itemHeight));
    box.setFillColor(sf::Color::Blue);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Blue);

    Button expand("Expand", 800, 195, 80, 50, sf::Color(135, 206, 235), sf::Color::White);
    Button Checking(" ", 600, 195, 80, 50, sf::Color(135, 206, 235), sf::Color::Black);
    Button ListRecord("List Records of a Patient", 200, 195, 300, 50, sf::Color(135, 206, 235), sf::Color::Black);
    if (typedoctor == "general")  Checking.setString("Checking");
    if (typedoctor == "detail")  Checking.setString("Testing");

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {

            scrollOffset = std::max(scrollOffset - 1, 0);
        }
        else if (event.mouseWheelScroll.delta < 0) {

            scrollOffset = std::min(scrollOffset + 1, totalItems - visibleItems);
        }
    }

    Node<T>* current = temp_list.get_node(scrollOffset);

    if (flag == 1) list.setcolum(window, "records.txt", current);
    for (int i = 0; i < visibleItems; i++) {

        if (current && flag == 1) {
            if (!textboarderflag) box.setPosition(50, 300 + i * (itemHeight));
            if (textboarderflag) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Kiểm tra click vào text
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (expand.isClicked(mousePos)) {
                        ChoseNode->data.display();
                        flag = 1;

                    }
                    if (ListRecord.isClicked(mousePos)) {
                        flag = 2;

                    }
                    if (Checking.isClicked(mousePos)&&current->data.get_status_checking() == typestatus) {
                        flag = 3;
                        loop = 1;

                    }

                }

                ListRecord.draw(window);
                Checking.draw(window);
                expand.draw(window);
                box.setPosition(50, posittionY);
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (!textboarderflag && event.type == sf::Event::MouseButtonPressed) {
                // Kiểm tra click vào ô
                if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    ChoseNode = current;
                    //ID = current->data.get_id();
                    posittionY = 300 + i * (itemHeight);
                    textboarderflag = true;
                }
            }
            if (textboarderflag && event.type == sf::Event::MouseButtonPressed) {
                // Kiểm tra click vào ô
                if (!box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    posittionY = 0;
                    textboarderflag = false;
                }
            }
            if (textboarderflag) {
                window.draw(box);
            }
            current = current->next;
        }
        else {
            break;
        }

    }

    if (flag == 2) {

        search_record_patient(ChoseNode->data.get_id_patient(), window, event);
    }
    if (flag == 3 && typedoctor == "general") {
        checkingscreen(ChoseNode->data.get_id(), ID_doctor, list, window, event);
    }
    if (loop == 1 && flag == 3 && typedoctor == "detail") {
        testscreen(ChoseNode->data.get_id(), ID_doctor);
        loop = 0;
    }



    current = temp_list.get_node(scrollOffset);


    for (int i = 0; i < visibleItems; i++) {
        if (current && flag == 1) {
            sf::Text text;
            text.setFont(font);
            text.setString(current->data.toString());
            if (current->data.get_priority() == 1) text.setFillColor(sf::Color::Red);
            if (current->data.get_priority() == 2) text.setFillColor(sf::Color(255, 165, 0));
            if (current->data.get_priority() == 3) text.setFillColor(sf::Color(0, 0, 139));
            text.setCharacterSize(15.5);
            text.setPosition(50, 300 + i * (itemHeight));
            window.draw(text);
            current = current->next;

        }
    }

}

template <typename T>
int LinkedList<T>::count_patients(long long ID_doctor, const std::string& function, int priority) {
    int count = 0;
    time_t now = time(0);
    tm ltm; // Sử dụng biến tm thay vì con trỏ  
    // Sử dụng localtime_s để lấy thời gian địa phương  
    if (localtime_s(&ltm, &now) == 0) { // localtime_s trả về 0 nếu thành công  
        std::string current_date = std::to_string(1900 + ltm.tm_year) + "-" +
            std::to_string(1 + ltm.tm_mon) + "-" +
            std::to_string(ltm.tm_mday);
        Node<T>* current = head;

        if (current == nullptr) {
            std::cout << "List is empty" << std::endl;
        }
        while (current != nullptr) {
            const T& record = current->data;
            if (record.get_id_doctor() == ID_doctor && !record.get_is_deleted()) {
                if (function == "today") {
                    if (record.get_date().substr(0, 10) == current_date) count++;
                }
                else if (function == "waiting") {
                    if (record.get_status_checking() == "waiting") count++;
                }
                else if (function == "priority") {
                    if (record.get_status_checking() == "waiting" && record.get_priority() == priority) count++;
                }
            }
            current = current->next;
        }
    }
    else {
        std::cerr << "Lỗi khi lấy thời gian địa phương." << std::endl; // Xử lý lỗi  
    }
    return count;
}

template <typename T>
int LinkedList<T>::check_test_having_another_test(long long ID_checking, long long ID_doctor) {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr) {
        // chưa update
        if (current->data.get_id_doctor() == ID_doctor && current->data.get_id() == ID_checking && current->data.get_date() == "0" && !current->data.get_is_having_another_testing()) {
            current->data.update_data();
            return 1;
        }
        current = current->next;
    }
    // update rồi
    return 0;
}

template <typename T>
void LinkedList<T>::display_result_testing(long long ID) const {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "List empty" << endl;
        return;
    }
    while (current != nullptr) {
        // date!= 0 -> has result testing -> doctor(general)-> watch, and update result
        if (current->data.get_id() == ID && current->data.get_date() != "0" && !current->data.get_is_deleted()) {
            current->data.display();
        }
        current = current->next;
    }
}

template <typename T>
int LinkedList<T>::checkExist_updateResult_for_record(long long ID, const string& function) {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr) {
        if (current->data.get_id() == ID) {
            if (function == "check_test_or_not") {
                if (current->data.get_testing_or_not()) return 1;
                else return 0;
            }
            else if (function == "update_result") {
                current->data.update_result_by_doctor();
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}

// kiểm tra xem bác sĩ đó có ID khám đó không
template <typename T>
int LinkedList<T>::check_a_doctor_has_ID_checking(long long ID_checking, long long ID_doctor, const string& function)
{
    Node<T>* current = head;
    if (current == nullptr)
    {
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr)
    {
        if (current->data.get_id() == ID_checking && current->data.get_id_doctor() == ID_doctor && !current->data.get_is_deleted())
        {
            if (function == "check")
                return 1;
            else if (function == "update")
            {
                if (current->data.get_date() == "0")
                {
                    current->data.update_data();
                    return 1;
                }
            }
            else if (function == "check_completed")
            {
                if (current->data.get_status_checking() == "completed")
                {
                    return 1;
                }
            } 
        }
        current = current->next;
    }
    return 0;
}

template <typename T>
int LinkedList<T>::check_doctor_updated_result(long long ID_checking) {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "List empty" << endl;
        return 2;
    }
    while (current != nullptr) {
        // chưa update
        if (current->data.get_id() == ID_checking && current->data.get_date() == "0")
            return 0;

        current = current->next;
    }
    // update rồi
    return 1;
}

//FILE
template <typename T>
void read_data_from_file(LinkedList<T>& list, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        T item;
        item.read_a_object_from_file(line);
        list.add(item);
    }
    file.close();
}

template <typename T>
void read_data_from_file_for_test(LinkedList<T>& list, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        T item;
        item.read_a_object_from_file(line);
        list.add_for_test(item);
    }
    file.close();
}

template <typename T>
void write_data_to_file(LinkedList<T>& list, const string& filename) {
    ofstream file(filename);
    Node<T>* temp = list.get_head();
    while (temp != nullptr) {
        temp->data.write_a_object_to_file(file);
        temp = temp->next;
    }

    file.close();
    cout << "Data was wrote in: " << filename << endl;
}
template <typename T>
int LinkedList<T>::search_check_update_delete_recover_by_id(long long ID, const string& function) {
    Node<T>* current = head;
    if (current == nullptr) {
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr) {
        if (current->data.get_id() == ID) {
            if (function == "search") {
                current->data.display();
                return 1;
            }
            else if ((function == "check") || (function == "update") || (function == "delete")) {
                if (current->data.get_is_deleted() == false) {
                    current->data.display();
                    if (function == "update") current->data.update_data();
                    else if (function == "delete") current->data.update_is_deleted();
                    return 1;
                }
                else {
                    ErrorWindow( "Item don't exist" );
                    return 0;
                }
            }
            else if (function == "recover") {
                if (current->data.get_is_deleted() == true) {
                    current->data.display();
                    current->data.update_is_recovered();
                    return 1;
                }
                else {
                    ErrorWindow( "Item may still not deleted " );
                    return 0;
                }
            }
        }

        current = current->next;
    }
    ErrorWindow( "Item don't exist" );
    return 0;
}


// chung DOCTOR, PATIENT
//template <typename T>
//void module_menu_manage_personal_information(long long ID, LinkedList<T>& list, const string& filename)
//{
//    //read_data_from_file(list, filename);
//    int choice;
//    do
//    {
//        cout << "1. Display your information" << endl
//            << "2. Update your information" << endl
//            << "0. Exit" << endl;
//        cout << "Choose your option: ";
//        cin >> choice;
//        cin.ignore();
//        switch (choice)
//        {
//        case 1:
//        {
//            list.search_check_update_delete_recover_by_id(ID, "check");
//            break;
//        }
//        case 2:
//        {
//            list.search_check_update_delete_recover_by_id(ID, "update");
//            write_data_to_file(list, filename);
//            break;
//        }
//        case 0:
//        {
//        }
//        }
//
//    } while (choice != 0);
//}


#endif
