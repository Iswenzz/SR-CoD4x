add_subdirectory(demo)
add_subdirectory(audio)

target_sources(SR PUBLIC
	Debug.hpp
	Debug.cpp
	Entity.hpp
	Entity.cpp
	Map.hpp
	Map.cpp
	Server.hpp
	Server.cpp
	Vegas.hpp
	Vegas.cpp)
