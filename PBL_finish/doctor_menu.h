#ifndef DOCTORMENU_H
#define DOCTORMEUNU_H
#include "linklist.h"
#include "doctor.h"
#include "record.h"
#include "medicine.h"
#include "prescription.h"
#include "testing.h"
#include <SFML/Graphics.hpp>
#include "button.h"


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

// kiểm tra chuyên môn hóa của bác sĩ là gì, để phân ra menu
int check_specialization(long long ID_doctor, LinkedList<Doctor>& doctor_list) {
	Node<Doctor>* current = doctor_list.get_head();
	if (current == nullptr) {
		cout << "List empty" << endl;
		return 0;
	}
	while (current) {
		if (current->data.get_id() == ID_doctor && current->data.get_is_deleted() == false)
			if (current->data.get_specialization() == "General") {
				return 1;
			}
			else return 2;

		current = current->next;
	}
	return 0;
}
void search_record_patient(long long ID_patient, sf::RenderWindow& window1, sf::Event& event1) {
	sf::Font font;
	if (!font.loadFromFile("consola.ttf")) {
		ErrorWindow("Cannot load font file!");
	}
	LinkedList<Record> record_list;
	read_data_from_file(record_list, "records.txt");

	static int loop = 1;
	static LinkedList<Record> temp_list;

	if (loop) {
		Node<Record>* temp = record_list.get_head();
		while (temp) {
			if (temp->data.get_id_patient() == ID_patient && !temp->data.get_is_deleted()) {
				Record needadd = temp->data;
				temp_list.add(needadd);
			}
			temp = temp->next;
		}
	}

	loop = 0;


	int itemHeight = 20;
	int visibleItems = 3;
	int totalItems = record_list.size();
	static float posittionY;
	static int scrollOffset = 0;
	static bool textboarderflag = false;
	static Node<Record>* ChoseNode;

	Node<Record>* forlenght = record_list.get_head();

	sf::RectangleShape box;
	box.setSize(sf::Vector2f(float((forlenght->data.setheader()).size()) * 8, itemHeight));
	box.setFillColor(sf::Color::Blue);
	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Blue);

	Button expand("Expand", 800, 195, 80, 50, sf::Color::Blue, sf::Color::White);

	if (event1.type == sf::Event::MouseWheelScrolled) {
		if (event1.mouseWheelScroll.delta > 0) {

			scrollOffset = std::max(scrollOffset - 1, 0);
		}
		else if (event1.mouseWheelScroll.delta < 0) {

			scrollOffset = std::min(scrollOffset + 1, totalItems - visibleItems);
		}
	}

	Node<Record>* current = temp_list.get_node(scrollOffset);

	record_list.setcolum(window1, "records.txt", current);

	for (int i = 0; i < visibleItems; i++) {

		if (current) {

			if (!textboarderflag) box.setPosition(50, 300 + i * (itemHeight));
			if (textboarderflag) {
				if (event1.type == sf::Event::MouseButtonPressed) {
					// Kiểm tra click vào text
					sf::Vector2i mousePos = sf::Mouse::getPosition(window1);

					if (expand.isClicked(mousePos)) {
						ChoseNode->data.display();

					}
				}

				expand.draw(window1);
				box.setPosition(50, posittionY);
			}

			if (!textboarderflag && event1.type == sf::Event::MouseButtonPressed) {
				// Kiểm tra click vào ô
				if (box.getGlobalBounds().contains(event1.mouseButton.x, event1.mouseButton.y)) {
					ChoseNode = current;
					//ID = current->data.get_id();
					posittionY = 300 + i * (itemHeight);
					textboarderflag = true;
				}
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(window1);
			if (textboarderflag && event1.type == sf::Event::MouseButtonPressed) {
				// Kiểm tra click vào ô
				if (!box.getGlobalBounds().contains(event1.mouseButton.x, event1.mouseButton.y)) {
					posittionY = 0;
					textboarderflag = false;
				}
			}
			if (textboarderflag) {
				window1.draw(box);
			}
			current = current->next;
		}
		else {
			break;
		}

	}
	// ve bang
	current = temp_list.get_node(scrollOffset);
	for (int i = 0; i < visibleItems; i++) {
		if (current) {
			sf::Text text;
			text.setFont(font);
			text.setString(current->data.toString());
			if (current->data.get_priority() == 1) text.setFillColor(sf::Color::Red);
			if (current->data.get_priority() == 2) text.setFillColor(sf::Color(255, 165, 0));
			if (current->data.get_priority() == 3) text.setFillColor(sf::Color(0, 0, 139));
			text.setCharacterSize(15.5);
			text.setPosition(50, 300 + i * (itemHeight));
			window1.draw(text);
			current = current->next;
		}

	}
}
template <typename T>
void display_prescription_screen(
	LinkedList<T>& record_list,
	long long ID_checking,
	long long ID_doctor) {
	LinkedList<Medicine> medicine_list;
	LinkedList<Prescription> prescription_list;
	read_data_from_file(medicine_list, "medicines.txt");
	read_data_from_file(prescription_list, "prescriptions.txt");
	// Kiểm tra điều kiện kê đơn
	if (!record_list.check_a_doctor_has_ID_checking(ID_checking, ID_doctor, "check_completed")) {
		std::cout << "Cannot prescribe medicine. Ensure the examination or testing results are completed first." << std::endl;
		return;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Prescription Screen");

	// Các thành phần giao diện
	TextBox medicineIDBox(100, 50, 200, 20, 15, 40, 4, false);
	TextBox quantityBox(100, 100, 200, 20, 15, 40, 4, false);
	TextBox instructionBox(100, 150, 200, 20, 15, 40, 0, false);

	Button addButton("Add Medicine", 350, 50);
	Button finishButton("Finish Prescription", 350, 150);

	sf::Font font;
	font.loadFromFile("consola.ttf");
	sf::Text prescriptionListText("", font, 15);
	prescriptionListText.setPosition(50, 250);

	sf::Text ID("ID:", font, 15);
	ID.setFillColor(sf::Color::Black);
	ID.setPosition(10, 50);
	sf::Text quantity("quantity:", font, 15);
	quantity.setFillColor(sf::Color::Black);

	quantity.setPosition(10, 100);
	sf::Text instruction("instruction", font, 15);
	instruction.setFillColor(sf::Color::Black);

	instruction.setPosition(10, 150);

	std::vector<std::string> prescriptionDisplay;
	std::string message = "";

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Xử lý input cho TextBox
			medicineIDBox.handleEvent(event);
			quantityBox.handleEvent(event);
			instructionBox.handleEvent(event);

			// Xử lý sự kiện nút
			if (event.type == sf::Event::MouseButtonPressed) {
				if (addButton.isClicked(sf::Mouse::getPosition(window))) {
					long long ID_medicine = std::stoll(medicineIDBox.getContent());
					int quantity = std::stoi(quantityBox.getContent());
					std::string instruction = instructionBox.getContent();
					medicineIDBox.setcontentzero();
					quantityBox.setcontentzero();
					instructionBox.setcontentzero();


					// Kiểm tra thuốc có tồn tại
					if (!medicine_list.search_check_update_delete_recover_by_id(ID_medicine, "check")) {
						message = "Medicine not found. Please try again.";
					}
					else {
						Prescription prescription;
						prescription.set_data(ID_checking, ID_medicine, quantity, instruction, medicine_list);
						prescription_list.add_for_test(prescription);

						prescriptionDisplay.push_back("Medicine ID: " + std::to_string(ID_medicine) +
							", Qty: " + std::to_string(quantity) +
							", Instr: " + instruction);
						message = "Medicine added to the prescription.";
					}
				}

				if (finishButton.isClicked(sf::Mouse::getPosition(window))) {
					write_data_to_file(prescription_list, "prescriptions.txt");
					message = "Prescription saved successfully!";
					window.close();
				}
			}
		}

		// Cập nhật giao diện
		window.clear(sf::Color::White);
		medicineIDBox.update();
		quantityBox.update();
		instructionBox.update();

		// Hiển thị danh sách thuốc
		std::string displayText = "";
		for (const auto& item : prescriptionDisplay) {
			displayText += item + "\n";
		}
		prescriptionListText.setString(displayText);

		// Vẽ các thành phần
		medicineIDBox.draw(window);
		quantityBox.draw(window);
		instructionBox.draw(window);
		addButton.draw(window);
		finishButton.draw(window);
		window.draw(prescriptionListText);
		window.draw(ID);
		window.draw(quantity);
		window.draw(instruction);

		// Hiển thị thông báo
		sf::Text messageText(message, font, 15);
		messageText.setPosition(50, 500);
		window.draw(messageText);

		window.display();
	}
}
template <typename T>
void checkingscreen(long long ID_checking, long long ID_doctor, LinkedList<T>& record_list, sf::RenderWindow& window1, sf::Event& event1) {

	sf::Font font;
	if (!font.loadFromFile("consola.ttf")) {
		ErrorWindow("Cannot load font file!");
	}
	Button general("Checking general", 100, 200, 200, 50, sf::Color::Blue, sf::Color::White);
	Button Result("Result Testing", 100, 300, 200, 50, sf::Color::Blue, sf::Color::White);
	Button Prescription("Prescription", 100, 400, 200, 50, sf::Color::Blue, sf::Color::White);
	Button Appointment("Appointment", 100, 500, 200, 50, sf::Color::Blue, sf::Color::White);

	static sf::Text Message("", font, 20);
	Message.setFillColor(sf::Color::Red);
	Message.setPosition(800, 400);

	if (event1.type == sf::Event::MouseButtonPressed && event1.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window1);

		if (general.isClicked(mousePos)) {

			if (record_list.check_a_doctor_has_ID_checking(ID_checking, ID_doctor, "update"))
			{ // nếu chưa thì ghi vào thì sẽ ghi kết quả bth
				write_data_to_file(record_list, "records.txt");
			}
			else Message.setString("General result updated");
		}

		if (Result.isClicked(mousePos)) {
			LinkedList<Testing> testing_list;
			read_data_from_file_for_test(testing_list, "testings.txt");
			// kiểm tra record có testing hay không
			cout << "1";
			if (record_list.checkExist_updateResult_for_record(ID_checking, "check_test_or_not"))
			{
				// nếu có
				cout << "2";
				cout << ID_checking;
				testing_list.display_result_testing(ID_checking);
				cout << "3";
				// Kiểm tra xem kết quả testing đã được cập nhật bởi bác sĩ test hay chưa
				if (testing_list.check_doctor_updated_result(ID_checking) == 1)
				{
					cout << "4";
					// Cho phép bác sĩ General cập nhật kết quả cho record
					record_list.checkExist_updateResult_for_record(ID_checking, "update_result");
					write_data_to_file(record_list, "records.txt");
					cout << "5";
				}
				else
				{
					Message.setString("Testing results have not been updated by the test doctor yet.");
				}
			}
			else
			{
				Message.setString("This ID checking doesn't have testing.");
			}
		}
		else Message.setString(" ");

		if (Prescription.isClicked(mousePos)) {
			display_prescription_screen(record_list, ID_checking, ID_doctor);
			//long long ID_medicine;
			//LinkedList<Medicine> medicine_list;
			//LinkedList<Prescription> prescription_list;

			// Đọc danh sách thuốc và đơn thuốc từ file
			//read_data_from_file(medicine_list, "medicines.txt");
			//read_data_from_file(prescription_list, "prescriptions.txt");
			
		}

		if (Appointment.isClicked(mousePos)) {

		}

	}

	window1.draw(Message);
	general.draw(window1);
	Result.draw(window1);
	Prescription.draw(window1);
	Appointment.draw(window1);



}

void testscreen(long long ID_checking, long long ID_doctor) {
	LinkedList<Testing> testing_list;
	read_data_from_file_for_test(testing_list, "testings.txt");
	testing_list.check_test_having_another_test(ID_checking, ID_doctor);
	write_data_to_file(testing_list, "testings.txt");
	where(ID_checking, testing_list);
}

void Menu_general_doctor(long long ID_doctor, LinkedList<Record>& record_list, LinkedList<Doctor>& doctor_list, sf::RenderWindow& window) {

	int x = 225, y = 50;
	int flag = 1, flag1 = 1;
	static bool clickflag = false;

	Button WaitingList("Back To Waiting List", 50, 50, x, y, sf::Color(135, 206, 235), sf::Color::Black);

	Button Exit("Exit", 350, 50, x, y, sf::Color(135, 206, 235), sf::Color::Black);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (WaitingList.isClicked(mousePos)) {
					//read_data_from_file(record_list, "records.txt");
					flag = 1;
					flag1 = 1;
					clickflag = true;
				}
				else clickflag = false;


				if (Exit.isClicked(mousePos)) {

					return;
				}

			}
		}
		window.clear(sf::Color::White);

		if (flag == 1) {
			record_list.display_list_waiting("general", clickflag, flag1, ID_doctor, record_list, window, event);
		}
		WaitingList.draw(window);

		Exit.draw(window);
		window.display();
	}
}

void Menu_detail_doctor(long long ID_doctor, LinkedList<Record>& record_list, LinkedList<Doctor>& doctor_list, sf::RenderWindow& window) {
	LinkedList<Testing> testing_list;
	read_data_from_file_for_test(testing_list, "testings.txt");

	int x = 225, y = 50;
	int flag = 1, flag1 = 1;
	static bool clickflag = false;

	Button WaitingList("Back To Waiting List", 50, 50, x, y, sf::Color(135, 206, 235), sf::Color::Black);

	Button Exit("Exit", 350, 50, x, y, sf::Color(135, 206, 235), sf::Color::Black);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (WaitingList.isClicked(mousePos)) {
					//read_data_from_file(record_list, "records.txt");
					flag = 1;
					flag1 = 1;
					clickflag = true;
				}
				else clickflag = false;


				if (Exit.isClicked(mousePos)) {

					return;
				}

			}
		}
		window.clear(sf::Color::White);

		if (flag == 1) {
			testing_list.display_list_waiting("detail", clickflag, flag1, ID_doctor, testing_list, window, event);
		}
		WaitingList.draw(window);

		Exit.draw(window);
		window.display();
	}

	//	case 3: {
	//		long long ID_checking;
	//		bool checking_exists = false;
	//		do {
	//			cout << "Enter checking ID: ";
	//			cin >> ID_checking;
	//			cin.ignore();
	//			// xem lại đoạn này 
	//			// kiểm tra tồn tại, đã được ghi hay chưa, và có đg thực hiện test khác không -> thỏa mãn điều kiện mới update
	//			checking_exists = testing_list.check_test_having_another_test(ID_checking, ID_doctor);

	//			if (checking_exists == 0) {
	//				int choice;
	//				cout << "Checking ID not found or Patient is having another test. Choose an option:" << endl;
	//				cout << "1. Re-enter checking ID" << endl;
	//				cout << "2. Exit" << endl;
	//				cout << "Choose an option: ";
	//				cin >> choice;
	//				cin.ignore();
	//				if (choice == 2) {
	//					return;
	//				}
	//			}

	//		} while (checking_exists == 0);

	//		write_data_to_file(testing_list, "testings.txt");
	//		// sau khi update thì chỉ ra bệnh nhân nên đi đến đâu tiếp theo
	//		where(ID_checking, testing_list);
	//	}
	//	case 0: {

	//	}

	//	}
	//} while (choice != 0);
}


void menu_doctor(long long ID_doctor, sf::RenderWindow& window) {
	LinkedList<Doctor> doctor_list;
	read_data_from_file(doctor_list, "doctors.txt");
	LinkedList<Record> record_list;
	read_data_from_file(record_list, "records.txt");

	Node<Doctor>* current1 = doctor_list.get_head();
	while (current1 && current1->data.get_id() != ID_doctor) {
		current1 = current1->next;
	}
	if (!current1) { ErrorWindow("khong ton tai ID"); }

	Button information("Manage my information", 300, 100, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);
	Button updatepass("Update password", 300, 200, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);
	Button record("Manage medical record", 300, 300, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);
	Button Exit("Exit", 300, 400, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (information.isClicked(mousePos)) {
					int forcallfunction = 1;
					sf::RenderWindow window1(sf::VideoMode(800, 600), "Manage");
					current1->data.update_info(window1, event, forcallfunction);
					if (forcallfunction != 2) write_data_to_file(doctor_list, "doctors.txt");

				}
				if (updatepass.isClicked(mousePos)) {
					current1->data.update_data();
					write_data_to_file(doctor_list, "doctors.txt");
					//searchflag = 1;

				}

				if (record.isClicked(mousePos)) {
					if (check_specialization(ID_doctor, doctor_list) == 1)
					{
						Menu_general_doctor(ID_doctor, record_list, doctor_list, window);
					}
					else if (check_specialization(ID_doctor, doctor_list) == 2)
					{
						Menu_detail_doctor(ID_doctor, record_list, doctor_list, window);
					}

				}

				else if (Exit.isClicked(mousePos)) {
					return;
				}
			}
		}

		window.clear(sf::Color::White);
		information.draw(window);
		updatepass.draw(window);
		record.draw(window);
		Exit.draw(window);
		window.display();
	}

}
#endif
