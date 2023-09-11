#pragma once

C_EXTERN
{
	#include <entity.h>
}

#define IsDefinedEntity(ent)		(ent && ent->s.number > 0 && ent->s.number < MAX_GENTITIES)
#define IsDefinedEntityNum(num)		(SR->Entities[num] && SR->Entities[num]->g)

namespace Iswenzz::CoD4x
{
	/// @brief Entity class.
	class Entity
	{
	public:
		gentity_t *g;

		/// @brief Initialize a new Entity.
		/// @param ent - The entity.
		Entity(gentity_t *ent);
		~Entity() = default;

		/// @brief Add a new entity.
		/// @param g - The entity.
		static void Add(gentity_t *ent);

		/// @brief Get the entity.
		/// @param num - The entity number.
		/// @return
		static std::shared_ptr<Entity> Get(int num);
	};
}
