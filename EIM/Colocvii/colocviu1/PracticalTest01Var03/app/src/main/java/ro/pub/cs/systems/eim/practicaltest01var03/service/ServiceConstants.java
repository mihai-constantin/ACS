package ro.pub.cs.systems.eim.practicaltest01var03.service;

import android.icu.text.SimpleDateFormat;
import android.icu.util.Calendar;

public class ServiceConstants {

    final public static String TAG = "[Started Service]";

    final public static String ACTION_SUM = "ro.pub.cs.systems.eim.practicaltest01var03.service.string";
    final public static String ACTION_DIF = "ro.pub.cs.systems.eim.practicaltest01var03.service.integer";

    final public static int MESSAGE_SUM = 1;
    final public static int MESSAGE_DIF = 2;

    final public static String DATA = "ro.pub.cs.systems.eim.practicaltest01var03.service.data";

    final public static int INTEGER_DATA = Integer.parseInt(new SimpleDateFormat("yyyy").format(Calendar.getInstance().getTime()));

    final public static long SLEEP_TIME = 5000;

    final public static String DEBUG = "DEBUG";
    final public static String SERVICE = "SERVICE";
}
