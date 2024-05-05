package fr.epita.assistants.notifyme.user;

import fr.epita.assistants.notifyme.notify.INotificationSender;

import java.util.ArrayList;
import java.util.List;

public class User implements IMultiNotificationSender {
    String username;
    List<INotificationSender> parNotificationList;
    public User(final String username, final List<INotificationSender> parNotificationList)
    {
        this.username = username;
        this.parNotificationList = parNotificationList;
    }
    public User(final String username)
    {
        this.username = username;
        this.parNotificationList = new ArrayList<>();
    }
    public String getUsername()
    {
        return this.username;
    }
    @Override
    public void sendNotifications(String parRecipient, String parMessage) {
        for (INotificationSender iNotificationSender : parNotificationList) {
            iNotificationSender.notify(this.username, parRecipient, parMessage);
        }
    }

    @Override
    public void addNotifier(INotificationSender parNotifier) {
        this.parNotificationList.add(parNotifier);
    }

    @Override
    public List<INotificationSender> getNotifiers() {
        return this.parNotificationList;
    }
}