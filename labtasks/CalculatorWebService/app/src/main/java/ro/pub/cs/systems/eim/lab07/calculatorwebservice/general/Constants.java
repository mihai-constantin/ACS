package ro.pub.cs.systems.eim.lab07.calculatorwebservice.general;

public interface Constants {

    final public static boolean DEBUG = true;

    final public static String TAG = "[CalculatorWebService]";

    final public static String GET_WEB_SERVICE_ADDRESS = "http://eim2017.andreirosucojocaru.ro/exemple/laboratoare/laborator07/calculator/calculator_get.php";
    final public static String POST_WEB_SERVICE_ADDRESS = "http://eim2017.andreirosucojocaru.ro/exemple/laboratoare/laborator07/calculator/calculator_post.php";

    final public static String ERROR_MESSAGE_EMPTY = "Operator fields cannot be empty!";

    final public static int GET_OPERATION = 0;
    final public static int POST_OPERATION = 1;

    final public static String OPERATION_ATTRIBUTE = "operation";
    final public static String OPERATOR1_ATTRIBUTE = "operator1";
    final public static String OPERATOR2_ATTRIBUTE = "operator2";

}
