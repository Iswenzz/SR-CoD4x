#include "Entity.hpp"

#include "Application.hpp"

namespace Iswenzz::CoD4x
{
	Entity::Entity(gentity_t *ent)
	{
		g = ent;
	}

	void Entity::Add(gentity_t *ent)
	{
		SR->Entities[ent->s.number] = std::make_shared<Entity>(ent);
	}

	std::shared_ptr<Entity> Entity::Get(int num)
	{
		return IsDefinedEntityNum(num) ? SR->Entities[num] : nullptr;
	}
}
