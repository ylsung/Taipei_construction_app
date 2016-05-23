package com.example.user.myapplication;

import android.app.ProgressDialog;
import android.content.Intent;
import android.location.Geocoder;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;

import java.net.*;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class MainActivity extends AppCompatActivity {
    private Button button_Taipei;
    private ProgressDialog progressDialog;
    public RelativeLayout layout;
    private String WebFrom = "http://data.taipei/opendata/datalist/apiAccess?scope=resourceAquire&rid=201d8ae8-dffc-4d17-ae1f-e58d8a95b162&format=xml";
    public static NodeList nodeList;
    public TextView text;
    public Geocoder geocoder;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button_Taipei = (Button) findViewById(R.id.button_Taipei);
        text = (TextView) findViewById(R.id.textView);
        layout = (RelativeLayout) findViewById(R.id.layout);
        setProgressDialog();
        button_Taipei.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Toast.makeText(v.getContext(), R.string.toast, Toast.LENGTH_LONG).show();
		/* switch the scene*/
                clickToast(v);
                new MyAsyncTask().execute(WebFrom);
                Intent intent = new Intent();
                intent.setClass(MainActivity.this, DataActivity.class);
                startActivity(intent);
            }
        });

    }
    /*set progress Dialog*/
    public void setProgressDialog(){
        progressDialog = new ProgressDialog(MainActivity.this);
        progressDialog.setTitle("提示信息");
        progressDialog.setMessage("正在下載中，請稍後......");
        progressDialog.setCancelable(false);
        progressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
    }
    /*Toast*/
    public void clickToast(View view) {
        Toast.makeText(view.getContext(), R.string.toast, Toast.LENGTH_SHORT).show();
    }
    /*Basic Menu , only exit function*/
    protected static final int MENU_SETTINGS = 1;

    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add(0, MENU_SETTINGS, 100, "close");
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case MENU_SETTINGS:
                finish();
                break;
        }
        return super.onOptionsItemSelected(item);
    }
    /**
        * get the data from the web site, and I use AsyncTask to do it.
        */
    public class MyAsyncTask extends AsyncTask<String, Integer, NodeList> {
        protected void onPreExecute()
        {
            super.onPreExecute();
            progressDialog.show();
        }
        @Override
        protected NodeList doInBackground(String... params) {
            try {
                URL url = new URL(params[0]);
                DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
                DocumentBuilder db = dbf.newDocumentBuilder();
                Document doc = db.parse(new InputSource(url.openStream()));
                doc.getDocumentElement().normalize();
                nodeList = doc.getElementsByTagName("row");

            }catch(Exception e){
                System.out.println("XML Pasing Excpetion = " + e);
            }
            return nodeList;
        }
        @Override
        protected void onProgressUpdate(Integer... values)
        {
            super.onProgressUpdate(values);
        }

        protected void onPostExecute(NodeList nodeList)
        {
            super.onPostExecute(nodeList);
            Set<Node> SortedList = new TreeSet<Node>(new StringComparator());
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                //Element fstElmnt = (Element) node;
                SortedList.add(node);
            }
            /*List<String> keys = new ArrayList(SortedList.keySet());
            Collections.sort(keys);*/
            String content = "";
            String area = "";
            boolean SameArea = false;
            boolean space = false;
            Iterator<Node> itr=SortedList.iterator();
            while(itr.hasNext()) {
                Node node = itr.next();
                Element fstElmnt = (Element) node;
                if(!area.equals(fstElmnt.getElementsByTagName("C_NAME").item(0).getTextContent())){
                    area = fstElmnt.getElementsByTagName("C_NAME").item(0).getTextContent();
                    content = content + "----------------------" + fstElmnt.getElementsByTagName("C_NAME").item(0).getTextContent()
                            + "區---------------------\n";
                    SameArea = true;
                }else SameArea = false;
                content = content + "施工單位: " + fstElmnt.getElementsByTagName("APP_NAME").item(0).getTextContent() + "\n";
                content = content + "施工時間: " + fstElmnt.getElementsByTagName("CB_DA").item(0).getTextContent() + " --> "
                        + fstElmnt.getElementsByTagName("CE_DA").item(0).getTextContent() + "\n";
                content = content + "施工地點 = " + fstElmnt.getElementsByTagName("ADDR").item(0).getTextContent() + "\n\n";
            }
            //text.setText(content);
            DataActivity.textView.setText(content);
            //text.setMovementMethod(new ScrollingMovementMethod());
            DataActivity.textView.setMovementMethod(new ScrollingMovementMethod());
            progressDialog.dismiss();
        }
    }

    class StringComparator implements Comparator<Node>{
        private String C_name;
        StringComparator(){}
        StringComparator(String name){
            C_name = name;
        }
        public int compare(Node n1, Node n2)
        {
            Element fstElmnt1 = (Element) n1;
            Element fstElmnt2 = (Element) n2;
            String C_name1 = fstElmnt1.getElementsByTagName("C_NAME").item(0).getTextContent();
            String C_name2 = fstElmnt2.getElementsByTagName("C_NAME").item(0).getTextContent();
            if(C_name1.compareTo(C_name2) == 0){
                return 1;
            }
            else{
                return C_name1.compareTo(C_name2);
            }
        }
    }
}
