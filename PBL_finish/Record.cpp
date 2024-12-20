#include "record.h"

void where(long long ID_checking, LinkedList<Testing>& testing_list) {
    int min_priority_1_patients = INT_MAX;
    int min_total_waiting = INT_MAX;
    Testing* assigned_test = nullptr;
    Node<Testing>* current = testing_list.get_head();
    while (current != nullptr) {
        Testing& testing = current->data;
        if (testing.get_id() == ID_checking && testing.get_status_checking() == "waiting") {
            int priority_1_patients = testing_list.count_patients(testing.get_id_doctor(), "priority", testing.get_priority());
            int total_waiting = testing_list.count_patients(testing.get_id_doctor(), "waiting");
            if (testing.get_priority() == 1) {
                if (priority_1_patients < min_priority_1_patients ||
                    (priority_1_patients == min_priority_1_patients && total_waiting < min_total_waiting)) {
                    min_priority_1_patients = priority_1_patients;
                    min_total_waiting = total_waiting;
                    assigned_test = &testing;
                }
            }
            else {
                if (total_waiting < min_total_waiting || (total_waiting == min_total_waiting && priority_1_patients < min_priority_1_patients)) {
                    min_total_waiting = total_waiting;
                    min_priority_1_patients = priority_1_patients;
                    assigned_test = &testing;
                }
            }
        }
        current = current->next;
    }
    if (assigned_test == nullptr) {
        ErrorWindow("GO BACK GENERAL DOCTOR");
        return;
    }
    ErrorWindow("You should go to at: " + (*assigned_test).get_room() + " room");
    (*assigned_test).update_data_have_another_testing();
    write_data_to_file(testing_list, "testings.txt");

}
long long Record::set_id = 5000000;
Doctor* assign_doctor(LinkedList<Doctor>& doctor_list, LinkedList<Record>& record_list, int priority) {
    Doctor* assigned_doctor = nullptr;
    int min_priority_1_patients = INT_MAX;
    int min_total_waiting = INT_MAX;

    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = record_list.count_patients(doctor.get_id(), "today");
        if (doctor.get_specialization() == "General"
            && !doctor.get_is_deleted()
            && patients_today < 65) {
            int priority_1_patients = record_list.count_patients(doctor.get_id(), "priority", 1);
            if (priority == 1) {
                if (priority_1_patients < min_priority_1_patients ||
                    (priority_1_patients == min_priority_1_patients && doctor.get_waiting() < min_total_waiting)) {
                    min_priority_1_patients = priority_1_patients;
                    min_total_waiting = doctor.get_waiting();
                    assigned_doctor = &doctor;
                }
            }
            else {
                if (doctor.get_waiting() < min_total_waiting ||
                    (doctor.get_waiting() == min_total_waiting && priority_1_patients < min_priority_1_patients)) {
                    min_total_waiting = doctor.get_waiting();
                    min_priority_1_patients = priority_1_patients;
                    assigned_doctor = &doctor;
                }
            }
        }
        current = current->next;
    }

    return assigned_doctor;
}

void Record::display() const {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Display Screen");

    // Các hằng số chung
    const int textSize = 15;  // Kích thước chữ
    const int padding = 10;   // Khoảng cách lề giữa các TextBox và Text
    const float startX1 = 50; // Cột 1
    const float startX2 = 400; // Cột 2
    const float startX3 = 750; // Cột 3
    const float startY = 50;   // Dòng đầu tiên
    const float gapY = 40;     // Khoảng cách giữa các dòng

    // Chiều rộng tính theo số ký tự
    auto calcWidth = [](int numChars) { return numChars * 8; };

    // Tải font
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        // Hiển thị thông báo lỗi nếu không tải được font
        return;
    }
    sf::Text idPatientText("ID Patient: " + std::to_string(id_patient), font, textSize);
    sf::Text idDoctorText("ID Doctor: " + std::to_string(id_doctor), font, textSize);
    sf::Text idCheckingText("ID Checking: " + std::to_string(id_checking), font, textSize);
    sf::Text priorityText("Priority: " + to_string(priority), font, textSize);
    sf::Text roomText("Room: " + room, font, textSize);
    sf::Text statusCheckingText("Status Checking: " + status_checking, font, textSize);
    string isde = (is_deleted ? "Yes" : "No");
    sf::Text isDeletedText("Is Deleted: " + isde, font, textSize);
    sf::Text startCheckingText("Start Checking: " + start_checking, font, textSize);
    sf::Text endCheckingText("End Checking: " + end_checking, font, textSize);

    sf::Text finalResultText("Final Result: " + final_result, font, textSize);
    sf::Text doctorNoteText("Doctor Note: " + doctor_note, font, textSize);
    sf::Text heartRateText("Heart Rate: " + std::to_string(heart), font, textSize);
    sf::Text bloodPressureText("Blood Pressure: " + std::to_string(blood), font, textSize);
    sf::Text symptomText("Symptom: " + symptom, font, textSize);
    sf::Text diagnosisText("Diagnosis: " + diagnosis, font, textSize);
    sf::Text statusPatientText("Status Patient: " + status_patient, font, textSize);
    string test = (testing_or_not ? "Yes" : "No");
    sf::Text testingOrNotText("Testing or Not: " + test, font, textSize);
    string trans = (transfer_hospital ? "Yes" : "No");
    sf::Text transferHospitalText("Transfer Hospital: " + trans, font, textSize);
    sf::Text statusPaymentText("Status Payment: " + std::to_string(status_payment), font, textSize);
    sf::Text followUpAppointmentText("Follow-up Appointment: " + follow_up_appointment, font, textSize);
    // Chỉnh màu cho các Text thành Blue
    idPatientText.setFillColor(sf::Color::Blue);
    idDoctorText.setFillColor(sf::Color::Blue);
    idCheckingText.setFillColor(sf::Color::Blue);
    priorityText.setFillColor(sf::Color::Blue);
    roomText.setFillColor(sf::Color::Blue);
    statusCheckingText.setFillColor(sf::Color::Blue);
    isDeletedText.setFillColor(sf::Color::Blue);

    startCheckingText.setFillColor(sf::Color::Blue);
    endCheckingText.setFillColor(sf::Color::Blue);
    finalResultText.setFillColor(sf::Color::Blue);
    doctorNoteText.setFillColor(sf::Color::Blue);
    heartRateText.setFillColor(sf::Color::Blue);
    bloodPressureText.setFillColor(sf::Color::Blue);
    symptomText.setFillColor(sf::Color::Blue);

    diagnosisText.setFillColor(sf::Color::Blue);
    statusPatientText.setFillColor(sf::Color::Blue);
    testingOrNotText.setFillColor(sf::Color::Blue);
    transferHospitalText.setFillColor(sf::Color::Blue);
    statusPaymentText.setFillColor(sf::Color::Blue);
    followUpAppointmentText.setFillColor(sf::Color::Blue);


    // Đặt vị trí các Text
    idPatientText.setPosition(startX1+5, 5+startY);
    idDoctorText.setPosition(startX1+5, 5 + startY + gapY * 1);
    idCheckingText.setPosition(startX1+5, 5 + startY + gapY * 2);
    priorityText.setPosition(startX1+5, 5 + startY + gapY * 3);
    roomText.setPosition(startX1+5, 5 + startY + gapY * 4);
    statusCheckingText.setPosition(startX1+5, 5 + startY + gapY * 5);
    isDeletedText.setPosition(startX1+5, 5 + startY + gapY * 6);

    startCheckingText.setPosition(startX2+5, 5 + startY);
    endCheckingText.setPosition(startX2+5, 5 + startY + gapY * 1);
    finalResultText.setPosition(startX1+5, 5 + startY + 11 * gapY);
    doctorNoteText.setPosition(startX1+5, 5 + startY + 12 * gapY);
    heartRateText.setPosition(startX2+5, 5 + startY + gapY * 5);
    bloodPressureText.setPosition(startX2+5, 5 + startY + gapY * 6);
    symptomText.setPosition(startX1+5, 5 + startY + gapY * 8);

    diagnosisText.setPosition(startX1+5, 5 + startY + gapY * 10);
    statusPatientText.setPosition(startX1+5, 5 + startY + gapY * 9);
    testingOrNotText.setPosition(startX3+5, 5 + startY);
    transferHospitalText.setPosition(startX3+5, 5 + startY + gapY);
    statusPaymentText.setPosition(startX3+5, 5 + startY + gapY * 2);
    followUpAppointmentText.setPosition(startX3+5, 5 + startY + gapY * 3);

    // Tạo các TextBox tương ứng
    TextBox idPatientBox(startX1, startY, calcWidth(35), textSize + padding, padding);
    TextBox idDoctorBox(startX1, startY + gapY * 1, calcWidth(35), textSize + padding, padding);
    TextBox idCheckingBox(startX1, startY + gapY * 2, calcWidth(35), textSize + padding, padding);
    TextBox priorityBox(startX1, startY + gapY * 3, calcWidth(18), textSize + padding, padding);
    TextBox roomBox(startX1, startY + gapY * 4, calcWidth(10), textSize + padding, padding);
    TextBox statusCheckingBox(startX1, startY + gapY * 5, calcWidth(35), textSize + padding, padding);
    TextBox isDeletedBox(startX1, startY + gapY * 6, calcWidth(35), textSize + padding, padding);

    TextBox startCheckingBox(startX2, startY, calcWidth(40), textSize + padding, padding);
    TextBox endCheckingBox(startX2, startY + gapY * 1, calcWidth(40), textSize + padding, padding);
    TextBox finalResultBox(startX1, startY + gapY * 11, calcWidth(100), textSize + padding, padding);
    TextBox doctorNoteBox(startX1, startY + gapY * 12, calcWidth(100), textSize + padding, padding);
    TextBox heartRateBox(startX2, startY + gapY * 5, calcWidth(40), textSize + padding, padding);
    TextBox bloodPressureBox(startX2, startY + gapY * 6, calcWidth(40), textSize + padding, padding);
    TextBox symptomBox(startX1, startY + gapY * 8, calcWidth(100), textSize + padding, padding);

    TextBox diagnosisBox(startX1, startY + gapY * 10, calcWidth(100), textSize + padding, padding);
    TextBox statusPatientBox(startX1, startY + gapY * 9, calcWidth(100), textSize + padding, padding);
    TextBox testingOrNotBox(startX3, startY, calcWidth(40), textSize + padding, padding);
    TextBox transferHospitalBox(startX3, startY + gapY, calcWidth(40), textSize + padding, padding);
    TextBox statusPaymentBox(startX3, startY + gapY * 2, calcWidth(40), textSize + padding, padding);
    TextBox followUpAppointmentBox(startX3, startY + gapY * 3, calcWidth(40), textSize + padding, padding);

    Button okButton("OK", 550, 700, 100, 50, sf::Color(170, 220, 245), sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (okButton.isClicked(mousePos)) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::White);

        // Vẽ TextBox và Text
        idPatientBox.draw(window);
        idDoctorBox.draw(window);
        idCheckingBox.draw(window);
        priorityBox.draw(window);
        roomBox.draw(window);
        statusCheckingBox.draw(window);
        isDeletedBox.draw(window);

        startCheckingBox.draw(window);
        endCheckingBox.draw(window);
        finalResultBox.draw(window);
        doctorNoteBox.draw(window);
        heartRateBox.draw(window);
        bloodPressureBox.draw(window);
        symptomBox.draw(window);

        diagnosisBox.draw(window);
        statusPatientBox.draw(window);
        testingOrNotBox.draw(window);
        transferHospitalBox.draw(window);
        statusPaymentBox.draw(window);
        followUpAppointmentBox.draw(window);

        // Vẽ Text
        window.draw(idPatientText);
        window.draw(idDoctorText);
        window.draw(idCheckingText);
        window.draw(priorityText);
        window.draw(roomText);
        window.draw(statusCheckingText);
        window.draw(isDeletedText);

        window.draw(startCheckingText);
        window.draw(endCheckingText);
        window.draw(finalResultText);
        window.draw(doctorNoteText);
        window.draw(heartRateText);
        window.draw(bloodPressureText);
        window.draw(symptomText);

        window.draw(diagnosisText);
        window.draw(statusPatientText);
        window.draw(testingOrNotText);
        window.draw(transferHospitalText);
        window.draw(statusPaymentText);
        window.draw(followUpAppointmentText);

        okButton.draw(window);

        window.display();
    }

    return;

}
void Record::update_info(sf::RenderWindow& window, sf::Event& event, int& value) {
    // Định nghĩa nội dung hàm ở đây
}
void Record::set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    LinkedList<Patient> patient_list;
    LinkedList<Doctor> doctor_list;
    LinkedList<Record> record_list;
    read_data_from_file(doctor_list, "doctors.txt");
    read_data_from_file(patient_list, "patients.txt");
    read_data_from_file(record_list, "records.txt");
    // kiểm tra bệnh nhân đã tồn tại trong danh sách

    bool patient_exists = true;
    int loop = 1;
    id_checking = set_id++;

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        ErrorWindow("Cannot load font file!");
    }

    sf::Text title("", font, 40);
    title.setFillColor(sf::Color::Black);
    title.setPosition(250, 100); // Đặt tiêu đề

    sf::Text Prio("", font, 40);
    Prio.setPosition(250, 100); // Đặt tiêu đề

    sf::Text IDcheck("", font, 20);
    IDcheck.setPosition(200, 180); // Đặt tiêu đề
    IDcheck.setFillColor(sf::Color::Black);

    sf::Text doctorAndroom("", font, 20);
    doctorAndroom.setPosition(200, 200); // Đặt tiêu đề
    doctorAndroom.setFillColor(sf::Color::Black);

    sf::Text IDText("ID:", font, 15);
    IDText.setFillColor(sf::Color::Black);
    IDText.setPosition(275, 205);

    sf::Text errorMessage("", font, 20);
    errorMessage.setFillColor(sf::Color::Red); // Màu cho thông báo lỗi  
    errorMessage.setPosition(530, 200); // Vị trí thông báo lỗi   

    TextBox ID(300, 200, 200, 9, 20, 30, 4);
    Button check("Check", 350, 300, 100, 50, sf::Color::Blue, sf::Color::White);

    Button but1("1", 250, 200, 70, 50, sf::Color::Red, sf::Color::Black);
    Button but2("2", 350, 200, 70, 50, sf::Color(255, 165, 0), sf::Color::Black);
    Button but3("3", 450, 200, 70, 50, sf::Color::Yellow, sf::Color::Black);

    Button ok("OK", 350, 400, 70, 50, sf::Color::Blue, sf::Color::White);
    //bool shouldClose = false; // Biến đánh dấu trạng thái đóng cửa sổ

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                closeflag = 2;
                window.close();
            }

            if (patient_exists) {
                title.setString("Enter patient ID :");

                ID.handleEvent(event);
                ID.draw(window);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (check.isClicked(mousePos)) {
                        if (ID.getContent().empty()) {
                            errorMessage.setString("Please enter ID");
                        }
                        else {
                            Node<Patient>* current = patient_list.get_head();
                            if (current == nullptr) {
                                ErrorWindow("List empty");
                            }
                            while (current != nullptr) {
                                if (stoll(ID.getContent()) == current->data.get_id() && current->data.get_is_deleted() == false) {
                                    id_patient = stoll(ID.getContent());
                                    patient_exists = false;// vấn đề xóa rồi vẫn thêm vào khám được bình thường
                                    break;
                                }
                                current = current->next;
                            }
                            if (patient_exists) errorMessage.setString("Patient ID not found");
                        }
                    }
                }
            }
            if (!patient_exists && priority == 0) { // Trường hợp patient_exists == false
                title.setString("Priority ?");
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (but1.isClicked(mousePos)) priority = 1;
                    //if (but2.isClicked(mousePos)) priority = 2;
                    if (but3.isClicked(mousePos)) priority = 3;
                }
            }
            if (!patient_exists && priority != 0) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (ok.isClicked(mousePos)) {
                        window.close();
                    }
                }

            }
        }

        // Render giao diện
        window.clear(sf::Color::White);
        if (patient_exists) {
            window.draw(title);
            window.draw(IDText);
            ID.update();
            ID.draw(window);
            check.draw(window);
            window.draw(errorMessage);
        }
        if (!patient_exists && priority == 0) {
            window.draw(title);
            but1.draw(window);
            but2.draw(window);
            but3.draw(window);
        }
        if (!patient_exists && priority != 0) {
            if (priority == 1) {
                Prio.setFillColor(sf::Color::Black);
                Prio.setString("Priority: 1");
            }
            if (priority == 2) {
                Prio.setFillColor(sf::Color::Black);
                Prio.setString("Priority: 2");
            }
            if (priority == 3) {
                Prio.setFillColor(sf::Color::Black);
                Prio.setString("Priority: 3");
            }
            window.draw(Prio);

            IDcheck.setString("ID checking:" + to_string(id_checking));
            window.draw(IDcheck);
            Doctor* assigned_doctor = assign_doctor(doctor_list, record_list, priority);
            // Check if a suitable doctor was found
            if (assigned_doctor && loop) {
                id_doctor = assigned_doctor->get_id();
                room = assigned_doctor->get_room();
                assigned_doctor->update_patients_waiting("increasing");
                doctorAndroom.setString("Assigned to doctor ID: " + to_string(id_doctor)
                    + "\nAt room: " + room);
                write_data_to_file(doctor_list, "doctors.txt");
                loop = 0;
            }
            window.draw(doctorAndroom);
            if (!assigned_doctor) {
                ErrorWindow("No suitable doctor found.");
                closeflag = 2;
                window.close();
            }

            ok.draw(window);

        }
        window.display();
    }
    if (closeflag == 2) set_id--;

}

void Record::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;

    // Read and convert id_checking
    std::getline(ss, item, ',');
    id_checking = stoll(item);
    // Read the rest of the record's data
    std::getline(ss, item, ',');
    id_patient = stoll(item);
    std::getline(ss, item, ',');
    id_doctor = stoll(item);
    std::getline(ss, item, ',');
    priority = stoi(item);

    std::getline(ss, room, ',');
    std::getline(ss, status_checking, ',');
    std::getline(ss, start_checking, ',');
    std::getline(ss, end_checking, ',');

    std::getline(ss, item, ',');
    heart = stod(item);
    std::getline(ss, item, ',');
    blood = stod(item);

    std::getline(ss, symptom, ',');
    std::getline(ss, diagnosis, ',');
    std::getline(ss, status_patient, ',');

    //testing or not
    //transfer_hospital or not
    std::getline(ss, item, ',');
    testing_or_not = (item == "Yes");
    std::getline(ss, item, ',');
    transfer_hospital = (item == "Yes");

    std::getline(ss, final_result, ',');
    std::getline(ss, doctor_note, ',');
    std::getline(ss, follow_up_appointment, ',');

    std::getline(ss, item, ',');
    cost = stod(item);
    std::getline(ss, item, ',');
    status_payment = stod(item);
    std::getline(ss, item, ',');
    is_deleted = (item == "Yes");
}

void Record::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << id_checking << ","
            << id_patient << ","
            << id_doctor << ","
            << priority << ","
            << room << ","
            << status_checking << ","
            << start_checking << ","
            << end_checking << ","
            << heart << ","
            << blood << ","
            << symptom << ","
            << diagnosis << ","
            << status_patient << ","
            << (testing_or_not ? "Yes" : "No") << ","
            << (transfer_hospital ? "Yes" : "No") << ","
            << final_result << ","
            << doctor_note << ","
            << follow_up_appointment << ","
            << cost << ","
            << status_payment << ","
            << (is_deleted ? "Yes" : "No") << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}
void Record::update_data() {
    x = 0;
    status_checking = "processing";
    // decreasing?? doctors.txt
    update_patients_waiting_in_list(get_id_doctor(), "decreasing");

    update_start_day();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Patient Information Input");

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        cout << "Lỗi font";
        return;  // Kiểm tra xem font có thể tải hay không  
    }

    // TextBox cho các thuộc tính
    sf::Text heartRateLabel("HeartRate:", font, 20);
    heartRateLabel.setFillColor(sf::Color::Black);
    heartRateLabel.setPosition(50, 50);
    TextBox heartRateBox(50, 100, 300, 3, 20, 30, 4);

    sf::Text bloodPressureLabel("BloodPressure:", font, 20);
    bloodPressureLabel.setFillColor(sf::Color::Black);
    bloodPressureLabel.setPosition(50, 150);
    TextBox bloodPressureBox(50, 200, 300, 3, 20, 30, 4);

    sf::Text symptomLabel("Symptom:", font, 20);
    symptomLabel.setFillColor(sf::Color::Black);
    symptomLabel.setPosition(50, 250);
    TextBox symptomBox(50, 300, 480, 40, 20, 30);

    sf::Text diagnosisLabel("Diagnosis:", font, 20);
    diagnosisLabel.setFillColor(sf::Color::Black);
    diagnosisLabel.setPosition(50, 350);
    TextBox diagnosisBox(50, 400, 480, 40, 20, 30);

    sf::Text statusPatienLabel("StatusPatien:", font, 20);
    statusPatienLabel.setFillColor(sf::Color::Black);
    statusPatienLabel.setPosition(50, 450);
    TextBox statusPatientBox(50, 500, 600, 50, 20, 30);


    // Button cho Testing và Transfer
    Button testingButton("Testing", 400, 50, 150, 50);
    Button transferButton("Transfer", 400, 120, 150, 50);
    Button resultButton("Result", 400, 190, 150, 50);

    // Trạng thái của Testing và Transfer
    testing_or_not = false;
    transfer_hospital = false;



    sf::Text errorMessage("", font, 20);
    errorMessage.setFillColor(sf::Color::Red); // Màu cho thông báo lỗi  
    errorMessage.setPosition(100, 20); // Vị trí thông báo lỗi   

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                status_checking = "waiting";
                start_checking = "0";
                return;
            }

            // Xử lý sự kiện cho các TextBox
            heartRateBox.handleEvent(event);
            bloodPressureBox.handleEvent(event);
            symptomBox.handleEvent(event);
            diagnosisBox.handleEvent(event);
            statusPatientBox.handleEvent(event);

            // Kiểm tra nút Testing
            if (event.type == sf::Event::MouseButtonPressed) {
                if (testingButton.isClicked(sf::Mouse::getPosition(window))) {
                    if (!heartRateBox.getContent().empty() && !bloodPressureBox.getContent().empty() &&
                        !symptomBox.getContent().empty() && !diagnosisBox.getContent().empty() &&
                        !statusPatientBox.getContent().empty()) {
                        testing_or_not = true;
                    }
                    else {
                        // Hiển thị thông báo lỗi
                        errorMessage.setString("Please fill in all the fields before testing!");
                    }
                }

                // Kiểm tra nút Transfer
                if (transferButton.isClicked(sf::Mouse::getPosition(window))) {
                    if (!heartRateBox.getContent().empty() && !bloodPressureBox.getContent().empty() &&
                        !symptomBox.getContent().empty() && !diagnosisBox.getContent().empty() &&
                        !statusPatientBox.getContent().empty()) {
                        transfer_hospital = true;
                    }
                    else {
                        // Hiển thị thông báo lỗi
                        errorMessage.setString("Please fill in all the fields before transferring!");
                    }
                }
                if (resultButton.isClicked(sf::Mouse::getPosition(window))) {
                    if (!heartRateBox.getContent().empty() && !bloodPressureBox.getContent().empty() &&
                        !symptomBox.getContent().empty() && !diagnosisBox.getContent().empty() &&
                        !statusPatientBox.getContent().empty()) {
                        heart = stod(heartRateBox.getContent());
                        blood = stod(bloodPressureBox.getContent());
                        symptom = symptomBox.getContent();
                        diagnosis = diagnosisBox.getContent();
                        status_patient = statusPatientBox.getContent();
                        update_result_by_doctor();
                        return;

                    }
                    else {
                        // Hiển thị thông báo lỗi
                        errorMessage.setString("Please fill in all the fields before result!");
                    }
                }
            }
        }

        // Cập nhật trạng thái TextBox
        heartRateBox.update();
        bloodPressureBox.update();
        symptomBox.update();
        diagnosisBox.update();
        statusPatientBox.update();

        // Xóa màn hình
        window.clear(sf::Color::White);

        // Vẽ các TextBox
        heartRateBox.draw(window);
        bloodPressureBox.draw(window);
        symptomBox.draw(window);
        diagnosisBox.draw(window);
        statusPatientBox.draw(window);

        window.draw(heartRateLabel);
        window.draw(bloodPressureLabel);
        window.draw(symptomLabel);
        window.draw(diagnosisLabel);
        window.draw(statusPatienLabel);

        // Vẽ các Button
        testingButton.draw(window);
        transferButton.draw(window);
        resultButton.draw(window);

        window.draw(errorMessage); // Vẽ thông báo lỗi  

        // Hiển thị nội dung
        window.display();

        // nếu có ấn testing
        if (testing_or_not) {
            heart = stod(heartRateBox.getContent());
            blood = stod(bloodPressureBox.getContent());
            symptom = symptomBox.getContent();
            diagnosis = diagnosisBox.getContent();
            status_patient = statusPatientBox.getContent();

            testing_detail(get_id(), get_priority(), window);
            return;
        }
        
        else if (transfer_hospital) {
            heart = stod(heartRateBox.getContent());
            blood = stod(bloodPressureBox.getContent());
            symptom = symptomBox.getContent();
            diagnosis = diagnosisBox.getContent();
            status_patient = statusPatientBox.getContent();
            status_checking = "completed";
            transfer_hospital = true;
            update_end_day();
            cost = 0;
            return;
        }
    }
    heart = stod(heartRateBox.getContent());
    blood = stod(bloodPressureBox.getContent());
    symptom = symptomBox.getContent();
    diagnosis = diagnosisBox.getContent();
    status_patient = statusPatientBox.getContent();
}



void Record::testing_detail(long long ID_checking, int priority, sf::RenderWindow& window) {
    LinkedList<Testing> testing_list;
    read_data_from_file_for_test(testing_list, "testings.txt");

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        std::cerr << "Could not load font!" << std::endl;
        return;
    }

    // Tạo cửa sổ lớn hơn
    window.create(sf::VideoMode(800, 500), "Testing Detail");

    // TextBox để nhập liệu cho từng phần
    TextBox partBodyInputXray(300, 50, 300, 40, 20);
    TextBox partBodyInputEndoscopy(300, 100, 300, 40, 20);
    TextBox partBodyInputUltrasound(300, 150, 300, 40, 20);

    // Label chung
    sf::Text label("Enter Part of Body:", font, 20);
    label.setFillColor(sf::Color::Black);
    label.setPosition(300, 16);

    // Các checkbox và label
    std::vector<sf::RectangleShape> checkboxes;
    std::vector<sf::Text> labels;
    std::vector<TextBox*> textBoxes; // Danh sách các ô nhập liệu liên quan đến checkbox

    // Tên các loại kiểm tra
    std::vector<std::string> testTypes = { "X-ray", "Endoscopy", "Ultrasound", "Blood and Urine Test", "Electrocardiogram" };
    std::vector<TextBox*> partBodyInputs = { &partBodyInputXray, &partBodyInputEndoscopy, &partBodyInputUltrasound };

    // Tạo checkbox và label
    for (size_t i = 0; i < testTypes.size(); ++i) {
        sf::RectangleShape checkbox(sf::Vector2f(20, 20));
        checkbox.setPosition(100, 50 + i * 50);
        checkbox.setFillColor(sf::Color::White);
        checkbox.setOutlineColor(sf::Color::Black);
        checkbox.setOutlineThickness(2);
        checkboxes.push_back(checkbox);

        sf::Text text(testTypes[i], font, 20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(130, 50 + i * 50);
        labels.push_back(text);

        // Chỉ gắn TextBox cho 3 loại kiểm tra đầu tiên (phần body cần nhập)
        if (i < 3) {
            textBoxes.push_back(partBodyInputs[i]);
        }
        else {
            textBoxes.push_back(nullptr);
        }
    }

    Button Done("Done", 600, 300, 100, 40, sf::Color(135, 206, 235));

    // Trạng thái checkbox
    std::vector<bool> selected(testTypes.size(), false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                status_checking = "waiting";
                start_checking = "0";
                return;
            }

            // Xử lý sự kiện cho từng ô nhập liệu
            for (auto* textBox : partBodyInputs) {
                if (textBox) textBox->handleEvent(event);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (size_t i = 0; i < checkboxes.size(); ++i) {
                    if (checkboxes[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selected[i] = !selected[i];
                        checkboxes[i].setFillColor(selected[i] ? sf::Color::Blue : sf::Color::White);

                        if (selected[i]) {
                            Testing item;
                            std::string partBody = "";
                            if (textBoxes[i]) partBody = textBoxes[i]->getContent();
                            if (item.set_data(ID_checking, testTypes[i], priority, partBody)) {
                                testing_list.add_for_test(item);
                                write_data_to_file(testing_list, "testings.txt");
                                checkboxes[i].setFillColor(selected[i] ? sf::Color::Blue : sf::Color::White);
                            }
                            else {
                                ErrorWindow("Error: Could not add testing item to list.");
                                checkboxes[i].setFillColor(selected[i] ? sf::Color::White : sf::Color::White);
                            }
                        }
                    }


                }
                if (Done.isClicked(mousePos)) {
                    where(ID_checking, testing_list);
                    window.close();
                }
            }

            window.clear(sf::Color::White);

            // Vẽ các phần tử
            window.draw(label);
            for (size_t i = 0; i < checkboxes.size(); ++i) {
                window.draw(checkboxes[i]);
                window.draw(labels[i]);

                if (textBoxes[i]) {
                    textBoxes[i]->update();
                    textBoxes[i]->draw(window);
                }
            }
            Done.draw(window);

            window.display();
        }
    }
}


    //int choice;
    //do
    //{
    //    cout << "1. X-ray" << endl
    //        << "2. Endoscopy" << endl
    //        << "3. Ultrasound" << endl
    //        << "4. Blood and Urine Test" << endl
    //        << "5. Electrocardiogram" << endl
    //        << "0. Exit" << endl;
    //    cout << "Choose your choice: ";
    //    cin >> choice;
    //    cin.ignore();
    //    switch (choice)
    //    {
    //    case 1:
    //    {
    //        string part_body;
    //        cout << "Enter part of body need testing: ";
    //        getline(cin, part_body);
    //        item.set_data(ID_checking, "X-ray", priority, part_body);
    //        testing_list.add_for_test(item);
    //        write_data_to_file(testing_list, "testings.txt");
    //        break;
    //    }
    //    case 2:
    //    {
    //        string part_body;
    //        cout << "Enter part of body need testing: ";
    //        getline(cin, part_body);
    //        item.set_data(ID_checking, "Endoscopy", priority, part_body);
    //        testing_list.add_for_test(item);
    //        write_data_to_file(testing_list, "testings.txt");
    //        break;
    //    }
    //    case 3:
    //    {
    //        string part_body;
    //        cout << "Enter part of body need testing: ";
    //        getline(cin, part_body);
    //        item.set_data(ID_checking, "Ultrasound", priority, part_body);
    //        testing_list.add_for_test(item);
    //        write_data_to_file(testing_list, "testings.txt");
    //        break;
    //    }
    //    case 4:
    //    {
    //        item.set_data(ID_checking, "Blood and Urine Test", priority, "Blood and Urine");
    //        testing_list.add_for_test(item);
    //        write_data_to_file(testing_list, "testings.txt");
    //        break;
    //    }
    //    case 5:
    //    {
    //        item.set_data(ID_checking, "Electrocardiogram", priority, "Heart");
    //        testing_list.add_for_test(item);
    //        write_data_to_file(testing_list, "testings.txt");
    //        break;
    //    }

    //    case 0:
    //    {
    //        break;
    //    }
    //    }

    //} while (choice != 0);
//}

