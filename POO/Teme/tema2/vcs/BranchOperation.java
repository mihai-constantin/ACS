package vcs;

import utils.ErrorCodeManager;
import utils.IDGenerator;
import utils.OperationType;

import java.util.ArrayList;

public class BranchOperation extends VcsOperation {

    public BranchOperation(OperationType type, ArrayList<String> operationArgs) {
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

        String nameNewBranch = operationArgs.get(1);

        for (int i = 0; i < vcs.getBranches().size(); i++) {
            if (nameNewBranch.equals(vcs.getBranches().get(i).getName())) {
                return ErrorCodeManager.VCS_BAD_CMD_CODE;
            }
        }

        Commit newCommit = new Commit(IDGenerator.generateCommitID(),
                vcs.getCurrentCommit().getMessage(),
                vcs.getCurrentCommit().getFileSystemSnapshot());

        Branch newBranch = new Branch(nameNewBranch, newCommit);

        vcs.getBranches().add(newBranch);

        return ErrorCodeManager.OK;
    }


}
