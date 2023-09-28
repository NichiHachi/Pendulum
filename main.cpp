#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Point.h"
const int displayX = 720;
const int displayY = 720;

int main(void){
    int nbrPendulum;
    std::cout << "Number of pendulums:";
    std::cin >> nbrPendulum;
    int length = 0;
    if(nbrPendulum>0){
        length = (displayY/2-20)/nbrPendulum;
    }

    sf::RenderWindow window(sf::VideoMode(displayX,displayY), "Nichi Hachi");
    window.setFramerateLimit(500);

    sf::Image background;
    sf::Color backgroundColor(38,6,54,255);
    background.create(displayX, displayY, backgroundColor);

    sf::Image tipPendulum;
    sf::Color tipColor(255,0,0,150);
    tipPendulum.create(6, 6, tipColor);

    sf::Texture backgroundTexture;
    backgroundTexture.create(displayX, displayY);
    sf::Sprite backgroundSprite(backgroundTexture);

    srand (time(NULL));
    float xStart = (rand()%21+35)/100.0;
    if(rand()%2==0){
        xStart = -xStart;
    }

    std::vector<Point> points;
    points.push_back(Point(sf::Vector2f(displayX/2,displayY/2)));
    points[0].fixe();

    for(int i=1;i<nbrPendulum+1;i++){
        points.push_back(Point(sf::Vector2f(displayX/2+xStart*length*i,displayY/2-length*i)));
    }

    sf::Vector2f posLastPoint;    
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();

        posLastPoint = points[nbrPendulum].getPos();
        background.copy(tipPendulum,posLastPoint.x-3,posLastPoint.y-3);
        backgroundTexture.loadFromImage(background);
        window.draw(backgroundSprite);

        for(int i=0;i<nbrPendulum;i++){
            points[i].pendulumUpdate(points[i+1], length);
            points[i].draw(points[i+1], window, nbrPendulum);
        }

        window.display();
    }
}