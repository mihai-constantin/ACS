package Implementations;

/**
 * Clasa folosita pentru a afisa detaliile angajatilor. Aplica operatia doar pe obiecte ce
 * implementeaza interfata Visitable.
 */
public class RevenueVisitor implements Visitor {
    @Override
    public void visit(Employee employee) {
        System.out.println(employee.getName() + " " + employee.getSalary());
    }

    @Override
    public void visit(Manager manager) {
        System.out.println(manager.getName() + " " + (manager.getSalary() + manager.getBonus()));
    }

    @Override
    public void visit(Intern intern) {
        System.out.println(intern.getName() + " " + intern.getDuration());
    }
}
