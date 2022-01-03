/**
 * Constantin Mihai - 321CD
 */

package factories;

import entities.Cardiologist;
import entities.Doctor;
import entities.ERPhysician;
import entities.Gastroenterologist;
import entities.GeneralSurgeon;
import entities.Internist;
import entities.Neurologist;

public final class DoctorFactory {

    private DoctorFactory() {
    }

    /**
     * @param type            doctor's type
     * @param isSurgeon       if a doctor is a surgeon
     * @param maxForTreatment doctor's maxForTreatment
     * @return specialized doctor
     */
    public static Doctor createDoctor(Doctor.Type type, boolean isSurgeon, int maxForTreatment) {
        switch (type) {
            case CARDIOLOGIST:
                return new Cardiologist(type, type.toString(), isSurgeon, maxForTreatment);
            case ER_PHYSICIAN:
                return new ERPhysician(type, type.toString(), isSurgeon, maxForTreatment);
            case GASTROENTEROLOGIST:
                return new Gastroenterologist(type, type.toString(), isSurgeon, maxForTreatment);
            case GENERAL_SURGEON:
                return new GeneralSurgeon(type, type.toString(), isSurgeon, maxForTreatment);
            case INTERNIST:
                return new Internist(type, type.toString(), isSurgeon, maxForTreatment);
            default:
                return new Neurologist(type, type.toString(), isSurgeon, maxForTreatment);
        }
    }
}
