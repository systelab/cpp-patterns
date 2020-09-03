#include "stdafx.h"

#include "Observer.h"
#include "Subject.h"

namespace systelab { namespace patterns {
	
	Observer::~Observer()
	{
		for (auto& s: m_observedSubjects)
		{
			s->dettach(this);
		}
	}
	
	void Observer::observe(Subject* subject)
	{
		subject->attach(this);
		m_observedSubjects.push_back(subject);
	}
}}