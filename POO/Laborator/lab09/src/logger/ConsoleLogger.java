package logger;

import java.util.EnumSet;

public class ConsoleLogger extends LoggerBase {

    public ConsoleLogger(EnumSet<LogLevel> logMask) {
        super(logMask);
    }

    @Override
    protected void writeMessage(String msg) {
        System.out.println("[Console] " + msg);
    }
}
