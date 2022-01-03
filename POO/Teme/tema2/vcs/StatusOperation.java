package vcs;

import utils.ErrorCodeManager;
import utils.OperationType;

import java.util.ArrayList;
import java.util.List;

public class StatusOperation extends VcsOperation {

    public StatusOperation(OperationType type, ArrayList<String> operationArgs) {
        super(type, operationArgs);
    }

    /**
     * Executes the operation.
     *
     * @param vcs the vcs
     * @return the return code
     */
    @Override
    public int execute(Vcs vcs) {

        List<String> currentStaging = vcs.getStaging();

        vcs.getOutputWriter().write("On branch: "
                + vcs.getBranches().get(vcs.getIdxCurrentBranch()).getName() + "\n");

        vcs.getOutputWriter().write("Staged changes:" + "\n");
        for (int i = 0; i < currentStaging.size(); i++) {
            vcs.getOutputWriter().write("\t" + currentStaging.get(i) + "\n");
        }

        return ErrorCodeManager.OK;
    }


}
