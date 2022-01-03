package vcs;


import filesystem.FileSystemSnapshot;
import utils.EntityType;
import utils.ErrorCodeManager;
import utils.IDGenerator;
import utils.OperationType;

import java.util.ArrayList;

public class CommitOperation extends VcsOperation {

    public CommitOperation(OperationType type, ArrayList<String> operationArgs) {
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

        if (vcs.getStaging().size() == 0) {
            return ErrorCodeManager.VCS_BAD_CMD_CODE;
        }

        String newMessage = "";

        for (int i = 2; i < operationArgs.size() - 1; i++) {
            newMessage += operationArgs.get(i) + " ";
        }

        newMessage += operationArgs.get(operationArgs.size() - 1);

        FileSystemSnapshot fileSystemSnapshot = vcs.getActiveSnapshot().cloneFileSystem();

        for (int i = 0; i < vcs.getStaging().size(); i++) {

            final int position = 8;
            String entityType = vcs.getStaging().get(i).substring(position);

            if (entityType.startsWith("file")) {
                final int pos = 5;
                fileSystemSnapshot.addEntity(EntityType.FILE, "", entityType.substring(pos));
            }
        }

        Commit commit = new Commit(IDGenerator.generateCommitID(), newMessage, fileSystemSnapshot);
        vcs.getBranches().get(vcs.getIdxCurrentBranch()).getCommits().add(commit);

        vcs.setStaging(new ArrayList<String>());

        return ErrorCodeManager.OK;
    }
}
