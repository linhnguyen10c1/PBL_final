#include "checking.h"

long long Checking::set_id = 5000000;
int Checking::x = 0;

void Checking::display() const {
    cout << "ID checking: " << id_checking << ", "
        << "Priority: " << priority << ", "
        << "Room: " << room << ","
        << "Status Checking: " << status_checking << ", "
        << "Start Checking: " << start_checking << ", "
        << "End Checking: " << end_checking << ", "
        << "Result: " << final_result << ", "
        << "Doctor Note: " << doctor_note << ", "
        << "Is_deleted: " << is_deleted << ", ";
}


string get_current_time() {
    time_t now = time(0);
    tm ltm; // S? d?ng bi?n tm thay v? con tr?  
    // S? d?ng localtime_s �? l?y th?i gian �?a ph��ng  
    if (localtime_s(&ltm, &now) == 0) { // localtime_s tr? v? 0 n?u th�nh c�ng  
        return std::to_string(ltm.tm_mday) + "-" +
            std::to_string(1 + ltm.tm_mon) + "-" +
            std::to_string(1900 + ltm.tm_year) + " " +
            std::to_string(ltm.tm_hour) + ":" +
            std::to_string(ltm.tm_min) + ":" +
            std::to_string(ltm.tm_sec);
    }

}

void Checking::update_start_day() {
    start_checking = get_current_time();
}

void Checking::update_end_day() {
    end_checking = get_current_time();
}

// d�nh cho admin n�n �ang l� linklist Record
void Checking::update_is_recovered() {
    if (end_checking != "0") {
        is_deleted = false;
    }
    else {
        ErrorWindow("Please create new record\nbecause patients_waiting\nof a doctor changed");
    }
}

void Checking::update_is_deleted() {
    if (start_checking == "0") {
        is_deleted = true;
        update_patients_waiting_in_list(get_id_doctor(), "decreasing");
    }
    else {
        ErrorWindow("You don't allow delete \nwhen doctor is updating data");
    }
}


void Checking::update_result_by_doctor() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Patient Information Input");

    TextBox resultBox(50, 100, 600, 50, 20, 30);
    TextBox doctorNoteBox(50, 200, 740, 70, 20, 30);

    // Button Completed
    Button completedButton("Completed", 400, 300, 150, 50);

    // Nh?n th�ng b�o
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        throw std::runtime_error("Can load font!");
    }

    sf::Text resultLabel("Result:", font, 18);
    resultLabel.setPosition(50, 70);
    resultLabel.setFillColor(sf::Color::Black);

    sf::Text doctorNoteLabel("Doctor's Note:", font, 18);
    doctorNoteLabel.setPosition(50, 170);
    doctorNoteLabel.setFillColor(sf::Color::Black);

    sf::Text errorMessage("", font, 20);
    errorMessage.setFillColor(sf::Color::Red); // M�u cho th�ng b�o l?i  
    errorMessage.setPosition(100, 20); // V? tr� th�ng b�o l?i   

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return;

            // X? l? s? ki?n cho c�c TextBox
            resultBox.handleEvent(event);
            doctorNoteBox.handleEvent(event);

            // X? l? n�t Completed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (completedButton.isClicked(sf::Mouse::getPosition(window))) {
                    if (!resultBox.getContent().empty() && !doctorNoteBox.getContent().empty()) {
                        window.close(); // ��ng c?a s? khi nh?n Completed
                    }
                    else {
                        errorMessage.setString("Please fill in all fields!");
                    }
                }
            }
        }

        // C?p nh?t tr?ng th�i TextBox
        resultBox.update();
        doctorNoteBox.update();

        // X�a m�n h?nh
        window.clear(sf::Color::White);

        // V? c�c nh?n
        window.draw(resultLabel);
        window.draw(doctorNoteLabel);

        // V? c�c TextBox
        resultBox.draw(window);
        doctorNoteBox.draw(window);

        // V? n�t Completed
        completedButton.draw(window);

        window.draw(errorMessage); // V? th�ng b�o l?i  s

        // Hi?n th? n?i dung
        window.display();
    }
    final_result = resultBox.getContent();

    // Update doctor's note
    doctor_note = doctorNoteBox.getContent();

    // Update status checking to completed
    status_checking = "completed";
    update_end_day();
    cout << "id_doctor: " << get_id_doctor() << endl;
    x += get_price_of_doctor(get_id_doctor());
    cost = x;
}

void update_patients_waiting_in_list(long long ID_doctor, const string& modify, string room) {
    LinkedList<Doctor> doctor_list;
    read_data_from_file(doctor_list, "doctors.txt");
    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        if ((doctor.get_id() == ID_doctor || doctor.get_room() == room) && doctor.get_is_deleted() == false) {
            doctor.update_patients_waiting(modify);
        }
        current = current->next;
    }
    write_data_to_file(doctor_list, "doctors.txt");
}

double get_price_of_doctor(long long ID_doctor) {
    LinkedList<Doctor> doctor_list;
    read_data_from_file(doctor_list, "doctors.txt");
    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        if (doctor.get_id() == ID_doctor && doctor.get_is_deleted() == false) {
            return doctor.get_price();
        }
        current = current->next;
    }
    return 0;
}