#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "support.h"
class TextBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    std::string content;
    int typecontent;//=1 neu la ngay thang,=2 neu la emmail,=3neus la so dien thoai,=4 neu chi la so
    bool isActive;
    bool isPassword;
    size_t charLimit;
    sf::Clock cursorClock; // �?ng h? cho con tr? nh?p nh�y
    bool showCursor;

public:

    // Constructor
    TextBox(float x, float y, float width, size_t charLimit, int charactersize = 20, int height = 30,
        int typecontent = 0, bool isPassword = false)
        : isActive(false), isPassword(isPassword), charLimit(charLimit), showCursor(true) {
        this->typecontent = typecontent;
        // Load font
        if (!font.loadFromFile("consola.ttf")) {
            throw std::runtime_error("ERROR FRONT");
        }

        // Setup box
        box.setSize(sf::Vector2f(width, height));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);

        // Setup text
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(charactersize);
        text.setPosition(x + 5, y + 5); // C�n l? trong
    }
    void setcontent(const std::string& ContentOfNode) {
        content += ContentOfNode;
    }
    // X? l? s? ki?n
    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            // Ki?m tra click v�o �
            if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                isActive = true;
                box.setOutlineColor(sf::Color::Blue); // �?i m�u vi?n khi ch?n
            }
            else {
                isActive = false;
                box.setOutlineColor(sf::Color::Black); // �?t l?i m�u vi?n
            }
        }
        if (isActive && event.type == sf::Event::TextEntered) {
            char input = static_cast<char>(event.text.unicode);
            if (input == '\b') { // Backspace
                if (!content.empty())
                    content.pop_back();
            }
            else if (content.size() < charLimit && input >= 32 && input <= 126) {
                content += input;
            }
        }
    }

    // C?p nh?t tr?ng th�i con tr?
    void update() {
        if (isActive) {
            if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
                showCursor = !showCursor;////
                cursorClock.restart();
            }
        }
        else {
            showCursor = false;
        }
    }

    // V? � nh?p
    void draw(sf::RenderWindow& window) {
        window.draw(box);
        //kiem tra hop le
        if (!isActive && typecontent == 1) content = kiem_tra_ngay_thang_nam(content);
        if (!isActive && typecontent == 2) content = kiem_tra_email(content);
        if (!isActive && typecontent == 3) content = kiem_tra_so_chu_so(content);
        if (!isActive && typecontent == 4) content = kiem_tra_chi_so(content);
        // Hi?n th? n?i dung (ho?c d?u *)
        std::string displayText = isPassword ? std::string(content.size(), '*') : content;
        if (isActive && showCursor)
            displayText += '|'; // Hi?n th? con tr?
        text.setString(displayText);
        window.draw(text);
    }

    // L?y n?i dung �? nh?p
    std::string getContent() const {
        return content;
    }
    void setcontentzero() {
        content = "";
    }
};

class Button {
private:
    sf::RectangleShape shape; // H?nh ch? nh?t �?i di?n cho n�t
    sf::Text text;            // V�n b?n tr�n n�t
    sf::Font font;        
public:
    // Constructor v?i tham s? tu? ch?nh
    Button(const std::string& label, float x, float y, float width = 200, float height = 50,
        sf::Color buttonColor = sf::Color(135, 206, 235), sf::Color textColor = sf::Color::Black) {
        // T?i font
        if (!font.loadFromFile("consola.ttf")) {
            throw std::runtime_error("Cannot load font file!");
        }

        // Thi?t l?p v�n b?n
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(17);
        text.setFillColor(textColor);

        // C�n ch?nh v�n b?n ? gi?a n�t
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);

        // Thi?t l?p h?nh ch? nh?t (n�t)
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(buttonColor);
        shape.setPosition(x, y);

        // C�n ch?nh v? tr� c?a v�n b?n v�o gi?a n�t
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    // Ki?m tra n�t c� ��?c nh?n hay kh�ng
    bool isClicked(const sf::Vector2i& mousePos) const {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    // V? n�t ra m�n h?nh
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);
    }

    // �?i m�u n�t
    void setButtonColor(sf::Color color) {
        shape.setFillColor(color);
    }

    // �?i m�u ch?
    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }
    void setString(std::string label) {
        text.setString(label);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);

    }

    // �?i k�ch th�?c n�t
    void setSize(float width, float height) {
        shape.setSize(sf::Vector2f(width, height));

        // C?p nh?t v? tr� v�n b?n
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        text.setPosition(shape.getPosition().x + width / 2.0f,
            shape.getPosition().y + height / 2.0f);
    }

    // �?t l?i v? tr� n�t
    void setPosition(float x, float y) {
        shape.setPosition(x, y);
        text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
    }
};
#endif
