#include "stdafx.h"

#include "../src/Patterns/PublisherSubscriber/PublisherSubscriber.h"

namespace systelab::patterns
{
    class PublisherSubscriberTest : public ::testing::Test
    {
    protected:
        PublisherSubscriber pubsub;
        struct TestEvent : public PublisherSubscriber::Event
        {
            TestEvent(const std::string& name) { m_name = name; }
        };
    };

    TEST_F(PublisherSubscriberTest, SubscribeAndPublish)
    {
        bool callbackInvoked = false;

        pubsub.subscribe([&](const PublisherSubscriber::Event& evt) {
            callbackInvoked = true;
            EXPECT_EQ(evt.m_name, "TestTopic");
        }, "TestTopic");

        TestEvent evt("TestTopic");
        pubsub.publish(evt);

        EXPECT_TRUE(callbackInvoked);
    }

    TEST_F(PublisherSubscriberTest, Unsubscribe)
    {
        bool callbackInvoked = false;
        auto callback = [&](const PublisherSubscriber::Event& evt) {
            callbackInvoked = true;
        };

        pubsub.subscribe(callback, "TestTopic");
        pubsub.unsubscribe("TestTopic", callback);

        TestEvent evt("TestTopic");
        pubsub.publish(evt);

        EXPECT_FALSE(callbackInvoked);
    }

    TEST_F(PublisherSubscriberTest, PublishWithoutSubscribers)
    {
        TestEvent evt("NoSubscribers");
        EXPECT_NO_FATAL_FAILURE(pubsub.publish(evt));
    }
}