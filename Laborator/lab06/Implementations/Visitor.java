package Implementations;

public interface Visitor {
    void visit(Employee employee);

    void visit(Manager manager);

    void visit(Intern intern);
}