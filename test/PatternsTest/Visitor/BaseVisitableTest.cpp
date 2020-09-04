#include "stdafx.h"

#include "Patterns/Visitor/BaseVisitable.h"
#include "Patterns/Visitor/BaseVisitor.h"

using namespace testing;
namespace systelab { namespace patterns { namespace test {

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
		MOCK_METHOD1(visit, void(VisitableA&));
		MOCK_METHOD1(visit, void(VisitableB&));
		MOCK_METHOD1(visit, void(VisitableC&));
		MOCK_METHOD1(visit, void(VisitableD&));
	};
	
	class BaseVisitorTest: public Test
	{
	public:
		void SetUp()
		{
			m_visitableA = std::make_unique<VisitableA>();
			m_visitableB = std::make_unique<VisitableB>();
			m_visitableC = std::make_unique<VisitableC>();
			m_visitableD = std::make_unique<VisitableD>();
			
			m_visitor = std::make_unique<VisitorMock>();
		}
		
	protected:
		std::unique_ptr<VisitableA> m_visitableA;
		std::unique_ptr<VisitableB> m_visitableB;
		std::unique_ptr<VisitableC> m_visitableC;
		std::unique_ptr<VisitableD> m_visitableD;
		
		std::unique_ptr<VisitorMock> m_visitor;
	};
	
	TEST_F(BaseVisitorTest, testAcceptCallsVisitOfDerivedClass)
	{
		EXPECT_CALL(*m_visitor, visit(A<VisitableA&>()));
		m_visitableA->accept(*m_visitor);
	}
}}}