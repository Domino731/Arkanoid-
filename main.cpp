#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Headers/Ball.h"
#include "Headers/Paddle.h"
#include "Headers/Block.h"
#include <cmath>

using namespace std;
using namespace sf;

template <class T1, class T2>
bool isIntersecting(T1 &A, T2 &B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bot() >= B.top() && A.top() <= B.bot();
};

bool colisionTest(Paddle &paddle, Ball &ball)
{
    if (!isIntersecting(paddle, ball))
    {
        return false;
    };
    ball.moveUp();
    if (ball.getPosition().x < paddle.getPosition().x)
    {
        ball.moveLeft();
    }
    else if (ball.getPosition().x > paddle.getPosition().x)
    {
        ball.moveRight();
    }
};

bool colisionTest(Block &block, Ball &ball)
{
    if (!isIntersecting(block, ball))
    {
        return false;
    }

    // destroy block
    block.Destroy();

    // ball hit from left site
    float overlapLeft{ball.right() - block.left()};

    // ball hit from right site
    float overlapRight{ball.right() - block.left()};

    // ball hit from top site
    float overlapTop{ball.bot() - block.top()};

    // ball hit from top site
    float overlapBot{ball.bot() - block.top()};

    bool ballFromLeft(abs(overlapLeft) - abs(overlapRight));
    bool ballFromTop(abs(overlapTop) - abs(overlapBot));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBot};

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }
}

// #1
int main()
{

    Ball ball(400, 300);
    Paddle paddle(400, 500);

    RenderWindow window{VideoMode{800, 600}, "Magic tree"};

    window.setFramerateLimit(75);

    unsigned blocksX{8}, blocksY{4}, blockWidth{60}, blockHeight{20};

    vector<Block> blocks;

    for (int i = 0; i < blocksY; i++)
    {
        for (int j = 0; j < blocksX; j++)
            // creating object
            blocks.emplace_back((j + 1) * (blockWidth + 10), (i + 2) * (blockHeight + 5), blockWidth, blockHeight);
    }

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
        paddle.update();

        colisionTest(paddle, ball);

        for (auto &block : blocks)
        {
            if (!block.isDestroyed() && colisionTest(block, ball))
                break;
        }

        window.draw(ball);
        window.draw(paddle);

        // loop for objects
        for (auto &block : blocks)
        {
            if (!block.isDestroyed())
            {
                window.draw(block);
            }
        }

        window.display();
    };
    return 0;
};

/// Ball classs
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

void Ball::moveDown()
{
    this->velocity.y = ballVelocity;
};
void Ball::moveUp()
{
    this->velocity.y = -ballVelocity;
};
void Ball::moveLeft()
{
    this->velocity.x = -ballVelocity;
};
void Ball::moveRight()
{
    this->velocity.x = ballVelocity;
}

Vector2f Ball::getPosition()
{
    return shape.getPosition();
}

// Paddle class
Paddle::Paddle(float x, float y)
{
    shape.setPosition(x, y);
    shape.setSize({this->paddle_width, this->paddle_height});
    shape.setFillColor(Color::Green);
    shape.setOrigin(paddle_width / 2.f, paddle_height / 2.f);
}

void Paddle::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(this->shape, state);
}

void Paddle::update()
{
    shape.move(this->velocity);

    // handling hitting paddle left or right wall
    if (shape.getPosition().x <= 40)
    {
        velocity.x = paddle_velocity;
    }
    else if (shape.getPosition().x >= 760)
    {
        velocity.x = -paddle_velocity;
    }
    else
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
        {
            velocity.x = -paddle_velocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 800)
        {
            velocity.x = paddle_velocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        {
            velocity.x = 0;
        }
    }
}

float Paddle::top()
{
    return shape.getPosition().y - shape.getSize().y / 2.f;
}

float Paddle::bot()
{
    return shape.getPosition().y + shape.getSize().y / 2.f;
}

float Paddle::left()
{
    return shape.getPosition().x - shape.getSize().x / 2.f;
}

float Paddle::right()
{
    return shape.getPosition().x + shape.getSize().x / 2.f;
}

Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}

////////////////////////////////////////

Block::Block(float x, float y, float width, float height)
{
    shape.setPosition(x, y);
    shape.setSize({width, height});
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(width / 2.f, height / 2.f);
}

void Block::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(this->shape, state);
}

float Block::top()
{
    return shape.getPosition().y - shape.getSize().y / 2.f;
}

float Block::bot()
{
    return shape.getPosition().y + shape.getSize().y / 2.f;
}

float Block::left()
{
    return shape.getPosition().x - shape.getSize().x / 2.f;
}

float Block::right()
{
    return shape.getPosition().x + shape.getSize().x / 2.f;
}

Vector2f Block::getPosition()
{
    return shape.getPosition();
}

bool Block::isDestroyed()
{
    return this->destroyed;
}
void Block::Destroy()
{
    this->destroyed = true;
}
Vector2f Block::getSize()
{
    return shape.getSize();
}

void Block::update()
{
}