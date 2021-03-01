package Implementations;

/**
 * Clasa folosita pentru a vedea daca media numarului de ore suplimentare pentru angajati
 * este mai mare decat cea a managerilor.
 */
public class MostHardworkingEmployeeFinder implements Visitor {

    private float employessExtraHours;
    private float numberOfEmployees;
    private float managersExtraHours;
    private float numberOfManagers;

    private final float epsilon = 0.00001f;

    @Override
    public void visit(Employee employee) {
        employessExtraHours += employee.extraHours;
        numberOfEmployees++;
    }

    @Override
    public void visit(Manager manager) {
        managersExtraHours += manager.extraHours;
        numberOfManagers++;
    }

    @Override
    public void visit(Intern intern) {
        System.out.println(intern + " not paid");
    }

    public void isManagerHardWorking() {
        System.out.println("employeesExtraHours: " + employessExtraHours);
        System.out.println("managersExtraHours: " + managersExtraHours);

        float averageEmployeesExtraHours = employessExtraHours / numberOfEmployees;
        System.out.println("averageEmployeesExtraHours: " + averageEmployeesExtraHours);

        float averageManagersExtraHours = managersExtraHours / numberOfManagers;
        System.out.println("averageManagersExtraHours: " + averageManagersExtraHours);

        if (averageManagersExtraHours - averageEmployeesExtraHours > epsilon) {
            System.out.println("Managers are working harder that employees");
        } else {
            System.out.println("Employees are working harder than managers");
        }
    }
}
