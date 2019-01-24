#ifndef _SYSTEM_H_
#define _SYSTEM_H_
class Event;
class State;
class Event
{
	public:
		double clock;
		Event(State *state);
		virtual ~Event()
		{}
};
class State
{
	public:
		double clock;
		State()
			: clock(0)
		{}
		virtual ~State()
		{}
		virtual bool nextState()=0;
};
Event::Event(State *state) : clock(state->clock)
{}
#endif
