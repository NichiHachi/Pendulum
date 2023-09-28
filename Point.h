#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Point{
    private:
        sf::Vector2f pos,oldPos;
        bool fixed;
    public:
        Point(sf::Vector2f positionPoint);
        void update();
        void fixe();
        sf::Vector2f getPos();
        void pendulumUpdate(Point& point, int length);
        void draw(Point point, sf::RenderWindow& window);
};

