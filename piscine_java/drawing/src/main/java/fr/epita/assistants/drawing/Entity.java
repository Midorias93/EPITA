package fr.epita.assistants.drawing;
abstract public class Entity implements IDrawable {
    final private long id;

    private static long SEQUENCE = 0;
    public Entity() {
        id = SEQUENCE++;
    }
    public long getId()
    {
        return id;
    }
    @Override
    public void draw(){}


}