package ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.view;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.R;
import ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.network.WebPageKeywordSearchAsyncTask;

public class WebPageKeywordSearchActivity extends AppCompatActivity {

    private EditText webPageAddressEditText, keywordEditText;
    private Button displayResultsButton;
    private TextView resultsTextView;

    private DisplayResultsButtonClickListener displayResultsButtonClickListener = new DisplayResultsButtonClickListener();
    private class DisplayResultsButtonClickListener implements Button.OnClickListener {

        @Override
        public void onClick(View view) {
            String webPageAddress = webPageAddressEditText.getText().toString();
            String keyword = keywordEditText.getText().toString();
            WebPageKeywordSearchAsyncTask webPageKeywordSearchAsyncTask = new WebPageKeywordSearchAsyncTask(resultsTextView);
            webPageKeywordSearchAsyncTask.execute(webPageAddress, keyword);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_web_page_keyword_search);

        webPageAddressEditText = (EditText)findViewById(R.id.web_page_address_edit_text);
        keywordEditText = (EditText)findViewById(R.id.keyword_edit_text);
        displayResultsButton = (Button)findViewById(R.id.display_results_button);
        displayResultsButton.setOnClickListener(displayResultsButtonClickListener);
        resultsTextView = (TextView)findViewById(R.id.results_text_view);
    }
}
