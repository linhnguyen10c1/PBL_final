#include <iostream>
#include "linklist.h"
#include "admin.h"
#include "admin_menu.h"
#include "doctor_menu.h"
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;



template <typename T>
bool is_exist_in_file(long long ID, string password, const string& filename) {
    LinkedList<T> list;
    read_data_from_file(list, filename);
    return list.check_id_password(ID, password);
}
void loginscreen(long long& ID, string& password) {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Login Screen");

    TextBox idBox(120, 80, 200, 9, 20, 30); // Ô nhập ID  
    TextBox passwordBox(120, 130, 200, 18, 20, 30, 0, true); // Ô nhập mật khẩu  

    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        cout << "Error font";
        return;  // Kiểm tra xem font có thể tải hay không  
    }
    sf::Text title("Login", font, 40);
    title.setFillColor(sf::Color::Black);
    title.setPosition(150, 20); // Đặt tiêu đề  

    Button login("LOGIN", 80, 220, 250, 70, sf::Color(135, 206, 235), sf::Color::Black);
    sf::Text errorMessage("", font, 20);
    errorMessage.setFillColor(sf::Color::Red); // Màu cho thông báo lỗi  
    errorMessage.setPosition(50, 300); // Vị trí thông báo lỗi   

    sf::Text idLabel("ID:", font, 20);
    idLabel.setFillColor(sf::Color::Black);
    idLabel.setPosition(85, 80); // Vị trí nhãn ID  

    sf::Text passwordLabel("Password:", font, 20);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setPosition(20, 130); // Vị trí nhãn Password  

    bool shouldClose = false; // Biến đánh dấu trạng thái đóng cửa sổ

    while (!shouldClose && window.isOpen()) { // Chỉ đóng khi cần thiết
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                shouldClose = true; // Đánh dấu cửa sổ cần đóng
            }

            idBox.handleEvent(event);
            passwordBox.handleEvent(event);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (login.isClicked(mousePos)) {
                    // Kiểm tra xem ID và Password có được nhập đầy đủ không  
                    if (idBox.getContent().empty() || passwordBox.getContent().empty()) {
                        errorMessage.setString("Please enter both ID and Password."); // Cập nhật thông báo lỗi  
                    }
                    else {
                        ID = stoll(idBox.getContent());
                        password = passwordBox.getContent();
                        shouldClose = true; // Đóng cửa sổ nếu cả hai ô đã nhập đầy đủ
                    }
                }
            }
        }

        // Cập nhật trạng thái con trỏ  
        idBox.update();
        passwordBox.update();

        window.clear(sf::Color::White);
        window.draw(title); // Vẽ tiêu đề  
        window.draw(idLabel); // Vẽ nhãn ID  
        window.draw(passwordLabel); // Vẽ nhãn Password  
        idBox.draw(window); // Vẽ ô nhập ID  
        passwordBox.draw(window); // Vẽ ô nhập mật khẩu  
        login.draw(window); // Vẽ nút Login  
        window.draw(errorMessage); // Vẽ thông báo lỗi  
        window.display();
    }

    window.close(); // Đóng cửa sổ loginscreen
}



void login()
{
    long long ID;
    string password;
    int x = 250, y = 70;
    sf::RenderWindow window(sf::VideoMode(1800, 800), "app");
    Button admin("ADMINISTRATOR", 300, 100, x, y, sf::Color(135, 206, 235), sf::Color::Black);
    Button doctor("DOCTOR", 300, 200, x, y, sf::Color(135, 206, 235), sf::Color::Black);
    Button patient("PATIENT", 300, 300, x, y, sf::Color(135, 206, 235), sf::Color::Black);
    Button Exit("EXIST", 300, 400, x, y, sf::Color(135, 206, 235), sf::Color::Black);
    while (window.isOpen()) {
        ID = 0;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (admin.isClicked(mousePos)) {
                    loginscreen(ID, password);
                    if (ID) { if (is_exist_in_file<Admin>(ID, password, "admins.txt")) menu_admin(window); }

                }
                if (doctor.isClicked(mousePos)) {
                    loginscreen(ID, password);
                    if (ID) { if (is_exist_in_file<Doctor>(ID, password, "doctors.txt")) menu_doctor(ID, window); }

                }

                else if (Exit.isClicked(mousePos)) {
                    window.close(); // Đóng cửa sổ nếu nhấn nút Exit
                }
            }
        }

        window.clear(sf::Color::White);
        admin.draw(window);
        doctor.draw(window);
        patient.draw(window);
        Exit.draw(window);
        window.display();
    }
    // da xoa code (1)
}


void welcomeScreen() {
    // Tạo cửa sổ chào mừng
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome");

    // Tải font chữ
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        cout << "Lỗi font";
        return;
    }

    // Văn bản chào mừng
    sf::Text welcomeText("Welcome to", font, 40);
    welcomeText.setFillColor(sf::Color::Black);
    welcomeText.setPosition(300, 50); // Đặt văn bản ở gần trên cùng

    sf::Text softwareName("Patient Management Software", font, 40);
    softwareName.setFillColor(sf::Color::Black);
    softwareName.setPosition(150, 100);

    sf::Text developedBy("Developed by: Truong Le Gia An\n              Nguyen Thi Thuy Linh", font, 25);
    developedBy.setFillColor(sf::Color::Black);
    developedBy.setPosition(200, 330);

    sf::Text supervisedBy("Supervised by: Nguyen Van Hieu", font, 25);
    supervisedBy.setFillColor(sf::Color::Black);
    supervisedBy.setPosition(200, 400);

    // Nút "Start"
    Button startButton("START", 300, 480, 200, 60, sf::Color(135, 206, 235), sf::Color::Black);

    // Tải logo từ file
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("../Photo/logo.jpg")) {
        cout << "Lỗi: Không thể tải logo!" << endl;
        return;
    }

    // Tạo sprite cho logo
    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);

    // Đặt kích thước và vị trí cho logo
    sf::Vector2u logoSize = logoTexture.getSize();
    float scaleX = 100.0f / logoSize.x;  // Co giãn logo theo chiều ngang
    float scaleY = 100.0f / logoSize.y;  // Co giãn logo theo chiều dọc
    logoSprite.setScale(scaleX, scaleY); // Áp dụng tỉ lệ
    logoSprite.setPosition(350, 185);    // Đặt logo ở giữa cửa sổ

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.isClicked(mousePos)) {
                    window.close(); // Đóng cửa sổ chào mừng
                    login();        // Chuyển sang cửa sổ login
                }
            }
        }



        window.clear(sf::Color::White);
        window.draw(welcomeText);     // Vẽ dòng chào mừng
        window.draw(softwareName);   // Vẽ tên phần mềm
        window.draw(logoSprite);     // Vẽ logo
        window.draw(developedBy);    // Vẽ dòng Developed by
        window.draw(supervisedBy);   // Vẽ dòng Supervised by
        startButton.draw(window);    // Vẽ nút Start
        window.display();
    }
}



int main() {

    LinkedList<Admin> admin_list;
    Admin ad;
    admin_list.add(ad);
    write_data_to_file(admin_list, "admins.txt");
    welcomeScreen();

}