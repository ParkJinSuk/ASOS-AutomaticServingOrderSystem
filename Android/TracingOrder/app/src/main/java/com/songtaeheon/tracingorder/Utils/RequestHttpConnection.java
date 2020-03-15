package com.songtaeheon.tracingorder.Utils;

import android.content.ContentValues;
import android.icu.util.Output;
import android.util.Log;

import com.songtaeheon.tracingorder.model.OrderItemSet;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;

public class RequestHttpConnection {

    final String urlStr = "http://106.10.49.227/insert_song.php";
    final String TAG = "RequestHttpConnection";

    public RequestHttpConnection(){}
    public String request(OrderItemSet _params) {
        HttpURLConnection urlConn = null;

        OutputStream os = null;
        InputStream is = null;
        ByteArrayOutputStream baos = null;
        try {
            URL url = new URL(urlStr);
            urlConn = (HttpURLConnection) url.openConnection();

            urlConn.setReadTimeout(5000);
            urlConn.setConnectTimeout(5000);
            urlConn.setRequestMethod("POST");
            urlConn.connect();
            os = urlConn.getOutputStream();

            String sendingData = _params.makeDataForm();
            Log.d(TAG, "data : " + sendingData);
            os.write(sendingData.getBytes("UTF-8"));
            os.flush();
            os.close();

            String response;

            int responseCode = urlConn.getResponseCode();

            if (responseCode == HttpURLConnection.HTTP_OK) {

                is = urlConn.getInputStream();
                baos = new ByteArrayOutputStream();
                byte[] byteBuffer = new byte[1024];
                byte[] byteData = null;
                int nLength = 0;
                while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1) {
                    baos.write(byteBuffer, 0, nLength);
                }
                byteData = baos.toByteArray();

                response = new String(byteData);
                Log.i(TAG, "DATA response string = " + response);

                JSONObject responseJSON = new JSONObject(response);

                Log.i(TAG, "DATA response = " + responseJSON.toString());
                return responseJSON.toString();
            }else{
                Log.e(TAG, "responseCode = " + responseCode);

            }
        } catch (MalformedURLException e) { // for URL.
            e.printStackTrace();
        } catch (IOException e) { // for openConnection().
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        } finally {
            if (urlConn != null)
                urlConn.disconnect();
        }

        return null;
    }
}