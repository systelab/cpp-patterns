#pragma once

#include <list>

namespace systelab { namespace patterns {
	
	class Observer;
	
	class Subject
	{
	public:
		Subject();
		
		void attach(Observer*);
		void dettach(Observer*);
		void notify();
		
	private:
		std::list<Observer*> m_observers;
	};
	
}}