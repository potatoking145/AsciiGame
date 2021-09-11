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
		Application() = default;
		~Application() = default;

		void Progress();
	};

	class ApplicationManager {
	private:
		std::vector<Application> apps;
	public:
		ApplicationManager() = default;
		~ApplicationManager() = default;

		inline void CreateApplication( /*insert constructor args*/ )
		{
			apps.emplace_back(Application( /* insert constructor args */ ));
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