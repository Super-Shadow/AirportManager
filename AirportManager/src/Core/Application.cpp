#include "ampch.h" // Refer to EntryPoint.cpp for explanation

#include "Application.h"

#include "Airport.h"
#include "Input.h"
#include "Renderer.h"

// Create both renderer and input via their respective static create methods.
// Pass width and height of the renderer using aggregate initialisation which accepts only R(ight)-value reference.
// This has been done to hint at other developers that there is no need to store the object used to initialise the renderer.
Application::Application() : m_Renderer(Renderer::Create({1600, 960})), m_Input(Input::Create())
{
	// Visual flair
	m_Renderer->DisplayLogo();
	m_Renderer->DisplayCredits();

	// Check that no airports are nullptrs as it could cause a crash later on when looping through airports and trying to access their ID
	for(const auto airport : m_Airports)
	{
		if(airport == nullptr)
		{
			throw std::logic_error("An airport in m_Airports inside Application is nullptr, please check array length is correct and that each airport has been created.");
		}
	}
}

Application::~Application()
{
	// Cleanup pointers and dependencies before freeing self.
	Shutdown();
}

void Application::Run()
{
	// Main application loop
	while(m_Running)
	{
		// This loop will try and get a correct airport ID from the user and will keep trying until a correct ID has been input or the user types quit
		while(m_SelectedAirport == nullptr)
		{
			m_Renderer->DisplayText("Airports Available: ");

			// For each loop through existing airports and display their ID and "cooldown" (time until a new aircraft can arrive)
			for(const auto& airport : m_Airports)
			{
				m_Renderer->DisplayText(std::format("|{}: Cooldown is {} seconds| ", airport->GetIdentifier(), airport->GetCooldown()));
			}

			m_Renderer->DisplayText("\nPlease enter an airport ID for the aircraft to land.\n");

			const auto requestedAirportID = m_Input->GetSingleWord();

			// Early return and set running to false to exit application
			if(requestedAirportID == "quit")
			{
				m_Running = false;
				return;
			}

			// ValidateID will return 1 or more error flags if the ID is invalid. It is up to the developer to handle each flag however they want.
			const AirportUtils::IDErrorFlags AirportIDFlags = AirportUtils::ValidateID(requestedAirportID);

			// If the ID is valid, no flags will be returned which is equivalent to 0
			if(static_cast<std::uint32_t>(AirportIDFlags) == 0)
			{
				// Even though ID is valid, must check if that ID actually exists in our airports.
				for(const auto airport : m_Airports)
				{
					if(airport->GetIdentifier() == requestedAirportID)
					{
						// Found the airport, will now break out of this foreach loop
						m_SelectedAirport = airport;
						break;
					}
				}

				if(m_SelectedAirport == nullptr)
				{
					m_Renderer->DisplayText(std::format("\nYou entered {} which was not found the in the list of available airports.\nPlease try again or type quit to exit the program.\n", requestedAirportID));
				}
			}
			else
			{
				m_Renderer->DisplayText(std::format("\nYou entered {}.\n", requestedAirportID));

				// Handle various flags that could have occurred
				if(AirportIDFlags & AirportUtils::IDErrorFlags::NOT_UPPER_CASE)
				{
					m_Renderer->DisplayText("Please enter the airport ID in all upper case. For example, LGW instead of lgw or Lgw.\n");
				}
				if(AirportIDFlags & AirportUtils::IDErrorFlags::TOO_MANY_CHARS)
				{
					m_Renderer->DisplayText(std::format("Please ensure the airport ID has no more than {} letters.\n", AirportUtils::MaxIDLength));
				}
				if(AirportIDFlags & AirportUtils::IDErrorFlags::NOT_ENOUGH_CHARS)
				{
					m_Renderer->DisplayText(std::format("Please ensure the airport ID has at least {} letters.\n", AirportUtils::MinIDLength));
				}

				m_Renderer->DisplayText("\nPlease try again or type quit to exit the program.\n");
			}
		}

		// Found our airport, now try and land at it
		std::uint32_t prevCooldown = 0;
		while(!m_SelectedAirport->RequestLanding())
		{
			// prevCooldown holds the previous cooldown value to be able to compare it to the most recent cooldown value.
			// If they differ, a second has passed and should tell the user, since GetCooldown only changes if 1 second has passed.
			// If we don't do this, text will be displayed as fast as the CPU can run (not ideal).
			if(m_SelectedAirport->GetCooldown() != prevCooldown)
			{
				prevCooldown = m_SelectedAirport->GetCooldown();
				m_Renderer->DisplayText(std::format("Unfortunately, landing is denied since the last plane landed at {:%d-%m-%Y %X}. Please wait {} seconds.\n",
													std::chrono::current_zone()->to_local(AirportUtils::HighResolutionClockToSystemClock(m_SelectedAirport->GetLastArrivalTime())),
													m_SelectedAirport->GetCooldown()));
			}
		}

		// Able to successfully land at the airport, reset selected airport and ask the user if they want to land at an airport again (loop until quit is inputted)
		m_Renderer->DisplayText(std::format("Plane has landed at Airport {} successfully at {:%d-%m-%Y %X}!\n",
											m_SelectedAirport->GetIdentifier(),
											std::chrono::current_zone()->to_local(AirportUtils::HighResolutionClockToSystemClock(m_SelectedAirport->GetLastArrivalTime()))));
		m_SelectedAirport = nullptr;
	}
}

void Application::Shutdown()
{
	// Notify user, display visual flair and delete pointers
	m_Renderer->DisplayText("Shutting down Airport Manager system.\n");
	m_Renderer->DisplayLogo();
	m_Renderer->DisplayCredits();

	m_SelectedAirport = nullptr;
	for(const Airport* airport : m_Airports)
	{
		delete airport;
	}
	delete m_Input;
	delete m_Renderer;
}
