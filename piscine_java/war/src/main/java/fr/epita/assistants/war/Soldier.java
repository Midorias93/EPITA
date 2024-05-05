package fr.epita.assistants.war;

public class Soldier extends Combatant {
    int health;
    int damage_point;
    String scream;
    public Soldier() {
        this.health = 15;
        this.damage_point = 3;
        this.scream = "No pity for losers!";
    }
    public void kill() {
        this.health = 0;
    }
    @Override
    void attack(Soldier s) {
        s.health -= this.damage_point;
    }

    @Override
    void attack(Vehicle v) {
        System.out.println("I can't fight this.");
    }

    @Override
    public void scream() {
        System.out.println(this.scream);
    }
}