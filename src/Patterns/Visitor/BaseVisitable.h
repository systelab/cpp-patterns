#pragma once

#include "BaseVisitor.h"

namespace systelab { namespace patterns {
		
	class IVisitable
	{
	public:
		virtual void accept(IVisitor&) = 0;
	};
	
	template<class _Derived>
	class BaseVisitable: public IVisitable
	{
	public:
		typedef BaseVisitor<_Derived> DerivedVisitor;
		
		virtual ~BaseVisitable() = default;
	
		void accept(IVisitor& visitor) override
		{
			DerivedVisitor* derivedVisitor = dynamic_cast<DerivedVisitor*>(&visitor);
			acceptImpl(*derivedVisitor);
		}
	
		template<class _Visitor>
		void acceptImpl(_Visitor& visitor)
		{
			_Derived* derived = dynamic_cast<_Derived*>(this);
			visitor.visit(*derived);
		}
	};
	
}}