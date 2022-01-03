package ro.pub.cs.systems.eim.practicaltest01.service;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class ProcessingThread extends Thread{

    private Context context;
    private Integer firstNumber;
    private Integer secondNumber;

    public ProcessingThread(Context context, Integer firstNumber, Integer secondNumber) {
        this.context = context;
        this.firstNumber = firstNumber;
        this.secondNumber = secondNumber;
    }

    private void sendMessage(int messageType) {
        Intent intent = new Intent();
        if (messageType == ServiceConstants.MESSAGE_INTEGER) {
            intent.setAction(ServiceConstants.ACTION_INTEGER);
            intent.putExtra(ServiceConstants.DATA, ServiceConstants.INTEGER_DATA);
        } else if (messageType == ServiceConstants.MESSAGE_STRING) {
            intent.setAction(ServiceConstants.ACTION_STRING);
            Double ma = (this.firstNumber + this.secondNumber) / 2.0;
            intent.putExtra(ServiceConstants.DATA, ma.toString());
        } else if (messageType == ServiceConstants.MESSAGE_MG) {
            intent.setAction(ServiceConstants.ACTION_MG);
            Double mg = Math.sqrt(this.firstNumber + this.secondNumber);
            intent.putExtra(ServiceConstants.DATA, mg.toString());
        }
        context.sendBroadcast(intent);
    }

    private void sleep() {
        try {
            Thread.sleep(ServiceConstants.SLEEP_TIME);
        } catch (InterruptedException interruptedException) {
            interruptedException.printStackTrace();
        }
    }

    @Override
    public void run() {
        Log.d(ServiceConstants.TAG, "Thread.run() was invoked, PID: " + android.os.Process.myPid() + " TID: " + android.os.Process.myTid());
        while(true) {
            sendMessage(ServiceConstants.MESSAGE_INTEGER);
            sleep();
            sendMessage(ServiceConstants.MESSAGE_STRING);
            sleep();
            sendMessage(ServiceConstants.MESSAGE_MG);
            sleep();
        }
    }
}
