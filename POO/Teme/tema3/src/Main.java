/**
 * Constantin Mihai - 321CD
 */

import com.fasterxml.jackson.databind.ObjectMapper;
import entities.Doctor;
import entities.Patient;
import factories.DoctorFactory;
import input.InputFile;
import observers.NextRound;
import observers.SituationPrinter;
import simulation.Simulator;
import simulation.Hospital;
import skel.Urgency;
import skel.UrgencyEstimator;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public final class Main {

    private Main() {
    }

    public static void main(String[] args) throws Exception {
        // get inputFile
        String file = args[0];

        // read json file data to String
        byte[] jsonData = Files.readAllBytes(Paths.get(file));

        // create ObjectMapper instance
        ObjectMapper objectMapper = new ObjectMapper();

        // convert json string to object
        InputFile inputFile = objectMapper.readValue(jsonData, InputFile.class);

        // get the list of incomingPatients
        List<Patient> patients = inputFile.getIncomingPatients();

        UrgencyEstimator urgencyEstimator = UrgencyEstimator.getInstance();

        // set urgency for every patient
        for (Patient patient : patients) {
            Urgency urgency = urgencyEstimator.estimateUrgency(patient.getState().getIllnessName(),
                    patient.getState().getSeverity());
            patient.setUrgency(urgency);
        }

        // set the type for every doctor
        List<Doctor> doctors = inputFile.getDoctors();
        for (int i = 0; i < doctors.size(); i++) {
            switch (doctors.get(i).getType()) {
                case "CARDIOLOGIST":
                    doctors.get(i).setEnumType(Doctor.Type.CARDIOLOGIST);
                    break;
                case "ER_PHYSICIAN":
                    doctors.get(i).setEnumType(Doctor.Type.ER_PHYSICIAN);
                    break;
                case "GASTROENTEROLOGIST":
                    doctors.get(i).setEnumType(Doctor.Type.GASTROENTEROLOGIST);
                    break;
                case "GENERAL_SURGEON":
                    doctors.get(i).setEnumType(Doctor.Type.GENERAL_SURGEON);
                    doctors.get(i).setIsSurgeon(true);
                    break;
                case "INTERNIST":
                    doctors.get(i).setEnumType(Doctor.Type.INTERNIST);
                    break;
                case "NEUROLOGIST":
                    doctors.get(i).setEnumType(Doctor.Type.NEUROLOGIST);
                    break;
                default:
            }
        }

        Hospital hospital = Hospital.getInstance();
        hospital.setNumberOfNurses(inputFile.getNurses());
        hospital.setNumberOfInvestigators(inputFile.getInvestigators());

        // set SituationPrinter as observer for the hospital
        hospital.addObserver(new SituationPrinter());
        hospital.addObserver(new NextRound());

        // create specialized doctors and put them into hospital
        for (Doctor doctor : doctors) {
            hospital.getDoctors().add(DoctorFactory.createDoctor(doctor.getEnumType(),
                    doctor.getIsSurgeon(), doctor.getMaxForTreatment()));
        }

        // create an array that stores doctors in input order
        hospital.setInitialDoctors(new ArrayList<>(hospital.getDoctors()));

        // ER simulator
        Simulator simulator = Simulator.getInstance();
        simulator.simulate(inputFile.getSimulationLength(), patients);
    }
}
