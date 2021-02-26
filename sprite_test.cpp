#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
// class node : sf::Sprite

sf::Sprite create_sprite(const sf::Texture &texture, const sf::Vector2f &mouse){
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.01f, 0.01f);
    sprite.setPosition(mouse);
    return sprite;
}

bool is_sprite(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (auto &sprite : sprites){
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (bounds.contains(mouse)){
            return true;
        }
    }
    return false;
}

void  move_sprite(sf::Vector2f &mouse, sf::Sprite &sprite){
    sprite.setPosition(mouse);
}

int main(){

    sf::RenderWindow window(sf::VideoMode(500,500), "Grafos");
    std::vector<sf::Sprite> sprites;
    std::vector<sf::FloatRect> sprite_bounds;
    sf::Texture texture;

    if (!texture.loadFromFile("Assets/blue-circle.png")){
        std::cout << "Error con textura" << std::endl;
        return 0;
    }

    while (window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){

                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (sprites.size() > 0){
                    if (is_sprite(mouse, sprites))
                        std::cout << "Mira!, un sprite!!!" << std::endl;
                    
                }
                
                sf::Sprite sprite = create_sprite(texture, mouse);
                sprites.push_back(sprite);
            }

        window.clear();
        for (auto &s: sprites)
            window.draw(s);
        window.display();

    }

    return 0;
}