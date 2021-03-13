package ro.pub.systems.eim.lab02.activitylifecyclemonitor.entities;

public class Credential {

    private String username;
    private String password;

    public Credential() {
        username = new String();
        password = new String();
    }

    public Credential(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

}
