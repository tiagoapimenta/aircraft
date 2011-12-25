#ifndef EVENT_H
#define EVENT_H

#include "core.h"

class Event
{
public:
	static Event* getInstance();

	bool poll();
	void addKeyEvent(IKeyEventHandleable *keyEvent);
	void removeKeyEvent(IKeyEventHandleable *keyEvent);


protected:
private:
	static Event *instance;

	std::set<IKeyEventHandleable*> keyEvents;

	Event();
};

#endif // EVENT_H
