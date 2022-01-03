/**
 * Constantin Mihai - 321CD
 */

package utils;

import skel.IllnessType;

public final class PatientState {

    private IllnessType illnessName;
    private int severity;

    public IllnessType getIllnessName() {
        return illnessName;
    }

    public void setIllnessName(IllnessType illnessName) {
        this.illnessName = illnessName;
    }

    public int getSeverity() {
        return severity;
    }

    public void setSeverity(int severity) {
        this.severity = severity;
    }
}
