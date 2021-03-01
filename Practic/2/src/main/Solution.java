package main;

import java.util.*;

/*
 * DO NOT MODIFY THIS INTERFACE
 */
interface Visitable {
    void accept(Visitor printer, int number);
}

interface Visitor {
    /*
     * Add signatures of methods here in order to implement
     * Double Dispatch
     */

    void visit(GuitarStudent guitarStudent, int number);

    void visit(PianoStudent pianoStudent, int number);

    void visit(DrumsStudent drumsStudent, int number);
}

class PermissionVisitor implements Visitor {
    /*
     * TODO:
     * Complete this class with the methods from the interface.
     */

    @Override
    public void visit(GuitarStudent guitarStudent, int number) {
//        System.out.println("intra");
//        System.out.println(guitarStudent.money + " " + guitarStudent.moneyPerCourse + " " + number);

//        System.out.println(guitarStudent.money / guitarStudent.moneyPerCourse);

        System.out.println("The student can go to " + guitarStudent.money / guitarStudent.moneyPerCourse
                + " guitar classes out of " + number);
    }

    @Override
    public void visit(PianoStudent pianoStudent, int number) {

        System.out.println("The student can go to " + pianoStudent.money / pianoStudent.moneyPerCourse
                + " piano classes out of " + number);
    }

    @Override
    public void visit(DrumsStudent drumsStudent, int number) {

        System.out.println("The student can go to " + drumsStudent.money / drumsStudent.moneyPerCourse
                + " drums classes out of " + number);
    }
}

class AccountantVisitor implements Visitor {
    /*
     * Complete this class with the methods from the interface.
     */

    @Override
    public void visit(GuitarStudent guitarStudent, int number) {

        guitarStudent.money += number;
        System.out.println("Successful payment for guitar class");
    }

    @Override
    public void visit(PianoStudent pianoStudent, int number) {
        pianoStudent.money += number;
        System.out.println("Successful payment for piano class");
    }

    @Override
    public void visit(DrumsStudent drumsStudent, int number) {
        drumsStudent.money += number;
        System.out.println("Successful payment for drums class");
    }
}

class GuitarStudent implements Visitable {
    public String name;
    public int moneyPerCourse = 20;
    public int money;

    public GuitarStudent(String name) {
        this.name = name;
    }

    public void accept(Visitor visitor, int number) {
        /*
         * TODO:
         * Complete this method.
         */

        visitor.visit(this, number);
    }
}

class PianoStudent implements Visitable {
    public String name;
    public int moneyPerCourse = 30;
    public int money;

    public PianoStudent(String name) {
        this.name = name;
    }

    public void accept(Visitor visitor, int number) {
        /*
         * TODO:
         * Complete this method.
         */

        visitor.visit(this, number);
    }
}

class DrumsStudent implements Visitable {
    public String name;
    public int moneyPerCourse = 15;
    public int money;

    public DrumsStudent(String name) {
        this.name = name;
    }

    public void accept(Visitor visitor, int number) {
        /*
         * TODO:
         * Complete this method.
         */

        visitor.visit(this, number);
    }
}

/*
 * DO NOT MODIFY THIS CLASS
 */
class Register {
    // static variable register of type Register
    private static Register register = null;

    // keeping record of all students with a hashmap
    public HashMap<String, Visitable> students;

    // private constructor
    private Register() {
        students = new HashMap<>();
    }

    public Visitable getStudent(String name) {
        return students.get(name);
    }

    public void addStudent(String name, String course) {
        if (course.equals("guitar")) {
            students.put(name, new GuitarStudent(name));
        }
        if (course.equals("piano")) {
            students.put(name, new PianoStudent(name));
        }
        if (course.equals("drums")) {
            students.put(name, new DrumsStudent(name));
        }
    }

    // static method to create instance of Register class
    public static Register getInstance() {
        if (register == null)
            register = new Register();
        return register;
    }
}

/*
 * DO NOT MODIFY THIS CLASS
 */
public class Solution {
    public static void main(String[] args) {
        Register register = Register.getInstance();
        HashMap<String, Visitor> visitors = new HashMap<>();

        visitors.put("permission", new PermissionVisitor());
        visitors.put("accountant", new AccountantVisitor());

        Scanner scanner = new Scanner(System.in);
        while (!scanner.hasNext("stop")) {
            if (scanner.hasNext("enroll")) {
                scanner.next();
                register.addStudent(scanner.next(), scanner.next());
            } else {
                Visitor visitor = visitors.get(scanner.next());
                register.getStudent(scanner.next()).accept(visitor, scanner.nextInt());
            }
        }

        scanner.close();
    }
}