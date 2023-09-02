#pragma once
#include <entity.h>

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
	};
}
