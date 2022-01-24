// Enum with integer data stored in an instance field
package com.luxoft.effectivejava.module04.item23;

public enum Team {
	SOLO(1), DUET(2), TRIO(3), QUARTET(4), QUINTET(5), SEXTET(6), SEPTET(7), OCTET(8), DOUBLE_QUARTET(8), NONET(
			9), DECTET(10), TRIPLE_QUARTET(12);

	private final int numberOfMembers;

	Team(int size) {
		this.numberOfMembers = size;
	}

	public int numberOfMembers() {
		return numberOfMembers;
	}
}
