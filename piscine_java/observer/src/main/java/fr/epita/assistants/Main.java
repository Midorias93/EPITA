package fr.epita.assistants;

import fr.epita.assistants.observer.Lifeguard;
import fr.epita.assistants.observer.Person;
import fr.epita.assistants.observer.Swimmer;
import fr.epita.assistants.observer.SwimmerStatus;

public class Main {

    public static void main(String[] args) {
        final var swimmer = new Swimmer("Swimmer");
        final var lifeguard = new Lifeguard("Lifeguard");
        final var person = new Person("caca");

        swimmer.register(lifeguard);
        swimmer.register(person);

        swimmer.setStatus(SwimmerStatus.DROWNING);
        swimmer.setStatus(SwimmerStatus.TOO_FAR);
    }
}
