#pragma once

#include "String.h"
#include "BoundSlot.h"
#include "SubsrcibeSlot.h"
#include "RefCounted.h"

#include <map>

namespace CEGUI
{

class CEGUIEXPORT Event
{
public:
	typedef RefCounted<BoundSlot> Connection;
	typedef CEGUI::SubscriberSlot Subscriber;
	typedef unsigned int Group;
	//Event::Connection wrapper that automatically disconnects the connection
	//when the object is deleted (or goes out of scope)
	class ScopedConnection: public Connection
	{
	public:
		ScopedConnection(){}
		ScopedConnection(const Event::Connection &connection):
			d_connection(connection){}
		~ScopedConnection()
		{
			disconnect();
		}
		ScopedConnection& operator=(const Event::Connection &connection)
		{
			d_connection = connection;
			return *this;
		}
		bool connected() const
		{
			return d_connection.isValid()? d_connection->connected():false;
		}
		bool disconnect()
		{
			if (d_connection.isValid())
			{
				d_connection->disconnect();
			}
		}
	private:
		Event::Connection d_connection;
	};

	Event(const String &name);
	~Event();

	const String& getName(void) const
	{
		return d_name;
	}
	Connection subscriber(const Subscriber &slot);
	Connection subscriber(Group group, const Subscriber &slot);
	void operator()(EventArgs &args);
private:
	friend void CEGUI::BoundSlot::disconnect();
	//不能被客户代码使用，使用subscribe返回的Connection对象来调用
	void unsubscribe(const BoundSlot &slot);
	//不允许事件复制
	Event(const Event&){}
	Event& operator=(const Event&){return *this;}

	typedef std::multimap<Group, Connection> SlotContainer;
	SlotContainer d_slots;  //事件的容器，通过组号来管理
	const String d_name;    //事件名
};

}