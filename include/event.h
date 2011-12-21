#ifndef EVENT_H
#define EVENT_H

#include "core.h"

class Event
{
	public:
		static Event& getInstance();

		bool poll();

	protected:
	private:
		static Event *instance;

		Event();
};

#endif // EVENT_H
