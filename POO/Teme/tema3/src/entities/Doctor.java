/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class Doctor {

    private String type;
    private Type enumType;
    private boolean isSurgeon;
    private int maxForTreatment;
    private List<IllnessType> illnessTypes;
    private double c1;
    private double c2;
    private static final int T = 22;

    private List<Patient> patients = new ArrayList<>();

    public Doctor() {
    }

    public Doctor(Type enumType, String type, boolean isSurgeon, int maxForTreatment) {
        this.enumType = enumType;
        this.type = type;
        this.isSurgeon = isSurgeon;
        this.maxForTreatment = maxForTreatment;
    }

    /**
     * @return doctor's type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type Set type of a doctor to this value
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * @return if a doctor is or is not a surgeon
     */
    public boolean getIsSurgeon() {
        return isSurgeon;
    }

    /**
     * @param surgeon Set if a doctor can be a surgeon
     */
    public void setIsSurgeon(boolean surgeon) {
        isSurgeon = surgeon;
    }

    /**
     * @return doctor's maxForTreatment
     */
    public int getMaxForTreatment() {
        return maxForTreatment;
    }

    /**
     * @return the list of illnesses that a doctor can treat
     */
    public List<IllnessType> getIllnessTypes() {
        return illnessTypes;
    }

    /**
     * @param illnessTypes Set the list of illnesses that a doctor can treat
     */
    public void setIllnessTypes(List<IllnessType> illnessTypes) {
        this.illnessTypes = illnessTypes;
    }

    /**
     * @return factor c1 of a doctor
     */
    public double getC1() {
        return c1;
    }

    /**
     * @param c1 Set factor c1 for a doctor
     */
    public void setC1(double c1) {
        this.c1 = c1;
    }

    /**
     * @return factor c2 of a doctor
     */
    public double getC2() {
        return c2;
    }

    /**
     * @param c2 Set factor c2 for a doctor
     */
    public void setC2(double c2) {
        this.c2 = c2;
    }

    /**
     * @return the doctor's patients
     */
    public List<Patient> getPatients() {
        return patients;
    }

    public static int getT() {
        return T;
    }

    public enum Type {
        CARDIOLOGIST("Cardiologist"),
        ER_PHYSICIAN("ERPhysician"),
        GASTROENTEROLOGIST("Gastroenterologist"),
        GENERAL_SURGEON("General Surgeon"),
        INTERNIST("Internist"),
        NEUROLOGIST("Neurologist");
        private String value;

        Type(String value) {
            this.value = value;
        }

        public String getValue() {
            return value;
        }
    }

    /**
     * @return the type of a doctor
     */
    public Type getEnumType() {
        return enumType;
    }

    /**
     * @param enumType Set doctor's type
     */
    public void setEnumType(Type enumType) {
        this.enumType = enumType;
    }
}
