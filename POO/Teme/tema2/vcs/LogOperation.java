package vcs;


import utils.ErrorCodeManager;
import utils.OperationType;

import java.util.ArrayList;

public class LogOperation extends VcsOperation {

    public LogOperation(OperationType type, ArrayList<String> operationArgs) {
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

        Branch currentBranch = vcs.getBranches().get(vcs.getIdxCurrentBranch());

        for (int i = 0; i < currentBranch.getCommits().size(); i++) {

            vcs.getOutputWriter().write("Commit id: "
                    + currentBranch.getCommits().get(i).getId() + "\n");

            vcs.getOutputWriter().write("Message: "
                    + currentBranch.getCommits().get(i).getMessage() + "\n");

            if (i != currentBranch.getCommits().size() - 1) {
                vcs.getOutputWriter().write("\n");
            }
        }

        return ErrorCodeManager.OK;
    }


}
