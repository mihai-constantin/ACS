package vcs;

import filesystem.FileSystemSnapshot;

public class Commit {

    private int id;
    private String message;
    private FileSystemSnapshot fileSystemSnapshot;

    public Commit(int id, String message, FileSystemSnapshot fileSystemSnapshot) {
        this.id = id;
        this.message = message;
        this.fileSystemSnapshot = fileSystemSnapshot.cloneFileSystem();
    }

    /**
     * Gets the commit's id.
     *
     * @return the commit's id
     */
    public int getId() {
        return id;
    }

    /**
     * Sets the commit's id.
     *
     * @param id the commit's id
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Gets the commit's message.
     *
     * @return the commit's message
     */
    public String getMessage() {
        return message;
    }

    /**
     * Sets the commit's message.
     *
     * @param message the commit's message
     */
    public void setMessage(String message) {
        this.message = message;
    }

    /**
     * Gets the fileSystemSnapshot.
     *
     * @return the fileSystemSnapshot
     */
    public FileSystemSnapshot getFileSystemSnapshot() {
        return fileSystemSnapshot;
    }
}
