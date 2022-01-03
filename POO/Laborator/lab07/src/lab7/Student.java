package lab7;

public class Student {

    String nume;
    float medie;

    public Student(String nume, float medie){
        this.nume = nume;
        this.medie = medie;
    }

    @Override
    public String toString() {
        return this.nume + " " + this.medie;
    }

    public static void main(String[] args){

    }
}
