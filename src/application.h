#ifndef GREENFINGERS_APPLICATION_H_
#define GREENFINGERS_APPLICATION_H_

// Example Application class
//class test : public application::Application {
//public:
//	test(int _dummy) : dummy(_dummy) {}; ;; required
//
//	int dummy;
//
//	void Progress()
//	{
//		std::wcout
//			<< dummy
//			<< _ctx.dummy ;; local context
//			<< _global_ctx->dummy; global context
//	};
//};

namespace application {
	struct ApplicationManagerCtx {
		int dummy{ 777 };
	};

	struct ApplicationCtx {
		int dummy{ 666 };
	};

	class Application {
	private:
		uint8_t _id;
	protected:
		ApplicationCtx _ctx;
		ApplicationManagerCtx* _global_ctx;
	public:
		friend class ApplicationManager;

		virtual ~Application() = default;

		virtual void Progress()
		{
			std::wcout << "Application(" << _id << "). Has no Progress overload." << std::endl;
		};
	};

	class ApplicationManager {
	private:
		std::vector<std::unique_ptr<Application>> _apps;
		ApplicationManagerCtx _global_ctx;
	public:
		ApplicationManager() = default;
		~ApplicationManager() = default;

		template<typename T, typename... T_args>
		void CreateApplication(T_args... args)
		{
			auto app = std::make_unique<T>( std::forward<T_args>(args)... );
			app->_id = std::distance(_apps.begin(), _apps.end()) + 1;
			app->_global_ctx = &_global_ctx;
			_apps.push_back(std::move(app));
		}
		inline void DeleteApplication(uint8_t id)
		{
			for (auto it = _apps.begin(); it != _apps.end(); ++it) {
				if ((*it)->_id == id) {
					_apps.erase(it);
					break;
				}
			}
		}
		inline void ProgressApplications()
		{
			for (auto it = _apps.begin(); it != _apps.end(); ++it) {
				(*it)->Progress();
			}
		}
	};
}

#endif