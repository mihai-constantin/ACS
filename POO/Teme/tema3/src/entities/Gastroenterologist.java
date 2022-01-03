/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class Gastroenterologist extends Doctor {

    private static final double C1 = 0.5;
    private static final double C2 = 0;

    public Gastroenterologist(Doctor.Type enumType, String type, boolean isSurgeon,
                              int maxForTreatment) {
        super(enumType, type, isSurgeon, maxForTreatment);
        List<IllnessType> array = new ArrayList<>();
        array.add(IllnessType.ABDOMINAL_PAIN);
        array.add(IllnessType.ALLERGIC_REACTION);
        array.add(IllnessType.FOOD_POISONING);
        setIllnessTypes(array);
        setC1(C1);
        setC2(C2);
    }
}
