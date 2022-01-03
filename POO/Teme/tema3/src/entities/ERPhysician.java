/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.IllnessType;

import java.util.ArrayList;
import java.util.List;

public class ERPhysician extends Doctor {

    private static final double C1 = 0.1;
    private static final double C2 = 0.3;

    public ERPhysician(Doctor.Type enumType, String type, boolean isSurgeon, int maxForTreatment) {
        super(enumType, type, isSurgeon, maxForTreatment);

        List<IllnessType> array = new ArrayList<>();
        array.add(IllnessType.ALLERGIC_REACTION);
        array.add(IllnessType.BROKEN_BONES);
        array.add(IllnessType.BURNS);
        array.add(IllnessType.CAR_ACCIDENT);
        array.add(IllnessType.CUTS);
        array.add(IllnessType.HIGH_FEVER);
        array.add(IllnessType.SPORT_INJURIES);
        setIllnessTypes(array);
        setC1(C1);
        setC2(C2);
    }
}
