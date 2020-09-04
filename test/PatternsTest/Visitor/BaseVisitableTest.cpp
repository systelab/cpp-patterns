#include "stdafx.h"

#include "Patterns/Visitor/BaseVisitable.h"
#include "Patterns/Visitor/BaseVisitor.h"

#include <iostream>

using namespace testing;
namespace systelab { namespace patterns { namespace test {

	namespace	{
		class VisitableA : public BaseVisitable<VisitableA> {};
		class VisitableB : public BaseVisitable<VisitableB> {};
		class VisitableC : public BaseVisitable<VisitableC> {};
		class VisitableD : public BaseVisitable<VisitableD> {};
		
		class VisitorMock : 
			public BaseVisitor<VisitableA>,
			public BaseVisitor<VisitableB>,
			public BaseVisitor<VisitableC>,
			public BaseVisitor<VisitableD>
		{
		public:
			VisitorMock();
			
			MOCK_METHOD1(visit, void(IVisitable&));
			MOCK_METHOD1(visit, void(VisitableA&));
			MOCK_METHOD1(visit, void(VisitableB&));
			MOCK_METHOD1(visit, void(VisitableC&));
			MOCK_METHOD1(visit, void(VisitableD&));
		};
		
		VisitorMock::VisitorMock()
		{
			ON_CALL(*this, visit(A<IVisitable&>())).WillByDefault(Throw(std::exception("Visiting IVisitable!!")));
			ON_CALL(*this, visit(A<VisitableA&>())).WillByDefault(InvokeWithoutArgs([](){std::cout << "Visiting VisitableA" << std::endl;}));
			ON_CALL(*this, visit(A<VisitableB&>())).WillByDefault(InvokeWithoutArgs([](){std::cout << "Visiting VisitableB" << std::endl;}));
			ON_CALL(*this, visit(A<VisitableC&>())).WillByDefault(InvokeWithoutArgs([](){std::cout << "Visiting VisitableC" << std::endl;}));
			ON_CALL(*this, visit(A<VisitableD&>())).WillByDefault(InvokeWithoutArgs([](){std::cout << "Visiting VisitableD" << std::endl;}));
		}
	}
	
	class BaseVisitorTest: public Test
	{
	public:
		void SetUp()
		{
			m_visitable = std::make_unique<VisitableA>();
			
			m_visitor = std::make_unique<VisitorMock>();
		}
		
	protected:
		std::unique_ptr<IVisitable> m_visitable;
		
		std::unique_ptr<VisitorMock> m_visitor;
	};
	
	TEST_F(BaseVisitorTest, testAcceptCallsVisitOfDerivedClass)
	{
		InSequence sequence;
		EXPECT_CALL(*m_visitor, visit(A<VisitableA&>()));
		EXPECT_CALL(*m_visitor, visit(A<VisitableB&>()));
		EXPECT_CALL(*m_visitor, visit(A<VisitableC&>()));
		EXPECT_CALL(*m_visitor, visit(A<VisitableD&>()));

		m_visitable->accept(*m_visitor);
		m_visitable = std::make_unique<VisitableB>();
		m_visitable->accept(*m_visitor);
		m_visitable = std::make_unique<VisitableC>();
		m_visitable->accept(*m_visitor);
		m_visitable = std::make_unique<VisitableD>();
		m_visitable->accept(*m_visitor);
	}
}}}