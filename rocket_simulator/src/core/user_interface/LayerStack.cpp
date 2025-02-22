#include "LayerStack.h"
namespace Core::UserInterface {


	LayerStack::LayerStack()
	{
		mLayerStackInserter = mLayerStack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : mLayerStack) {
			delete layer;
		}
	}

	void LayerStack::pushOverlay(Layer* layer)
	{
		mLayerStack.emplace_back(layer);
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		mLayerStackInserter = mLayerStack.emplace(mLayerStackInserter, layer);
	}

	void LayerStack::popOverlay(const Layer* overlay)
	{
		auto it = std::find(mLayerStack.begin(), mLayerStack.end(), overlay);
		if (it != mLayerStack.end()) {
			mLayerStack.erase(it);
		}
	}

	void LayerStack::popLayer(const Layer* layer)
	{
		auto it = std::find(mLayerStack.begin(), mLayerStack.end(), layer);
		if (it != mLayerStack.end()) {
			mLayerStack.erase(it);
			mLayerStackInserter--;
		}

	}
}