#pragma once

#include <list>

namespace systelab { namespace patterns {
	
	class Subject;
	
	class Observer
	{
	public:
		virtual ~Observer();
		
		virtual void update(const Subject*) = 0;
		
		void observe(Subject*);
		
	private:
		std::list<Subject*> m_observedSubjects;
	};
}}