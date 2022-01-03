package ro.pub.cs.systems.eim.lab07.calculatorwebservice.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import cz.msebera.android.httpclient.NameValuePair;
import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.entity.UrlEncodedFormEntity;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import cz.msebera.android.httpclient.message.BasicNameValuePair;
import cz.msebera.android.httpclient.protocol.HTTP;
import ro.pub.cs.systems.eim.lab07.calculatorwebservice.general.Constants;

public class CalculatorWebServiceAsyncTask extends AsyncTask<String, Void, String> {

    private TextView resultTextView;

    public CalculatorWebServiceAsyncTask(TextView resultTextView) {
        this.resultTextView = resultTextView;
    }

    @Override
    protected String doInBackground(String... params) {
        String operator1 = params[0];
        String operator2 = params[1];
        String operation = params[2];
        int method = Integer.parseInt(params[3]);

        String errorMessage = null;
        if (operator1 == null || operator1.isEmpty()) {
            errorMessage = Constants.ERROR_MESSAGE_EMPTY;
        }
        if (operator2 == null || operator2.isEmpty()) {
            errorMessage = Constants.ERROR_MESSAGE_EMPTY;
        }
        if (errorMessage != null) {
            return errorMessage;
        }

        HttpClient httpClient = new DefaultHttpClient();
        switch(method) {
            case Constants.GET_OPERATION:
                HttpGet httpGet = new HttpGet(Constants.GET_WEB_SERVICE_ADDRESS
                    + "?" + Constants.OPERATION_ATTRIBUTE + "=" + operation
                    + "&" + Constants.OPERATOR1_ATTRIBUTE + "=" + operator1
                    + "&" + Constants.OPERATOR2_ATTRIBUTE + "=" + operator2);
                ResponseHandler<String> responseHandlerGet = new BasicResponseHandler();
                try {
                    return httpClient.execute(httpGet, responseHandlerGet);
                } catch (ClientProtocolException clientProtocolException) {
                    Log.e(Constants.TAG, clientProtocolException.getMessage());
                    if (Constants.DEBUG) {
                        clientProtocolException.printStackTrace();
                    }
                } catch (IOException ioException) {
                    Log.e(Constants.TAG, ioException.getMessage());
                    if (Constants.DEBUG) {
                        ioException.printStackTrace();
                    }
                }
                break;
            case Constants.POST_OPERATION:
                HttpPost httpPost = new HttpPost(Constants.POST_WEB_SERVICE_ADDRESS);
                List<NameValuePair> parameters = new ArrayList<>();
                parameters.add(new BasicNameValuePair(Constants.OPERATION_ATTRIBUTE, operation));
                parameters.add(new BasicNameValuePair(Constants.OPERATOR1_ATTRIBUTE, operator1));
                parameters.add(new BasicNameValuePair(Constants.OPERATOR2_ATTRIBUTE, operator2));
                try {
                    UrlEncodedFormEntity urlEncodedFormEntity = new UrlEncodedFormEntity(parameters, HTTP.UTF_8);
                    httpPost.setEntity(urlEncodedFormEntity);
                } catch (UnsupportedEncodingException unsupportedEncodingException) {
                    Log.e(Constants.TAG, unsupportedEncodingException.getMessage());
                    if (Constants.DEBUG) {
                        unsupportedEncodingException.printStackTrace();
                    }
                }
                ResponseHandler<String> responseHandlerPost = new BasicResponseHandler();
                try {
                    return httpClient.execute(httpPost, responseHandlerPost);
                } catch (ClientProtocolException clientProtocolException) {
                    Log.e(Constants.TAG, clientProtocolException.getMessage());
                    if (Constants.DEBUG) {
                        clientProtocolException.printStackTrace();
                    }
                } catch (IOException ioException) {
                    Log.e(Constants.TAG, ioException.getMessage());
                    if (Constants.DEBUG) {
                        ioException.printStackTrace();
                    }
                }
                break;
        }
        return null;
    }

    @Override
    protected void onPostExecute(String result) {
        resultTextView.setText(result);
    }

}
