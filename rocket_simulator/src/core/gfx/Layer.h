#pragma once
#include <memory>
#include <string>
#include "../events/EventHandler.h"

namespace Core::gfx {
    
	class Layer {
		
	public:
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate() = 0;
		virtual void onEvent(const std::unique_ptr<Core ::Events::Event>&) = 0;

		inline const std::string& getLayerName() const noexcept { return mLayerName; };
	protected:
		std::string mLayerName;
	};
}