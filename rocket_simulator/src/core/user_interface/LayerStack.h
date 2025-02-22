#pragma once
#include <vector>

class Layer;

namespace Core::UserInterface {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void pushOverlay(Layer* layer);
		void pushLayer(Layer* layer);

		void popOverlay(const Layer* overlay);
		void popLayer(const Layer* layer);

		std::vector <Layer*>::iterator begin() { return mLayerStack.begin(); };
		std::vector <Layer*>::iterator end() { return mLayerStack.end(); }
	protected :
		std :: vector <Layer*> mLayerStack;
		std::vector <Layer*>::iterator mLayerStackInserter;
	};
}