#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::Texture texture) : board(texture)
{
}
StateGameplay::~StateGameplay(){}

void StateGameplay::init()
{
    //instanciar una pieza cualquiera y añadirla al board
}

void StateGameplay::terminate()
{
    //si usamos shared pointers entonces no necesitamos eliminar la pieza creada en init
}

void StateGameplay::update(float dt)
{
    //if mouse left button pressed down

        //if selected != nullptr
            //selected piece sprite's position = mouse position
        
        //else if mouse position inside any piece from board
            //selected = pointer to that piece

    //if mouse left button not pressed and selected != null
        //ask board for where should that piece be placed, and tell that piece to move to that cell.
        //then selected = null

    //update board, its pieces should be update
}

void StateGameplay::render(sf::RenderWindow window)
{
    //board.render(window)
}
