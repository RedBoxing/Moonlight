#pragma once

#include "nn/os/os_tick.hpp"
#include "nn/time.hpp"
#include "window.hpp"
#include <vector>
#include <string>

namespace Starlight
{
    namespace UI
    {
        enum NotificationPhase
        {
            Queuing,
            FadeIn,
            Display,
            FadeOut,
            Expired
        };

        class Notification
        {
        public:
            Notification(std::string text, nn::TimeSpan duration);

            void update();
            NotificationPhase getPhase();
            float getDisplayPercent();

            std::string getText();
            nn::TimeSpan getDuration();
            nn::TimeSpan getTimeElapsed();

        private:
            std::string text;
            nn::TimeSpan duration;
            nn::os::Tick startTime;
            NotificationPhase phase = NotificationPhase::Queuing;
        };

        namespace Windows
        {
            class NotificationsWindow : public Window
            {
            public:
                NotificationsWindow();
                ~NotificationsWindow();

                void render();

                void addNotification(Notification notification);

            private:
                std::vector<Notification> notifications;
            };
        }
    }
}