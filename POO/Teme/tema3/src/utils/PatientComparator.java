/**
 * Constantin Mihai - 321CD
 */

package utils;

import entities.Patient;

import java.util.Comparator;

public final class PatientComparator implements Comparator<Patient> {

    @Override
    public int compare(Patient o1, Patient o2) {
        if (o1.getUrgency().ordinal() == o2.getUrgency().ordinal()) {
            if (o1.getState().getSeverity() == o2.getState().getSeverity()) {
                return o2.getName().compareTo(o1.getName());
            }
            return o2.getState().getSeverity() - o1.getState().getSeverity();
        }
        return o1.getUrgency().ordinal() - o2.getUrgency().ordinal();
    }
}
