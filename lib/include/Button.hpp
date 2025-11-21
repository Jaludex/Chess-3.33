#include <IGameObject.hpp>

class Button : public IGameObject
{
public:
    Button() = delete;
    Button(sf::texture);
    Button(sf::texture, sf::Vector2f);
    Button(sf::Vector2f, sf::Vector2f, sf::Color);
    bool get_state()const;
    bool toggle();
    virtual void update(float) override;
    virtual void render(sf::RenderWindow&) override;

private:
    bool activated;
};
