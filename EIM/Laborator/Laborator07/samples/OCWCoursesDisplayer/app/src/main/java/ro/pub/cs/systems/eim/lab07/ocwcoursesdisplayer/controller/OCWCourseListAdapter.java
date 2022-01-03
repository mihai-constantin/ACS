package ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.controller;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.List;

import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.R;
import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.model.OCWCourseContent;

public class OCWCourseListAdapter extends BaseAdapter {

    private Context context;
    private List<OCWCourseContent> content;

    private LayoutInflater layoutInflater;

    private static class OCWCourseInformationViewHolder {
        ImageView logoImageView;
        TextView nameTextView;
    }

    public OCWCourseListAdapter(Context context, List<OCWCourseContent> content) {
        this.context = context;
        this.content = content;
        this.layoutInflater = (LayoutInflater)this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
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
        OCWCourseInformationViewHolder ocwCourseInformationViewHolder;

        OCWCourseContent ocwCourseContent = content.get(position);

        if (convertView == null) {
            view = layoutInflater.inflate(R.layout.ocw_course_information, parent, false);
            ocwCourseInformationViewHolder = new OCWCourseInformationViewHolder();
            ocwCourseInformationViewHolder.logoImageView = (ImageView)view.findViewById(R.id.logo_image_view);
            ocwCourseInformationViewHolder.nameTextView = (TextView)view.findViewById(R.id.name_text_view);
            view.setTag(ocwCourseInformationViewHolder);
        } else {
            view = convertView;
        }
        ocwCourseInformationViewHolder = (OCWCourseInformationViewHolder)view.getTag();
        ocwCourseInformationViewHolder.logoImageView.setImageBitmap(ocwCourseContent.getLogo());
        ocwCourseInformationViewHolder.nameTextView.setText(ocwCourseContent.getName());
        return view;
    }
}
