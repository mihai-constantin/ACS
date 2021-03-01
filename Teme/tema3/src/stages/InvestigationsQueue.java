/**
 * Constantin Mihai - 321CD
 */

package stages;

import entities.ERTechnician;
import entities.Patient;
import simulation.Hospital;
import skel.InvestigationResult;
import skel.State;
import utils.PatientComparator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class InvestigationsQueue {

    private List<Patient> queue = new ArrayList<>();
    private static InvestigationsQueue investigationsQueue = null;

    private InvestigationsQueue() {
    }

    public static InvestigationsQueue getInstance() {
        if (investigationsQueue == null) {
            investigationsQueue = new InvestigationsQueue();
        }
        return investigationsQueue;
    }

    public List<Patient> getQueue() {
        return queue;
    }

    public void investigate() {
        Hospital hospital = Hospital.getInstance();

        PatientComparator patientComparator = new PatientComparator();
        Collections.sort(queue, patientComparator);

        for (Patient patient : queue) {
            patient.setStatus(State.INVESTIGATIONSQUEUE);
        }

        ExaminationQueue examinationQueue = ExaminationQueue.getInstance();
        ERTechnician erTechnician = ERTechnician.getInstance();

        for (int i = 0; i < Math.min(queue.size(), hospital.getNumberOfInvestigators()); i++) {
            examinationQueue.getQueue().add(queue.get(i));
            queue.get(i).setStatus(State.EXAMINATIONSQUEUE);
            queue.get(i).setVisitedByERTechnician(true);
            InvestigationResult investigationResult = erTechnician.investigate(queue.get(i));
            queue.get(i).setInvestigationResult(investigationResult);
        }

        int size = queue.size();
        for (int i = 0; i < Math.min(size, hospital.getNumberOfInvestigators()); i++) {
            queue.remove(0);
        }

    }

}
