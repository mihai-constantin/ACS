package exercise1;

public class Persoana {

    private String name;
    private int age;
    private final double GPA;

    public Persoana(final String name, final int age, final double GPA) {
        this.name = name;
        this.age = age;
        this.GPA = GPA;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public double getGPA() {
        return GPA;
    }

    @Override
    public int hashCode() {
        return (int) ((name.length() + age + Math.ceil(GPA)) % MyHashMap.getDIMENSION());
    }

    @Override
    public String toString() {
        return "{" + name + " " + age + " " + GPA + "}";
    }
}
