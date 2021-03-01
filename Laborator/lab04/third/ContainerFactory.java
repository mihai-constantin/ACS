package third;

import second.Container;
import second.Queue;
import second.Stack;

public class ContainerFactory implements IFactory {
    public static final ContainerFactory INSTANCE = new ContainerFactory();

    private ContainerFactory() {
    		
    }

    public Container createContainer(Strategy strategy) {
    	
    	Container container;
        
    	switch (strategy) {
			case FIFO:
				container = new Queue();
				break;
	
			default:
				container = new Stack();
				break;
		}
    	
    	return container;
    }
}