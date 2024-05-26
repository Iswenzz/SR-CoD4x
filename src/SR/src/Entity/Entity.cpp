#include "Entity.hpp"

namespace SR
{
	Entity::Entity(gentity_t *ent)
	{
		g = ent;
	}

	void Entity::Add(gentity_t *ent)
	{
		List[ent->s.number] = CreateRef<Entity>(ent);
	}

	Ref<Entity> &Entity::Get(int num)
	{
		return List[num];
	}
}
