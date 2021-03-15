#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <chrono>

#include "player.h"
#include "entity.h"
#include "block.h"

namespace cb
{
    class Game
    {
        private:
            void initVariables();
            void initWindow();
            void initEnemies();
            void initFonts();
            void initText();
            void initScenery();

            // Timing
            float dt;
            std::chrono::time_point<std::chrono::system_clock> time;
            std::chrono::time_point<std::chrono::system_clock> lastTime;

            // Window
            sf::VideoMode m_videoMode;
            sf::RenderWindow* m_window;
            sf::Event m_event;

            // Mouse positions
            sf::Vector2i m_mouseWindow;
            sf::Vector2f m_mouseView;

            // Resources
            sf::Font m_font;

            // Text
            sf::Text m_uiText;

            // Game logic
            bool m_endGame;
            int m_points;
            int m_health;
            bool m_mouseHeld;

            // Game objects
            std::vector<cb::Entities::Entity*> m_gameObjects;

        public:
            Game();
            virtual ~Game();

            const bool isOpen() const;
            const bool getEndGame() const;

            void updateText();
            void renderText(sf::RenderTarget &target);
            void renderSceneElements(sf::RenderTarget &target);

            void pollEvents();
            void updateMouse();
            void update();
            void detectCollisions();
            void render();
    };
}

#endif