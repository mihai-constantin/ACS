package ro.pub.cs.systems.eim.practicaltest01var03.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class PracticalTest01Var03Service  extends Service {

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(ServiceConstants.TAG, "onCreate() method was invoked");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d(ServiceConstants.TAG, "onBind() method was invoked");
        return null;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.d(ServiceConstants.TAG, "onUnbind() method was invoked");
        return true;
    }

    @Override
    public void onRebind(Intent intent) {
        Log.d(ServiceConstants.TAG, "onRebind() method was invoked");
    }

    @Override
    public void onDestroy() {
        Log.d(ServiceConstants.TAG, "onDestroy() method was invoked");
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d(ServiceConstants.TAG, "onStartCommand() method was invoked");

        Integer firstNumber = Integer.valueOf(intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01var03.FIRST_NUMBER"));
        Integer secondNumber = Integer.valueOf(intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01var03.SECOND_NUMBER"));

        Log.d(ServiceConstants.DEBUG, "onstartCommand: " + firstNumber);
        Log.d(ServiceConstants.DEBUG, "onstartCommand: " + secondNumber);

        ProcessingThread processingThread = new ProcessingThread(this, firstNumber, secondNumber);
        processingThread.start();
        return START_REDELIVER_INTENT;
    }
}
