/**
 * Constantin Mihai - 321CD
 */

package observers;

import entities.Doctor;
import entities.Nurses;
import entities.Patient;
import simulation.Hospital;
import skel.State;

import java.util.Observer;
import java.util.Observable;
import java.util.Comparator;
import java.util.List;
import java.util.Collections;
import java.util.ArrayList;

public final class SituationPrinter implements Observer {

    /**
     * @param o   the observable object, i.e. the hospital
     * @param arg unused
     */
    @Override
    public void update(Observable o, Object arg) {
        Hospital h = (Hospital) o;
        System.out.println("~~~~ Patients in round " + h.getNumberOfRound() + " ~~~~");

        List<Patient> patients = h.getPatients(); // the list of patients to be printed

        // sort the list alphabetically
        Collections.sort(patients, Comparator.comparing(Patient::getName));

        // print the status for every patient
        for (Patient patient : patients) {
            System.out.println(patient.getName() + " is " + patient.getStatus().getValue());
        }

        System.out.println();
        System.out.println("~~~~ Nurses treat patients ~~~~");

        Nurses nurses = Nurses.getInstance();
        // get the list of hospitalized patients
        List<Patient> hospitalizedPatients = nurses.getPatients();
        // sort the list alphabetically
        Collections.sort(hospitalizedPatients, Comparator.comparing(Patient::getName));
        int idx = 0;
        int print = 0;
        if (hospitalizedPatients.size() > 0) {
            do {
                String name = hospitalizedPatients.get(print).getName();
                int rounds = hospitalizedPatients.get(print).getNumberOfRoundsInHospital();
                if (hospitalizedPatients.get(print).getNumberOfRoundsInHospital() == 1) {
                    System.out.println("Nurse " + idx + " treated " + name
                            + " and patient has " + rounds + " more round");
                } else {
                    System.out.println("Nurse " + idx + " treated " + name
                            + " and patient has " + rounds + " more rounds");
                }

                print++;
                idx++;

                if (idx == h.getNumberOfNurses()) {
                    idx = 0;
                }
            } while (print < hospitalizedPatients.size());

            // verify if any patient has finished his treatment
            List<Patient> newHospitalizedPatients = new ArrayList<>();
            for (Patient patient : hospitalizedPatients) {
                int severity = patient.getState().getSeverity();
                int rounds = patient.getNumberOfRoundsInHospital();
                if (severity > 0 && rounds != 0) {
                    newHospitalizedPatients.add(patient);
                }
            }

            // set the list of hospitalized patients to its new value
            nurses.setPatients(newHospitalizedPatients);
        }

        System.out.println();
        System.out.println("~~~~ Doctors check their hospitalized patients and give verdicts ~~~~");

        // get the list of doctors in input order
        List<Doctor> initialDoctors = h.getInitialDoctors();
        for (Doctor doctor : initialDoctors) {
            List<Patient> copyPatients = new ArrayList<>(doctor.getPatients());
            Collections.sort(copyPatients, Comparator.comparing(Patient::getName));
            // every doctor visits his patients
            for (Patient patient : copyPatients) {
                if (patient.getStatus() != State.HOME_DONE_TREATMENT) {
                    int severity = patient.getState().getSeverity();
                    int rounds = patient.getNumberOfRoundsInHospital();
                    if (severity <= 0 || rounds == 0) {
                        // doctor sent the patient home
                        System.out.println(doctor.getEnumType().getValue() + " sent "
                                + patient.getName() + " home");
                        patient.setStatus(State.HOME_DONE_TREATMENT);
                    } else {
                        // patient needs more days in hospital
                        System.out.println(doctor.getEnumType().getValue()
                                + " says that " + patient.getName() + " should remain in hospital");
                    }
                }

            }
        }
        System.out.println();
    }
}
