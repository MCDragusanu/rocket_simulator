#pragma once
#include <memory>
#include <string>



namespace Core::Window {
	
	
	struct WindowAttributes {
		unsigned int width = { 1920 };
		unsigned int height = { 1080 };
		bool VSyncEnabled = { false };
		std::string windowTitle = { "Default Window" };
	};

	class MainWindow {
	public:
		virtual void initWindow(WindowAttributes& data) = 0;
		virtual void shutDown() = 0;
		virtual void onUpdate() = 0;
		virtual void* getWindowPtr() const = 0;
		virtual void setVsync(bool isEnabled) = 0;
		
		inline void setEventHandler(void* handler) { 
			this->mData.pHandler = handler;
		}
		
		inline auto getEventHandler() const noexcept {
			return this->mData.pHandler;
		}
		
		inline int getHeight() const noexcept { return this->mData.attributes.height; };
		
		inline int getWidth()const noexcept { return this->mData.attributes.width; };
		
		inline const char* getWindowTitle() const noexcept { return this->mData.attributes.windowTitle.c_str(); };
		
	protected:
	
		virtual ~MainWindow() {
			
		};
		struct WindowData {
			WindowAttributes attributes = {};
			void* pHandler = { nullptr };
		};
		WindowData mData;
	
	};
}