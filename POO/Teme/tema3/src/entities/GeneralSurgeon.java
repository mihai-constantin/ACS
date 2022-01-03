/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class GeneralSurgeon extends Doctor {

    private static final double C1 = 0.2;
    private static final double C2 = 0.2;

    public GeneralSurgeon(Doctor.Type enumType, String type, boolean isSurgeon,
                          int maxForTreatment) {
        super(enumType, type, isSurgeon, maxForTreatment);

        List<IllnessType> array = new ArrayList<>();
        array.add(IllnessType.ABDOMINAL_PAIN);
        array.add(IllnessType.BURNS);
        array.add(IllnessType.CAR_ACCIDENT);
        array.add(IllnessType.CUTS);
        array.add(IllnessType.SPORT_INJURIES);
        setIllnessTypes(array);
        setC1(C1);
        setC2(C2);
    }
}
