#pragma once

namespace systelab { namespace patterns {
	
	class IVisitor;
	
	template<class _Derived>
	class BaseVisitable
	{
	public:
		virtual ~BaseVisitable() = default;
	
		template<class _Visitor>
		void accept(_Visitor& visitor)
		{
			_Derived* derived = dynamic_cast<_Derived*>(this);
			visitor.visit(*derived);
		}
	};
}}