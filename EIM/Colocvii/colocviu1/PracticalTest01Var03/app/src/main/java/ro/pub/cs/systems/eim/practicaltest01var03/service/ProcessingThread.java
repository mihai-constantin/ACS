package ro.pub.cs.systems.eim.practicaltest01var03.service;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class ProcessingThread extends Thread {

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
        if (messageType == ServiceConstants.MESSAGE_SUM) {
            intent.setAction(ServiceConstants.ACTION_SUM);
            Integer sum = this.firstNumber + this.secondNumber;

            Log.d(ServiceConstants.DEBUG, "sendMessage: " + firstNumber);
            Log.d(ServiceConstants.DEBUG, "sendMessage: " + secondNumber);
            Log.d(ServiceConstants.DEBUG, "sendMessage sum: " + sum);

            intent.putExtra(ServiceConstants.DATA, sum.toString());
        } else if (messageType == ServiceConstants.MESSAGE_DIF) {
            intent.setAction(ServiceConstants.ACTION_DIF);
            Integer diff = this.firstNumber - this.secondNumber;
            intent.putExtra(ServiceConstants.DATA, diff.toString());
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
            sendMessage(ServiceConstants.MESSAGE_SUM);
            sleep();
            sendMessage(ServiceConstants.MESSAGE_DIF);
            sleep();
        }
    }
}
