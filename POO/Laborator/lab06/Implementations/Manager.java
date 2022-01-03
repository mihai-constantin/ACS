package Implementations;

import java.util.LinkedList;

public class Manager extends Employee {
    protected float bonus;

    private LinkedList<Visitable> subordinates = new LinkedList<Visitable>();

    public Manager(String name, float salary, float bonus) {
        super(name, salary);
        this.bonus = bonus;
    }

    public Manager(String name, float salary, float extraHours, float bonus) {
        super(name, salary, extraHours);

        this.bonus = bonus;
    }

    public float getBonus() {
        return bonus;
    }

    public LinkedList<Visitable> getSubordinates() {
        return this.subordinates;
    }

    public void addSubordinate(Visitable subordinate) {
        subordinates.add(subordinate);
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
