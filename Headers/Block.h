#include <SFML/Graphics.hpp>

using namespace sf;

class Block : public sf::Drawable
{
public:
    Block(float x, float y, float width, float height);
    Block() = delete;
    ~Block() = default;

    void update();
    Vector2f getPosition();

    // get positon of block
    float top();
    float bot();
    float left();
    float right();

    bool isDestroyed();
    void Destroy();
    Vector2f getSize();

private:
    RectangleShape shape;
    void draw(RenderTarget &target, RenderStates state) const override;
    bool destroyed{false};
};