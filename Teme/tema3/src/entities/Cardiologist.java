/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class Cardiologist extends Doctor {

    private static final double C1 = 0.4;
    private static final double C2 = 0.1;

    public Cardiologist(Doctor.Type enumType, String type, boolean isSurgeon, int maxForTreatment) {
        super(enumType, type, isSurgeon, maxForTreatment);

        List<IllnessType> array = new ArrayList<>();
        array.add(IllnessType.HEART_ATTACK);
        array.add(IllnessType.HEART_DISEASE);
        setIllnessTypes(array);
        setC1(C1);
        setC2(C2);
    }
}
