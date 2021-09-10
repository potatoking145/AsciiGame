#ifndef GREENFINGERS_APPLICATION_H_
#define GREENFINGERS_APPLICATION_H_

namespace application {
	struct ApplicationManagerCtx {
		int dummy; // delete later
	};

	struct ApplicationCtx {
		ApplicationManagerCtx* global;

		int dummy; //delete later

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

		void CreateApplication();
		void ProgressApplications();
	};
}

#endif