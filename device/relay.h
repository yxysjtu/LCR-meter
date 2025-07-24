#ifndef RELAY_H
#define RELAY_H

class Relay{
public:
	GPIO& set;
	GPIO& reset;
	//bool state = false;
	Relay(GPIO& set, GPIO& reset) : set(set), reset(reset) {}

	void on_blocking(){
		set.set_pin(1);
		set_state = 1;
		HAL_Delay(debounce_delay);
		set_state = 0;
	}

	void off_blocking(){
		reset.set_pin(1);
		reset_state = 1;
		HAL_Delay(debounce_delay);
		reset_state = 0;
	}

	void on(){
		set.set_pin(1);
		set_state = 1;
	}
	void off(){
		reset.set_pin(1);
		reset_state = 1;
	}
	void task_handler(){
//		state = btn.read_pin();
		if((reset_state > 0 || set_state > 0 ) && debounce_tick == 0){
			debounce_tick = 1;
		}
		if(debounce_tick > 0){
			if(debounce_tick < debounce_delay) debounce_tick++;
			else{
				debounce_tick = 0;
				if(reset_state == 1){
					reset_state = 0;
					reset.set_pin(0);
				}
				if(set_state == 1){
					set_state = 0;
					set.set_pin(0);
				}
				//if(state == !pullup) pressed = true;
			}
		}
//		prev_state = state;
	}

//	bool get_pressed_state(){
//		bool result = pressed;
//		pressed = false;
//		return result;
//	}

private:
	int debounce_delay = 20;
	int set_state = 0;
	int reset_state = 0;
	int debounce_tick = 0;

//	int prev_state = 0;
//	bool pullup;
//	bool pressed = false;

};
#endif
