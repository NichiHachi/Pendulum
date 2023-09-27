#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "Point.h"

Point::Point(sf::Vector2f positionPoint){
    this->pos = positionPoint;
    this->oldPos = positionPoint;
    this->fixed = false;
}

void Point::update(){
    if(!fixed){
        sf::Vector2f velocity = pos - oldPos;
        oldPos = pos;
        pos += velocity;
        //Gravity
        pos.y += 0.0005;
    }
}

void Point::fixe(){
    fixed = true;
}

void Point::pendulumUpdate(Point& point, int length){
    sf::Vector2f pendulumVector = point.pos - pos;
    float norme = sqrt(pendulumVector.x*pendulumVector.x+pendulumVector.y*pendulumVector.y);
    float surplus = norme - length;
    float percent = surplus / norme / 2;

    if(!fixed){
        pos += percent * pendulumVector;
    }
    if(!point.fixed){
        point.pos -= percent * pendulumVector;
    }
    update();
    point.update();
}

void Point::draw(Point point, sf::RenderWindow& window){
    sf::VertexArray line(sf::Lines,2);
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    line[0].position = pos;
    line[1].position = point.pos;

    window.draw(line);
}