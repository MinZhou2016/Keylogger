#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer
{
	std::thread Thread;
	bool Alive = false;
	long repeate_count = -1L;
	std::function<void(void)> funct = nullptr;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	long CallNumber = -1L;

	void SleepAndRun(){
		std::this_thread::sleep_for(interval);
		if (Alive) {
			Function()();
		}
	};
	void ThreadFunc() {
		if (CallNumber == infinite){
			while (Alive){
				SleepAndRun();
			}
		}else {
			while (repeate_count--){
				SleepAndRun();
			}
		}
	};
public:
	static const long infinite = -1L;

	Timer(){}

	Timer(const std::function<void(void)> &f):funct (f) {}

	Timer(const std::function<void(void)> &f,
		  const unsigned long &i,
		  const long repeat = Timer::infinite):funct(f), interval(std::chrono::milliseconds(i)), CallNumber(repeat){}

	void Start(bool Async = true){
		if (IsAlive()) return;
		Alive = true;
		repeate_count = CallNumber;
		if (Async) {
			Thread = std::thread(&Timer::ThreadFunc, this);
		}else {
			this -> ThreadFunc();
		}
	}
	void Stop() {
		Alive = false;
		Thread.join();
	}
	void SetFunction(const std::function<void(void)> &func){
		funct = func;
	}
	bool IsAlive() {
		return Alive;
	}
	void RepeatCount (const long r){
		if (IsAlive()) return;
		CallNumber = r;
	}
	long GetLeftCount() const {
		return repeate_count;
	}
	long RepeatCount () const {
		return CallNumber;
	}
	void SetInterval (const unsigned int& i){
		if (IsAlive()) return;
		interval = std::chrono::milliseconds(i);
	}
	unsigned long Interval() const {
		return interval.count();
	}
	const std::function<void(void)> & Function() {
		return funct;
	}
};
#endif
