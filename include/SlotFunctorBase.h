#pragma once
namespace
{

class EventArgs;

class SlotFunctorBase
{
public:
	virtual ~SlotFunctorBase(){};
	virtual bool operator()(const EventArgs& args)=0;
};

}