#pragma once

namespace systelab { namespace patterns {
		
	template <class Visitable>
	class BaseVisitor
	{
	public:
		virtual void visit(Visitable&) = 0;
	};
}}