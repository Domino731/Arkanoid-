#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ball : public Drawable
{
public:
    Ball(float x, float y);
    Ball() = delete;
    ~Ball() = default;

    // update
    void update();

    // get positon of ball
    float top();
    float bot();
    float left();
    float right();

private:
    CircleShape shape;
    const float ballRadius{10.1f};
    const float ballVelocity{3.0f};

    // 2 means 2 vectors
    Vector2f velocity{ballVelocity, ballVelocity};

    void draw(RenderTarget &target, RenderStates state) const override;
};
