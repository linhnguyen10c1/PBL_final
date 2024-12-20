#include "medicine.h"

long long Medicine::set_id = 4000000;

void Medicine::set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    id_medicine = set_id++;
    update_info(window, event, closeflag);
}

void Medicine::display() const {
    //const float startX = 950;
    //const float startY = 50;
    //int a = 17 * 8 + 10,
    //    b = 10 * 8 + 10,
    //    c = 35 * 8 + 10,
    //    d = 15 * 8 + 10,
    //    e = 35 * 8 + 10,
    //    f = 40 * 8 + 10,
    //    h = 14 * 8 + 10,
    //    j = 4 * 8 + 10,
    //    k = 9 * 8 + 10,
    //    l = 5 * 8 + 10,
    //    g = 15;
    //const float startX1 = 1400;
    //const float gapY = 50; // Kho?ng cách gi?a các TextBox
    //sf::Font font;
    //if (!font.loadFromFile("consola.ttf")) {
    //    ErrorWindow("Cannot load font file!");
    //}
    //sf::Text nameText(name, font, 15);
    //sf::Text typeText(type, font, 15);
    //sf::Text usageText(usage, font, 15);
    //sf::Text dosageText(dosage, font, 15);
    //sf::Text sideEffectsText(side_effects, font, 15);
    //sf::Text warningsText(warnings, font, 15);
    //sf::Text NSXText(NSX, font, 15);
    //sf::Text HSDText(std::to_string(HSD), font, 15);
    //sf::Text quantityText(std::to_string(quantity), font, 15);
    //stringstream ss;ss<< std::fixed << std::setprecision(3) << cost;
    //sf::Text costText(ss.str(), font, 15);

    //// Cài màu cho các ðo?n vãn b?n
    //nameText.setFillColor(sf::Color::Blue);
    //typeText.setFillColor(sf::Color::Blue);
    //usageText.setFillColor(sf::Color::Blue);
    //dosageText.setFillColor(sf::Color::Blue);
    //sideEffectsText.setFillColor(sf::Color::Blue);
    //warningsText.setFillColor(sf::Color::Blue);
    //NSXText.setFillColor(sf::Color::Blue);
    //HSDText.setFillColor(sf::Color::Blue);
    //quantityText.setFillColor(sf::Color::Blue);
    //costText.setFillColor(sf::Color::Blue);

    //// Kh?i t?o các TextBox
    //TextBox nameBox(startX, startY + gapY, a, 17, g);
    //TextBox typeBox(startX, startY + 2 * gapY, b, 10, g);
    //TextBox usageBox(startX, startY + 3 * gapY, c, 30, g);
    //TextBox dosageBox(startX, startY + 4 * gapY, d, 15, g);
    //TextBox sideEffectsBox(startX, startY + 5 * gapY, e, 35, g);
    //TextBox warningsBox(startX, startY + 6 * gapY, f, 40, g);

    //TextBox NSXBox(startX1, startY + gapY, h, 14, g);
    //TextBox HSDBox(startX1, startY + 2 * gapY, j, 4, g);
    //TextBox quantityBox(startX1, startY + 3 * gapY, k, 9, g);
    //TextBox costBox(startX1, startY + 4 * gapY, l, 5, g);

    //// Ð?t v? trí c?a t?ng text sao cho n?m gi?a các TextBox
    //nameText.setPosition(startX , startY + gapY + g / 2.0f);
    //typeText.setPosition(startX , startY + 2 * gapY + g / 2.0f);
    //usageText.setPosition(startX , startY + 3 * gapY + g / 2.0f);
    //dosageText.setPosition(startX , startY + 4 * gapY + g / 2.0f);
    //sideEffectsText.setPosition(startX , startY + 5 * gapY + g / 2.0f);
    //warningsText.setPosition(startX , startY + 6 * gapY + g / 2.0f);

    //NSXText.setPosition(startX1 , startY + gapY + g / 2.0f);  // C?t 2
    //HSDText.setPosition(startX1 , startY + 2 * gapY + g / 2.0f); // C?t 2
    //quantityText.setPosition(startX1 , startY + 3 * gapY + g / 2.0f); // C?t 2
    //costText.setPosition(startX1 , startY + 4 * gapY + g / 2.0f);        // C?t 2

    //textbefore(window, "medicine", startX, startY + 7.5f, startX1, gapY);
    //

    //// V? các TextBox lên c?a s?
    //nameBox.draw(window);
    //typeBox.draw(window);
    //usageBox.draw(window);
    //dosageBox.draw(window);
    //sideEffectsBox.draw(window);
    //warningsBox.draw(window);
    //NSXBox.draw(window);
    //HSDBox.draw(window);
    //quantityBox.draw(window);
    //costBox.draw(window);
    //window.draw(nameText);
    //window.draw(typeText);
    //window.draw(usageText);
    //window.draw(dosageText);
    //window.draw(sideEffectsText);
    //window.draw(warningsText);
    //window.draw(NSXText);
    //window.draw(HSDText);
    //window.draw(quantityText);
    //window.draw(costText);
}

void Medicine::update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag) {
    static bool loop = true;
    const float startX = 150;
    const float startY = 50;
    int a = 17 * 8 + 10,
        b = 10 * 8 + 10,
        c = 35 * 8 + 10,
        d = 15 * 8 + 10,
        e = 35 * 8 + 10,
        f = 40 * 8 + 10,
        h = 14 * 8 + 10,
        j = 4 * 8 + 10,
        k = 9 * 8 + 10,
        l = 5 * 8 + 10,
        g = 15;
    const float startX1 = 600;
    const float gapY = 50; // Kho?ng cách gi?a các TextBox


    TextBox nameBox(startX, startY + gapY, e, 17, g);
    TextBox typeBox(startX, startY + 2 * gapY, e, 10, g);
    TextBox usageBox(startX, startY + 3 * gapY, e, 30, g);
    TextBox dosageBox(startX, startY + 4 * gapY, e, 15, g);
    TextBox side_effectsBox(startX, startY + 5 * gapY, e, 35, g);
    TextBox warningsBox(startX, startY + 6 * gapY, f+240, 40, g);

    TextBox NSX(startX1, startY + gapY, h, 14, g, 30, 1);
    TextBox HSD(startX1, startY + 2 * gapY, h, 4, g, 30, 4);
    TextBox quantity(startX1, startY + 3 * gapY, h, 9, g, 30, 4);
    TextBox cost(startX1, startY + 4 * gapY, h, 5, g, 30, 4);
    Button submitButton("Submit", 400, 500, 100, 50, sf::Color::Blue, sf::Color::Black);

    bool shouldClose = false;

    while (!shouldClose && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                closeflag = 2;
                window.close();
            }
            nameBox.handleEvent(event);
            typeBox.handleEvent(event);
            usageBox.handleEvent(event);
            dosageBox.handleEvent(event);
            side_effectsBox.handleEvent(event);
            warningsBox.handleEvent(event);
            //
            NSX.handleEvent(event);
            HSD.handleEvent(event);
            quantity.handleEvent(event);
            cost.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (submitButton.isClicked(mousePos)) {
                    if (nameBox.getContent().empty() || typeBox.getContent().empty() || usageBox.getContent().empty()
                        || dosageBox.getContent().empty() || side_effectsBox.getContent().empty() || warningsBox.getContent().empty()
                        || NSX.getContent().empty() || HSD.getContent().empty() || quantity.getContent().empty() || cost.getContent().empty()) {
                        ErrorWindow("Please enter both all box."); // C?p nh?t thông báo l?i  
                    }
                    else {

                        name = nameBox.getContent();
                        type = typeBox.getContent();
                        usage = usageBox.getContent();
                        dosage = dosageBox.getContent();
                        side_effects = side_effectsBox.getContent();
                        warnings = warningsBox.getContent();
                        //
                        this->NSX = NSX.getContent();
                        this->HSD = stoi(HSD.getContent());
                        this->quantity = stoi(quantity.getContent());
                        this->cost = stoi(cost.getContent());

                        shouldClose = true; // Ðóng c?a s? n?u c? hai ô ð? nh?p ð?y ð?
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        //
        textbefore(window, "medicine", startX, startY + 7.5f, startX1, gapY);
        if (closeflag == 1 && loop) {
            nameBox.setcontent(name);
            typeBox.setcontent(type);
            usageBox.setcontent(usage);
            dosageBox.setcontent(dosage);
            side_effectsBox.setcontent(side_effects);
            warningsBox.setcontent(this->warnings);
            NSX.setcontent(this->NSX);
            HSD.setcontent(to_string(this->HSD));
            quantity.setcontent(to_string((this->quantity)));
            cost.setcontent(to_string(int(this->cost)));
            loop = false;
        }
        //
        nameBox.update();
        typeBox.update();
        usageBox.update();
        dosageBox.update();
        side_effectsBox.update();
        warningsBox.update();
        NSX.update();
        HSD.update();
        quantity.update();
        cost.update();

        // V? m?i th?
        nameBox.draw(window);
        typeBox.draw(window);
        usageBox.draw(window);
        dosageBox.draw(window);
        side_effectsBox.draw(window);
        warningsBox.draw(window);
        //
        NSX.draw(window);
        HSD.draw(window);
        quantity.draw(window);
        cost.draw(window);
        submitButton.draw(window);
        window.display();
    }
    window.close();
    loop = true;
    //cout << "Enter name: ";
    //std::getline(cin, name);
    //cout << "Enter type: ";
    //std::getline(cin, type);
    //cout << "Enter usage: ";
    //std::getline(cin, usage);
    //cout << "Enter dosage: ";
    //std::getline(cin, dosage);
    //cout << "Enter side side_effects: ";
    //std::getline(cin, side_side_effects);
    //cout << "Enter warnings: ";
    //std::getline(cin, warnings);
    //cout << "Enter NSX: ";
    //std::getline(cin, NSX);
    //cout << "Enter HSD (in months): ";
    //cin >> HSD;
    //cin.ignore();
    //cout << "Enter cost: ";
    //cin >> cost;
    //cin.ignore();
}

void Medicine::update_data() {
    /*int choice;
    do {
        cout << "1. Update Information\n"
            << "2. Update Quantity\n"
            << "3. Exit\n";
        cout << "Choose your option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            update_info(window,event,closeflag);
            cout << "Update successfully" << endl;
            display(window,event);
            cout << "\n";
            break;
        }
        case 2: {
            int x;
            cout << "How many new drugs are imported?: ";
            cin >> x;
            cin.ignore();
            update_quantity(x);
            display(window,event);
            cout << "\n";
            break;
        }
        case 3: {
            break;
        }

        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    } while (choice != 3);*/
}

void Medicine::update_is_deleted() {
    is_deleted = true;
}

void Medicine::update_is_recovered() {
    is_deleted = false;
}


void Medicine::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;

    std::getline(ss, item, ',');
    id_medicine = stoll(item);

    std::getline(ss, name, ',');
    std::getline(ss, type, ',');
    std::getline(ss, usage, ',');
    std::getline(ss, dosage, ',');
    std::getline(ss, side_effects, ',');
    std::getline(ss, warnings, ',');
    std::getline(ss, NSX, ',');

    std::getline(ss, item, ',');
    HSD = stoi(item);

    std::getline(ss, item, ',');
    quantity = stoi(item);

    std::getline(ss, item, ',');
    cost = stod(item);

    std::getline(ss, item, ',');
    is_deleted = (item == "1");
}

void Medicine::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << id_medicine << ","
            << name << ","
            << type << ","
            << usage << ","
            << dosage << ","
            << side_effects << ","
            << warnings << ","
            << NSX << ","
            << HSD << ","
            << quantity << ","
            << cost << ","
            << (is_deleted ? "1" : "0") << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}