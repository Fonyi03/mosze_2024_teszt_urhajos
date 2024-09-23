#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <cmath>

// Ablak méretei
const int windowWidth = 800;
const int windowHeight = 600;

// Űrhajós paraméterei
const float playerSpeed = 300.0f;
const float bulletSpeed = 500.0f;
const sf::Vector2f playerSize(50.0f, 30.0f);
const float bulletRadius = 5.0f;

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bullet(float x, float y) {
        shape.setRadius(bulletRadius);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);
        velocity.x = bulletSpeed;
    }

    void update(float deltaTime) {
        shape.move(velocity * deltaTime);
    }
};

class Player {
public:
    sf::RectangleShape shape;
    Player(float x, float y) {
        shape.setSize(playerSize);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);
    }

    void move(sf::Vector2f direction, float deltaTime) {
        shape.move(direction * playerSpeed * deltaTime);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "2D Space Shooter");

    Player player(windowWidth / 2.0f - playerSize.x / 2.0f, windowHeight - playerSize.y - 10.0f);
    std::vector<Bullet> bullets;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Delta idő a mozgás pontos számításához
        float deltaTime = clock.restart().asSeconds();

        // Irányítás
        sf::Vector2f direction(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction.x += 1.0f;
        }

        // Lövés
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            bullets.emplace_back(player.shape.getPosition().x + playerSize.x / 2.0f, player.shape.getPosition().y);
        }

        // Játékos mozgatása
        player.move(direction, deltaTime);

        // Lövedékek frissítése
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }

        // Kilépés a képernyőről
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
            return bullet.shape.getPosition().x > windowWidth;
        }), bullets.end());

        // Ablak törlése és újrarajzolása
        window.clear();
        window.draw(player.shape);
        for (auto& bullet : bullets) {
            window.draw(bullet.shape);
        }
        window.display();
    }

    return 0;
}


//teszt file hozzáadva githez 