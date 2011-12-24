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
	void addUpdater(IUpdatable *updater);
	void removeUpdater(IUpdatable *updater);

protected:
private:
	static Event *instance;

	std::vector<IKeyEventHandleable*> keyEvents;
	std::vector<IUpdatable*> updaters;

	Event();
};

#endif // EVENT_H
