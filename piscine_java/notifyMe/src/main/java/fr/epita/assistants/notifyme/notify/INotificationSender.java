package fr.epita.assistants.notifyme.notify;

public interface INotificationSender {
    void notify(final String parSender, final String parReceiver, final String parMessage);
}