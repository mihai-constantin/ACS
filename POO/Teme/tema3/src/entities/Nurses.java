/**
 * Constantin Mihai - 321CD
 */

package entities;

import java.util.ArrayList;
import java.util.List;

public final class Nurses {

    private List<Patient> patients = new ArrayList<>();
    private static Nurses nurses = null;

    private Nurses() {
    }

    public static Nurses getInstance() {
        if (nurses == null) {
            nurses = new Nurses();
        }
        return nurses;
    }

    public List<Patient> getPatients() {
        return patients;
    }

    public void setPatients(List<Patient> patients) {
        this.patients = patients;
    }

    public void treat() {
        for (Patient patient : patients) {
            patient.setNumberOfRoundsInHospital(patient.getNumberOfRoundsInHospital() - 1);
            patient.getState().setSeverity(patient.getState().getSeverity() - Doctor.getT());
        }
    }
}
