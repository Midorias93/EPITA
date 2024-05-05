package fr.epita.assistants.triad;

public class WriteGettersAndConstructorForMe {
    private final String name;
    private final String firstName;

    public String getName() {
        return name;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getRandom() {
        return random;
    }

    public String getAnotherOne() {
        return anotherOne;
    }

    public String getAnotherOne2() {
        return anotherOne2;
    }

    public String getAnotherOne3() {
        return anotherOne3;
    }

    public String getXyz() {
        return xyz;
    }

    public int getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public float getZ() {
        return z;
    }

    public Boolean getB() {
        return b;
    }

    public boolean isC() {
        return c;
    }

    private final String lastName;

    private final String random;

    private final String anotherOne;

    private final String anotherOne2;

    private final String anotherOne3;

    private final String xyz;

    private final int x;

    private final double y;

    private final float z;

    private final Boolean b;

    private final boolean c;

    public WriteGettersAndConstructorForMe(String name, String firstName, String lastName, String random, String anotherOne, String anotherOne2, String anotherOne3, String xyz, int x, double y, float z, Boolean b, boolean c) {
        this.name = name;
        this.firstName = firstName;
        this.lastName = lastName;
        this.random = random;
        this.anotherOne = anotherOne;
        this.anotherOne2 = anotherOne2;
        this.anotherOne3 = anotherOne3;
        this.xyz = xyz;
        this.x = x;
        this.y = y;
        this.z = z;
        this.b = b;
        this.c = c;
    }

    // FIXME: Add a constructor with all the parameters and all the getters
}
