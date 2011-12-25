#ifndef EVENT_H
#define EVENT_H

#include "core.h"

class Event
{
public:
	Event();

	bool poll();
	void addKeyEvent(IKeyEventHandleable *keyEvent);
	void removeKeyEvent(IKeyEventHandleable *keyEvent);


protected:
private:
	std::set<IKeyEventHandleable*> keyEvents;
};

#endif // EVENT_H
