package second;

import java.util.ArrayList;

import first.Task;

public class Queue extends C {

	@Override
	public Task pop() {
		Task task = list.get(0);
		list.remove(0);
		return task;
	}
}