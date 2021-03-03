#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
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

int get_sprite_index(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (int i = 0; i < sprites.size(); ++ i){
        sf::FloatRect bounds = sprites[i].getGlobalBounds();
        if (bounds.contains(mouse))
            return i;
    }
    return -1;
}

// void update_lines(const std::vector<sf::Sprite> &sprites, const std::vector<std::vector<int>> &connected_nodes_index, std::vector<sf::Vertex> &lines, const int &global_sprite_index){

// }

int main(){

    sf::RenderWindow window(sf::VideoMode(500,500), "Grafos");

    std::vector<sf::Sprite> sprites;
    std::vector<sf::Vertex> lines;
    std::vector<std::vector<sf::Vector2f>> connected_lines;
    std::vector<std::vector<int>> connected_nodes_index;
    std::vector<int> node_index;
    std::vector<sf::Vector2f> mouse_points;

    std::vector<int> modified_lines_index;

    sf::Texture texture;
    sf::Sprite current_sprite;
 
    int global_sprite_index;
 
    std::string mouse_button;

    bool sprite_selected = false;
    bool button_pressed = false;

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
                        int index = get_sprite_index(mouse, sprites);
                        std::cout << "Mira!, el sprite " << index << "!!!" << std::endl;
                        if(sprite_selected){
                            mouse_points.push_back(mouse);
                            connected_lines.push_back(mouse_points);
                            node_index.push_back(index);
                            connected_nodes_index.push_back(node_index);
                            lines.push_back(sf::Vertex(mouse_points[0]));
                            lines.push_back(sf::Vertex(mouse_points[1]));
                            
                            std::cout << "Una linea" << std::endl;
                            sprite_selected = false;
                            mouse_points.clear();
                            node_index.clear();
                            // window.draw(line, 2, sf::Lines);
                        }
                        else if (!sprite_selected){
                            mouse_points.push_back(mouse);
                            std::cout << "aqui no hay linea" << std::endl;
                            connected_lines.push_back(mouse_points);
                            node_index.push_back(index);
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
                button_pressed = true;

                if (sprites.size() > 0){
                    global_sprite_index = get_sprite_index(mouse, sprites);
                    if (global_sprite_index != -1){
                        std::cout << "el sprite que buscas es el " << global_sprite_index << std::endl;

                        mouse_button = "Middle";
                        if (lines.size() > 0){
                            for (int i = 0; i < lines.size(); ++i){
                                if (sprites[global_sprite_index].getGlobalBounds().contains(lines[i].position))
                                    modified_lines_index.push_back(i);

                            }
                        }

                        sprites[global_sprite_index].setPosition(mouse);
                        if(modified_lines_index.size() > 0){
                            for (int i = 0; i < modified_lines_index.size(); ++i)
                                lines[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
                        }
                        
                        sprite_selected = true;
                    }
                    else{

                        std::cout << "aqui no hay nada mi chavo" << std::endl; 
                        button_pressed = false;
                    }
                    
                }
            }
            else if (event.type == sf::Event::MouseMoved && mouse_button == "Middle"){
                if (sprite_selected){
                    if (lines.size() > 0){
                        for (int i = 0; i < lines.size(); ++i){
                            if (sprites[global_sprite_index].getGlobalBounds().contains(lines[i].position))
                                modified_lines_index.push_back(i);

                        }
                    
                    }
                    sprites[global_sprite_index].setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

                    if(modified_lines_index.size() > 0){
                        for (int i = 0; i < modified_lines_index.size(); ++i)
                            lines[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased && mouse_button == "Middle"){
                mouse_button = "";
                sprite_selected = false;
                global_sprite_index = -1;
                if(modified_lines_index.size() > 0)
                    modified_lines_index.clear();
            }
                
            

        window.clear();
        for (auto &s: sprites){
            window.draw(s);
            // std::cout<< s.getPosition().x << " " << s.getPosition().y << std::endl;
        }
        if (lines.size() > 0)
            window.draw(&lines[0],lines.size(), sf::Lines);

        window.display();

        }
    }

    return 0;
}