package fr.epita.assistants.war;

abstract public class Combatant {
    void printState() {
        if (this instanceof Vehicle)
            System.out.println("I have " + ((Vehicle) this).defense_points +" defense points.");
        else if (this instanceof Soldier)
            System.out.println("I have " + ((Soldier) this).health + " health points.");
        else
            System.err.println("Error 404. Class not found.");
    }
    abstract void attack(Soldier s);
    abstract void attack(Vehicle v);
    abstract void scream();
}