#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 200.0f;
const float OBSTACLE_SPEED = 150.0f;

struct Player {
    sf::RectangleShape shape;
    float speed;
};

struct Obstacle {
    sf::RectangleShape shape;
    float speed;
};

void resetObstacle(Obstacle &obstacle) {
    obstacle.shape.setPosition(rand() % WINDOW_WIDTH, 0);
    obstacle.speed = OBSTACLE_SPEED + (rand() % 100);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Subway Surfers Clone");
    window.setFramerateLimit(60);

    Player player;
    player.shape.setSize(sf::Vector2f(50, 50));
    player.shape.setFillColor(sf::Color::Green);
    player.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 60);
    player.speed = PLAYER_SPEED;

    std::vector<Obstacle> obstacles(5);
    for (auto &obstacle : obstacles) {
        obstacle.shape.setSize(sf::Vector2f(50, 50));
        obstacle.shape.setFillColor(sf::Color::Red);
        resetObstacle(obstacle);
    }

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.shape.getPosition().x > 0) {
            player.shape.move(-player.speed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.shape.getPosition().x < WINDOW_WIDTH - player.shape.getSize().x) {
            player.shape.move(player.speed * deltaTime, 0);
        }

        for (auto &obstacle : obstacles) {
            obstacle.shape.move(0, obstacle.speed * deltaTime);
            if (obstacle.shape.getPosition().y > WINDOW_HEIGHT) {
                resetObstacle(obstacle);
            }
            if (player.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
                window.close();
            }
        }

        window.clear();
        window.draw(player.shape);
        for (const auto &obstacle : obstacles) {
            window.draw(obstacle.shape);
        }
        window.display();
    }

    return 0;
}