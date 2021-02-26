#include <SFML/Graphics.hpp>
#include <vector>
// #include "node.hpp"
sf::CircleShape shape(const sf::Vector2f &mouse_pos){
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color(150,50,250));
    shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250,150,100));
    shape.setPosition(mouse_pos);
    return shape;        
}


int main(){

    sf::RenderWindow window(sf::VideoMode(500,500), "Grafos");
    std::vector<sf::CircleShape> circles;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();
            
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                // sf::CircleShape shape(10.f);
                // shape.setFillColor(sf::Color(150,50,250));
                // shape.setOutlineThickness(10.f);
                // shape.setOutlineColor(sf::Color(250,150,100));
                // shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                
                circles.push_back(shape(sf::Vector2f(sf::Mouse::getPosition(window))));
            }
        }
            

        window.clear();
        for (auto &c : circles)
            window.draw(c);
        window.display();
    }


    return 0;
}