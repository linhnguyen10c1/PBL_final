#include "linklist.h"
#include <SFML/Graphics.hpp>
#include "button.h"

void showErrorWindow(const std::string& message) {
    // Tạo cửa sổ thông báo lỗi
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Error", sf::Style::Titlebar | sf::Style::Close);

    // Tải font
    sf::Font font;
    if (!font.loadFromFile("consola.tff")) {
        throw std::runtime_error("Không thể tải font!");
    }

    // Tạo dòng chữ thông báo lỗi
    sf::Text errorText;
    errorText.setFont(font);
    errorText.setString(message);           // Đặt thông báo lỗi
    errorText.setCharacterSize(20);         // Kích thước chữ
    errorText.setFillColor(sf::Color::Black);
    errorText.setPosition(50, 50);          // Vị trí của thông báo

    // Tạo nút "OK"
    Button okButton("OK", 150, 120, 100, 50, sf::Color::Blue, sf::Color::White);

    // Vòng lặp sự kiện của cửa sổ thông báo lỗi
    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            // Đóng cửa sổ khi người dùng nhấn nút "Close"
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
            }

            // Kiểm tra nút "OK" được nhấn
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(errorWindow);
                if (okButton.isClicked(mousePos)) {
                    errorWindow.close(); // Đóng cửa sổ thông báo lỗi
                }
            }
        }

        // Vẽ cửa sổ thông báo
        errorWindow.clear(sf::Color::White); // Màu nền trắng
        errorWindow.draw(errorText);         // Vẽ thông báo lỗi
        okButton.draw(errorWindow);          // Vẽ nút "OK"
        errorWindow.display();               // Hiển thị nội dung
    }
}
