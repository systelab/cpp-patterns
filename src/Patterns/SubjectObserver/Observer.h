#pragma once

namespace systelab { namespace patterns {
	
	class Subject;
	
	class Observer
	{
	public:
		virtual void update(const Subject*) = 0;
		
		void observe(Subject*);
	};
}}