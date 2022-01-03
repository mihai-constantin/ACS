package vcs;

import filesystem.FileSystemOperation;
import filesystem.FileSystemSnapshot;
import utils.IDGenerator;
import utils.OutputWriter;
import utils.Visitor;

import java.util.ArrayList;
import java.util.List;

public final class Vcs implements Visitor {
    private final OutputWriter outputWriter;
    private FileSystemSnapshot activeSnapshot;

    private List<Branch> branches = new ArrayList<Branch>();
    private List<String> staging = new ArrayList<String>();

    private int idxCurrentBranch;
    private Commit currentCommit;

    /**
     * Vcs constructor.
     *
     * @param outputWriter the output writer
     */
    public Vcs(OutputWriter outputWriter) {
        this.outputWriter = outputWriter;
    }

    /**
     * Does initialisations.
     */
    public void init() {
        this.activeSnapshot = new FileSystemSnapshot(outputWriter);

        Commit initialCommit = new Commit(IDGenerator.generateCommitID(),
                "First commit", getActiveSnapshot().cloneFileSystem());

        Branch initialBranch = new Branch("master", initialCommit);
        branches.add(initialBranch);

        this.idxCurrentBranch = 0;
        this.currentCommit = initialCommit;

    }

    /**
     * Visits a file system operation.
     *
     * @param fileSystemOperation the file system operation
     * @return the return code
     */
    public int visit(FileSystemOperation fileSystemOperation) {
        return fileSystemOperation.execute(this.activeSnapshot);
    }

    /**
     * Visits a vcs operation.
     *
     * @param vcsOperation the vcs operation
     * @return return code
     */
    @Override
    public int visit(VcsOperation vcsOperation) {
        return vcsOperation.execute(this);
    }


    public OutputWriter getOutputWriter() {
        return outputWriter;
    }

    public void setStaging(List<String> staging) {
        this.staging = staging;
    }

    public List<String> getStaging() {
        return staging;
    }

    public void setCurrentCommit(Commit currentCommit) {
        this.currentCommit = currentCommit;
    }

    public Commit getCurrentCommit() {
        return this.currentCommit;
    }

    public void setIdxCurrentBranch(int idxCurrentBranch) {
        this.idxCurrentBranch = idxCurrentBranch;
    }

    public int getIdxCurrentBranch() {
        return idxCurrentBranch;
    }

    public List<Branch> getBranches() {
        return branches;
    }

    public void setActiveSnapshot(FileSystemSnapshot activeSnapshot) {
        this.activeSnapshot = activeSnapshot;
    }

    public FileSystemSnapshot getActiveSnapshot() {
        return activeSnapshot;
    }

}
