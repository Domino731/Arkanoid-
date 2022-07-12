#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Paddle : public sf::Drawable
{
public:
    Paddle(float x, float y);
    Paddle() = delete;
    ~Paddle() = default;

    string const lastPressedKey = "";

    void update();
    // get positon of ball
    float top();
    float bot();
    float left();
    float right();

private:
    RectangleShape shape;

    float const paddle_width{80.0f};
    float const paddle_height{20.0f};
    float const paddle_velocity{6.0f};

    Vector2f velocity{paddle_velocity, 0.f};

    void draw(RenderTarget &target, RenderStates state) const override;
};