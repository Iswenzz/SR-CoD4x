#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Entity class.
	class Entity
	{
	public:
		static inline std::array<Ref<Entity>, MAX_GENTITIES> List;

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
		static Ref<Entity> &Get(int num);
	};
}
