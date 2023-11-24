#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include "Category.h"
#include "Item.h"
#include "User.h"
#include "Order.h"
#include "Market.h"
#include <SFML/Graphics.hpp>




int main()
{
    //system("chcp 1251 | cls");
    Market market;
    market.loadShop();

    const int W_WIDTH = 640;
    const int W_HEIGHT = 480;
    const int ROWS = 4;
    const int COLS = 5;

    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), L"Кофейня",
        sf::Style::Default);
    //sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Full",
    //    sf::Style::Fullscreen);
    window.setFramerateLimit(30);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    int textFontSize = (W_WIDTH + W_HEIGHT) / 2 / 26;

    int coord = 0;
    // 0 - категории, 1 - товары, 2 - корзина
    int state = 0;

    int w = W_WIDTH / COLS;
    int h = W_HEIGHT / ROWS;

    Order order;

    Category currentCategory;
    Item currentItem;

    while (window.isOpen()) {
        sf::Color color(205, 130, 76);
        window.clear(color);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                // Проверяем, является ли кнопка мыши правой кнопкой (sf::Mouse::left)
                if (event.mouseButton.button == sf::Mouse::Left) {

                    int x = sf::Mouse::getPosition(window).x / w;
                    int y = sf::Mouse::getPosition(window).y / h;
                    coord = x * ROWS + y;

                    //если нажать на заказ отправит 
                    if (coord == 17) {
                        state = 2;
                    }


                    //отрисовка основного окна с категориями
                    if (state == 0) {
                        state += 1;
                        int index = 0;
                        for (auto const& cat : market.Shop) {
                            if (index == coord) {
                                currentCategory = cat;
                                break;
                            }
                            index++;
                        }
                    }

                    else if (state == 1) {
                        int index = 0;

                        for (auto const& item : currentCategory.Items) {
                            if (index == coord) {
                                currentItem = item;
                                order.Items.push_back(item);
                                break;
                            }
                            index++;
                        }
                    }
                    else if (state == 2) {                                                      //
                        int x = sf::Mouse::getPosition(window).x;
                        int y = sf::Mouse::getPosition(window).y;


                        int lineNamber = (y / (textFontSize * 1.4)) - 2;//определения номера заказа в корзине
                        int index = 0;
                        if (lineNamber < order.Items.size() && x < w * (COLS - 1)) {
                            std::list<Item>::iterator it = order.Items.begin();

                            while (index != lineNamber)
                            {
                                it++;
                                index++;
                            }
                            order.Items.erase(it);
                        }

                        if (x >= 0 && x < w && y >= h * 3 && y <= h * 3.5)
                        {
                            window.setTitle("1");
                            order.DateTime = time(NULL);
                            order.Status = "CARD";
                            order.SaveOrder();
                            order.Clear();
                            state = 0;
                        }
                        else if (x >= w && x < w * 2 && y >= h * 3 && y <= h * 3.5) {                    //  НАЖАТИЕ НА ТРИ КНОПКИ
                            window.setTitle("2");
                            order.DateTime = time(NULL);
                            order.Status = "CASH";
                            order.SaveOrder();
                            order.Clear();
                            state = 0;
                        }
                        else if (x >= w * 2 && x < w * 3 && y >= h * 3 && y <= h * 3.5) {
                            window.setTitle("3");
                            order.DateTime = time(NULL);
                            order.Status = "CANCEL";
                            order.SaveOrder();
                            order.Clear();
                            state = 0;

                        }
                    }
                    //если нажать на назад отправит 
                    if (coord == 19) {
                        state = 0;

                    }

                    //window.setTitle("Coord = " + 
                    //    std::to_string(coord));
                }
            }
        }

        // dynbot.ru/files/shop.zip
        text.setCharacterSize(textFontSize);  //размер шрифта
        text.setFillColor(sf::Color::Black);
        int x = 0, y = 0;

        if (state == 0) {
            for (auto const& cat : market.Shop) {
                sf::String title = sf::String::fromUtf8(
                    cat.Title.begin(), cat.Title.end());
                title.replace(" ", "\n");
                text.setString(title);
                text.setPosition(x * w + 20, y++ * h + 35);
                if (y == ROWS) { x++; y = 0; }
                window.draw(text);
            }
        }
        else if (state == 1) {
            
            for (auto const& item : currentCategory.Items) {
                sf::String title = sf::String::fromUtf8(
                    item.Title.begin(), item.Title.end());
                title.replace(" ", "\n");
                text.setString(title);
                text.setPosition(x * w + 20, y++ * h + 35);
                if (y == ROWS) { x ++; y=0; }
                window.draw(text);
            }
            //отрисовка кнопки назад
            text.setString(L"НАЗАД");
            text.setPosition(W_WIDTH - w + 20, W_HEIGHT - h + 20);
            window.draw(text);
        }
        else if (state == 2) {
            //отрисовка корзины
            text.setString(L"Корзина");
            text.setPosition(w/2,20);
            window.draw(text);
            int index = 1;
            for (auto const& item : order.Items) {
                sf::String title = sf::String::fromUtf8(
                    item.Title.begin(), item.Title.end());
                title = std::to_string(index) + "." + title + "-";
                title += std::to_string(item.Price);
                text.setString(title);
                text.setPosition(w / 2, 20 + index * textFontSize*1.4);
                window.draw(text);
                index++;
            }


            //отрисовка первой   кнопки
            sf::RectangleShape button1(sf::Vector2f(w, h/2));                               //
            button1.setPosition(0, h *3);
            button1.setFillColor(sf::Color::Blue);
            text.setString(L"картой");
            text.setPosition(textFontSize, h * 3+ textFontSize/2 );
            window.draw(button1);
            window.draw(text);
            //отрисовка второй кнопки
            sf::RectangleShape button2(sf::Vector2f(w, h/2));
            button2.setPosition(w, h * 3);                                                 //   ОТРИСОВКА 3х КНОПОК
            button2.setFillColor(sf::Color::Green);
            text.setString(L"наличные");
            text.setPosition(w+textFontSize, h * 3 + textFontSize / 2);
            window.draw(button2);
            window.draw(text);
            //отрисовка третей кнопки
            sf::RectangleShape button3(sf::Vector2f(w, h/2));
            button3.setPosition( w*2, h * 3);
            button3.setFillColor(sf::Color::Red);
            text.setString(L"Отмена");
            text.setPosition(w*2+textFontSize, h * 3 + textFontSize / 2);
            window.draw(button3);
            window.draw(text);                                                                 //     
           //отрисовка кнопки назад в корзине
            text.setString(L"НАЗАД");
            text.setPosition(W_WIDTH - w + 20, W_HEIGHT - h + 20);
            window.draw(text);

        }


        if (order.Items.size() > 0) {
            text.setString(std::to_string(order.Items.size()));
            text.setPosition(W_WIDTH - 100, W_HEIGHT / ROWS + 5);
            window.draw(text);
            text.setString(std::to_string(order.GetTotalSum()) + " P");
            text.setPosition(W_WIDTH - 100, W_HEIGHT / ROWS + 35);
            window.draw(text);
        }


        //отрисовка линий если мы не в корзине
        if (state != 2) {
            for (int i = 0; i < W_HEIGHT; i += W_HEIGHT / ROWS) {
                sf::RectangleShape line(sf::Vector2f(W_WIDTH, 1));
                line.setPosition(0, i);
                window.draw(line);
            }
            for (int i = 0; i < W_WIDTH; i += W_WIDTH / COLS) {
                sf::RectangleShape l(sf::Vector2f(W_HEIGHT, 1));
                l.setPosition(i, 0);
                l.rotate(90);
                window.draw(l);
            }
        }
        window.display();
    }






            /*for (auto const& cat : market.Shop){
                std::cout << cat.Title << std::endl;
                for (auto const& item : cat.Items) {
                    std::cout << "|--------" << item.Title << " : " << item.Price << std::endl;

                }
            }

            Order order;
            order.Items.push_back(market.Shop.front().Items.front());

            order.Status = "оплата наличными";
            time_t mytime = time(NULL);
            struct tm* now = localtime(&mytime);*/
            /*Category cat;
            Item item;

            cat.Title = "Горячие напитки";

            item.Title = "Раф сникерс 350 мл";
            item.Price = 250;
            cat.Items.push_back(item);

            User user;
            user.Id = 234;
            user.Login = "ivan";
            user.Name = "Ivan ivanov";
            user.Password = "1234";

            Order order;
            order.Person = user;
            order.Status = "Оплачен картой";
            order.TotalSum = 234;*/
            /*auto t = std::time(nullptr);
            std::tm* now = std::localtime(&t);
            strftime*/

  
}

