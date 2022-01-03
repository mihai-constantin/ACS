/**
 * Constantin Mihai - 321CD
 */

package simulation;

import entities.Doctor;
import entities.Patient;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;

public final class Hospital extends Observable {

    private List<Doctor> doctors = new ArrayList<>();
    private List<Doctor> initialDoctors;
    private List<Patient> patients = new ArrayList<>();

    private int numberOfRound;

    private int numberOfNurses;
    private int numberOfInvestigators;

    private static Hospital hospital = null;

    private Hospital() {
    }

    public static Hospital getInstance() {
        if (hospital == null) {
            hospital = new Hospital();
        }
        return hospital;
    }

    public void update() {
        this.setChanged();
        this.notifyObservers();
    }

    public List<Doctor> getDoctors() {
        return doctors;
    }

    public void setDoctors(List<Doctor> doctors) {
        this.doctors = doctors;
    }

    public List<Patient> getPatients() {
        return patients;
    }

    public void setPatients(List<Patient> patients) {
        this.patients = patients;
    }

    public int getNumberOfRound() {
        return numberOfRound;
    }

    public void setNumberOfRound(int numberOfRound) {
        this.numberOfRound = numberOfRound;
    }

    public void setNumberOfNurses(int numberOfNurses) {
        this.numberOfNurses = numberOfNurses;
    }

    public void setNumberOfInvestigators(int numberOfInvestigators) {
        this.numberOfInvestigators = numberOfInvestigators;
    }

    public int getNumberOfNurses() {
        return numberOfNurses;
    }

    public int getNumberOfInvestigators() {
        return numberOfInvestigators;
    }

    public List<Doctor> getInitialDoctors() {
        return initialDoctors;
    }

    public void setInitialDoctors(List<Doctor> initialDoctors) {
        this.initialDoctors = initialDoctors;
    }
}
