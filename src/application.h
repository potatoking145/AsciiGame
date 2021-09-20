#ifndef GREENFINGERS_APPLICATION_H_
#define GREENFINGERS_APPLICATION_H_

namespace application
{
	struct ApplicationManagerCtx {
		std::unordered_map<std::string, flecs::world*> ecs_worlds;
		std::unordered_map<std::string, bool> keyboard_inputs;
	};

	struct ApplicationCtx {
		ApplicationManagerCtx* global_ctx;
		tcod::ConsolePtr console;
		SDL_Event* event;
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
		inline void InitContextParams(const char* title, bool vsync, int flags, int renderer, tcod::ConsolePtr* console)
		{
			_context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
			_context_params.window_title = title;
			_context_params.vsync = vsync;
			_context_params.sdl_window_flags = flags;
			_context_params.renderer_type = renderer;
			_context_params.rows = console->get()->h;
			_context_params.columns = console->get()->w;
		}

		tcod::ContextPtr _context;
	public:
		ApplicationInterface();
		~ApplicationInterface();

		inline void InitContext()
		{
			InitContextParams();
			_context = tcod::new_context(_context_params);
		}
		inline void InitContext(const char* title, bool vsync, int flags, int renderer, tcod::ConsolePtr* console)
		{
			InitContextParams(title, vsync, flags, renderer, console);
			_context = tcod::new_context(_context_params);
		}

		inline void DisplayConsole(TCOD_Console& console) { _context->present(console); };
		inline bool IsEventInThisWindow(SDL_Event* event)
		{
			if (event != nullptr) {
				return event->window.windowID == _id ? true : false;
			}
			else {
				return false;
			}
		};

		inline bool IsClosed(SDL_Event* event) { return (IsEventInThisWindow(event) && event->window.event == SDL_WINDOWEVENT_CLOSE); };//Checks if the close window button has been pressed
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
	};

	class Application {
	private:
		uint8_t _id;
		bool _is_closed = false;
	protected:
		ApplicationCtx _ctx;
		ApplicationInterface _interface;
		flecs::world _ecs_world;
	public:
		friend class ApplicationManager;

		Application() = default;
		~Application() = default;

		virtual void Init()
		{
			std::wcout << "Application(" << _id << "). Has no Init overload." << std::endl;
		}
		virtual inline void Progress()
		{
			if (_interface.IfClosedClose(_ctx.event))
			{
				_is_closed = true;
				return;
			}

			TCOD_console_clear(_ctx.console.get());
			_ecs_world.progress(0); // 0 means that flecs will find the delta_time on its own
			_interface.DisplayConsole(*_ctx.console);
		}
		inline bool DidKeyboardInputHappen(const char* input)
		{
			if (_interface.IsEventInThisWindow(_ctx.event)) {
				return _ctx.global_ctx->keyboard_inputs[input];
			}

			return false;
		}
	};

	class ApplicationManager {
	private:
		std::unordered_multimap<int, std::string> _keyboard_input_events;
		std::vector<std::unique_ptr<Application>> _apps;
		ApplicationManagerCtx _global_ctx;
		SDL_Event* _event;

		inline void UpdateInputEvents()
		{
			for (auto it = _keyboard_input_events.begin(); it != _keyboard_input_events.end(); ++it) {
				if (_event->type == SDL_KEYDOWN
					&& _event->key.keysym.sym == it->first 
					&& _global_ctx.keyboard_inputs.find(it->second) != _global_ctx.keyboard_inputs.end()) 
				{
					_global_ctx.keyboard_inputs[it->second] = true;
					continue;
				}

				_global_ctx.keyboard_inputs[it->second] = false;
			}
		}
	public:
		bool is_closed = false;

		ApplicationManager(SDL_Event* event)
		{
			_event = event;
		}
		~ApplicationManager() = default;

		template<typename T, typename... T_args>
		int CreateApplication(T_args... args)
		{
			auto id = std::distance(_apps.begin(), _apps.end()) + 1;

			auto app = std::make_unique<T>(std::forward<T_args>(args)...);
			app->_id = id;
			app->_ctx.global_ctx = &_global_ctx;
			app->_ctx.event = _event;

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
			if (_apps.size() == 0) { // check if all of the apps have been closed
				is_closed = true;
				return;
			}

			UpdateInputEvents();

			for (auto it = _apps.begin(); it != _apps.end(); ++it) {
				(*it)->Progress();

				if ((*it)->_is_closed) {
					DeleteApplication((*it)->_id);
					return;
				}
			}
		}

		inline void AddKeyboardInputEvent(int key_code, const char* input)
		{
			_keyboard_input_events.insert(std::pair(key_code, input));
		}
	};
} // namespace application

#endif