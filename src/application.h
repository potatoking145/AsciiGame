#ifndef GREENFINGERS_APPLICATION_H_
#define GREENFINGERS_APPLICATION_H_

namespace application {
	struct ApplicationManagerCtx {
		int dummy; // delete later
	};

	struct ApplicationCtx {
		ApplicationManagerCtx* global;

		~ApplicationCtx() { delete global; } // prevents memory leak
	};

	class Application {
	public:
		uint8_t id;

		Application(uint8_t _id)
			: id(std::move(_id)) {};

		~Application() = default;

		virtual void Progress()
		{
			std::cout << "Application(" << id << "). Has no Progress overload." << std::endl;
		};
	};

	class ApplicationManager {
	private:
		std::vector<Application> apps;
	public:
		ApplicationManager() = default;
		~ApplicationManager() = default;

		inline void CreateApplication( /*insert constructor args*/ )
		{
			apps.emplace_back( std::distance(apps.begin(), apps.end()) + 1 );
		}
		inline void DeleteApplication(uint8_t id)
		{
			for (auto it = apps.begin(); it != apps.end(); ++it) {
				if (it->id == id) {
					apps.erase(it);
					break;
				}
			}
		}
		inline void ProgressApplications()
		{
			for (Application app : apps) {
				app.Progress();
			}
		}
	};
}

#endif