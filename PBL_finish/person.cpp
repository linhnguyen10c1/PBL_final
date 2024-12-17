#include "person.h"

string Person::generate_random_password(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;  // Seed for the random number engine
    mt19937 generator(rd());  // Mersenne Twister random number engine
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    string password;
    for (int i = 0; i < length; ++i) {
        password += characters[distribution(generator)];
    }

    return password;
}

void Person::set_data(sf::RenderWindow& window, sf::Event& event) {




}

void Person::update_password() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Update password");
    TextBox passwordBox(150, 130, 200, 18, 20, 30);
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        cout << "Lỗi font";
        return;  // Kiểm tra xem font có thể tải hay không  
    }
    Button Update("Update", 80, 220, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);

    sf::Text passwordt("Password:" + password, font, 20);
    passwordt.setFillColor(sf::Color::Black);
    passwordt.setPosition(55, 80); // Vị trí nhãn Password  


    sf::Text passwordLabel("New Password:", font, 20);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setPosition(05, 130); // Vị trí nhãn Password  
    bool shouldClose = false; // Biến đánh dấu trạng thái đóng cửa sổ

    while (!shouldClose && window.isOpen()) { // Chỉ đóng khi cần thiết
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                shouldClose = true; // Đánh dấu cửa sổ cần đóng
            }

            passwordBox.handleEvent(event);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (Update.isClicked(mousePos)) {
                    // Kiểm tra xem ID và Password có được nhập đầy đủ không  
                    if (passwordBox.getContent().empty()) {
                        ErrorWindow("Please enter both ID and Password."); // Cập nhật thông báo lỗi  
                    }
                    else {
                        password = passwordBox.getContent();
                        shouldClose = true; // Đóng cửa sổ nếu cả hai ô đã nhập đầy đủ
                    }
                }
            }
        }

        // Cập nhật trạng thái con trỏ  
        passwordBox.update();

        window.clear(sf::Color::White);
        window.draw(passwordLabel); // Vẽ nhãn Password  
        window.draw(passwordt);
        passwordBox.draw(window); // Vẽ ô nhập mật khẩu  
        Update.draw(window); // Vẽ nút Login  
        window.display();
    }

    window.close(); // Đóng cửa sổ loginscreen
}

void Person::update_is_deleted() {
    is_deleted = true;
}
void Person::update_is_recovered() {
    is_deleted = false;
}

void Person::display_for_out_person(sf::RenderWindow& window, sf::Event& event) const {
    cout << "ID: " << ID
        << ", Full Name: " << name
        //<< "Password: " << password
        << ", Birthday: " << birthday
        << ", Gender: " << gender
        << ", Address: " << address
        << ", Email: " << email
        << ", Phone: " << phone
        << ", Is_deleted: " << is_deleted;
}

