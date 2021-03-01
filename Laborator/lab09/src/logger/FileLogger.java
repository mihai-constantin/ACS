package logger;

import java.util.EnumSet;

public class FileLogger extends LoggerBase {

    public FileLogger(EnumSet<LogLevel> logMask) {
        super(logMask);
    }

    @Override
    protected void writeMessage(String msg) {
        System.out.println("[File] " + msg);
    }
}
