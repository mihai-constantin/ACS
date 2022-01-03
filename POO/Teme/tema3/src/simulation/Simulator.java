/**
 * Constantin Mihai - 321CD
 */

package simulation;

import entities.Nurses;
import entities.Patient;
import stages.ExaminationQueue;
import stages.InvestigationsQueue;
import stages.TriageQueue;

import java.util.List;

public final class Simulator {

    private static Simulator simulator = null;

    private Simulator() {
    }

    public static Simulator getInstance() {
        if (simulator == null) {
            simulator = new Simulator();
        }
        return simulator;
    }

    public void simulate(int length, List<Patient> patients) {

        Hospital hospital = Hospital.getInstance();
        TriageQueue triageQueue = TriageQueue.getInstance();
        ExaminationQueue examinationQueue = ExaminationQueue.getInstance();
        InvestigationsQueue investigationsQueue = InvestigationsQueue.getInstance();
        Nurses nurses = Nurses.getInstance();

        for (int i = 0; i < length; i++) {
            triageQueue.addPatients(patients, i);
            examinationQueue.investigate();
            investigationsQueue.investigate();
            nurses.treat();
            hospital.update();
        }

    }
}
