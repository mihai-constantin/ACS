/**
 * Constantin Mihai - 321CD
 */

package stages;

import entities.Patient;
import simulation.Hospital;
import skel.State;
import utils.SeverityComparator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class TriageQueue {

    private List<Patient> queue = new ArrayList<>();
    private static TriageQueue triageQueue = null;

    private TriageQueue() {
    }

    public static TriageQueue getInstance() {
        if (triageQueue == null) {
            triageQueue = new TriageQueue();
        }
        return triageQueue;
    }

    public List<Patient> getQueue() {
        return queue;
    }


    public void addPatients(List<Patient> patients, int time) {
        Hospital hospital = Hospital.getInstance();

        for (Patient patient : patients) {
            if (patient.getTime() == time) {
                queue.add(patient);
                hospital.getPatients().add(patient);
            }
        }

        SeverityComparator severityComparator = new SeverityComparator();
        Collections.sort(queue, severityComparator);

        for (Patient patient : queue) {
            patient.setStatus(State.TRIAGEQUEUE);
        }

        ExaminationQueue examinationQueue = ExaminationQueue.getInstance();

        for (int i = 0; i < Math.min(queue.size(), hospital.getNumberOfNurses()); i++) {
            examinationQueue.getQueue().add(queue.get(i));
        }

        int size = queue.size();

        for (int i = 0; i < Math.min(size, hospital.getNumberOfNurses()); i++) {
            queue.remove(0);
        }
    }
}
