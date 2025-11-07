#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IGameObject.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class PieceInstantiator : public IGameObject
{
    public:
    PieceInstantiator(PieceType _type, bool _team, sf::Vector2f position);
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    void return_to_origin();
    PiecePtr make_piece(int startX, int startY);
    
private:
    PieceType type;
    bool team;
    sf::Vector2f originalposition;
};
