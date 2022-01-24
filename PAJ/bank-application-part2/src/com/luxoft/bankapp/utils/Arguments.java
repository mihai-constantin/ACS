package com.luxoft.bankapp.utils;

public class Arguments {
    private String[] arguments;
    
    public Arguments(String[] arguments) {
        this.arguments = arguments;
    }

    public boolean hasKey(String key){
        for (String arg: arguments) {
            if (arg.equals(key)) {
                return true;
            }
        }
        return false;
    }
}