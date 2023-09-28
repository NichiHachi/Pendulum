#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include "Point.h"
const int displayX = 1280;
const int displayY = 720;

int main(void){
    int nbrPendulum;
    std::cout << "Number of pendulums :";
    std::cin >> nbrPendulum;
    int length = 0;
    if(nbrPendulum>0){
        length = (displayY/2-20)/nbrPendulum;
    }

    sf::RenderWindow window(sf::VideoMode(displayX,displayY), "Nichi Hachi");
    window.setFramerateLimit(1000);

    sf::Texture backgroundTexture;
    backgroundTexture.create(displayX, displayY);
    sf::Sprite backgroundSprite(backgroundTexture);

    srand (time(NULL));
    float xStart = (rand()%101-50)/100.0;

    std::vector<Point> points;
    points.push_back(Point(sf::Vector2f(displayX/2,displayY/2)));
    points[0].fixe();

    for(int i=1;i<nbrPendulum+1;i++){
        points.push_back(Point(sf::Vector2f(displayX/2+xStart*length*i,displayY/2-length*i)));
    }

    sf::Image background;
    background.create(displayX, displayY, sf::Color::Black);

    sf::Vector2f posLastPoint;    
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }


        posLastPoint = points[nbrPendulum].getPos();
        background.setPixel(posLastPoint.x, posLastPoint.y, sf::Color::Red);
        backgroundTexture.loadFromImage(background);
        window.draw(backgroundSprite);

        for(int i=0;i<nbrPendulum;i++){
            points[i].pendulumUpdate(points[i+1], length);
            points[i].draw(points[i+1], window);
        }

        window.display();
    }
}