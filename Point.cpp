#include <SFML/Graphics.hpp>
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
        pos.y += 0.0015;
    }
}

void Point::fixe(){
    fixed = true;
}

sf::Vector2f Point::getPos(){
    return pos;
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

void Point::draw(Point point, sf::RenderWindow& window, int nbrPendulum){
    sf::VertexArray line(sf::Lines,2);
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    line[0].position = pos;
    line[1].position = point.pos;

    window.draw(line);

    sf::CircleShape circle;
    int circleRadius = 5;
    circle.setRadius(circleRadius);
    circle.setOutlineColor(sf::Color::White);
    circle.setPosition(point.pos-sf::Vector2f(circleRadius,circleRadius));

    window.draw(circle);
}