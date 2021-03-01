package com.oop_pub.agregare_mostenire;

public class QueueInheritance extends Array {
	
	private int u;
	
	public String enqueue(int x) {
		if(this.set(u, x) != 0) {
			return "ERROR!";
		}
		
		u++;
		return "1";
	}
	
	public String dequeue() {
		
		if(u == 0) {
			return "ERROR";
		}
		
		int value = this.get(0);
		for(int i = 1; i < u; i++) {
			this.set(i - 1, this.get(i));
		}
		
		this.set(u - 1, 0);
		u--;
		
		return Integer.toString(value);
	}

	public static void main(String[] args) {
		
		QueueInheritance queue = new QueueInheritance();
		
		System.out.println(queue.dequeue());
		
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
		System.out.println(queue.enqueue(12)); // ERROR
		
		System.out.println(queue.toString());
		
		System.out.println(queue.dequeue());
		queue.dequeue();
		queue.dequeue();
		queue.dequeue();
		System.out.println(queue.toString());
		
		queue.enqueue(10);
		queue.enqueue(15);
		queue.enqueue(27);
		queue.enqueue(33);
		System.out.println(queue.enqueue(22)); // ERROR
		System.out.println(queue.toString());
		
	}
}
