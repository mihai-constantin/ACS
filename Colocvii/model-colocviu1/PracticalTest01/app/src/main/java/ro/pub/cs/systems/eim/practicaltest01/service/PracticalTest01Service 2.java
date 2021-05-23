package ro.pub.cs.systems.eim.practicaltest01.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class PracticalTest01Service  extends Service {
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

        Integer firstNumber = Integer.valueOf(intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME"));
        Integer secondNumber = Integer.valueOf(intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME_TOO"));

        ProcessingThread processingThread = new ProcessingThread(this, firstNumber, secondNumber);
        processingThread.start();
        return START_REDELIVER_INTENT;
    }
}
