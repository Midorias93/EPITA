package fr.epita.assistants.war;

public class Vehicle extends Combatant {
    String name;
    int defense_points;
    public Vehicle(String name, int defense) {
        this.defense_points = defense;
        this.name = name;
    }
    @Override
    void attack(Soldier s) {
        s.kill();
    }

    @Override
    void attack(Vehicle v) {
        v.defense_points /= 2;
    }

    @Override
    public void scream() {
        System.out.println("I'm " + this.name + "!");
    }
}