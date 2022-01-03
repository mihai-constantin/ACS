package main;

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

/* ONLY WRITE CODE WHERE THE TODO'S ARE! */
class EmployeesManagement {
    public Employee bestEmployee;

    public Employee getBestEmployee() {
        return bestEmployee;
    }

    public class Employee {
        int hours;
        String name;

        Employee(int hours, String name) {
            this.name = name;
            this.hours = hours;
            /*
             * TODO
             * Complete the constructor by figuring out if this employee is the best one yet
             */

            if (bestEmployee == null) {
                bestEmployee = this;
            } else {
                if (hours >= bestEmployee.hours) {
                    bestEmployee = this;
                }
            }
        }

    }
}

public class Solution {

    public static void main(String[] args) {

        EmployeesManagement employeesManagement = new EmployeesManagement();
        Scanner sc = new Scanner(System.in);

        int nrArguments = Integer.parseInt(sc.nextLine());

        for (int i = 0; i < nrArguments; i++) {
            String input = sc.nextLine();
            String[] params = input.split(" ");
            /*
             * TODO
             * Create new Employee
             */
            EmployeesManagement.Employee employee = employeesManagement.new Employee(Integer.parseInt(params[0]), params[1]);

//            System.out.println(Integer.parseInt(params[0]) + " " + params[1]);

        }

        System.out.println(employeesManagement.getBestEmployee().name);
    }
}