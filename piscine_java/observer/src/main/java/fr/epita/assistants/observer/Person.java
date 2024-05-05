package fr.epita.assistants.observer;

public class Person implements Observable.Observer<Swimmer> {
    String personName;
    public Person(String personName) {
        this.personName = personName;
    }
    @Override
    public void onEvent(Swimmer event) {
        if (event.status == SwimmerStatus.WAVING)
            System.out.println(this.personName + ": Waves at " + event.swimmerName + ".");
    }
}