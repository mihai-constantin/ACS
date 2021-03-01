package vcs;

import java.util.ArrayList;
import java.util.List;

public class Branch {

    private String name;
    private List<Commit> commits = new ArrayList<Commit>();

    public Branch(String name, Commit initialCommit) {
        this.name = name;
        this.commits.add(initialCommit);
    }

    /**
     * Sets the branch's name.
     *
     * @param name the branch's name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Gets the branch's name.
     *
     * @return the branch's name
     */

    public String getName() {
        return name;
    }

    /**
     * Gets the branch's commits.
     *
     * @return the branch's commits
     */

    public List<Commit> getCommits() {
        return commits;
    }

    /**
     * Sets the branch's commits.
     *
     * @param commits the branch's commits.
     */

    public void setCommits(List<Commit> commits) {
        this.commits = commits;
    }
}
