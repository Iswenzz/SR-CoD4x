#pragma once
#include "Streamable.hpp"

namespace SR
{
	class MP3 : public Streamable
	{
	public:
		MP3(const std::string& filepath);
		virtual ~MP3() = default;

		void Open() override;
		void Save(const std::string& path) override;
	};
}
