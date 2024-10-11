#include "Clock.h"
#include <chrono>
#include <iostream>
#include <string.h>



using namespace gen;


Clock::Clock() {
	startTime_ = std::chrono::steady_clock::now();
	currentTime_micros = std::chrono::microseconds(0);
	lastFrameTime_micros = std::chrono::microseconds(0);
}

void Clock::updateTime() {
	currentTime_micros = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime_);
	currentDeltaTime_sec = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime_micros - lastFrameTime_micros);
}

void Clock::newFrame() {
	lastDeltaTime_sec = currentDeltaTime_sec;
	lastFrameTime_micros = currentTime_micros;
}

void Clock::setEvent(const char *name, float timeToWait_sec) {
	Event event;
	event.name = name;
	// event.timeToWait_sec = std::chrono::duration_cast<std::chrono::duration<float>>(timeToWait_sec);
	event.timeToWait_sec = std::chrono::duration<float>(timeToWait_sec);
	event.lastTriggerTime_micros = std::chrono::microseconds(0);
	events.push_back(event);
}

bool Clock::checkEventAndTrigger(const char *name) {
	// for (Event event : events) {
	// 	if (strcmp(event.name, name) == 0) {
	// 		std::chrono::duration<float> timeElapsed_sec = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime_micros - event.lastTriggerTime_micros);
	// 		std::cout << "timeElapsed_sec: " << timeElapsed_sec.count() << std::endl;
	// 		if (timeElapsed_sec > event.timeToWait_sec) {
	// 			event.lastTriggerTime_micros = currentTime_micros;
	// 			return true;
	// 		}
	// 	}
	// }
	// return false;
	Event *event = nullptr;
	for (int i = 0; i < events.size() && event == nullptr; i++) {
		if (strcmp(events.at(i).name, name) == 0) event = &(events.at(i));
	}
	if (event != nullptr) {
		std::chrono::duration<float> timeElapsed_sec = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime_micros - event->lastTriggerTime_micros);
		if (timeElapsed_sec > event->timeToWait_sec) {
			event->lastTriggerTime_micros = currentTime_micros;
			return true;
		}
	}
	return false;
}

float Clock::deltaTime() {
	return lastDeltaTime_sec.count();
}

float Clock::getCurrentDeltaTime() {
	// return static_cast<float>(currentDeltaTime_sec.count());
	return currentDeltaTime_sec.count();
}

int Clock::getCurrentTime_micros() {
	return currentTime_micros.count();
}

float Clock::getCurrentTime_sec() {
	return currentTime_micros.count() / 1000000.0f;
}

int Clock::getLastFrameTime_micros() {
	return lastFrameTime_micros.count();
}