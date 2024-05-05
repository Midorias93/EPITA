package fr.epita.assistants.notifyme.notify;

public class ShellNotifier implements INotificationSender{

    boolean parSTDErr;
    public ShellNotifier(final boolean parSTDErr) {
        this.parSTDErr = parSTDErr;

    }

    @Override
    public void notify(String parSender, String parReceiver, String parMessage) {
        if(parSTDErr)
            System.err.println("Notification from " + parSender + " to " + parReceiver + " received: "  + parMessage);
        else
            System.out.println("Notification from " + parSender + " to " + parReceiver + " received: "  + parMessage);
    }
}