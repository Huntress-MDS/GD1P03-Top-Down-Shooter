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
                return CheckCollidingTile(_collisionVector, i);
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x + m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            break;
        case (DOWN):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x - m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x + m_hitboxResizer) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            break;
        case (LEFT):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y - m_hitboxResizer))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x - m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y + m_hitboxResizer))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            break;
        case (RIGHT):
            if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y + m_hitbox.y - m_hitboxResizer))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            else if (_collisionVector->at(i)->CheckIfPointInAreaX(m_position.x + m_hitbox.x) && _collisionVector->at(i)->CheckIfPointInAreaY(m_position.y - m_hitbox.y + m_hitboxResizer))
            {
                return CheckCollidingTile(_collisionVector, i);
            }
            break;
        }
    }

    return false;
}


bool Entity::Collide(Entity* _entity)
{
    // Simpler code where it just checks the corner positions of the two entities hurtboxes and kills one of them based on where they collide
    if (_entity->CheckIfPointInAreaX(m_position.x + m_hurtbox.x) && _entity->CheckIfPointInAreaY(m_position.y + m_hurtbox.y))
    {
        m_queuedForDeletion = true;
        _entity->m_queuedForDeletion = true;
        return true;
    }
    else if (_entity->CheckIfPointInAreaX(m_position.x - m_hurtbox.x) && _entity->CheckIfPointInAreaY(m_position.y + m_hurtbox.y))
    {
        m_queuedForDeletion = true;
        _entity->m_queuedForDeletion = true;
        return true;
    }
    else if (_entity->CheckIfPointInAreaX(m_position.x + m_hurtbox.x) && _entity->CheckIfPointInAreaY(m_position.y - m_hurtbox.y))
    {
        m_queuedForDeletion = true;
        _entity->m_queuedForDeletion = true;
        return true;
    }
    else if (_entity->CheckIfPointInAreaX(m_position.x - m_hurtbox.x) && _entity->CheckIfPointInAreaY(m_position.y - m_hurtbox.y))
    {
        m_queuedForDeletion = true;
        _entity->m_queuedForDeletion = true;
        return true;
    }

    return false;
}


bool Entity::CheckCollidingTile(std::vector<Tile*>* _collisionVector, int _i)
{
    if (_collisionVector->at(_i)->GetTileType() == "Wall")
    {
        return true;
    }
    else if (_collisionVector->at(_i)->GetTileType() == "Goal")
    {
        return false;
    }
}


void Entity::RotateTowardsPosition(Vector2f _position, bool _worldSpace)
{
    Vector2f screenPos = _worldSpace ? m_position : (Vector2f)m_windowPointer->mapCoordsToPixel(m_position, m_windowPointer->getView());

	float opposite = _position.y - screenPos.y;
	float adjacent = _position.x - screenPos.x;

    m_lookDirection = radians(atan2(opposite, adjacent));

	setRotation(m_lookDirection);
}


// Do math to check if a point is within the tile's x position and size
bool Entity::CheckIfPointInAreaX(float _point)
{
    if (_point > getPosition().x && _point < getPosition().x + getSize().x)
    {
        return true;
    }

    return false;
}


// Do math to check if a point is within the tile's y position and size
bool Entity::CheckIfPointInAreaY(float _point)
{
    if (_point > getPosition().y && _point < getPosition().y + getSize().y)
    {
        return true;
    }

    return false;
}