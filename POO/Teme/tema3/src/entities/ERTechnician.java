/**
 * Constantin Mihai - 321CD
 */

package entities;

import skel.InvestigationResult;

public final class ERTechnician {

    private static final int C1 = 75;
    private static final int C2 = 40;

    private static ERTechnician erTechnician = null;

    private ERTechnician() {
    }

    public static ERTechnician getInstance() {
        if (erTechnician == null) {
            erTechnician = new ERTechnician();
        }
        return erTechnician;
    }

    public InvestigationResult investigate(Patient patient) {
        // ERTechnician decides if the patient should be operated, hospitalized or sent home
        if (patient.getState().getSeverity() > C1) {
            return InvestigationResult.OPERATE;
        }
        if (patient.getState().getSeverity() > C2) {
            return InvestigationResult.HOSPITALIZE;
        }
        return InvestigationResult.TREATMENT;
    }
}
