package logger;

import java.util.EnumSet;

public enum LogLevel {
    None,
    Info,
    Debug,
    Warning,
    Error,
    FunctionalMessage,
    FunctionalError;

    public static EnumSet<LogLevel> All(){
        return EnumSet.allOf(LogLevel.class);
    }
}
