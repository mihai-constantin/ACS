package ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.view;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.R;
import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.controller.OCWCourseListAdapter;
import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.model.OCWCourseContent;
import ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.network.OCWCourseDisplayerAsyncTask;

public class OCWCoursesDisplayerActivity extends AppCompatActivity {

    private ListView ocwCoursesListView;
    private List<OCWCourseContent> ocwCourseContentList;
    private OCWCourseListAdapter ocwCourseListAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ocw_courses_displayer);

        ocwCoursesListView = (ListView)findViewById(R.id.ocw_courses_list_view);
        ocwCourseContentList = new ArrayList<>();
        ocwCourseListAdapter = new OCWCourseListAdapter(this, ocwCourseContentList);
        ocwCoursesListView.setAdapter(ocwCourseListAdapter);

        OCWCourseDisplayerAsyncTask ocwCourseDisplayerAsyncTask = new OCWCourseDisplayerAsyncTask(ocwCourseContentList, ocwCourseListAdapter, ocwCoursesListView);
        ocwCourseDisplayerAsyncTask.execute();

    }
}
