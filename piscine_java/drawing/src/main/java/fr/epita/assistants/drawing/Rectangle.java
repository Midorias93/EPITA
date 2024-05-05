package fr.epita.assistants.drawing;

public class Rectangle extends Sharp {
    int width;

    public Rectangle(int width ,int length) {
        super(length);
        this.width = width;
    }
    @Override
    public void draw()
    {
        if (this.length == 0 || this.width == 0)
            return;
        for (int i = 0; i < this.width; i++)
        {
            System.out.printf("# ");
        }
        System.out.println();
        for (int i = 2; i < this.length; i++)
        {
            System.out.printf("# ");
            for(int j = 2; j < this.width; j++)
            {
                System.out.printf("  ");
            }
            System.out.printf("#");
            System.out.println();
        }
        if (this.length > 1) {
            for (int i = 0; i < this.width; i++) {
                System.out.printf("# ");
            }
        }
        System.out.println();
    }
}