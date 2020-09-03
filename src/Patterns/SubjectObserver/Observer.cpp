#include "stdafx.h"

#include "Observer.h"
#include "Subject.h"

namespace systelab { namespace patterns {
	void Observer::observe(Subject* subject)
	{
		subject->attach(this);
	}
}}