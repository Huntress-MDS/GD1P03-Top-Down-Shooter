#include "Entity.h"
#include <iostream>


bool Entity::Collide(std::vector<Tile*>* _collisionVector, MOVE_DIRECTION _direction)
{
    // Simpler code where it just checks the corner positions of the two entities hurtboxes and kills one of them based on where they collide
    for (int i = 0; i < _collisionVector->size(); i++)
    {
        switch (_direction)
        {
        case (UP):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x - m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y))
            {
                return true;
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x + m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y))
            {
                return true;
            }
            break;
        case (DOWN):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x - m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y))
            {
                return true;
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x + m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y))
            {
                return true;
            }
            break;
        case (LEFT):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y - m_hitboxResizer))
            {
                return true;
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y + m_hitboxResizer))
            {
                return true;
            }
            break;
        case (RIGHT):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y - m_hitboxResizer))
            {
                return true;
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y + m_hitboxResizer))
            {
                return true;
            }
            break;
        }
    }

    return false;
}


void Entity::RotateTowardsPosition(Vector2f _position)
{
    Vector2f screenPos = (Vector2f)m_windowPointer->mapCoordsToPixel(m_position, m_windowPointer->getView());

	float opposite = _position.y - screenPos.y;
	float adjacent = _position.x - screenPos.x;

    m_lookDirection = radians(atan2(opposite, adjacent));

	setRotation(m_lookDirection);
}
