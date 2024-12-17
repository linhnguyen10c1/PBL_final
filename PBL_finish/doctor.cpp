#include "doctor.h"

long long Doctor::set_id = 1000000;

void Doctor::set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    ID = set_id++;
    Doctor::update_info(window, event, closeflag);
    stringstream ss;
    ss << "Doctor has ID: " << ID << endl << "password: " << password;
    if (closeflag == 0) ErrorWindow(ss.str());
}

// ch? m?i thông tin cá nhân thôi
void Doctor::update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    // T?o header v?i c? ch? và v? trí
    static bool loop = true;
    const float startX = 150;
    const float startY = 50;
    int a = 170,
        b = 98,
        c = 90,
        d = 170,
        e = 250,
        f = 98,
        h = 170,
        j = 98,
        k = 90,
        l = 170,
        g = 15;
    const float startX1 = 600;
    const float gapY = 50; // Kho?ng cách gi?a các TextBox


    TextBox nameBox(startX, startY + gapY, a, 20, g);
    TextBox birthdayBox(startX, startY + 2 * gapY, b, 11, g, 30, 1);
    //TextBox genderBox(startX , startY+3*gapY, c, 10, g);
    TextBox addressBox(startX, startY + 4 * gapY, d, 20, g);
    TextBox emailBox(startX, startY + 5 * gapY, e, 30, g, 30, 2);
    TextBox phoneBox(startX, startY + 6 * gapY, f, 11, g, 30, 3);

    TextBox specialization(startX1, startY + gapY, h, 20, g);
    TextBox room(startX1, startY + 2 * gapY, j, 11, g);
    TextBox experience_year(startX1, startY + 3 * gapY, k, 10, g, 30, 4);
    TextBox price(startX1, startY + 4 * gapY, l, 20, g, 30, 4);
    Button submitButton("Submit", 400, 500, 100, 50, sf::Color(170, 220, 245), sf::Color::White);

    bool shouldClose = false;
    int gen;
    cout << gender<<"1";
    if (this->gender == "Male") gen = 1;
    if (this->gender == "Female") gen = 2;
    if (gender != "Male" && gender != "Female") gen = 0;

    while (!shouldClose && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                closeflag = 2;
                window.close();
            }
            nameBox.handleEvent(event);
            birthdayBox.handleEvent(event);
            //genderBox.handleEvent(event);
            addressBox.handleEvent(event);
            emailBox.handleEvent(event);
            phoneBox.handleEvent(event);
            //
            specialization.handleEvent(event);
            room.handleEvent(event);
            experience_year.handleEvent(event);
            price.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (submitButton.isClicked(mousePos)) {
                    if (nameBox.getContent().empty() || birthdayBox.getContent().empty() /*|| genderBox.getContent().empty()*/
                        || addressBox.getContent().empty() || emailBox.getContent().empty() || phoneBox.getContent().empty()
                        || specialization.getContent().empty() || room.getContent().empty() || experience_year.getContent().empty()
                        || price.getContent().empty()) {
                        ErrorWindow("Please enter both all box."); // C?p nh?t thông báo l?i  
                    }
                    else {

                        name = nameBox.getContent();
                        birthday = birthdayBox.getContent();
                        gender = tickgender(startX, startY + 3 * gapY + 10, gen, window, event);//genderBox.getContent();
                        address = addressBox.getContent();
                        email = emailBox.getContent();
                        phone = phoneBox.getContent();
                        //
                        this->specialization = specialization.getContent();
                        this->room = room.getContent();
                        this->experience_year = stoi(experience_year.getContent());
                        this->price = stof(price.getContent());

                        shouldClose = true; // Ðóng c?a s? n?u c? hai ô ð? nh?p ð?y ð?
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        //
        textbefore(window, "doctor", startX, startY + 7.5f, startX1, gapY);
        if (closeflag == 1 && loop) {
            nameBox.setcontent(name);
            birthdayBox.setcontent(birthday);
            addressBox.setcontent(address);
            emailBox.setcontent(email);
            phoneBox.setcontent(phone);
            specialization.setcontent(this->specialization);
            room.setcontent(this->room);
            experience_year.setcontent(to_string(this->experience_year));
            price.setcontent(to_string(int(this->price)));

            loop = false;
        } //this->display(window, event);

        //
        this->gender = tickgender(startX, startY + 3 * gapY + 10, gen, window, event);
        //
        nameBox.update();
        birthdayBox.update();
        //genderBox.update();
        addressBox.update();
        emailBox.update();
        phoneBox.update();
        specialization.update();
        room.update();
        experience_year.update();
        price.update();

        // V? m?i th?
        nameBox.draw(window);
        birthdayBox.draw(window);
        //genderBox.draw(window);
        addressBox.draw(window);
        emailBox.draw(window);
        phoneBox.draw(window);
        //
        specialization.draw(window);
        room.draw(window);
        experience_year.draw(window);
        price.draw(window);
        submitButton.draw(window);
        window.display();
    }
    window.close();
    loop = true;

}

// t?t c? thông tin và password
void Doctor::update_data() {

    Person::update_password();

}

void Doctor::update_patients_waiting(const string& modify) {
    if (modify == "increasing") {
        ++patients_waiting;
    }
    else if (modify == "decreasing" && patients_waiting > 0) {
        --patients_waiting;
    }
}

void Doctor::display() const {
    //sf::RenderWindow& window; sf::Event& event;
    //const float startX = 950;
    //const float startY = 50;
    //int a = 170,
    //    b = 98,
    //    c = 90,
    //    d = 170,
    //    e = 250,
    //    f = 98,
    //    h = 170,
    //    j = 98,
    //    k = 90,
    //    l = 170,
    //    g = 15;
    //const float startX1 = 1400;
    //const float gapY = 50; 
    //sf::Font font;
    //if (!font.loadFromFile("consola.ttf")) {
    //    ErrorWindow("Cannot load font file!");
    //}
    //sf::Text nameText(name, font, 15);
    //sf::Text birthdayText(birthday, font, 15);
    //sf::Text genderText(gender, font, 15);
    //sf::Text addressText(address, font, 15);
    //sf::Text emailText(email, font, 15);
    //sf::Text phoneText(phone, font, 15);
    //sf::Text specializationTextObj(specialization, font, 15);
    //sf::Text roomTextObj(room, font, 15);
    //sf::Text experienceYearTextObj(std::to_string(experience_year), font, 15);
    //sf::Text priceTextObj(std::to_string(price), font, 15);

    //nameText.setFillColor(sf::Color::Blue);
    //birthdayText.setFillColor(sf::Color::Blue);
    //genderText.setFillColor(sf::Color::Blue);
    //addressText.setFillColor(sf::Color::Blue);
    //emailText.setFillColor(sf::Color::Blue);
    //phoneText.setFillColor(sf::Color::Blue);
    //specializationTextObj.setFillColor(sf::Color::Blue);
    //roomTextObj.setFillColor(sf::Color::Blue);
    //experienceYearTextObj.setFillColor(sf::Color::Blue);
    //priceTextObj.setFillColor(sf::Color::Blue);

    //TextBox nameBox(startX, startY + gapY, a, 20, g);
    //TextBox birthdayBox(startX, startY + 2 * gapY, b, 11, g);
    //TextBox genderBox(startX, startY + 3 * gapY, c, 10, g);
    //TextBox addressBox(startX, startY + 4 * gapY, d, 20, g);
    //TextBox emailBox(startX, startY + 5 * gapY, e, 30, g);
    //TextBox phoneBox(startX, startY + 6 * gapY, f, 11, g);

    //TextBox specialization(startX1, startY + gapY, h, 20, g);
    //TextBox room(startX1, startY + 2 * gapY, j, 11, g);
    //TextBox experience_year(startX1, startY + 3 * gapY, k, 10, g);
    //TextBox price(startX1, startY + 4 * gapY, l, 20, g);
    //// Ð?t v? trí c?a t?ng text sao cho n?m gi?a các TextBox
    //nameText.setPosition(startX , startY + gapY + g / 2.0f);
    //birthdayText.setPosition(startX , startY + 2 * gapY + g / 2.0f);
    //genderText.setPosition(startX , startY + 3 * gapY + g / 2.0f);
    //addressText.setPosition(startX , startY + 4 * gapY + g / 2.0f);
    //emailText.setPosition(startX , startY + 5 * gapY + g / 2.0f);
    //phoneText.setPosition(startX, startY + 6 * gapY + g / 2.0f);

    //specializationTextObj.setPosition(startX1 , startY + gapY + g / 2.0f);  // C?t 2
    //roomTextObj.setPosition(startX1 , startY + 2 * gapY + g / 2.0f);         // C?t 2
    //experienceYearTextObj.setPosition(startX1 , startY + 3 * gapY + g / 2.0f); // C?t 2
    //priceTextObj.setPosition(startX1 , startY + 4 * gapY + g / 2.0f);        // C?t 2

    //// V? các ðo?n text lên c?a s?
    //textbefore(window, "doctor", startX, startY+7.5f, startX1, gapY);
    //nameBox.draw(window);
    //birthdayBox.draw(window);
    //genderBox.draw(window);
    //addressBox.draw(window);
    //emailBox.draw(window);
    //phoneBox.draw(window);
    ////
    //specialization.draw(window);
    //room.draw(window);
    //experience_year.draw(window);
    //price.draw(window);

    //window.draw(nameText);
    //window.draw(birthdayText);
    //window.draw(genderText);
    //window.draw(addressText);
    //window.draw(emailText);
    //window.draw(phoneText);
    //window.draw(specializationTextObj);
    //window.draw(roomTextObj);
    //window.draw(experienceYearTextObj);
    //window.draw(priceTextObj);

    //
}

void Doctor::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;

    std::getline(ss, item, ',');
    ID = stoll(item);

    std::getline(ss, name, ',');
    std::getline(ss, password, ',');
    std::getline(ss, birthday, ',');
    std::getline(ss, gender, ',');
    std::getline(ss, address, ',');
    std::getline(ss, email, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, item, ',');
    is_deleted = (item == "1");
    // Read Doctor specific data
    std::getline(ss, specialization, ',');
    std::getline(ss, room, ',');

    std::getline(ss, item, ',');
    experience_year = stoi(item);

    std::getline(ss, item, ',');
    patients_waiting = stoi(item);

    std::getline(ss, item, ',');
    price = stod(item);

}

void Doctor::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << ID << ","
            << name << ","
            << password << ","
            << birthday << ","
            << gender << ","
            << address << ","
            << email << ","
            << phone << ","
            << (is_deleted ? "1" : "0") << ","
            << specialization << ","
            << room << ","
            << experience_year << ","
            << patients_waiting << ","
            << price << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}