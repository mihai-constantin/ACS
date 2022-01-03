/**
 * Constantin Mihai - 321CD
 */

package stages;

import entities.Doctor;
import entities.Nurses;
import entities.Patient;
import simulation.Hospital;
import skel.IllnessType;
import skel.State;
import utils.PatientComparator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class ExaminationQueue {

    private List<Patient> queue = new ArrayList<>();
    private static ExaminationQueue examinationQueue = null;
    private static final int CONST = 3;

    private ExaminationQueue() {
    }

    public static ExaminationQueue getInstance() {
        if (examinationQueue == null) {
            examinationQueue = new ExaminationQueue();
        }
        return examinationQueue;
    }

    public List<Patient> getQueue() {
        return queue;
    }

    public static void homeComing(Doctor.Type type, Patient patient) {
        switch (type) {
            case CARDIOLOGIST:
                patient.setStatus(State.HOME_CARDIO);
                break;
            case ER_PHYSICIAN:
                patient.setStatus(State.HOME_ERPHYSICIAN);
                break;
            case GASTROENTEROLOGIST:
                patient.setStatus(State.HOME_GASTRO);
                break;
            case GENERAL_SURGEON:
                patient.setStatus(State.HOME_SURGEON);
                break;
            case INTERNIST:
                patient.setStatus(State.HOME_INTERNIST);
                break;
            case NEUROLOGIST:
                patient.setStatus(State.HOME_NEURO);
                break;
            default:
        }
    }

    public static void numberOfRoundsPatient(Patient patient, Doctor doctor) {
        double ans = patient.getState().getSeverity() * doctor.getC1();
        int rounds = Math.max((int) (Math.round(ans)), CONST);

        patient.setNumberOfRoundsInHospital(rounds);
    }

    public static void searchSurgeon(Doctor.Type type, Patient patient, Doctor doctor) {
        int oldSeverity = patient.getState().getSeverity();
        int newSeverity = oldSeverity - (int) (Math.round(oldSeverity * doctor.getC2()));
        patient.getState().setSeverity(newSeverity);

        numberOfRoundsPatient(patient, doctor);
        Nurses nurses = Nurses.getInstance();
        nurses.getPatients().add(patient);
        switch (type) {
            case CARDIOLOGIST:
                patient.setStatus(State.OPERATED_CARDIO);
                doctor.getPatients().add(patient);
                break;
            case ER_PHYSICIAN:
                patient.setStatus(State.OPERATED_ERPHYSICIAN);
                doctor.getPatients().add(patient);
                break;
            case GENERAL_SURGEON:
                patient.setStatus(State.OPERATED_SURGEON);
                doctor.getPatients().add(patient);
                break;
            case NEUROLOGIST:
                patient.setStatus(State.OPERATED_NEURO);
                doctor.getPatients().add(patient);
                break;
            default:
        }
    }

    public void investigate() {

        PatientComparator patientComparator = new PatientComparator();
        Collections.sort(queue, patientComparator);

        for (Patient patient : queue) {
            patient.setStatus(State.EXAMINATIONSQUEUE);
        }

        Hospital hospital = Hospital.getInstance();
        List<Doctor> doctors = hospital.getDoctors();

        int idx;
        for (int i = 0; i < queue.size(); i++) {
            idx = -1;
            Patient patient = queue.get(i);
            for (int j = 0; j < doctors.size(); j++) {
                for (IllnessType illnessType : doctors.get(j).getIllnessTypes()) {
                    if (illnessType.equals(patient.getState().getIllnessName())) {
                        idx = j;
                        break;
                    }
                }

                if (idx != -1) {
                    break;
                }
            }

            if (idx != -1) {
                Doctor doctor = doctors.get(idx);
                Doctor.Type type = doctor.getEnumType();
                if (!patient.isVisitedByERTechnician()) {
                    // verify if the patient can be sent at home
                    if (patient.getState().getSeverity() <= doctor.getMaxForTreatment()) {
                        homeComing(type, patient);
                    } else {
                        // patient goes to InvestigationQueue
                        InvestigationsQueue investigationsQueue = InvestigationsQueue.getInstance();
                        investigationsQueue.getQueue().add(patient);
                    }
                } else {
                    // patient has been visited by an ER Technician

                    switch (patient.getInvestigationResult()) {
                        case OPERATE:
                            // verify if doctor isSurgeon
                            if (!doctor.getIsSurgeon()) {
                                // search for another doctor
                                idx = -1;
                                for (int j = idx + 1; j < doctors.size(); j++) {
                                    for (IllnessType illness : doctors.get(j).getIllnessTypes()) {
                                        if (illness.equals(patient.getState().getIllnessName())
                                                && doctors.get(j).getIsSurgeon()) {
                                            idx = j;
                                            break;
                                        }
                                    }
                                    if (idx != -1) {
                                        break;
                                    }
                                }

                                if (idx == -1) {
                                    patient.setStatus(State.OTHERHOSPITAL);
                                } else {
                                    doctor = doctors.get(idx);
                                    type = doctor.getEnumType();

                                    searchSurgeon(type, patient, doctor);
                                }

                            } else {
                                searchSurgeon(type, patient, doctor);
                            }

                            break;
                        case HOSPITALIZE:
                            numberOfRoundsPatient(patient, doctor);

                            Nurses nurses = Nurses.getInstance();
                            nurses.getPatients().add(patient);

                            switch (type) {
                                case CARDIOLOGIST:
                                    patient.setStatus(State.HOSPITALIZED_CARDIO);
                                    doctor.getPatients().add(patient);
                                    break;
                                case ER_PHYSICIAN:
                                    patient.setStatus(State.HOSPITALIZED_ERPHYSICIAN);
                                    doctor.getPatients().add(patient);
                                    break;
                                case GASTROENTEROLOGIST:
                                    patient.setStatus(State.HOSPITALIZED_GASTRO);
                                    doctor.getPatients().add(patient);
                                    break;
                                case GENERAL_SURGEON:
                                    patient.setStatus(State.HOSPITALIZED_SURGEON);
                                    doctor.getPatients().add(patient);
                                    break;
                                case INTERNIST:
                                    patient.setStatus(State.HOSPITALIZED_INTERNIST);
                                    doctor.getPatients().add(patient);
                                    break;
                                case NEUROLOGIST:
                                    patient.setStatus(State.HOSPITALIZED_NEURO);
                                    doctor.getPatients().add(patient);
                                    break;
                                default:
                            }
                            break;
                        case TREATMENT:
                            homeComing(type, patient);
                            break;
                        default:
                    }

                }

                if (idx != -1) {
                    doctors.remove(idx);
                    doctors.add(doctor);
                }

            } else {
                // no doctor found
                patient.setStatus(State.OTHERHOSPITAL);
            }
        }

        queue.clear();
    }

}
