#include "notifications_window.hpp"
#include "starlight/ui.hpp"
#include "imgui.h"

Starlight::UI::Windows::NotificationsWindow::NotificationsWindow() : Window("Notifications", 1280 - 250, 0, 250, 50, true)
{
    this->setTitleBar(false);
    this->setCollapse(false);
    this->setResize(false);
    this->setMove(false);
    this->setBringToFront(false);
    this->setNavFocus(false);
}

void Starlight::UI::Windows::NotificationsWindow::render()
{
    if (this->isEnabled() && this->notifications.size() > 0)
    {
        if (this->notifications[0].getPhase() == NotificationPhase::Expired)
        {
            this->notifications.erase(this->notifications.begin());
            return;
        }

        Notification notification = this->notifications[0];

        float displayPercentage = notification.getDisplayPercent();

        // use displayPercentage to show the notification from left to right
        int x = this->getX() - (this->getWidth() * displayPercentage);

        ImGui::SetNextWindowPos(ImVec2(x, this->getY()));
        ImGui::SetNextWindowSize(ImVec2(this->getWidth(), this->getHeight()));
        ImGui::Begin(this->getTitle().c_str(), nullptr, this->getFlags());

        ImGui::Text(notification.getText().c_str());

        ImGui::End();
    }
}

Starlight::UI::Notification::Notification(std::string text, nn::TimeSpan duration) : text(text), duration(duration), startTime(nn::os::GetSystemTick())
{
}

void Starlight::UI::Windows::NotificationsWindow::addNotification(Notification notification)
{
    this->notifications.push_back(notification);
}

nn::TimeSpan Starlight::UI::Notification::getTimeElapsed()
{
    return (nn::os::GetSystemTick() - this->startTime).ToTimeSpan();
}

void Starlight::UI::Notification::update()
{
    nn::TimeSpan elapsed = this->getTimeElapsed();

    if (this->phase == NotificationPhase::Queuing)
    {
        this->phase = NotificationPhase::FadeIn;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::FadeIn && elapsed > nn::TimeSpan::FromSeconds(1))
    {
        this->phase = NotificationPhase::Display;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::Display && elapsed > this->duration)
    {
        this->phase = NotificationPhase::FadeOut;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::FadeOut && elapsed > nn::TimeSpan::FromSeconds(1))
    {
        this->phase = NotificationPhase::Expired;
    }
}

Starlight::UI::NotificationPhase Starlight::UI::Notification::getPhase()
{
    return this->phase;
}

float Starlight::UI::Notification::getDisplayPercent()
{
    nn::TimeSpan elapsed = this->getTimeElapsed();
    this->update();

    if (this->phase == NotificationPhase::FadeIn)
    {
        return elapsed.GetMilliSeconds() / this->duration.GetMilliSeconds();
    }
    else if (this->phase == NotificationPhase::Display)
    {
        return 1;
    }
    else if (this->phase == NotificationPhase::FadeOut)
    {
        return 1 - (elapsed.GetMilliSeconds() / this->duration.GetMilliSeconds());
    }
    else
    {
        return 0;
    }
}