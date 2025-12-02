#pragma once
#include "Base.hpp"

namespace SR
{
	class Entity
	{
	public:
		static inline std::array<Ref<Entity>, MAX_GENTITIES> List;
		gentity_t *g;

		Entity(gentity_t *ent);
		~Entity() = default;

		static void Add(gentity_t *ent);
		static Ref<Entity> &Get(int num);
	};
}
