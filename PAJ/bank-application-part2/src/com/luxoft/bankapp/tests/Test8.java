package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.luxoft.bankapp.domain.Department;
import com.luxoft.bankapp.employees.BankEmployee;

public class Test8 {
	
	@Test
	public void testManager() {
		Department department = new Department("Accounting");
		BankEmployee richard = new BankEmployee("Richard", department, 1000);
		BankEmployee bob = new BankEmployee("Bob", department, 1000);
		department.setManager(richard);
		assertEquals(bob.getDepartment().getManager().name, "Richard");
	}

}
