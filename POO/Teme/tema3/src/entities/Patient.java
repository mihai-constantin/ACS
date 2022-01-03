/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.InvestigationResult;
import skel.State;
import skel.Urgency;
import utils.PatientState;

import static skel.InvestigationResult.NOT_DIAGNOSED;

public final class Patient {

    private int id;
    private String name;
    private int age;
    private int time;
    private PatientState state;
    private State status;
    private boolean visitedByERTechnician;

    private InvestigationResult investigationResult = NOT_DIAGNOSED;
    private Urgency urgency = Urgency.NOT_DETERMINED;

    private int numberOfRoundsInHospital;

    public Patient() {
    }

    public Patient(int id, String name, int age, int time, PatientState state) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.time = time;
        this.state = state;
    }

    /**
     * @return Get patient's id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id Set patient's id to this value
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return Get patient's name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name Set patient's name to this value
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return Get patient's age
     */
    public int getAge() {
        return age;
    }

    /**
     * @return Get patient's time
     */
    public int getTime() {
        return time;
    }

    /**
     * @return Get patient's state
     */
    public PatientState getState() {
        return state;
    }

    /**
     * @return Get patient's status
     */
    public State getStatus() {
        return status;
    }

    /**
     * @param status Set patient's status to this value
     */
    public void setStatus(State status) {
        this.status = status;
    }

    /**
     * @return Get patient's investigationResult
     */
    public InvestigationResult getInvestigationResult() {
        return investigationResult;
    }

    /**
     * @param investigationResult Set patient's investigationResult to this value
     */
    public void setInvestigationResult(InvestigationResult investigationResult) {
        this.investigationResult = investigationResult;
    }

    /**
     * @return Get patient's urgency
     */
    public Urgency getUrgency() {
        return urgency;
    }

    /**
     * @param urgency Set patient's urgency to this value
     */
    public void setUrgency(Urgency urgency) {
        this.urgency = urgency;
    }

    /**
     * @return if a patient has benn visited by an ERTechnician
     */
    public boolean isVisitedByERTechnician() {
        return visitedByERTechnician;
    }

    /**
     * @param visitedByERTechnician Set if a patient has been visited by an ERTechnician
     */
    public void setVisitedByERTechnician(boolean visitedByERTechnician) {
        this.visitedByERTechnician = visitedByERTechnician;
    }

    /**
     * @return Get patient's numberOfRoundsInHospital
     */
    public int getNumberOfRoundsInHospital() {
        return numberOfRoundsInHospital;
    }

    /**
     * @param numberOfRoundsInHospital Set patient's numberOfRoundsInHospital to this value
     */
    public void setNumberOfRoundsInHospital(int numberOfRoundsInHospital) {
        this.numberOfRoundsInHospital = numberOfRoundsInHospital;
    }
}
