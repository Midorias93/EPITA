package fr.epita.assistants.drawing;

public class Circle extends Entity {
    public Circle(int radius) {
        this.radius = radius;
    }
    int radius;
    @Override
    public void draw(){
        int sqDist = 0;
        for (int y = -radius; y <= radius; y++)
        {
            for(int x = -radius; x <= radius; x++)
            {
                sqDist = Math.abs(radius * radius - (x * x + y * y));

                if (sqDist < radius)
                {
                    System.out.printf("#");
                }
                else
                {
                    System.out.printf(" ");
                }
                if (x < radius)
                    System.out.printf(" ");
            }
            if (y < radius) {
                System.out.println();
            }
        }
    }
}
