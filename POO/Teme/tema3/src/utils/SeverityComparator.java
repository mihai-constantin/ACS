/**
 * Constantin Mihai - 321CD
 */

package utils;

import entities.Patient;

import java.util.Comparator;

public final class SeverityComparator implements Comparator<Patient> {

    @Override
    public int compare(Patient o1, Patient o2) {
        return o2.getState().getSeverity() - o1.getState().getSeverity();
    }
}
