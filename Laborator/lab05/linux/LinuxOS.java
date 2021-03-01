package linux;

import bash.Bash;

public final class LinuxOS {

    private LinuxOS() {
    	
    }

    public static void main(final String[] args) {
        Bash tty1 = new Bash();
        tty1.start();
    }
}
