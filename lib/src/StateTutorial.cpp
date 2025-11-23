#include"StateTutorial.hpp"
#include <iostream>
StateTutorial::StateTutorial(sf::RenderWindow* _window) : current_sprite(texExit), btn_next(texNext), btn_prev(texPrev), btn_exit(texExit) 
{
    window = _window;
    current_indx = 0;
    input_cooldown = 0.0f;
}

StateTutorial::~StateTutorial() 
{
    //empty
}

void StateTutorial::init()
{
    slides_tutorial.clear();
    progress_dots.clear();
    for(int i = 1; i <= 8; i++) 
    {
        sf::Texture texture;
        std::string path = "assets/tutorial/slide" + std::to_string(i) + ".png";
        if (texture.loadFromFile(path))
        {
            texture.setSmooth(true); 
            slides_tutorial.push_back(texture);
        }
        else
        {
            std::cerr << "Error cargando: " << path << std::endl;
        }
    }

    if (!slides_tutorial.empty())
    {
        current_sprite.setTexture(slides_tutorial[0]);
        auto size = slides_tutorial[0].getSize();
        current_sprite.setTextureRect({{0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}});
    }

    if (!texPrev.loadFromFile("assets/tutorial/prevBtn.png")) std::cerr << "Falta prevBtn.png" << std::endl;
    if (!texNext.loadFromFile("assets/tutorial/nextBtn.png")) std::cerr << "Falta nextBtn.png" << std::endl;
    if (!texExit.loadFromFile("assets/tutorial/exitBtn.png")) std::cerr << "Falta exitBtn.png" << std::endl;

    btn_prev.setTexture(texPrev);
    btn_next.setTexture(texNext);
    btn_exit.setTexture(texExit);

    auto prev_size = texPrev.getSize();
    btn_prev.setTextureRect({{0, 0}, {static_cast<int>(prev_size.x), static_cast<int>(prev_size.y)}});

    auto next_size = texNext.getSize();
    btn_next.setTextureRect({{0, 0}, {static_cast<int>(next_size.x), static_cast<int>(next_size.y)}});

    auto exit_size = texExit.getSize();
    btn_exit.setTextureRect({{0, 0}, {static_cast<int>(exit_size.x), static_cast<int>(exit_size.y)}});

    float dot_radius = 10.0f;
    for(size_t i = 0; i < slides_tutorial.size(); i++)
    {
        sf::CircleShape dot(dot_radius);
        dot.setOutlineThickness(2);
        dot.setOutlineColor(sf::Color::White);
        progress_dots.push_back(dot);
    }
    update_dots();
    setup_layout();
}

void StateTutorial::setup_layout()
{
    if(!window) return;
    
    sf::Vector2u sizeU = window->getSize();
    sf::Vector2f winSize((float)sizeU.x, (float)sizeU.y);
    
    float margin = 30.0f;
    float btn_scale = 0.8f;

    btn_exit.setScale(sf::Vector2f(btn_scale, btn_scale)); 
    btn_next.setScale(sf::Vector2f(btn_scale, btn_scale));
    btn_prev.setScale(sf::Vector2f(btn_scale, btn_scale));

    if (!slides_tutorial.empty()) 
    {
        sf::FloatRect bounds = current_sprite.getLocalBounds(); 
        
        if (bounds.size.x > 0 && bounds.size.y > 0)
        {
            current_sprite.setOrigin(sf::Vector2f(bounds.size.x  / 2.f, bounds.size.y / 2.f)); 
            
            current_sprite.setPosition(sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f)); 
            
            float max_width = winSize.x * 0.9f;
            float scale = max_width / bounds.size.x ;
            
            if (bounds.size.y * scale > winSize.y * 0.9f) 
            { 
                scale = (winSize.y * 0.9f) / bounds.size.y; 
            }
            current_sprite.setScale(sf::Vector2f(scale, scale));
        }
    }

    sf::FloatRect exit_bounds = btn_exit.getLocalBounds();
    sf::FloatRect next_bounds = btn_next.getLocalBounds();
    sf::FloatRect prev_bounds = btn_prev.getLocalBounds();

    btn_exit.setOrigin(sf::Vector2f(exit_bounds.size.x, 0.0f)); 
    btn_exit.setPosition(sf::Vector2f(winSize.x - margin, margin));

    btn_next.setOrigin(sf::Vector2f(next_bounds.size.x , next_bounds.size.y));
    btn_next.setPosition(sf::Vector2f(winSize.x - margin, winSize.y - margin));

    btn_prev.setOrigin(sf::Vector2f(0.0f, prev_bounds.size.y));
    btn_prev.setPosition(sf::Vector2f(margin, winSize.y - margin));

    if (!progress_dots.empty())
    {
        float dot_spacing = 30.0f; 
        float totalWidth = (progress_dots.size() - 1) * dot_spacing; 
        float startX = (winSize.x / 2.0f) - (totalWidth / 2.0f);
        
        for(size_t i = 0; i < progress_dots.size(); i++)
        {
            float dot_pos_x = startX + (i * dot_spacing) - progress_dots[i].getRadius();
            float dot_pos_y = winSize.y - margin - 40.0f - progress_dots[i].getRadius();

            progress_dots[i].setPosition(sf::Vector2f(dot_pos_x, dot_pos_y));
        }
    }
}

void StateTutorial::on_resize()
{
    setup_layout();   
}

void StateTutorial::update(float dt)
{
    if (input_cooldown > 0.0f) input_cooldown -= dt;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && input_cooldown <= 0.0f) 
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);    
        float cooldown = 30;
        if (is_clicked(btn_next, mousePos)) 
        {
            input_cooldown = cooldown; 
            if (current_indx < (int)slides_tutorial.size() - 1) 
            {
                current_indx++;
                current_sprite.setTexture(slides_tutorial[current_indx]);
                auto size = slides_tutorial[current_indx].getSize();
                current_sprite.setTextureRect({{0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}});
                setup_layout(); 
            } 
            else 
            {
                save_tutorial_completed();
                go_to = StateType::Return;
            }
        }

        if (current_indx > 0 && is_clicked(btn_prev, mousePos)) 
        {
            input_cooldown = cooldown;
            current_indx--;
            current_sprite.setTexture(slides_tutorial[current_indx]);
            auto size = slides_tutorial[current_indx].getSize();
            current_sprite.setTextureRect({{0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}});
            setup_layout();
        }

        if (is_clicked(btn_exit, mousePos)) 
        {
            input_cooldown = cooldown;
            save_tutorial_completed();
            go_to = StateType::Return;
        }
    }
    update_dots();
}
void StateTutorial::update_dots()
{
    for(size_t i = 0; i < progress_dots.size(); i++)
    {
        if ((int)i == current_indx) 
        {
            progress_dots[i].setFillColor(sf::Color::White);
        }
        else 
        {
            progress_dots[i].setFillColor(sf::Color::Transparent);
        }
    }
}

void StateTutorial::render(sf::RenderWindow& window) {

    window.clear(sf::Color(130,130,200,255));

    window.draw(current_sprite);
    
    if(current_indx > 0) window.draw(btn_prev);
    window.draw(btn_next);
    window.draw(btn_exit);

    for(auto& dot : progress_dots)
    {
        window.draw(dot);
    }
}

bool StateTutorial::is_clicked(sf::Sprite& sprite, sf::Vector2i mousePos)
{
    sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return sprite.getGlobalBounds().contains(mouseF);
}

void StateTutorial::save_tutorial_completed()
{
    std::ofstream file("game_config.dat");
    if (file.is_open())
    {
        file << "tutorial_seen=1";
        file.close();
    }
}

void StateTutorial::terminate()
{

}