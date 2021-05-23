package ro.pub.cs.systems.eim.lab07.landmarklister.controller;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;

import ro.pub.cs.systems.eim.lab07.landmarklister.R;
import ro.pub.cs.systems.eim.lab07.landmarklister.model.LandmarkInformation;

public class LandmarkInformationAdapter extends BaseAdapter {

    private Context context;
    private List<LandmarkInformation> content;

    private LayoutInflater layoutInflater;

    private static class LandmarkInformationViewHolder {
        TextView latitudeTextView, longitudeTextView;
        TextView toponymNameTextView;
        TextView populationTextView;
        TextView codeNameTextView;
        TextView nameTextView;
        TextView wikipediaWebPageAddressTextView;
        TextView countryCodeTextView;
    };

    public LandmarkInformationAdapter(Context context, List<LandmarkInformation> content) {
        this.context = context;
        this.content = content;
        this.layoutInflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return content.size();
    }

    @Override
    public Object getItem(int position) {
        return content.get(position);
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view;
        LandmarkInformationViewHolder landmarkInformationViewHolder;

        LandmarkInformation landmarkInformation = content.get(position);

        if (convertView == null) {
            view = layoutInflater.inflate(R.layout.landmark_information, parent, false);
            landmarkInformationViewHolder = new LandmarkInformationViewHolder();
            landmarkInformationViewHolder.latitudeTextView = (TextView)view.findViewById(R.id.latitude_text_view);
            landmarkInformationViewHolder.longitudeTextView = (TextView)view.findViewById(R.id.longitude_text_view);
            landmarkInformationViewHolder.toponymNameTextView = (TextView)view.findViewById(R.id.toponym_name_text_view);
            landmarkInformationViewHolder.populationTextView = (TextView)view.findViewById(R.id.population_text_view);
            landmarkInformationViewHolder.codeNameTextView = (TextView)view.findViewById(R.id.code_name_text_view);
            landmarkInformationViewHolder.nameTextView = (TextView)view.findViewById(R.id.name_text_view);
            landmarkInformationViewHolder.wikipediaWebPageAddressTextView = (TextView)view.findViewById(R.id.wikipedia_web_page_address_text_view);
            landmarkInformationViewHolder.countryCodeTextView= (TextView)view.findViewById(R.id.country_code_text_view);
            view.setTag(landmarkInformationViewHolder);
        } else {
            view = convertView;
        }
        landmarkInformationViewHolder = (LandmarkInformationViewHolder)view.getTag();
        landmarkInformationViewHolder.latitudeTextView.setText(String.valueOf(landmarkInformation.getLatitude()));
        landmarkInformationViewHolder.longitudeTextView.setText(String.valueOf(landmarkInformation.getLongitude()));
        landmarkInformationViewHolder.toponymNameTextView.setText(landmarkInformation.getToponymName());
        landmarkInformationViewHolder.populationTextView.setText(String.valueOf(landmarkInformation.getPopulation()));
        landmarkInformationViewHolder.codeNameTextView.setText(landmarkInformation.getCodeName());
        landmarkInformationViewHolder.nameTextView.setText(landmarkInformation.getName());
        landmarkInformationViewHolder.wikipediaWebPageAddressTextView.setText(landmarkInformation.getWikipediaWebPageAddressName());
        landmarkInformationViewHolder.countryCodeTextView.setText(landmarkInformation.getCountryCode());

        return view;
    }
}
