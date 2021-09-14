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
		std::unordered_map<std::string, flecs::world*> worlds;

		int s{1};
	};

	struct ApplicationCtx {
		int dummy;
	};

	class ApplicationInterface
	{
	private:
		uint8_t _id; //tracks this window's id ;; used for checking which window an event happened in

		TCOD_ContextParams _context_params;
		inline void InitContextParams()
		{
			//Default values
			_context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
			_context_params.window_title = "Greenfingers";
			_context_params.vsync = true;
			_context_params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
			_context_params.renderer_type = TCOD_RENDERER_SDL2;
		}
		inline void InitContextParams(const char* title, bool vsync, int flags, int renderer)
		{
			_context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
			_context_params.window_title = title;
			_context_params.vsync = vsync;
			_context_params.sdl_window_flags = flags;
			_context_params.renderer_type = renderer;
		}

		tcod::ContextPtr _context;

		SDL_Event* _captured_event{ nullptr }; //nullptr indicates no captured event
	public:
		ApplicationInterface();
		~ApplicationInterface();

		inline void InitContext()
		{
			InitContextParams();
			_context = tcod::new_context(_context_params);
		}
		inline void InitContext(const char* title, bool vsync, int flags, int renderer)
		{
			InitContextParams(title, vsync, flags, renderer);
			_context = tcod::new_context(_context_params);
		}

		inline void DisplayConsole(TCOD_Console& console) { _context->present(console); };
		inline void CaptureEvent(SDL_Event* event)
		{
			_captured_event = (event->window.windowID == _id) ? event : nullptr;
		};

		inline bool IsClosed() { return (_captured_event->window.windowID == _id && _captured_event->window.event == SDL_WINDOWEVENT_CLOSE); }; //Checks if the close window button has been pressed
		inline bool IsClosed(SDL_Event* event) { return (event->window.windowID == _id && event->window.event == SDL_WINDOWEVENT_CLOSE); };

		inline bool IfClosedClose() //Closes the window if the close button has been pressed
		{
			if (IsClosed(_captured_event)) {
				_context.reset();
				return true;
			}
			else {
				return false;
			}
		};
		inline bool IfClosedClose(SDL_Event* event)
		{
			if (IsClosed(event)) {
				_context.reset();
				return true;
			}
			else {
				return false;
			}
		};

		inline uint8_t GetId() { return _id; };
		inline SDL_Event* GetCapturedEvent() { return _captured_event; };
	};

	class Application {
	private:
		uint8_t _id;
	protected:
		ApplicationCtx _ctx;
		ApplicationManagerCtx* _global_ctx;
		ApplicationInterface _interface;
		flecs::world _ecs_world;
	public:
		friend class ApplicationManager;

		virtual ~Application() = default;

		virtual void Init()
		{
			std::wcout << "Application(" << _id << "). Has no Init overload." << std::endl;
		}

		virtual void Progress()
		{
			std::wcout << "Application(" << _id << "). Has no Progress overload." << std::endl;
		}
	};

	class ApplicationManager {
	private:
		std::vector<std::unique_ptr<Application>> _apps;
		ApplicationManagerCtx _global_ctx;
	public:
		ApplicationManager() = default;
		~ApplicationManager() = default;

		template<typename T, typename... T_args>
		int CreateApplication(T_args... args)
		{
			auto id = std::distance(_apps.begin(), _apps.end()) + 1;

			auto app = std::make_unique<T>( std::forward<T_args>(args)... );
			app->_id = id;
			app->_global_ctx = &_global_ctx;

			app->Init();
			_apps.push_back(std::move(app));

			return id;
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