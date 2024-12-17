#include "support.h"
#include "button.h"
#include <stdexcept>

void ErrorWindow(const std::string& message) {
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "notice", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        throw std::runtime_error("Không thể tải font!");
    }

    sf::Text errorText;
    errorText.setFont(font);
    errorText.setString(message);
    errorText.setCharacterSize(20);
    errorText.setFillColor(sf::Color::Black);
    errorText.setPosition(50, 50);

    Button okButton("OK", 150, 120, 100, 50, sf::Color::Blue, sf::Color::White);

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(errorWindow);
                if (okButton.isClicked(mousePos)) {
                    errorWindow.close();
                }
            }
        }

        errorWindow.clear(sf::Color::White);
        errorWindow.draw(errorText);
        okButton.draw(errorWindow);
        errorWindow.display();
    }
}
string kiem_tra_email(const string& str) {
    regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return regex_match(str, pattern) ? str : "";
}

// Hàm kiểm tra chuỗi có phải chỉ chứa số không
string kiem_tra_chi_so(const string& str) {
    regex pattern(R"(\d+)");
    return regex_match(str, pattern) ? str : "";
}

// Hàm kiểm tra chuỗi có phải dạng ngày-tháng-năm không (dd-mm-yyyy)
string kiem_tra_ngay_thang_nam(const string& str) {
    regex pattern(R"((0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(\d{4}))");
    return regex_match(str, pattern) ? str : "";
}

// Hàm kiểm tra chuỗi có phải chỉ chứa số và số chữ số nằm từ 8 đến 12 không
string kiem_tra_so_chu_so(const string& str) {
    regex pattern(R"(\d{10,10})");
    return regex_match(str, pattern) ? str : "";
}


void searchscreen(long long& ID, int& searchflag) {
    sf::RenderWindow window(sf::VideoMode(400, 400), "search Screen");
    TextBox idBox(120, 80, 200, 10); // Ô nhập ID  
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        return;
    }// Kiểm tra xem font có thể tải hay không  
    sf::Text idLabel("ID:", font, 20);
    idLabel.setFillColor(sf::Color::Black);
    idLabel.setPosition(60, 80); // Vị trí nhãn ID  
    bool shouldClose = false; // Biến đánh dấu trạng thái đóng cửa sổ
    Button search("Search", 80, 220, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);
    while (!shouldClose && window.isOpen()) { // Chỉ đóng khi cần thiết
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                shouldClose = true; // Đánh dấu cửa sổ cần đóng
            }

            idBox.handleEvent(event);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (search.isClicked(mousePos)) {
                    // Kiểm tra xem ID và Password có được nhập đầy đủ không  
                    if (idBox.getContent().empty()) {
                        ErrorWindow("Please enter both ID and Password."); // Cập nhật thông báo lỗi  
                    }
                    else {
                        ID = stoll(idBox.getContent());
                        searchflag = 1;
                        shouldClose = true; // Đóng cửa sổ nếu cả hai ô đã nhập đầy đủ
                    }
                }
            }
        }
        idBox.update();

        window.clear(sf::Color::White);
        window.draw(idLabel); // Vẽ nhãn ID  
        idBox.draw(window); // Vẽ ô nhập ID  
        search.draw(window); // Vẽ nút Login  
        window.display();
    }
    window.close(); // Đóng cửa sổ loginscreen
}

void textbefore(sf::RenderWindow& window, std::string who, const float startX = 100,
    const float startY = 50 + 7.5f, const float startX1 = 400, const float gapY = 50) {
    sf::Font font;
    if (!font.loadFromFile("../Font/consola.ttf")) {
        ErrorWindow("Cannot load font file!");
    }
    for (int i = 1; i <= 10; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(st(header(i, who), 20));
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(15.5);
        text.setPosition(i <= 6 ? startX - 130 : startX1 - 130, startY + (i <= 6 ? i : i - 6) * gapY);
        window.draw(text);
    }
}


std::string tickgender(int x, int y, int z, sf::RenderWindow& window, sf::Event event) {
    static int choseflag = z;
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        ErrorWindow("Cannot load font file!");
    }
    sf::Text maleText("Male", font, 15);
    sf::Text femaleText("Female", font, 15);
    maleText.setPosition(x, y);
    maleText.setFillColor(sf::Color::Black);
    femaleText.setPosition(x + 65, y);
    femaleText.setFillColor(sf::Color::Black);

    // Nút tick (CircleShape)
    sf::CircleShape maleCircle(10);
    sf::CircleShape femaleCircle(10);
    maleCircle.setPosition(x + 40, y); // Vị trí nút Male
    femaleCircle.setPosition(x + 120, y); // Vị trí nút Female
    maleCircle.setOutlineThickness(2);
    femaleCircle.setOutlineThickness(2);
    maleCircle.setOutlineColor(sf::Color::Black);
    femaleCircle.setOutlineColor(sf::Color::Black);
    maleCircle.setFillColor(sf::Color::White);
    femaleCircle.setFillColor(sf::Color::White);

    // Biến lưu trạng thái lựa chọn

    static std::string selectedGender = "";
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Kiểm tra nếu nhấn vào nút Male
        if (maleCircle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            selectedGender = "Male";
            choseflag = 1;
        }

        // Kiểm tra nếu nhấn vào nút Female
        if (femaleCircle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            selectedGender = "Female";
            choseflag = 2;
        }
    }
    if (choseflag == 1) {
        maleCircle.setFillColor(sf::Color::Blue); // Tick chọn Male
        femaleCircle.setFillColor(sf::Color::White); // Bỏ chọn Female}
    }
    if (choseflag == 2) {
        femaleCircle.setFillColor(sf::Color::Blue); // Tick chọn Female
        maleCircle.setFillColor(sf::Color::White); // Bỏ chọn Male
    }

    window.draw(maleText);
    window.draw(femaleText);
    window.draw(maleCircle);
    window.draw(femaleCircle);
    return selectedGender;

}


std::string header(int i, std::string who) {
    if (who == "medicine") { return headerm(i); }
    else if (i == 1) { return "Name:"; }
    else if (i == 2) { return "Birthday:"; }
    else if (i == 3) { return "Gender:"; }
    else if (i == 4) { return "Address:"; }
    else if (i == 5) { return "Email:"; }
    else if (i == 6) { return "Phone:"; }
    else if (who == "doctor") { return headerd(i); }
    else if (who == "patient") { return headerp(i); }
    else if (who == "record") { return headerr(i); }
}

std::string headerd(int i) {
    if (i == 7) { return "Specialization:"; }
    else if (i == 8) { return "Room:"; }
    else if (i == 9) { return "Experience_year:"; }
    else if (i == 10) { return "Price:"; }
    else { return ""; }
}

std::string headerp(int i) {
    if (i == 7) { return "Allergy:"; }
    else if (i == 8) { return "Phone_family:"; }
    else { return ""; }
}

std::string headerm(int i) {
    if (i == 1) { return "Name:"; }
    else if (i == 2) { return "Type:"; }
    else if (i == 3) { return "Usage:"; }
    else if (i == 4) { return "Dosage:"; }
    else if (i == 5) { return "Side_effects:"; }
    else if (i == 6) { return "Warnings:"; }
    else if (i == 7) { return "NSX:"; }
    else if (i == 8) { return "HSD:"; }
    else if (i == 9) { return "Quantity:"; }
    else if (i == 10) { return "Cost"; }
    else { return ""; }
}

std::string headerr(int i) {
    if (i == 1) { return "name:"; }
    else if (i == 2) { return "birthday:"; }
    else if (i == 3) { return "gender:"; }
    else if (i == 4) { return "address:"; }
    else if (i == 5) { return "email:"; }
    else if (i == 6) { return "phone:"; }
    else { return ""; }
}
