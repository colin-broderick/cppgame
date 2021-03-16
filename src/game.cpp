#include <iostream>
#include <map>
#include <algorithm>

#include "game.h"
#include "block.h"
#include "camera.h"
#include "collisions.h"
#include "platform.h"

// Global reference to player and camera since they're needed all over the place.
cb::Entities::Player* PLAYER;
cb::Entities::Camera* CAMERA;

namespace cb::Collisions
{
    extern std::map<EntityTypes, std::map<EntityTypes, cb::Collisions::CollisionFunction>> collisions;
}

/** \brief Game object constructor. */
cb::Game::Game()
{
    initVariables();
    initWindow();
    initFonts();
    initText();
    initScenery();
    cb::Collisions::initCollisionMap();
    lastTime = std::chrono::system_clock::now();
}

/** \brief Create main scene objects like player and blocks. */
void cb::Game::initScenery()
{
    auto &scene = m_gameObjects;

    scene.push_back(new cb::Entities::Player{600, 100, 0, 0});
    scene.push_back(new cb::Entities::Block{-10, 1000, 1940, 100});   // floor
    scene.push_back(new cb::Entities::Block{-10, -200, 1940, 100});   // ceiling
    scene.push_back(new cb::Entities::Block{-10, -200, 100, 1300});   // left wall
    scene.push_back(new cb::Entities::Block{1840, -200, 100, 1300});  // right wall
    scene.push_back(new cb::Entities::Block{200, 200, 200, 100});   
    scene.push_back(new cb::Entities::Block{200, 500, 200, 200});

    scene.push_back(new cb::Entities::Platform{400, 400, 400, 400});

    for (int i = 0; i < 400; i++)
    {
        scene.push_back(new cb::Entities::Projectile{120, 120, 200+(float)rand()/RAND_MAX*50, 118+(float)rand()/RAND_MAX*50});
    }

    PLAYER = (cb::Entities::Player*)scene[0];
    CAMERA = new cb::Entities::Camera{
        PLAYER->getX() + PLAYER->getWidth()/2 - m_window->getSize().y/2 + PLAYER->getFacing()*80,
        0,
        -10, 1940, -200, 1100
    };
}

/** \brief Destructor for game object. */
cb::Game::~Game()
{
    delete m_window;
}

/** \brief Check whether the game is in an end state caused by e.g. dead player.
 * \return Boolean true if game is dead, otherwise false.
 */
const bool cb::Game::getEndGame() const
{
    return m_endGame;
}

/** \brief This is the main game update loop; all logic starts here. */
void cb::Game::update()
{
    dt = (lastTime - std::chrono::system_clock::now()).count()/1e6;

    CAMERA->setX(PLAYER->getX() + PLAYER->getWidth()/2 - m_window->getSize().x/2 + PLAYER->getFacing()*100);
    CAMERA->setY(PLAYER->getY() - m_window->getSize().y/2 - PLAYER->getVerticalCameraFactor()*160);

    // Check for deletions
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_gameObjects[i]->requestsDeletion())
        {
            m_gameObjects.erase(m_gameObjects.begin() + i);
            i--;
        }
    }

    pollEvents();

    if (!m_endGame)
    {
        updateMouse();
        updateText();
    }

    if (m_health <= 0)
    {
        m_endGame = true;
    }

    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update(std::max(dt, 0.02f));
    }
}

/** \brief Loop over all pairs of objects, check if they collide, and take appropriate action. */
void cb::Game::detectCollisions()
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        auto el1 = m_gameObjects[i];
        for (unsigned int j = i+1; j < m_gameObjects.size(); j++)
        {
            auto el2 = m_gameObjects[j];
            if ((cb::Collisions::collisions[el1->getType()][el2->getType()])(el1, el2))
            {
                if (el1->getType() == ProjectileType && el2->getType() == ProjectileType)
                {   
                    cb::Entities::Projectile el1temp{
                        el1->getX(),
                        el1->getY(),
                        el1->getDx(),
                        el1->getDy()
                    };
                    el1->collide(el2);
                    el2->collide(&el1temp);
                }
                else
                {
                    el1->collide(el2);
                    el2->collide(el1);
                }
            }
        }
    }
}

/** \brief Update game HUD text. */
void cb::Game::updateText()
{
    std::stringstream ss;
    ss << "Score:  " << m_points << "\nHealth: " << PLAYER->getHealth();
    m_uiText.setString(ss.str());
}

/** \brief Render game HUD text. */
void cb::Game::renderText(sf::RenderTarget &target)
{
    target.draw(m_uiText);
}

/** \brief Update the stored mouse position to track mouse activity. */
void cb::Game::updateMouse()
{
    m_mouseWindow = sf::Mouse::getPosition(*m_window);
    m_mouseView = m_window->mapPixelToCoords(m_mouseWindow);
}

/** \brief Render the game scene. */
void cb::Game::render()
{
    m_window->clear();

    renderSceneElements(*m_window);
    renderText(*m_window);

    m_window->display();
}

/** \brief Render scene objects like player, platforms, projectiles, etc.
 * \param target Where to draw the scene.
 */
void cb::Game::renderSceneElements(sf::RenderTarget &target)
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw(*m_window, *CAMERA);
    }
}

/** \brief Process all events which occurred since the last frame. */
void cb::Game::pollEvents()
{
    while (m_window->pollEvent(m_event))
    {
        switch (m_event.type)
        {
            case sf::Event::KeyPressed:
                PLAYER->keyDown(m_event);
                if (m_event.key.code == sf::Keyboard::Escape)
                {
                    m_window->close();
                }
                break;
            case sf::Event::KeyReleased:
                PLAYER->keyUp(m_event);
                break;
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
        }
    }
}

/** \brief Initialize game HUD elements. */
void cb::Game::initText()
{
    m_uiText.setFont(m_font);
    m_uiText.setCharacterSize(50);
    m_uiText.setFillColor(sf::Color::White);
    m_uiText.setOutlineColor(sf::Color::Black);
    m_uiText.setOutlineThickness(3);
    m_uiText.setPosition(sf::Vector2f{10, 10});
    m_uiText.setString("(Hello world)");
}

/** \brief Load fonts. */
void cb::Game::initFonts()
{
    if (!m_font.loadFromFile("fonts/fatinlove.otf"))
    {
        std::cerr << "Failed to load font from fonts/fatinlove.otf\n";
    }
}

/** \brief Load game internal variables. */
void cb::Game::initVariables()
{
    m_window = nullptr;
    m_points = 0;
    m_mouseHeld = false;
    m_health = 10;
    m_endGame = false;

}

/** \brief Create SFML game window. */
void cb::Game::initWindow()
{
    // TODO Detect window size
    m_videoMode.width = 800;
    m_videoMode.height = 600;
    // m_videoMode.getDesktopMode();
    m_window = new sf::RenderWindow{m_videoMode, "WindowGame", sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen};
    m_window->setFramerateLimit(60);
    m_window->setVerticalSyncEnabled(true);
}

/** \brief Check if the game window is still open.
 * \return Boolean true if window is open, otherwise false.
*/
const bool cb::Game::isOpen() const
{
    return m_window->isOpen();
}
