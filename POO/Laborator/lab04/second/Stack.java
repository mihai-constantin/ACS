package second;

import java.util.ArrayList;

import first.Task;

public class Stack extends C {

	@Override
	public Task pop() {
		int idx = list.size() - 1;
		Task task = list.get(idx);
		list.remove(idx);
		return task;
	}


}
