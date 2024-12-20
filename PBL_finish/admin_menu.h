#pragma once
#ifndef ADMINMENU_H
#define ADMINMEUNU_H

#include "doctor.h"
#include "patient.h"
#include "medicine.h"
#include "record.h"
#include "linklist.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
int flag = 0, flag1 = 0; bool textboarderflag = false;////d=1,,p=2,m=3,mr=4,s=5
static bool show_patient_buttons = false;
static bool show_medicine_buttons = false;
static bool show_testing_buttons = false;

using namespace std;

template <typename T>
void module_menu_admin(sf::RenderWindow& window, sf::Event& event, LinkedList<T>& list, const string& filename) {
	int closeflag = 0;// neu cua so add dong thi khong luu node vao list vaf file
	//sf::Color(70, 130, 180)
	Button Display("Display list objects", 100, 195, 200, 50, sf::Color(100, 180, 220), sf::Color::Black);
	Button Add("Add", 320, 195, 100, 50, sf::Color(100, 180, 220), sf::Color::Black);
	// ??
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(1710, 80));
	shape.setFillColor(sf::Color(200, 200, 200));
	shape.setPosition(50, 180);

	

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (Display.isClicked(mousePos)) {
			flag1 = 1;
		}
		else if (Add.isClicked(mousePos)) {
			string titel;
			if (filename == "doctors.txt") titel = "Add Doctor";
			if (filename == "patients.txt") titel = "Add Patient";
			if (filename == "medicines.txt") titel = "Add Medicine";
			if (filename == "records.txt") titel = "Add Record";
			sf::RenderWindow window1(sf::VideoMode(800, 600), titel);
			T::set_id = list.get_id_from_file();
			T item;
			item.set_data(window1, event, closeflag);
			if (closeflag == 0) { list.add(item); }
			if (closeflag == 0) write_data_to_file(list, filename);
		}
	}

	window.draw(shape);
	if (flag1 == 1) {
		list.display_list(textboarderflag, window, event, list, filename);
	}
	Display.draw(window);
	Add.draw(window);
}

void drawPatientPerMonth(sf::RenderWindow& window, sf::Event& event, LinkedList<Record>& record_list) {
    // Thống kê số lượng bệnh nhân theo tháng
    int monthly_patient[12] = { 0 };

    auto current = record_list.get_head();
    while (current) {
        if (current->data.get_month() >= 1 && current->data.get_month() <= 12) {
            monthly_patient[current->data.get_month() - 1]++;
        }
        current = current->next;
    }

    // Font chữ
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        return;
    }

    // 1. Vẽ bảng ngang
    const int cell_width = 100;  // Chiều rộng của mỗi ô
    const int cell_height = 120; // Chiều cao của mỗi ô
    const int start_x = 80;     // Vị trí bắt đầu theo trục X
    const int start_y = 650;    // Vị trí bắt đầu theo trục Y

    for (int i = 0; i < 12; ++i) {
        // Ô tháng và số bệnh nhân
        sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
        cell.setFillColor(sf::Color::White);
        cell.setOutlineColor(sf::Color::Black);
        cell.setOutlineThickness(2);
        cell.setPosition(start_x + i * cell_width, start_y);
        window.draw(cell);

        // Đường gạch ngang chia tháng và số bệnh nhân
        sf::RectangleShape line(sf::Vector2f(cell_width, 2));
        line.setFillColor(sf::Color::Black);
        line.setPosition(start_x + i * cell_width, start_y + cell_height / 2);
        window.draw(line);

        // Tháng
        sf::Text month_text("Th " + std::to_string(i + 1), font, 15);
        month_text.setFillColor(sf::Color::Black);
        month_text.setPosition(start_x + i * cell_width + 10, start_y + 10);
        window.draw(month_text);

        // Số bệnh nhân
        sf::Text patient_text(std::to_string(monthly_patient[i]), font, 15);
        patient_text.setFillColor(sf::Color::Black);
        patient_text.setPosition(start_x + i * cell_width + 20, start_y + cell_height / 2 + 10);
        window.draw(patient_text);
    }

    // 2. Vẽ đồ thị
    const int graph_start_x = 60;     // Điểm bắt đầu trục X của đồ thị
    const int graph_start_y = 600;   // Điểm bắt đầu trục Y của đồ thị (nằm dưới bảng)
    const int graph_width = 1200;    // Chiều rộng đồ thị (12 tháng)
    const int graph_height = 300;    // Chiều cao đồ thị
    const int max_patients = 1000;  // Số bệnh nhân tối đa để chuẩn hóa trục Y

    // Trục X
    sf::RectangleShape x_axis(sf::Vector2f(graph_width, 2));
    x_axis.setFillColor(sf::Color::Black);
    x_axis.setPosition(graph_start_x, graph_start_y);
    window.draw(x_axis);

    // Trục Y
    sf::RectangleShape y_axis(sf::Vector2f(2, graph_height));
    y_axis.setFillColor(sf::Color::Black);
    y_axis.setPosition(graph_start_x, graph_start_y - graph_height);
    window.draw(y_axis);

    // Vẽ cột trên trục Y (chia thành các khoảng)
    const int y_divisions = 10; // Chia trục Y thành 10 khoảng
    for (int i = 1; i <= y_divisions; ++i) {
        int y = graph_start_y - i * (graph_height / y_divisions);
        int patient_count = i * (max_patients / y_divisions);

        // Nhãn trên trục Y
        sf::Text label(std::to_string(patient_count), font, 12);
        label.setFillColor(sf::Color::Black);
        label.setPosition(graph_start_x - 40, y - 10);
        window.draw(label);

        // Đường kẻ ngang trên đồ thị
        sf::RectangleShape horizontal_line(sf::Vector2f(graph_width, 1));
        horizontal_line.setFillColor(sf::Color(200, 200, 200)); // Màu xám nhạt
        horizontal_line.setPosition(graph_start_x, y);
        window.draw(horizontal_line);
    }

    // Vẽ đường nối giữa các điểm
    sf::VertexArray graph_line(sf::LineStrip, 12);
    for (int i = 0; i < 12; ++i) {
        float x = graph_start_x + i * (graph_width / 12) + (graph_width / 24); // Căn giữa tháng
        float y = graph_start_y - (monthly_patient[i] * graph_height / max_patients);
        graph_line[i].position = sf::Vector2f(x, y);
        graph_line[i].color = sf::Color::Red;
    }
    window.draw(graph_line);

    // Vẽ các điểm trên đồ thị
    for (int i = 0; i < 12; ++i) {
        float x = graph_start_x + i * (graph_width / 12) + (graph_width / 24);
        float y = graph_start_y - (monthly_patient[i] * graph_height / max_patients);

        sf::CircleShape point(5);
        point.setFillColor(sf::Color::Blue);
        point.setPosition(x - 5, y - 5);
        window.draw(point);
    }
}

void thongke(sf::RenderWindow& window, sf::Event& event, LinkedList<Patient>& patient_list, LinkedList<Doctor>& doctor_list,
    LinkedList<Medicine>& medicine_list, LinkedList<Record>& record_list, LinkedList<Testing>& testing_list) {
    // Khởi tạo các nút chính
    
    Button patient_per_month("Patient per month", 60, 150, 200, 50, sf::Color(100, 180, 220), sf::Color::Black);
    

    Button medicine_stock("Medicine stock", 330, 150, 200, 50, sf::Color(100, 180, 220), sf::Color::Black);

    
    Button testing_per_month("Testing per month", 600, 150, 250, 50, sf::Color(100, 180, 220), sf::Color::Black);


	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(1710, 80));
	shape.setFillColor(sf::Color(200, 200, 200));
	shape.setPosition(50, 130);

    // Cờ trạng thái hiển thị
	//static bool show_patient_buttons = false;
	//static bool show_medicine_buttons = false;
	//static bool show_testing_buttons = false;



			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				// Nhấn vào các tab chính
				
				if (patient_per_month.isClicked(mousePos)) {
					show_patient_buttons = true;
					show_medicine_buttons = false;
					show_testing_buttons = false;

					// Đổi màu nút chính
					patient_per_month.setButtonColor(sf::Color(170, 220, 245));
					medicine_stock.setButtonColor(sf::Color(100, 180, 220));
					testing_per_month.setButtonColor(sf::Color(100, 180, 220));
				}
				else if (medicine_stock.isClicked(mousePos)) {
					show_patient_buttons = false;
					show_medicine_buttons = true;
					show_testing_buttons = false;

					medicine_stock.setButtonColor(sf::Color(170, 220, 245));
					patient_per_month.setButtonColor(sf::Color(100, 180, 220));
					testing_per_month.setButtonColor(sf::Color(100, 180, 220));
				}
				else if (testing_per_month.isClicked(mousePos)) {
					show_patient_buttons = false;
					show_medicine_buttons = false;
					show_testing_buttons = true;

					testing_per_month.setButtonColor(sf::Color(170, 220, 245));
					patient_per_month.setButtonColor(sf::Color(100, 180, 220));
					medicine_stock.setButtonColor(sf::Color(100, 180, 220));
				}

			}
	
			window.draw(shape);
			
				// Hiển thị các nút chính
				patient_per_month.draw(window);
				medicine_stock.draw(window);
				testing_per_month.draw(window);
			

				if (show_patient_buttons) {
					medicine_stock.setButtonColor(sf::Color(170, 220, 245));
					drawPatientPerMonth(window, event, record_list);
				}
				else if (show_medicine_buttons) {
					//drawMedicineStock(window, event, medicine_list);
				}
				else if (show_testing_buttons) {
					//drawTestingPerMonth(window, event, testing_list);
				}
			
		
}


void menu_admin(sf::RenderWindow& window) {
	LinkedList<Patient> patient_list;
	LinkedList<Doctor> doctor_list;
	LinkedList<Medicine> medicine_list;
	LinkedList<Record> record_list;
	LinkedList<Testing> testing_list;
	read_data_from_file(doctor_list, "doctors.txt");
	read_data_from_file(patient_list, "patients.txt");
	read_data_from_file(medicine_list, "medicines.txt");
	read_data_from_file(record_list, "records.txt");
	read_data_from_file(testing_list, "testings.txt");
	// 135, 206, 235
	int x = 225, y = 50;
	Button doctor("Manage doctors", 50, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	Button patient("Manage patients", 350, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	Button medicines("Manage medicines", 650, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	Button medical("Manage medical record", 950, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	Button Statistic("Statistic", 1250, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	Button Exit("Exit", 1550, 50, x, y, sf::Color(51, 153, 204), sf::Color::Black);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (doctor.isClicked(mousePos)) {
					flag = 1;
				}
				else if (patient.isClicked(mousePos)) {
					flag = 2;
				}
				else if (medicines.isClicked(mousePos)) {
					flag = 3;
				}
				else if (medical.isClicked(mousePos)) {
					flag = 4;
				}
				else if (Statistic.isClicked(mousePos)) {
					flag = 5;
				}
				else if (Exit.isClicked(mousePos)) {
					return;
				}
			}

			if (flag == 1) { 
				doctor.setButtonColor(sf::Color(170, 220, 245));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(51, 153, 204));
				module_menu_admin(window, event, doctor_list, "doctors.txt"); 
			}
			//Button doctor("Manage doctors", 50, 50, x, y, sf::Color(135, 206, 235), sf::Color::Black);
			if (flag == 2) { 
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(170, 220, 245));
				medicines.setButtonColor(sf::Color(51, 153, 204));
				Statistic.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(51, 153, 204));
				module_menu_admin(window, event, patient_list, "patients.txt");
			}
			if (flag == 3) { 
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(170, 220, 245));
				Statistic.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(51, 153, 204));
				module_menu_admin(window, event, medicine_list, "medicines.txt"); }
			if (flag == 4) { 
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(51, 153, 204));
				Statistic.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(170, 220, 245));
				module_menu_admin(window, event, record_list, "records.txt"); }
			//if (flag == 5) module_menu_admin(window, event, doctor_list, "doctors.txt");
			if (flag == 5) {
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(51, 153, 204));
				Statistic.setButtonColor(sf::Color(170, 220, 245));
				thongke(window, event, patient_list, doctor_list,medicine_list, record_list, testing_list);

			}
		}

		window.clear(sf::Color::White);

		if (flag == 1)module_menu_admin(window, event, doctor_list, "doctors.txt");
		if (flag == 2)module_menu_admin(window, event, patient_list, "patients.txt");
		if (flag == 3) module_menu_admin(window, event, medicine_list, "medicines.txt");
		if (flag == 4) module_menu_admin(window, event, record_list, "records.txt");
		if (flag == 5) thongke(window, event, patient_list, doctor_list, medicine_list, record_list, testing_list);
		//doctor.setButtonColor(sf::Color(135, 206, 235));
		doctor.draw(window);
		patient.draw(window);
		medicines.draw(window);
		medical.draw(window);
		patient.draw(window);
		Statistic.draw(window);
		Exit.draw(window);
		window.display();
	}

}

#endif 
