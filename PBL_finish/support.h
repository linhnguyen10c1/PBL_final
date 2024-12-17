#ifndef ST_H
#define ST_H
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <SFML/Graphics.hpp>
using namespace std;
// Khai báo hàm
void ErrorWindow(const std::string& message);
string kiem_tra_email(const string& str);
string kiem_tra_chi_so(const string& str);
string kiem_tra_ngay_thang_nam(const string& str);
string kiem_tra_so_chu_so(const string& str);
void textbefore(sf::RenderWindow& window, std::string who, const float startX,
    const float startY, const float startX1, const float gapY);
bool YesNoScreen(const std::string& titel, const std::string& mess);
std::string tickgender(int x, int y, int z, sf::RenderWindow& window, sf::Event event);
std::string header(int i, std::string who);
std::string headerd(int i);
std::string headerp(int i);
std::string headerm(int i);
std::string headerr(int i);


void searchscreen(long long& ID, int& searchflag);
inline std::string st(const std::string& chuoi, int n) {
    int doDaiChuoi = chuoi.length();
    return chuoi + std::string(n - doDaiChuoi, ' ');
}

#endif
