package fr.epita.assistants.observer;

public class Lifeguard implements Observable.Observer<Swimmer> {
    String lifeguardName;
    public Lifeguard(String lifeguardName) {
        this.lifeguardName = lifeguardName;
        System.out.println(lifeguardName + " begins to keep an eye on the swimmers.");
    }
    @Override
    public void onEvent(Swimmer event) {
        if(event.status == SwimmerStatus.DROWNING)
            System.out.println(this.lifeguardName + ": I will save you " + event.swimmerName + "!");
        if(event.status == SwimmerStatus.TOO_FAR)
            System.out.println(this.lifeguardName + ": " + event.swimmerName + "! You are too far, come back!");
    }
}