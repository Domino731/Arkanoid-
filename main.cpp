#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Headers/Ball.h"

using namespace std;
using namespace sf;

// #1
int main()
{

    Ball ball(400, 300);

    RenderWindow window{VideoMode{800, 600}, "Magic tree"};

    window.setFramerateLimit(60);

    Event event;
    while (true)
    {
        window.clear(Color::Black);
        window.pollEvent(event);

        if (event.type == Event::Closed)
        {
            window.close();
            break;
        }
        ball.update();

        window.draw(ball);
        window.display();
    };
    cout << "TEST";
    return 0;
};

Ball::Ball(float x, float y)
{
    shape.setPosition(x, y);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(this->ballRadius, this->ballRadius);
};

void Ball::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(this->shape, state);
}

void Ball::update()
{
    shape.move(this->velocity);

    if (this->left() < 0)
    {
        velocity.x = ballVelocity;
    }
    else if (this->right() > 800)
    {
        velocity.x = -ballVelocity;
    }
    if (this->top() < 0)
    {
        velocity.y = ballVelocity;
    }
    else if (this->bot() > 600)
    {
        velocity.y = -ballVelocity;
    }
}

float Ball::top()
{
    return shape.getPosition().y - shape.getRadius();
}

float Ball::bot()
{
    return shape.getPosition().y + shape.getRadius();
}

float Ball::left()
{
    return shape.getPosition().x - shape.getRadius();
}

float Ball::right()
{
    return shape.getPosition().x + shape.getRadius();
}