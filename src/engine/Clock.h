#pragma once
#include <chrono>
// #include <iostream>
#include <vector>


namespace gen{


	class Clock
	{

	private:
		struct Event
		{
			const char *name;
			std::chrono::duration<float> timeToWait_sec;
			std::chrono::microseconds lastTriggerTime_micros;
		};		

		std::chrono::steady_clock::time_point startTime_;
		std::chrono::microseconds currentTime_micros, lastFrameTime_micros;
		std::chrono::duration<float> currentDeltaTime_sec, lastDeltaTime_sec;
		std::vector<Event> events;


	public:
		Clock();
		~Clock();
		void updateTime();
		void newFrame();
		void setEvent(const char *, float);
		bool checkEventAndTrigger(const char *);
		float deltaTime();
		float getCurrentDeltaTime();
		int getCurrentTime_micros();
		float getCurrentTime_sec();
		int getLastFrameTime_micros();
	};


} // namespace gen
