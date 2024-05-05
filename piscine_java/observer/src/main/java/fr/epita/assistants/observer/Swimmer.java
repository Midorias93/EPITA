package fr.epita.assistants.observer;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Swimmer implements Observable<Swimmer> {
    Set<Observer<Swimmer>> observers;
    String swimmerName;
    SwimmerStatus status = SwimmerStatus.OK;

    public void setStatus(SwimmerStatus status) {
        if (status == SwimmerStatus.DROWNING) {
            this.status = status;
            System.out.println(this.swimmerName + ": I'm drowning, help!!");
            fire(this);
        } else if (status == SwimmerStatus.WAVING) {
            this.status = status;
            System.out.println(swimmerName + ": Waves towards the shore.");
            fire(this);
        } else {
            this.status = status;
            fire(this);
        }
    }

    public String getName() {
        return swimmerName;
    }

    public SwimmerStatus getStatus() {
        return status;
    }

    public Swimmer(String swimmerName) {
        this.swimmerName = swimmerName;
        System.out.println(swimmerName + " goes into the sea.");
        this.observers = new HashSet<>();
    }

    @Override
    public Set<Observer<Swimmer>> getObservers() {
        return this.observers;
    }

    @Override
    public void register(Observer<Swimmer>... observers) {
        if (observers == null) {
            return;
        }
        this.observers.addAll(List.of(observers));

    }

    @Override
    public void unregister(Observer<Swimmer> observer) {
        this.observers.remove(observer);
    }

    @Override
    public void fire(Swimmer event) {
        if (this.observers != null) {
            for (int i = 0; i < this.observers.size(); i++) {
                this.observers.stream().toList().get(i).onEvent(event);
            }
        }
    }
}