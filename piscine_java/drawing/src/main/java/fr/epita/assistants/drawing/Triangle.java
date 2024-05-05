package fr.epita.assistants.drawing;

public class Triangle extends Sharp {
    public Triangle(int lenght) {
        super(lenght);
    }
    @Override
    public void draw()
    {
        if (this.length == 0)
            return;
        System.out.println("#");

        for(int i = 0; i < this.length - 2; i++)
        {
            System.out.printf("# ");
            for (int j = 0; j < i; j++) {
                System.out.printf("  ");
            }
            System.out.println("#");
        }

        if(this.length > 1) {
            for (int i = 0; i < this.length; i++) {
                System.out.printf("# ");
            }
        }
        System.out.println();
    }
}