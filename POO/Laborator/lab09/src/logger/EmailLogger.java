package logger;

import java.util.EnumSet;

public class EmailLogger extends LoggerBase {

    public EmailLogger(EnumSet<LogLevel> logMask) {
        super(logMask);
    }

    @Override
    protected void writeMessage(String msg) {
        System.out.println("[Email] " + msg);
    }
}
