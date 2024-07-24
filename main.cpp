#include <SFML/Graphics.hpp>
#include <sstream>

int windowWidth = 800;
int windowHeight = 600;
float paddleSpeed = 400.0f;
float ballSpeed = 400.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");

    sf::RectangleShape leftPaddle(sf::Vector2f(25.0f, 100.0f));
    leftPaddle.setPosition(50.0f, windowHeight / 2 - 100.0f / 2);
    sf::RectangleShape rightPaddle(sf::Vector2f(25.0f, 100.0f));
    rightPaddle.setPosition(windowWidth - 50.0f - 25.0f, windowHeight / 2 - 100.0f / 2);
    sf::CircleShape ball(10.0f);
    ball.setPosition(windowWidth / 2 - 10.0f, windowHeight / 2 - 10.0f);
    sf::Vector2f ballVelocity(ballSpeed, ballSpeed);

    std::vector<sf::RectangleShape> netLines;
    float currentY = 0.0f;
    while (currentY < windowHeight) {
        sf::RectangleShape segment(sf::Vector2f(5, 15.0f));
        segment.setPosition(windowWidth / 2 - 5 / 2, currentY);
        netLines.push_back(segment);
        currentY += 15.0f + 15.0f;
    }

    int leftScore = 0;
    int rightScore = 0;
    sf::Font font;
    font.loadFromFile("C:/Users/Erik/CLionProjects/SFML/Robot Rebels.ttf");

    sf::Text leftScoreText;
    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(30);
    leftScoreText.setPosition(windowWidth / 4, 20);

    sf::Text rightScoreText;
    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(30);
    rightScoreText.setPosition(windowWidth * 3 / 4, 20);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0.0f, -paddleSpeed * deltaTime.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + 100.0f < windowHeight) {
            leftPaddle.move(0.0f, paddleSpeed * deltaTime.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0.0f, -paddleSpeed * deltaTime.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + 100.0f < windowHeight) {
            rightPaddle.move(0.0f, paddleSpeed * deltaTime.asSeconds());
        }

        ball.move(ballVelocity * deltaTime.asSeconds());
        if (ball.getPosition().y <= 0 || ball.getPosition().y + 10.0f * 2 >= windowHeight) {
            ballVelocity.y = -ballVelocity.y;
        }
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        if (ball.getPosition().x <= 0) {
            rightScore++;
            ball.setPosition(windowWidth / 2 - 10.0f, windowHeight / 2 - 10.0f);
            ballVelocity = sf::Vector2f(ballSpeed, ballSpeed);
        }
        if (ball.getPosition().x + 10.0f * 2 >= windowWidth) {
            leftScore++;
            ball.setPosition(windowWidth / 2 - 10.0f, windowHeight / 2 - 10.0f);
            ballVelocity = sf::Vector2f(-ballSpeed, ballSpeed);
        }

        std::stringstream leftScoreStream;
        leftScoreStream << leftScore;
        leftScoreText.setString(leftScoreStream.str());

        std::stringstream rightScoreStream;
        rightScoreStream << rightScore;
        rightScoreText.setString(rightScoreStream.str());
        
        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(leftScoreText);
        window.draw(rightScoreText);
        for (auto& segment : netLines) {
            window.draw(segment);
        }
        window.display();
    }

    return 0;
}