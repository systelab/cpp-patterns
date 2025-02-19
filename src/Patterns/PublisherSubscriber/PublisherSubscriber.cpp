#include "PublisherSubscriber.h"

namespace systelab::patterns
{
    void PublisherSubscriber::subscribe(const std::function<void(const Event&)>& callback, const std::string& topic)
    {
        std::unique_lock lock(m_mutex);
        m_subscribers[topic].push_back(callback);
    }

    void PublisherSubscriber::unsubscribe(const std::string& topic, const std::function<void(const Event&)>& callback)
    {
        std::unique_lock lock(m_mutex);
        if (m_subscribers.contains(topic))
        {
            std::erase_if(m_subscribers[topic], [&](const auto& func)
            { 
                return  func.target_type() == callback.target_type() && 
                        func.target<void(const Event&)>() == callback.target<void(const Event&)>();
            });

            if (m_subscribers[topic].empty())
            {
                m_subscribers.erase(topic);
            }
        }
    }

    void PublisherSubscriber::publish(const Event& evt)
    {
        std::shared_lock lock(m_mutex);
        if (m_subscribers.contains(evt.m_name))
        {
            for (const auto& subscriber : m_subscribers[evt.m_name])
            {
                subscriber(evt);
            }
        }
    }
}