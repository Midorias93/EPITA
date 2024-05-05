package fr.epita.assistants.staticpen;

public class Pen {
    public enum Color {
        RED,
        BLUE
    };
    Color couleur;
    static int counter = 0;
    static int red_counter = 0;
    static int blue_counter = 0;

    public Pen(final Color color) {
        couleur = color;
        counter++;
        if (color == Color.RED)
            red_counter++;
        if (color == Color.BLUE)
            blue_counter++;
    }

    public static int getRedPenCounter() {
        return red_counter;
    }

    public static int getPenCounter() {
        return counter;
    }

    public static int getBluePenCounter() {
       return blue_counter;
    }

    public void changeColor(final Color color) {
        if (this.couleur == Color.BLUE) {
            this.couleur = Color.RED;
            red_counter++;
            blue_counter--;
        }
        else
        {
            this.couleur = Color.BLUE;
            blue_counter++;
            red_counter--;
        }
    }

    public static void resetCounts() {
        red_counter = 0;
        blue_counter =0;
        counter = 0;
    }

    public void print() {
        System.out.println("I'm a " + couleur.toString() +  " pen.");
    }
}
