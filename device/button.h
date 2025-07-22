#ifndef BUTTON_H
#define BUTTON_H

class Button{
public:
	GPIO& btn;
	bool state = false;

	Button(GPIO& btn, bool pullup) : btn(btn), pullup(pullup) {}

	void task_handler(){
		state = btn.read_pin();
		if(prev_state == pullup && state == !pullup){
			debounce_tick = 1;
		}
		if(debounce_tick > 0){
			if(debounce_tick < debounce_delay) debounce_tick++;
			else{
				debounce_tick = 0;
				if(state == !pullup) pressed = true;
			}
		}
		prev_state = state;
	}

	bool get_pressed_state(){
		bool result = pressed;
		pressed = false;
		return result;
	}

private:
	int debounce_delay = 10;
	int debounce_tick = 0;
	int prev_state = 0;
	bool pullup;
	bool pressed = false;

};
#endif
