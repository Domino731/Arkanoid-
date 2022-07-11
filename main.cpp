#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Headers/Ball.h"

using namespace std;
using namespace sf;

// #1
int main()
{

    Ball ball(400, 400);

    RenderWindow window{VideoMode{800, 800}, "Magic tree"};

    window.setFramerateLimit(60);

    Event event;
    // while (true)
    // {
    //     window.clear(Color::Black);
    //     window.pollEvent(event);

    //     if (event.type == Event::Closed)
    //     {
    //         window.close();
    //         break;
    //     }
    //     window.draw(ball);
    //     window.display();
    // }

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