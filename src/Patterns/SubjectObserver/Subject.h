#pragma once

namespace systelab { namespace patterns {
	
	class Observer;
	
	class Subject
	{
	public:
		Subject();
		
		void attach(Observer*);
		void dettach(Observer*);
		void notify();
	};
	
}}