package Implementations;

public class Intern implements Visitable {

    private String name;
    private int duration;  // in months

    public Intern(String name, int duration){
        this.name = name;
        this.duration = duration;
    }

    public String getName() {
        return name;
    }

    public int getDuration() {
        return duration;
    }

    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }

    @Override
    public String toString() {
        return name;
    }
}
