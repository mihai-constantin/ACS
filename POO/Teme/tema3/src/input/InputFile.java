/**
 * Constantin Mihai - 321CD
 */

package input;

import entities.Doctor;
import entities.Patient;

import java.util.List;

public final class InputFile {

    private int simulationLength;
    private int nurses;
    private int investigators;
    private List<Doctor> doctors;
    private List<Patient> incomingPatients;

    /**
     * @return Get simulationLength
     */
    public int getSimulationLength() {
        return simulationLength;
    }

    /**
     * @param simulationLength Set simulationLength to this value
     */
    public void setSimulationLength(int simulationLength) {
        this.simulationLength = simulationLength;
    }

    /**
     * @return Get number of nurses
     */
    public int getNurses() {
        return nurses;
    }

    /**
     * @param nurses Set number of nurses to this value
     */
    public void setNurses(int nurses) {
        this.nurses = nurses;
    }

    /**
     * @return Get number of ERTechnicians
     */
    public int getInvestigators() {
        return investigators;
    }

    /**
     * @param investigators Set number of ERTechnicians to this value
     */
    public void setInvestigators(int investigators) {
        this.investigators = investigators;
    }

    /**
     * @return Get list of doctors
     */
    public List<Doctor> getDoctors() {
        return doctors;
    }

    /**
     * @param doctors Set list of doctors to this value
     */
    public void setDoctors(List<Doctor> doctors) {
        this.doctors = doctors;
    }

    /**
     * @return Get list of incoming patients
     */
    public List<Patient> getIncomingPatients() {
        return incomingPatients;
    }

    /**
     * @param incomingPatients Set list of incoming patients to this value
     */
    public void setIncomingPatients(List<Patient> incomingPatients) {
        this.incomingPatients = incomingPatients;
    }
}
