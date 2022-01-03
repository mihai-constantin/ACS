/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class Internist extends Doctor {

    private static final double C1 = 0.01;
    private static final double C2 = 0;

    public Internist(Doctor.Type enumType, String type, boolean isSurgeon, int maxForTreatment) {
        super(enumType, type, isSurgeon, maxForTreatment);
        List<IllnessType> array = new ArrayList<>();
        array.add(IllnessType.ABDOMINAL_PAIN);
        array.add(IllnessType.ALLERGIC_REACTION);
        array.add(IllnessType.FOOD_POISONING);
        array.add(IllnessType.HEART_DISEASE);
        array.add(IllnessType.HIGH_FEVER);
        array.add(IllnessType.PNEUMONIA);
        setIllnessTypes(array);
        setC1(C1);
        setC2(C2);
    }
}
