package ro.pub.cs.systems.eim.lab07.xkcdcartoondisplayer.network;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.io.IOException;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import ro.pub.cs.systems.eim.lab07.xkcdcartoondisplayer.entities.XKCDCartoonInformation;
import ro.pub.cs.systems.eim.lab07.xkcdcartoondisplayer.general.Constants;

public class XKCDCartoonDisplayerAsyncTask extends AsyncTask<String, Void, XKCDCartoonInformation> {

    private TextView xkcdCartoonTitleTextView;
    private ImageView xkcdCartoonImageView;
    private TextView xkcdCartoonUrlTextView;
    private Button previousButton, nextButton;

    private class XKCDCartoonButtonClickListener implements Button.OnClickListener {

        private String xkcdComicUrl;

        public XKCDCartoonButtonClickListener(String xkcdComicUrl) {
            this.xkcdComicUrl = xkcdComicUrl;
        }

        @Override
        public void onClick(View view) {
            new XKCDCartoonDisplayerAsyncTask(xkcdCartoonTitleTextView, xkcdCartoonImageView, xkcdCartoonUrlTextView, previousButton, nextButton).execute(xkcdComicUrl);
        }

    }

    public XKCDCartoonDisplayerAsyncTask(TextView xkcdCartoonTitleTextView, ImageView xkcdCartoonImageView, TextView xkcdCartoonUrlTextView, Button previousButton, Button nextButton) {
        this.xkcdCartoonTitleTextView = xkcdCartoonTitleTextView;
        this.xkcdCartoonImageView = xkcdCartoonImageView;
        this.xkcdCartoonUrlTextView = xkcdCartoonUrlTextView;
        this.previousButton = previousButton;
        this.nextButton = nextButton;
    }

    @Override
    public XKCDCartoonInformation doInBackground(String... urls) {
        XKCDCartoonInformation xkcdCartoonInformation = new XKCDCartoonInformation();

        // exercise 5a)
        // 1. obtain the content of the web page (whose Internet address is stored in urls[0])

        // - create an instance of a HttpClient object
        HttpClient httpClient = new DefaultHttpClient();

        // - create an instance of a HttpGet object
        HttpGet httpGetXKCD = new HttpGet(urls[0]);

        // - create an instance of a ResponseHandler object
        ResponseHandler<String> responseHandler = new BasicResponseHandler();

        // - execute the request, thus obtaining the web page source code
        String pageSourceCode = null;
        try {
            pageSourceCode = httpClient.execute(httpGetXKCD, responseHandler);
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

        // 2. parse the web page source code
        if (pageSourceCode != null) {
            Document document = Jsoup.parse(pageSourceCode);
            Element htmlTag = document.child(0);

            // - cartoon title: get the tag whose id equals "ctitle"
            Element divTagIdCtitle = htmlTag.getElementsByAttributeValue(Constants.ID_ATTRIBUTE, Constants.CTITLE_VALUE).first();
            xkcdCartoonInformation.setCartoonTitle(divTagIdCtitle.ownText());

            // - cartoon url
            //   * get the first tag whose id equals "comic"
            Element divTagIdComic = htmlTag.getElementsByAttributeValue(Constants.ID_ATTRIBUTE, Constants.COMIC_VALUE).first();
            //   * get the embedded <img> tag
            //   * get the value of the attribute "src"
            String cartoonInternetAddress = divTagIdComic.getElementsByTag(Constants.IMG_TAG).attr(Constants.SRC_ATTRIBUTE);
            //   * prepend the protocol: "http:"
            String cartoonUrl = Constants.HTTP_PROTOCOL + cartoonInternetAddress;
            xkcdCartoonInformation.setCartoonUrl(cartoonUrl);

            // - cartoon bitmap (only if using Apache HTTP Components)
            //   * create the HttpGet object
            //   * execute the request and obtain the HttpResponse object
            //   * get the HttpEntity object from the response
            //   * get the bitmap from the HttpEntity stream (obtained by getContent()) using Bitmap.decodeStream() method
            try {
                HttpGet httpGetCartoon = new HttpGet(cartoonUrl);
                HttpResponse httpResponse = httpClient.execute(httpGetCartoon);
                HttpEntity httpEntity = httpResponse.getEntity();
                if (httpEntity != null) {
                    xkcdCartoonInformation.setCartoonBitmap(BitmapFactory.decodeStream(httpEntity.getContent()));
                }
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

            // - previous cartoon address
            //   * attach the previous button a click listener with the address attached

            //   * get the first tag whole rel attribute equals "prev"
            Element aTagRelPrev = htmlTag.getElementsByAttributeValue(Constants.REL_ATTRIBUTE, Constants.PREVIOUS_VALUE).first();
            //   * get the href attribute of the tag
            String previousCartoonInternetAddress = Constants.XKCD_INTERNET_ADDRESS + aTagRelPrev.attr(Constants.HREF_ATTRIBUTE);
            //   * prepend the value with the base url: http://www.xkcd.com
            xkcdCartoonInformation.setPreviousCartoonUrl(previousCartoonInternetAddress);

            // - next cartoon address
            //   * attach the next button a click listener with the address attached

            //   * get the first tag whole rel attribute equals "next"
            Element aTagRelNext = htmlTag.getElementsByAttributeValue(Constants.REL_ATTRIBUTE, Constants.NEXT_VALUE).first();
            //   * get the href attribute of the tag
            String nextCartoonInternetAddress = Constants.XKCD_INTERNET_ADDRESS + aTagRelNext.attr(Constants.HREF_ATTRIBUTE);
            //   * prepend the value with the base url: http://www.xkcd.com
            xkcdCartoonInformation.setNextCartoonUrl(nextCartoonInternetAddress);
        }

        return  xkcdCartoonInformation;
    }

    @Override
    protected void onPostExecute(final XKCDCartoonInformation xkcdCartoonInformation) {
        // exercise 5b)
        // map each member of xkcdCartoonInformation object to the corresponding widget
        if (xkcdCartoonInformation != null) {
            // cartoonTitle -> xkcdCartoonTitleTextView
            String cartoonTitle = xkcdCartoonInformation.getCartoonTitle();
            if (cartoonTitle != null) {
                xkcdCartoonTitleTextView.setText(cartoonTitle);
            }
            // cartoonBitmap -> xkcdCartoonImageView (only if using Apache HTTP Components)
            // based on cartoonUrl fetch the bitmap
            // and put it into xkcdCartoonImageView
            Bitmap cartoonBitmap = xkcdCartoonInformation.getCartoonBitmap();
            if (cartoonBitmap != null) {
                xkcdCartoonImageView.setImageBitmap(cartoonBitmap);
            }
            // cartoonUrl -> xkcdCartoonUrlTextView
            String cartoonUrl = xkcdCartoonInformation.getCartoonUrl();
            if (cartoonUrl != null) {
                xkcdCartoonUrlTextView.setText(cartoonUrl);
            }
            // previousCartoonUrl, nextCartoonUrl -> set the XKCDCartoonUrlButtonClickListener for previousButton, nextButton
            String previousCartoonUrl = xkcdCartoonInformation.getPreviousCartoonUrl();
            if (previousCartoonUrl != null) {
                previousButton.setOnClickListener(new XKCDCartoonButtonClickListener(previousCartoonUrl));
            }

            String nextCartoonUrl = xkcdCartoonInformation.getNextCartoonUrl();
            if (nextCartoonUrl != null) {
                nextButton.setOnClickListener(new XKCDCartoonButtonClickListener(nextCartoonUrl));
            }
        }
    }

}
