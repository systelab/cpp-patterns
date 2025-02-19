#include "stdafx.h"

#include <functional>
#include <shared_mutex>
#include <unordered_map>
#include <thread>
#include <vector>

namespace systelab::patterns 
{
	class PublisherSubscriber
    {
    public:
        struct Event
        {
            virtual ~Event() = default;
            std::string m_name;
        };

		virtual ~PublisherSubscriber() = default;

        void subscribe(const std::function<void(const Event&)>& callback, const std::string& topic);
        void unsubscribe(const std::string& topic, const std::function<void(const Event&)>& callback);
        void publish(const Event& evt);
    private:
        std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> m_subscribers;
        mutable std::shared_mutex m_mutex;
    };
}