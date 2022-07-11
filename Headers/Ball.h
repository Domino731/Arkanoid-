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
    string name = "ASAS";

private:
    CircleShape shape;
    const float ballRadius{10.1f};

    void draw(RenderTarget &target, RenderStates state) const override;
};
// class Ball
// {
// public:
//     Ball();
//     // Ball(float t_x, float t_y);
//     // Ball() = delete;
//     // ~Ball() = default;

//     string name = "cos";

// private:
//     CircleShape shape;
//     const float ballRadius{10.1f};

//     // void draw(RenderTarget &target, RenderStates state) const override;
// };
