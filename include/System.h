#ifndef _SYSTEM_H_
#define _SYSTEM_H_
class Event;
class State;
class Event
{
	public:
		Event(State *state)
		{}
		virtual ~Event()
		{}
};
class State
{
	protected:
		double clock;
	public:
		State()
			: clock(0)
		{}
		virtual ~State()
		{}
		virtual bool nextState()=0;
};
#endif
