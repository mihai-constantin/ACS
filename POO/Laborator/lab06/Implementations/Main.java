package Implementations;

import java.util.LinkedList;
import java.util.List;

/**
 * @author Mihai Constantin, 321 CD
 */
public class Main {

    public static void main(String[] args) {

        Manager manager1 = new Manager("Edward", 110, 10, 15);
        Manager manager2 = new Manager("Bob", 100, 8, 10);

        List<Visitable> employees = new LinkedList<>();

        employees.add(manager1);
        employees.add(manager2);
        employees.add(new Employee("Alice", 20, 5));
        employees.add(new Employee("Angela", 25, 13));
        employees.add(new Employee("Emilia", 30, 8));
        employees.add(new Intern("Rares", 3));
        employees.add(new Intern("Misu", 5));

        manager1.addSubordinate(employees.get(2)); // Alice
        manager2.addSubordinate(employees.get(4)); // Emilia

        System.out.println("----------     RevenueVisitor     ----------");
        Visitor revenueVisitor = new RevenueVisitor();
        for (Visitable e : employees) {
            e.accept(revenueVisitor);
        }

        System.out.println("----------     TreeVisitor     ----------");
        Visitor treeVisitor = new TreeVisitor(revenueVisitor);
        for (Visitable e : employees) {
            e.accept(treeVisitor);
        }

        System.out.println("----------     MostHardworkingEmployeeFinder      ----------");
        Visitor mostHardworkingEmployeeFinder = new MostHardworkingEmployeeFinder();
        for (Visitable e : employees) {
            e.accept(mostHardworkingEmployeeFinder);
        }

        ((MostHardworkingEmployeeFinder) mostHardworkingEmployeeFinder).isManagerHardWorking();
    }
}
