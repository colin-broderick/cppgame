#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>

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

sf::Vector2f cb::Game::getMouse() const
{
    return m_mouseView;
}

float cb::Game::getMouseX() const
{
    return m_mouseView.x;
}

float cb::Game::getMouseY() const
{
    return m_mouseView.y;
}

/** \brief Create main scene objects like player and blocks. */
void cb::Game::initScenery()
{
    auto &scene = m_sceneObjects;

    scene.push_back(new cb::Entities::Player{600, 100, 0, 0});
    scene.push_back(new cb::Entities::Block{-10, 1000, 1940, 100});   // floor
    scene.push_back(new cb::Entities::Block{-10, -200, 1940, 100});   // ceiling
    scene.push_back(new cb::Entities::Block{-10, -200, 100, 1300});   // left wall
    scene.push_back(new cb::Entities::Block{1840, -200, 100, 1300});  // right wall
    scene.push_back(new cb::Entities::Block{200, 200, 200, 100});   
    scene.push_back(new cb::Entities::Block{200, 500, 200, 200});

    scene.push_back(new cb::Entities::Platform{400, 400, 400, 400});

    for (int i = 0; i < 100; i++)
    {
        scene.push_back(new cb::Entities::Projectile{120, 120, 200+(float)rand()/RAND_MAX*50, 118+(float)rand()/RAND_MAX*50});
    }

    PLAYER = (cb::Entities::Player*)scene[0];
    CAMERA = new cb::Entities::Camera{
        PLAYER->getX() + PLAYER->getWidth()/2 - m_window->getSize().y/2 + PLAYER->getFacing()*80,
        0,
        -10, 1940, -200, 1100
    };
    PLAYER->setScene(this);
    PLAYER->setCamera(CAMERA);
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
    for (unsigned int i = 0; i < m_sceneObjects.size(); i++)
    {
        if (m_sceneObjects[i]->requestsDeletion())
        {
            m_sceneObjects.erase(m_sceneObjects.begin() + i);
            i--;
        }
    }

    // Add new scene objects.
    for (unsigned int i = 0; i < m_newSceneObjects.size(); i++)
    {
        // std::cout << "Added element to scene" << std::endl;
        m_sceneObjects.push_back(m_newSceneObjects[i]);
    }
    m_newSceneObjects.clear();

    // Check for input events.
    pollEvents();

    // Check for end game condition.
    if (!m_endGame)
    {
        updateMouse();
        updateText();
    }
    if (m_health <= 0)
    {
        m_endGame = true;
    }

    // Update states of scene objects.
    for (unsigned int i = 0; i < m_sceneObjects.size(); i++)
    {
        m_sceneObjects[i]->update(std::max(dt, 0.02f));
    }
}


void cb::Game::addNewObject(cb::Entities::Entity* newElement)
{
    m_newSceneObjects.push_back(newElement);
}

/** \brief Loop over all pairs of objects, check if they collide, and take appropriate action. */
void cb::Game::detectCollisions()
{
    sf::Vector2f collisionVector;
    float distance, speed;
    sf::Vector2f collisionVectorNorm;
    sf::Vector2f relativeVelocityVector;
    for (unsigned int i = 0; i < m_sceneObjects.size(); i++)
    {
        auto& el1 = m_sceneObjects[i];
        for (unsigned int j = i+1; j < m_sceneObjects.size(); j++)
        {
            auto& el2 = m_sceneObjects[j];
            if ((cb::Collisions::collisions[el1->getType()][el2->getType()])(el1, el2))
            {
                if (el1->getType() == ProjectileType && el2->getType() == ProjectileType)
                {   
                    // TODO I'd really rather not have this here.
                    collisionVector.x = el2->getX() - el1->getX();
                    collisionVector.y = el2->getY() - el1->getY();
                    
                    distance = sqrt(
                        (el2->getX()-el1->getX())*(el2->getX()-el1->getX())
                        + (el2->getY()-el1->getY())*(el2->getY()-el1->getY())
                    );
                    collisionVectorNorm = collisionVector/distance;
                    relativeVelocityVector.x = el1->getDx() - el2->getDx();
                    relativeVelocityVector.y = el1->getDy() - el2->getDy();
                    
                    speed = relativeVelocityVector.x*collisionVectorNorm.x
                                + relativeVelocityVector.y*collisionVectorNorm.y;
                    // TODO Calculate impulse here.
                    if (speed > 0)    
                    {
                        el1->setDx(el1->getDx() - speed*collisionVectorNorm.x);
                        el1->setDy(el1->getDy() - speed*collisionVectorNorm.y);
                        el2->setDx(el2->getDx() + speed*collisionVectorNorm.x);
                        el2->setDy(el2->getDy() + speed*collisionVectorNorm.y);
                    }
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
    for (unsigned int i = 0; i < m_sceneObjects.size(); i++)
    {
        m_sceneObjects[i]->draw(*m_window, *CAMERA);
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
            case sf::Event::MouseButtonPressed:
                PLAYER->mouseDown(m_event);
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
