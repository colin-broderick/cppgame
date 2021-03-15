#include <algorithm>

#include "camera.h"

// Constructors ===================================================================================

/** \brief Camera constructor.
 * \param x Starting x position of the camera.
 * \param y Starting y position of the camera.
 */
cb::Entities::Camera::Camera(float x, float y, float minimumX, float maximumX, float minimumY, float maximumY)
{
    this->x = x;
    this->y = y;
    this->minimumX = minimumX;
    this->maximumX = maximumX;
    this->minimumY = minimumY;
    this->maximumY = maximumY;
}

// Getters ========================================================================================

float cb::Entities::Camera::getX() const
{
    return x;
}

float cb::Entities::Camera::getY() const
{
    return y;
}

EntityTypes cb::Entities::Camera::getType()
{
    return CameraType;
}

// Setters ========================================================================================

void cb::Entities::Camera::setX(float x)
{
    this->x = std::min(std::max(x, minimumX), maximumX - 1920);
}

void cb::Entities::Camera::setY(float y)
{
    this->y = std::min(std::max(y, minimumY), maximumY - 1080);
}