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

using namespace std;

template <typename T>
void module_menu_admin(sf::RenderWindow& window, sf::Event& event, LinkedList<T>& list, const string& filename) {
	int closeflag = 0;// neu cua so add dong thi khong luu node vao list vaf file
	//sf::Color(70, 130, 180)
	Button Display("Display list objects", 100, 195, 200, 50, sf::Color(135, 206, 235), sf::Color::Black);
	Button Add("Add", 320, 195, 50, 50, sf::Color(100, 180, 220), sf::Color::Black);
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


void menu_admin(sf::RenderWindow& window) {
	LinkedList<Patient> patient_list;
	LinkedList<Doctor> doctor_list;
	LinkedList<Medicine> medicine_list;
	LinkedList<Record> record_list;
	read_data_from_file(doctor_list, "doctors.txt");
	read_data_from_file(patient_list, "patients.txt");
	read_data_from_file(medicine_list, "medicines.txt");
	read_data_from_file(record_list, "records.txt");
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
				medical.setButtonColor(sf::Color(51, 153, 204));
				module_menu_admin(window, event, patient_list, "patients.txt");
			}
			if (flag == 3) { 
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(170, 220, 245));
				medical.setButtonColor(sf::Color(51, 153, 204));
				module_menu_admin(window, event, medicine_list, "medicines.txt"); }
			if (flag == 4) { 
				doctor.setButtonColor(sf::Color(51, 153, 204));
				patient.setButtonColor(sf::Color(51, 153, 204));
				medicines.setButtonColor(sf::Color(51, 153, 204));
				medical.setButtonColor(sf::Color(170, 220, 245));
				module_menu_admin(window, event, record_list, "records.txt"); }
			//if (flag == 5) module_menu_admin(window, event, doctor_list, "doctors.txt");
		}

		window.clear(sf::Color::White);

		if (flag == 1)module_menu_admin(window, event, doctor_list, "doctors.txt");
		if (flag == 2)module_menu_admin(window, event, patient_list, "patients.txt");
		if (flag == 3) module_menu_admin(window, event, medicine_list, "medicines.txt");
		if (flag == 4) module_menu_admin(window, event, record_list, "records.txt");
		//if (flag == 5) module_menu_admin(window, event, doctor_list, "doctors.txt");
		doctor.setButtonColor(sf::Color(135, 206, 235));
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
