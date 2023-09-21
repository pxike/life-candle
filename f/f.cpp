#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <numeric>
#include <random>

int main()
{
    int w = 900;
    int r = 1;

    sf::RenderWindow window(sf::VideoMode(w, w), "game of life");
    bool isDrawing = false;
    std::vector<sf::RectangleShape> squares;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> diss(0, 1);
    std::uniform_real_distribution<double> dis(0.0, 1.0);  // Generate random double between 0 and 1
    std::vector<std::vector<int>> life((w / r) + 2, std::vector<int>((w / r) + 2));
    sf::RectangleShape square(sf::Vector2f(r, r));
    sf::Vector2f lastPosition;
    sf::Clock clock;
    sf::Clock clock2;
    sf::Vector2i mousePosition;

    for (int i = 0; i < life.size(); i++) {
        for (int j = 0; j < life[i].size(); j++) {
            if (dis(gen) <= 0.1) {
                life[i][j] = 1;
                0.035634;
            }
            else {
                life[i][j] = 0;
            }
        }
    }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDrawing = true;
                    clock.restart();
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDrawing = false;
                }
                break;
            default:
                break;
            }
        }
        window.clear();
        if (isDrawing) {
            mousePosition = sf::Mouse::getPosition(window);
            int xIndex = mousePosition.x / r;
            int yIndex = mousePosition.y / r;
            for (int i = 0; i < 50; i++) {
                for (int j = 0; j < 50; j++) {
                    if (xIndex + i -25 >= 0 && xIndex +i -25 < life.size() && yIndex + j - 25 >= 0 && yIndex + j - 25 < life[xIndex].size() && std::pow(i-25,2) + std::pow(j-25, 2) < std::pow(25, 2)){
                        
                        life[xIndex + i - 25][yIndex + j - 25] = diss(gen);
                    }
                }
            }
            
        }

        

        if (clock.getElapsedTime().asSeconds() >=0 ) {
            std::vector<std::vector<int>> newLife(life);

            for (int i = 1; i < life.size() - 1; i++) {
                for (int j = 1; j < life[i].size() - 1; j++) {
                    int x = life[i - 1][j - 1] + life[i - 1][j] + life[i - 1][j + 1]
                        + life[i][j - 1] + life[i][j + 1]
                        + life[i + 1][j - 1] + life[i + 1][j] + life[i + 1][j + 1];
                    if (x == 3) {
                        newLife[i][j] = 1;
                    }
                    else if (x > 3 || x < 2) {
                        newLife[i][j] = 0;
                    }
                }
            }
            std::swap(life, newLife);
            clock.restart();
        }

        for (int i = 1; i < life.size() - 1; i++) {
            for (int j = 1; j < life[i].size() - 1; j++) {
                if (life[i][j] == 1) {
                    sf::Vector2i m(i * r, j * r);
                    square.setPosition(static_cast<sf::Vector2f>(m));
                    window.draw(square);
                }
            }
        }
        window.display();
    }

    return 0;
}
