#include "EventHandler.h"
namespace Core::Events {
	EventType Core::Events::getEventType(const Event& event)
	{
		return static_cast<EventType>(event.bytes[sizeof(event.bytes) - 1]);
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
		event.bytes[sizeof(event.bytes) - 1] = byte;
	}
	void setPaddingByte(Event& event, uint8_t byte)
	{
		event.bytes[sizeof(event.bytes) - 2] = byte;
	}
	std::unique_ptr<Event> create_keyboard_event(long int key_code, unsigned char event)
	{
		auto inst = std::make_unique<Event>();
		inst->key_code = key_code;
		setPaddingByte((*inst), 0x00);
		setEventByte((*inst), event);
		return inst;
	}
	std::unique_ptr<Event> create_mouse_event(float mouseX, float mouseY, unsigned char button, unsigned char event)
	{
		auto inst = std::make_unique<Event>();
		inst->mouseCoordinates[0] = mouseX;
		inst->mouseCoordinates[1] = mouseY;
		setPaddingByte((*inst), button);
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