#include "testing.h"

long long Testing::get_id_patient() {
    LinkedList<Record> record_list;
    read_data_from_file(record_list, "records.txt");
    Node<Record>* temp = record_list.get_head();
    while (temp) {

        if (get_status_checking() == "waiting" && temp->data.get_id() == id_checking) {
            return temp->data.get_id_patient();
        }
        temp = temp->next;
    }
    return 0;
}


void Testing::check_condition_doctor(const string& type) {
    LinkedList<Doctor> doctor_list;
    read_data_from_file(doctor_list, "doctors.txt");
    LinkedList<Testing> testing_list;
    read_data_from_file(testing_list, "testings.txt");
    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = testing_list.count_patients(doctor.get_id(), "today");
        if (doctor.get_specialization() == type && !doctor.get_is_deleted() && patients_today < 65) {
            if (id_doctor2 == 0) {
                this->id_doctor2 = doctor.get_id();
                doctor.update_patients_waiting("increasing");
            }
            else {
                this->id_doctor = doctor.get_id();
                doctor.update_patients_waiting("increasing");
            }
            room = doctor.get_room();
            Testing::cost = doctor.get_price();
        }

        current = current->next;
    }
    write_data_to_file(doctor_list, "doctors.txt");
}

void Testing::set_data(long long ID_checking, const string& type, int priority, const string& part_body) {
    id_doctor2 = 0;
    id_checking = ID_checking;
    this->type = type;
    this->priority = priority;
    this->part_of_body_need_test = part_body;
    status_checking = "waiting";
    check_condition_doctor(type);
    ErrorWindow("ID doctor1: " + to_string(id_doctor) + "\n"
        + "ID doctor2: " + to_string(id_doctor2) + "\n"
        + "At room: " + room);
    // xem bác sĩ khám type đó có tồn tại không, có thỏa mãn điều kiện khám bao nhiêu ca một ngày không
    // thì bác sĩ được gán vào, và tăng số lượng người đang chờ đợi

}

void Testing::update_data() {
    update_start_day();
    status_checking = "processing";

    update_patients_waiting_in_list(get_id_doctor(), "decreasing", get_room());
    Checking::update_result_by_doctor();
}


void Testing::display() const {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Data Display");

    // Define the labels and data to display
    std::vector<std::string> labels = {
        "ID doctor 1:", "ID doctor 2:", "ID checking:", "Priority:", "Room:",
        "Status Testing:", "Start Testing:", "End Testing:", "Result:",
        "Doctor Note:", "Is_deleted:", "Type:", "Test_part_of_body:", "Cost:",
        "Having another test:"
    };

    std::vector<std::string> data = {
        std::to_string(id_doctor),
        std::to_string(id_doctor2),
        std::to_string(id_checking),
        std::to_string(priority),
        room,
        status_checking,
        start_checking,
        end_checking,
        final_result,
        doctor_note,
        (is_deleted ? "Yes" : "No"),
        type,
        part_of_body_need_test,
        std::to_string(cost),
        (is_having_another_testing ? "Yes" : "No")
    };

    // Define positions and sizes for elements
    float startX = 50.0f;
    float startY = 50.0f;
    float labelWidth = 200.0f;
    float boxWidth = 300.0f;
    float boxHeight = 30.0f;
    float spacing = 10.0f;

    std::vector<sf::Text> text;
    std::vector<sf::Text> content;
    std::vector<sf::RectangleShape> boxes;
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        // Handle font loading error
        return;
    }

    // Create TextBox for labels
    for (int i = 0; i < labels.size(); ++i) {
        sf::Text labeltext(labels[i], font, 20);
        labeltext.setFillColor(sf::Color::Black);
        labeltext.setPosition(startX, startY + i * (boxHeight + spacing)); // Vị trí nhãn ID  
        text.push_back(labeltext);
    }

    // Create TextBox for data
    for (int i = 0; i < data.size(); ++i) {
        sf::RectangleShape box;
        box.setSize(sf::Vector2f(boxWidth, boxHeight));
        box.setPosition(startX + labelWidth + spacing + 20, startY + i * (boxHeight + spacing));
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);
        //TextBox dataTextBox(startX + labelWidth + spacing+20, startY + i * (boxHeight + spacing), boxWidth, 9, 20, 30);
        //dataTextBox.setcontent("");
        boxes.push_back(box);
        sf::Text labeltext(data[i], font, 20);
        labeltext.setFillColor(sf::Color::Black);
        labeltext.setPosition(startX + labelWidth + spacing + 25,5+ startY + i * (boxHeight + spacing)); // Vị trí nhãn ID  
        content.push_back(labeltext);
    }

    // Create the OK button
    Button okButton("OK", startX, startY + labels.size() * (boxHeight + spacing) + 20, 100, 40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (okButton.isClicked(sf::Mouse::getPosition(window))) {
                    window.close();
                }
            }
        }

        // Draw everything
        window.clear(sf::Color::White);

        for (int i = 0; i < data.size(); ++i) {
            window.draw(boxes[i]);
            window.draw(content[i]);
        }
        for (auto& text : text) {
            window.draw(text);
        }

        okButton.draw(window);

        window.display();
    }

}

void Testing::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;
    getline(ss, item, ',');
    id_doctor = stoll(item);
    getline(ss, item, ',');
    id_doctor2 = stoll(item);
    // Read and convert id_checking
    getline(ss, item, ',');
    id_checking = stoll(item);
    // Read the rest of the record's data
    getline(ss, type, ',');
    getline(ss, part_of_body_need_test, ',');
    getline(ss, item, ',');
    priority = stoi(item);

    getline(ss, room, ',');
    getline(ss, status_checking, ',');
    getline(ss, start_checking, ',');
    getline(ss, end_checking, ',');
    //có đang thực hiện một test khác hay không
    getline(ss, item, ',');
    is_having_another_testing = (item == "Yes");

    getline(ss, final_result, ',');
    getline(ss, doctor_note, ',');

    getline(ss, item, ',');
    cost = stod(item);

    getline(ss, item, ',');
    is_deleted = (item == "Yes");
}

void Testing::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << id_doctor << ","
            << id_doctor2 << ","
            << id_checking << ","
            << type << ","
            << part_of_body_need_test << ","
            << priority << ","
            << room << ","
            << status_checking << ","
            << start_checking << ","
            << end_checking << ","
            << (is_having_another_testing ? "Yes" : "No") << ","
            << final_result << ","
            << doctor_note << ","
            << cost << ","
            << (is_deleted ? "Yes" : "No") << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}