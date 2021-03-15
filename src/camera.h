#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

namespace cb::Entities
{
    class Camera : public Entity
    {
        public:
            // Constructors
            Camera(float x, float y, float minimumX, float maximumX, float minimumY, float maximumY);

            // Getters
            float getX() const;
            float getY() const;
            EntityTypes getType();

            // Setters
            void setY(float y);
            void setX(float x);

        private:
            // Properties
            float x, y, minimumX, maximumX, minimumY, maximumY;
    };
}

#endif
