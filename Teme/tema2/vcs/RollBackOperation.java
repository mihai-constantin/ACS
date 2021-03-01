package vcs;


import utils.ErrorCodeManager;
import utils.OperationType;

import java.util.ArrayList;

public class RollBackOperation extends VcsOperation {

    public RollBackOperation(OperationType type, ArrayList<String> operationArgs) {
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

        vcs.setStaging(new ArrayList<String>());

        Branch currentBranch = vcs.getBranches().get(vcs.getIdxCurrentBranch());

        vcs.setActiveSnapshot(currentBranch.getCommits()
                .get(currentBranch.getCommits().size() - 1)
                .getFileSystemSnapshot().cloneFileSystem());

        return ErrorCodeManager.OK;
    }
}
