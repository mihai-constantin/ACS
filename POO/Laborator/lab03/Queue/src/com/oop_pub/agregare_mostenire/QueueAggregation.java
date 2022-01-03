package com.oop_pub.agregare_mostenire;

public class QueueAggregation {
	
	private Array array;
	private int u;
	
	public QueueAggregation() {
		array = new Array();
	}
	
	public int enqueue(int x) {
		
		if(array.set(u, x) != 0) {
			return Array.ERROR;
		}
		u++;
		return 1;
	}
	
	public int dequeue() {
		if(u == 0) {
			return Array.ERROR;
		}
		
		int value =  array.get(0);
		for(int i = 1; i < u; i++) {
			array.set(i - 1, array.get(i));
		}
		
		array.set(u - 1, 0);
		u--;
		
		return value;
	}
	
	public static void main(String[] args) {
		
		QueueAggregation queue = new QueueAggregation();
		
		System.out.println(queue.dequeue()); // coada vida -> eroare
		
		queue.enqueue(Array.ERROR);
		queue.enqueue(15);
		queue.enqueue(27);
		queue.enqueue(30);
		queue.enqueue(21);
		queue.enqueue(34);
		queue.enqueue(56);
		queue.enqueue(98);
		queue.enqueue(23);
		queue.enqueue(54);
		System.out.println(queue.enqueue(12));
		
		System.out.println(queue.array.toString());
		
		queue.dequeue();
		System.out.println(queue.array.toString());
		
		queue.dequeue();
		queue.dequeue();
		queue.enqueue(7);
		queue.enqueue(17);
		queue.enqueue(27);
		System.out.println(queue.enqueue(37)); // coada plida -> eroare
		
		System.out.println(queue.array.toString());
		queue.dequeue();
		queue.enqueue(3);
		
		System.out.println(queue.array.toString());
		
	}

}
