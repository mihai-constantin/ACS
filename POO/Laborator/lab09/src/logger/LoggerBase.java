package logger;

import java.util.EnumSet;

abstract class LoggerBase {

    protected EnumSet<LogLevel> logMask;
    protected LoggerBase next;

    public LoggerBase(EnumSet<LogLevel> logMask) {
        this.logMask = logMask;
    }

    public LoggerBase setNext(LoggerBase nextLogger){
        this.next = nextLogger;
        return  nextLogger;
    }

    public void message(String msg, LogLevel severity){
       if(logMask.contains(severity)){
           writeMessage(msg);
       }
       if(next != null){
           next.message(msg, severity);
       }
    }

    abstract protected void writeMessage(String msg);
}
