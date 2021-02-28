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
    std::vector<sf::Vertex> lines;
    std::vector<std::vector<sf::Vector2f>> connected_nodes;
    sf::Texture texture;
    std::vector<sf::Vector2f> mouse_points;

    bool sprite_selected = false;
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
                    if (is_sprite(mouse, sprites)){
                        std::cout << "Mira!, un sprite!!!" << std::endl;
                        
                        if(sprite_selected){
                            mouse_points.push_back(mouse);
                            connected_nodes.push_back(mouse_points);
                            lines.push_back(sf::Vertex(mouse_points[0]));
                            lines.push_back(sf::Vertex(mouse_points[1]));
                            
                            std::cout << "Una linea" << std::endl;
                            sprite_selected = false;
                            mouse_points.clear();
                            // window.draw(line, 2, sf::Lines);
                        }
                        else if (!sprite_selected){
                            mouse_points.push_back(mouse);
                            std::cout << "aqui no hay linea" << std::endl;
                            connected_nodes.push_back(mouse_points);
                            sprite_selected = true;
                        }
                    }
                    else {
                        sf::Sprite sprite = create_sprite(texture, mouse);
                        sprites.push_back(sprite);
                    }
                }

                else{
                    sf::Sprite sprite = create_sprite(texture, mouse);
                    sprites.push_back(sprite);
                }
            }

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle){
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (sprites.size() > 0){
                    if (is_sprite(mouse, sprites)){
                        break;
                    }
                }
            }

        window.clear();
        for (auto &s: sprites)
            window.draw(s);
        // std::cout << lines.size() << std::endl;
        if (lines.size() > 0)
            window.draw(&lines[0],lines.size(), sf::Lines);

        window.display();

        }
    }

    return 0;
}