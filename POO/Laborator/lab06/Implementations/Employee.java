package Implementations;

public class Employee implements Visitable {
    protected String name;
    protected float salary;
    protected float extraHours;

    public Employee(final String name, final float salary) {
        this.name = name;
        this.salary = salary;
    }

    public Employee(final String name, final float salary, final float extraHours) {
        this.name = name;
        this.salary = salary;
        this.extraHours = extraHours;
    }

    public String getName() {
        return name;
    }

    public float getSalary() {
        return salary;
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
