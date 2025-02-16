#include "EventHandler.h"
namespace Core::Events {
	EventType Core::Events::getEventType(const Event& event)
	{
		return static_cast<EventType>(event.bytes[9]);
	}
	bool isKeyboardEvent(const Event& event)
	{
		EventType type = getEventType(event);
		return (static_cast<uint8_t>(type) & 0b00000100) == 0b00000100;
	}
	bool isMouseEvent(const Event& event)
	{
		EventType type = getEventType(event);
		return (static_cast<uint8_t>(type) & 0b00001000) == 0b00001000;
	}
	bool isWindowEvent(const Event& event)
	{
		EventType type = getEventType(event);
		return (static_cast<uint8_t>(type) & 0b00010000) == 0b00010000;
	}
	void setEventByte(Event& event, uint8_t byte)
	{
		event.bytes[9] = byte;
	}
	void setPaddingByte(Event& event, uint8_t byte)
	{
		event.bytes[8] = byte;
	}
	std::unique_ptr<Event> create_keyboard_event(KeyCode keyCode, unsigned char event)
	{
		auto inst = std::make_unique<Event>();
		inst->key_code = (long int)keyCode;
		setPaddingByte((*inst), 0x00);
		setEventByte((*inst), event);
		return inst;
	}
	std::unique_ptr<Event> create_mouse_event(float mouseX, float mouseY, MouseButton button, unsigned char event)
	{
		auto inst = std::make_unique<Event>();
		inst->mouseCoordinates[0] = mouseX;
		inst->mouseCoordinates[1] = mouseY;
		setPaddingByte((*inst), (uint8_t)button);
		setEventByte((*inst), event);
		return inst;
	}
	std::unique_ptr<Event> create_window_event(unsigned int width, unsigned int height, unsigned char event)
	{
		auto inst = std::make_unique<Event>();
		inst->windowSize[0] = width;
		inst->windowSize[1] = height;
		setPaddingByte((*inst), 0x00);
		setEventByte((*inst), event);
		return inst;
	}
}