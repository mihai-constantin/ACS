package second;

import first.Task;

import java.util.ArrayList;

abstract public class C implements Container {

    ArrayList<Task> list = new ArrayList<Task>();

    abstract public Task pop();

    @Override
    public void push(Task task) {
        list.add(task);
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public boolean isEmpty() {
        if(list.size() == 0) {
            return true;
        }
        return false;
    }

    @Override
    public void transferFrom(Container container) {
        while(!container.isEmpty()) {
            push(container.pop());
        }

    }

}
