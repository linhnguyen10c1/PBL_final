#include "patient.h"

long long Patient::set_id = 2000000;

void Patient::set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    ID = set_id++;
    Patient::update_info(window, event, closeflag);
    stringstream ss;
    ss << "patient has ID: " << ID << endl << "password: " << password;
    if (closeflag == 0) ErrorWindow(ss.str());
}

void Patient::update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    static bool loop = true;
    const float startX = 150;
    const float startY = 50;
    int a = 170,
        b = 98,
        c = 90,
        d = 170,
        e = 250,
        f = 98,
        h = 130,
        j = 13 * 8 + 10,
        g = 15;
    const float startX1 = 600;
    const float gapY = 50; // Kho?ng cách gi?a các TextBox


    TextBox nameBox(startX, startY + gapY, a, 20, g);
    TextBox birthdayBox(startX, startY + 2 * gapY, b, 11, g, 30, 1);
    //TextBox genderBox(startX, startY + 3 * gapY, c, 10, g);
    TextBox addressBox(startX, startY + 4 * gapY, d, 20, g);
    TextBox emailBox(startX, startY + 5 * gapY, e, 30, g, 30, 2);
    TextBox phoneBox(startX, startY + 6 * gapY, f, 11, g, 30, 3);

    TextBox allergy(startX1, startY + gapY, h, 15, g);
    TextBox phone_family(startX1, startY + 2 * gapY, j, 13, g, 30, 3);

    Button submitButton("Submit", 400, 500, 100, 50, sf::Color::Blue, sf::Color::White);

    bool shouldClose = false;
    int gen;
    if (gender == "Male") gen = 1;
    if (gender == "Female") gen = 2;
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
            allergy.handleEvent(event);
            phone_family.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (submitButton.isClicked(mousePos)) {
                    if (nameBox.getContent().empty() || birthdayBox.getContent().empty() /*|| genderBox.getContent().empty()*/
                        || addressBox.getContent().empty() || allergy.getContent().empty() || phone_family.getContent().empty()) {
                        ErrorWindow("Please enter both all box."); // C?p nh?t thông báo l?i  
                    }
                    else {

                        name = nameBox.getContent();
                        birthday = birthdayBox.getContent();
                        gender = tickgender(startX, startY + 3 * gapY + 10, gen, window, event);
                        address = addressBox.getContent();
                        email = emailBox.getContent();
                        phone = phoneBox.getContent();
                        //
                        this->allergy = allergy.getContent();
                        this->phone_family = phone_family.getContent();

                        shouldClose = true; // Đóng c?a s? n?u c? hai ô đ? nh?p đ?y đ?
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        //
        textbefore(window, "patient", startX, startY + 7.5f, startX1, gapY);
        if (closeflag == 1 && loop) {
            nameBox.setcontent(name);
            birthdayBox.setcontent(birthday);
            addressBox.setcontent(address);
            emailBox.setcontent(email);
            phoneBox.setcontent(phone);
            allergy.setcontent(this->allergy);
            phone_family.setcontent(this->phone_family);


            loop = false;
        }//this->display(window, event);

        //
        this->gender = tickgender(startX, startY + 3 * gapY + 10, gen, window, event);
        //
        nameBox.update();
        birthdayBox.update();
        //genderBox.update();
        addressBox.update();
        emailBox.update();
        phoneBox.update();
        allergy.update();
        phone_family.update();


        // V? m?i th?
        nameBox.draw(window);
        birthdayBox.draw(window);
        //genderBox.draw(window);
        addressBox.draw(window);
        emailBox.draw(window);
        phoneBox.draw(window);
        //
        allergy.draw(window);
        phone_family.draw(window);
        submitButton.draw(window);
        window.display();
    }
    window.close();
    loop = true;
}

void Patient::update_data() {
    Person::update_password();
}

void Patient::display() const {
    //const float startX = 950;
    //const float startY = 50;
    //int a = 170,
    //    b = 98,
    //    c = 90,
    //    d = 170,
    //    e = 250,
    //    f = 98,
    //    h = 130,
    //    j = 13 * 8 + 10,
    //    g = 15;
    //const float startX1 = 1400;
    //const float gapY = 50; // Kho?ng cách gi?a các TextBox
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
    //sf::Text allergyText(allergy, font, 15);
    //sf::Text phoneFamilyText(phone_family, font, 15);

    //// Cài màu cho các đo?n văn b?n
    //nameText.setFillColor(sf::Color::Blue);
    //birthdayText.setFillColor(sf::Color::Blue);
    //genderText.setFillColor(sf::Color::Blue);
    //addressText.setFillColor(sf::Color::Blue);
    //emailText.setFillColor(sf::Color::Blue);
    //phoneText.setFillColor(sf::Color::Blue);
    //allergyText.setFillColor(sf::Color::Blue);
    //phoneFamilyText.setFillColor(sf::Color::Blue);

    //// Kh?i t?o các TextBox
    //TextBox nameBox(startX, startY + gapY, a, 20, g);
    //TextBox birthdayBox(startX, startY + 2 * gapY, b, 11, g);
    //TextBox genderBox(startX, startY + 3 * gapY, c, 10, g);
    //TextBox addressBox(startX, startY + 4 * gapY, d, 20, g);
    //TextBox emailBox(startX, startY + 5 * gapY, e, 30, g);
    //TextBox phoneBox(startX, startY + 6 * gapY, f, 11, g);

    //TextBox allergyBox(startX1, startY + gapY, h, 15, g);
    //TextBox phoneFamilyBox(startX1, startY + 2 * gapY, j, 13, g);

    //// Đ?t v? trí c?a t?ng text sao cho n?m gi?a các TextBox
    //nameText.setPosition(startX , startY + gapY + g / 2.0f);
    //birthdayText.setPosition(startX , startY + 2 * gapY + g / 2.0f);
    //genderText.setPosition(startX , startY + 3 * gapY + g / 2.0f);
    //addressText.setPosition(startX , startY + 4 * gapY + g / 2.0f);
    //emailText.setPosition(startX , startY + 5 * gapY + g / 2.0f);
    //phoneText.setPosition(startX , startY + 6 * gapY + g / 2.0f);

    //allergyText.setPosition(startX1 , startY + gapY + g / 2.0f);  // C?t 2
    //phoneFamilyText.setPosition(startX1 , startY + 2 * gapY + g / 2.0f); // C?t 2



    //// V? các TextBox lên c?a s?
    //textbefore(window, "patient", startX, startY + 7.5f, startX1, gapY);
    //nameBox.draw(window);
    //birthdayBox.draw(window);
    //genderBox.draw(window);
    //addressBox.draw(window);
    //emailBox.draw(window);
    //phoneBox.draw(window);
    //allergyBox.draw(window);
    //phoneFamilyBox.draw(window);
    //window.draw(nameText);
    //window.draw(birthdayText);
    //window.draw(genderText);
    //window.draw(addressText);
    //window.draw(emailText);
    //window.draw(phoneText);
    //window.draw(allergyText);
    //window.draw(phoneFamilyText);
}
void Patient::show(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        throw std::runtime_error("Không thể tải font!");
    }

    std::vector<std::string> info = {
        "Name: " + name,
        "Birthday: " + birthday,
        "Gender: " + gender,
        "Address: " + address,
        "Email: " + email,
        "Phone: " + phone,
        "Allergy: " + allergy,
        "Phone Family: " + phone_family
    };

    float startX = 400;
    float startY = 200;
    float gapY = 50;
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(400, 420));
    box.setPosition(startX-30, startY-30);
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color::Black);
	window.draw(box);

        for (size_t i = 0; i < info.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(info[i]);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            text.setPosition(startX, startY + i * gapY);
            window.draw(text);
        }
       // window.display();
}

void Patient::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;

    // Read Patient specific data
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

    std::getline(ss, allergy, ',');
    std::getline(ss, phone_family, ',');
}

void Patient::write_a_object_to_file(ofstream& file) {
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
            << allergy << ","
            << phone_family << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}