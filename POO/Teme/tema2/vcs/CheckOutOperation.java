package vcs;


import utils.ErrorCodeManager;
import utils.OperationType;

import java.util.ArrayList;
import java.util.List;

public class CheckOutOperation extends VcsOperation {

    public CheckOutOperation(OperationType type, ArrayList<String> operationArgs) {
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

        operationArgs.remove(0);

        if (vcs.getStaging().size() != 0) {
            return ErrorCodeManager.VCS_STAGED_OP_CODE;
        }

        if (operationArgs.size() > 1) {

            boolean ok = false;
            int idxCommit = 0;
            Branch currentBranch = vcs.getBranches().get(vcs.getIdxCurrentBranch());
            for (int i = 0; i < currentBranch.getCommits().size(); i++) {

                if (currentBranch.getCommits().get(i).getId()
                        == Integer.parseInt(operationArgs.get(1))) {
                    ok = true;
                    idxCommit = i;
                    vcs.setCurrentCommit(currentBranch.getCommits().get(idxCommit));
                    break;
                }
            }

            if (!ok) {
                return ErrorCodeManager.VCS_BAD_PATH_CODE;
            } else {
                List<Commit> commits = new ArrayList<Commit>();

                for (int i = 0; i <= idxCommit; i++) {
                    commits.add(currentBranch.getCommits().get(i));
                }

                currentBranch.setCommits(commits);
                vcs.setActiveSnapshot(currentBranch.getCommits()
                        .get(idxCommit).getFileSystemSnapshot().cloneFileSystem());
            }

        } else {

            String branchName = operationArgs.get(0);

            boolean ok = false;
            int idxBranch = 0;
            for (int i = 0; i < vcs.getBranches().size(); i++) {
                if (vcs.getBranches().get(i).getName().equals(branchName)) {
                    ok = true;
                    idxBranch = i;
                }
            }

            if (!ok) {
                return ErrorCodeManager.VCS_BAD_CMD_CODE;
            }

            vcs.setIdxCurrentBranch(idxBranch);

            int numberOfCommitsOnCurrentBranch = vcs.getBranches()
                    .get(idxBranch).getCommits().size();
            Commit newCurrentCommit = vcs.getBranches().get(idxBranch)
                    .getCommits().get(numberOfCommitsOnCurrentBranch - 1);

            vcs.setCurrentCommit(newCurrentCommit);
            vcs.setActiveSnapshot(newCurrentCommit.getFileSystemSnapshot().cloneFileSystem());
        }

        return ErrorCodeManager.OK;
    }
}
