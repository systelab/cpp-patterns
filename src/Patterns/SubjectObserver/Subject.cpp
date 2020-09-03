#include "stdafx.h"

#include "Subject.h"
#include "Observer.h"

namespace systelab { namespace patterns {
	Subject::Subject()
	{
	}
	
	void Subject::attach(Observer* observer)
	{
		m_observers.push_back(observer);
	}
	
	void Subject::dettach(Observer*)
	{
	}
	
	void Subject::notify()
	{
		for(auto& o: m_observers)
		{
			o->update(NULL);
		}
	}
}}