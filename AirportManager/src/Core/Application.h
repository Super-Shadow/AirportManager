#pragma once
#include "Airport.h"

// Forward declare is better than including as in this case we only need to know it exists, not its definition.
// This results in a faster build time than including the header file.
class Input;
class Renderer;

class Application
{
public:
	Application();
	~Application();

	void Run();
	void Shutdown();

private:
	Renderer* m_Renderer = nullptr;
	Input* m_Input = nullptr;

	// Store airports in array instead of a vector since airports aren't being removed or added at runtime,
	// if they were this should be changed to a vector.
	std::array<Airport*, 3> m_Airports{
		new Airport({"LGW"}),
		new Airport({"EMA"}),
		new Airport({"MAN"})
	};
	Airport* m_SelectedAirport = nullptr;

	bool m_Running = true;
};
