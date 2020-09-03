#include "stdafx.h"

#include "Patterns/SubjectObserver/Subject.h"
#include "Patterns/SubjectObserver/Observer.h"

using namespace testing;

namespace systelab { namespace patterns { namespace test {

	namespace {
		class MockObserver: public Observer
		{
		public:
			MOCK_METHOD1(update, void (const Subject*));
		};
	}

	class SubjectTest: public Test
	{
	public:
		void SetUp()
		{
			m_subject = std::make_unique<Subject>();
		}
		
	protected:
		std::unique_ptr<Subject> m_subject;
	};
	
	TEST_F(SubjectTest, testNotifyObserversCallsUpdateOnAddedObserver)
	{
		MockObserver observer;
		m_subject->attach(&observer);
		
		EXPECT_CALL(observer, update(_));
		m_subject->notify();
	}
}}}