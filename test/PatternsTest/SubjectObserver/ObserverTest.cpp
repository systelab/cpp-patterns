#include "stdafx.h"

#include "Patterns/SubjectObserver/Observer.h"
#include "Patterns/SubjectObserver/Subject.h"

using namespace testing;

namespace systelab { namespace patterns { namespace test {

	namespace {
		class MockObserver: public Observer
		{
		public:
			MOCK_METHOD1(update, void (const Subject*));
		};
	}

	class ObserverTest: public Test
	{
	public:
		void SetUp()
		{
			m_subject = std::make_unique<Subject>();
			m_observer = std::make_unique<MockObserver>();
		}
		
	protected:
		std::unique_ptr<MockObserver> m_observer;
		std::unique_ptr<Subject> m_subject;
	};
	
	TEST_F(ObserverTest, testObserveAttachesObserverToSubject)
	{
		m_observer->observe(m_subject.get());
		EXPECT_CALL(*m_observer, update(_));
		m_subject->notify();
	}

}}}