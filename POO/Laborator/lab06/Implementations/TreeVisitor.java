package Implementations;

import java.util.LinkedList;

/**
 * Clasa folosita pentru a parcurge o structura ierarhica / arborescenta - separa doua
 * concepte: un obiect de tipul visitor ce realizeaza operatii pe un set de date
 * (ex. calculeaza media orelor suplimentare) si acest tip de visitor (TreeVisitor)
 * ce parcurge nodurile structurii arborescente si aplica visitor-ul ce realizeaza operatii
 * (prezentat anterior).
 */
public class TreeVisitor implements Visitor {

    private Visitor baseVisitor;

    public TreeVisitor(Visitor baseVisitor) {
        this.baseVisitor = baseVisitor;
    }

    @Override
    public void visit(Employee employee) {
        employee.accept(baseVisitor);
    }

    @Override
    public void visit(Manager manager) {
        manager.accept(baseVisitor);

        LinkedList<Visitable> subordinates = manager.getSubordinates();

        System.out.print("Subordinates: ");
        for (Visitable subordinate : subordinates) {
            System.out.print(subordinate + " ");
        }
        System.out.println();
    }

    @Override
    public void visit(Intern intern) {
        intern.accept(baseVisitor);
    }

    public Visitor getBaseVisitor() {
        return baseVisitor;
    }
}