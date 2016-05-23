package com.example.user.myapplication;


import android.location.Address;
import android.location.Geocoder;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;

import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptor;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

/**
 * Created by USER on 2016/5/23.
 */
public class MapActivity extends FragmentActivity {
    private Double toLat;
    private Double toLng;
    public static GoogleMap map;
    public Geocoder geocoder;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.maplayout);
        toLat = 25.033611;  //set the initial position
        toLng = 121.565000;
	/*intialize the geocoder*/
        geocoder = new Geocoder(getApplicationContext(), Locale.getDefault());

	/*get map object*/
        map = ((SupportMapFragment) this.getSupportFragmentManager().findFragmentById(R.id.map)).getMap();
        map.setMapType(GoogleMap.MAP_TYPE_NORMAL);
        map.getUiSettings().setZoomControlsEnabled(true);
	/*set the intial position*/
        setCamera(toLat, toLng);
	/*put on all the marker of the information*/
        putOnMarker(MainActivity.nodeList);
    }
    /*put on all the marker of the information*/
    private void putOnMarker(NodeList nodeList){
        String input;
        List<Address> addressList = null;
        Address address = null;
        BitmapDescriptor icon = BitmapDescriptorFactory.fromResource(R.drawable.google);
        try {
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                Element fstElmnt = (Element) node;
                input = fstElmnt.getElementsByTagName("ADDR").item(0).getTextContent();
                addressList = geocoder.getFromLocationName(input, 1);
                if (addressList != null && !addressList.isEmpty()) {
                    address = addressList.get(0);
                    double Latitude = address.getLatitude();
                    double Longitude = address.getLongitude();
                    MarkerOptions markerOpt = new MarkerOptions();
                    markerOpt.position(new LatLng(Latitude, Longitude));
                    markerOpt.title(input);
                    markerOpt.icon(icon);
                    map.addMarker(markerOpt);
                    System.out.println(input + "  " + Latitude + ", " + Longitude + "\n");
                }
            }
        }catch(IOException e){

        }
    }
    /*set the intial position*/
    private void setCamera(Double toLat, Double toLng){
        CameraUpdate center=
                CameraUpdateFactory.newLatLngZoom(new LatLng(toLat, toLng), 15);
        map.animateCamera(center);
    }
}
