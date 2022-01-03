package skel;

/**
 * IMMEDIATE > URGENT > LESS_URGENT > NON_URGENT.
 * NON_URGENT means it will not enter the emergency flows
 * <p>
 * [Part of the homework's skeleton]
 */
public enum Urgency {
    IMMEDIATE,
    URGENT,
    LESS_URGENT,
    NON_URGENT,
    NOT_DETERMINED;
}
