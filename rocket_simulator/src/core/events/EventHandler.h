#pragma once

namespace Core::Events {


	/**
	 * @brief Enum representing different types of events.
	 *
	 * Each event type is assigned a unique bit pattern for easy identification.The Event class is given by the first non null msg
	 */
	enum class EventType {
		KeyboardPressed  = 0b00000100,
		KeyboardRepeated = 0b00000101,
		KeyboardReleased = 0b00000110,

		MousePressed     = 0b00001000,
		MouseReleased    = 0b00001001,
		MouseMoved       = 0b00001010,

		WindowResized    = 0b00010000,
		WindowMinimised  = 0b00010001,
		WindowFocused    = 0b00010010,
		WindowClosed     = 0b00010011,
	};

	/**
	* @brief Union to store different types of event data.
	*
	* This union allows storing keyboard, mouse, or window event data in the same
	* memory location.  The last byte of the array is always the event type. The
	* second to last byte is a padding byte ( 0x00 for keyboard and window events) or
	* the mouse button ( != 0x00 for mouse events).
	*/
	union Event {
	
		float    mouseCoordinates[2];   //Memory Layout : xxxx yyyy p e
		uint8_t  bytes[10];				//Memory Layout : bbbb bbbb b b
		uint32_t windowSize[2];			//Memory Layout : wwww hhhh p e	
		uint64_t key_code;			    //Memory Layout : kkkk kkkk p e 

		/**
		 * @brief Retrieve the event type from the last byte.
		 */
		friend	EventType getEventType(const Event& event) {
			return static_cast<EventType>(event.bytes[sizeof(bytes) - 1]);
		}
		/**
		 * @brief Check if the event is a keyboard event.
		 */
		friend	bool isKeyboardEvent(const Event& event) {
			EventType type = getEventType(event);
			return (static_cast<uint8_t>(type) & 0b00000100) == 0b00000100;
		}
		/**
		 * @brief Check if the event is a mouse event.
		 */
		friend	bool isMouseEvent(const Event& event) {
			EventType type = getEventType(event);
			return (static_cast<uint8_t>(type) & 0b00001000) == 0b00001000;
		}
		/**
		 * @brief Check if the event is a window event.
		 */
		friend	bool isWindowEvent(const Event& event) {
			EventType type = getEventType(event);
			return (static_cast<uint8_t>(type) & 0b00010000) == 0b00010000;
		}
		/**
		 * @brief Set the event type byte.
		 */
		friend void setEventByte(Event& event,uint8_t byte) {
			event.bytes[sizeof(bytes) - 1] = byte;
		}
		/**
		 * @brief Set the padding byte (the byte before the last one byte).
		 * Used for mouse events to check what button has been pressed
		 */
		friend	void setPaddingByte(Event& event, uint8_t byte) {
			event.bytes[sizeof(bytes) - 2] = byte;
		}
	};
	/**
	 * @brief Create a keyboard event.
	 * @param key_code The key code for the keyboard event.
	 * @param event The event type (e.g., pressed, released).
	 * @return A unique pointer to the created event.
	 */
	std::unique_ptr<Event> create_keyboard_event(long int key_code, unsigned char event) {
		auto inst = std::make_unique<Event>();
		inst->key_code = key_code;
		setPaddingByte((*inst), 0x00);
		setEventByte((*inst), event);
		return inst;
	}
	/**
	 * @brief Create a mouse event. First float in the mouseCoordinates field is the x-coordinate. The second float in the mouseCoordinates field is the y-coordinate.
	 * @param mouseX The x-coordinate of the mouse. 
	 * @param mouseY The y-coordinate of the mouse. 
	 * @param button The mouse button pressed.
	 * @param event The event type (e.g., pressed, moved).
	 * @return A unique pointer to the created event.
	 */
	std::unique_ptr<Event> create_mouse_event(float mouseX, float mouseY, unsigned char button, unsigned char event) {
		auto inst = std::make_unique<Event>();
		inst->mouseCoordinates[0] = mouseX;
		inst->mouseCoordinates[1] = mouseY;
		setPaddingByte((*inst), button);
		setEventByte((*inst), event);
		return inst;
	}
	/**
	 * @brief Create a window event. First int in the windowSize field is the width. The second int in the windowSize field is height.
	 * @param width The new width of the window.
	 * @param height The new height of the window.
	 * @param event The event type (e.g., resized, focused).
	 * @return A unique pointer to the created event.
	 */
	std::unique_ptr<Event>  create_window_event(unsigned int width, unsigned int height, unsigned char event) {
		auto inst = std::make_unique<Event>();
		inst->windowSize[0] = width;
		inst->windowSize[1] = height;
		setPaddingByte((*inst), 0x00);
		setEventByte((*inst), event);
		return inst;
	}


	struct WindowEventHandler {
		virtual void on_window_event(const std::unique_ptr<Event>& event) = 0;
		virtual void on_keyboard_event(const std::unique_ptr<Event>& event) = 0;
		virtual void on_mouse_event(const std::unique_ptr<Event>& event) = 0;
	};
}