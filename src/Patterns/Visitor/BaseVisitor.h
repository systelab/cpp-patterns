#pragma once

namespace systelab { namespace patterns {
			
	class IVisitable;
			
	class IVisitor
	{
	public:
		virtual void visit(IVisitable&) = 0;
	};
	
	template <class Visitable>
	class BaseVisitor: public virtual IVisitor
	{
	public:
		virtual void visit(IVisitable&) override
		{}
		
		virtual void visit(Visitable&) = 0;
	};
}}