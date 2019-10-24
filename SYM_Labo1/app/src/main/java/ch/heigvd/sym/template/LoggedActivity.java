package ch.heigvd.sym.template;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;


public class LoggedActivity extends AppCompatActivity {

    private final int READ_PHONE_STATE_PERMISSION = 1;
    private final int ACCESS_SD_CARD_PERMISSION   = 2;

    TextView imei;
    TextView logged;
    Button logout;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.v("LoggedActivity", "onCreate");

        setContentView(R.layout.logged);

        logout = (Button) findViewById(R.id.logout_button);
        imei = findViewById(R.id.textview_imei);
        logged = findViewById(R.id.textview_loggin);

        String email;

        //onClick Listener for the logOut Button
        logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });


        if (savedInstanceState == null) {
            Bundle extras = getIntent().getExtras();
            if (extras == null) {
                Toast.makeText(this, getString(R.string.error_email), Toast.LENGTH_LONG).show();
                email = "-@-";
            } else {
                email = extras.getString("emailUsed");
            }
        } else {
            email = (String) savedInstanceState.getSerializable("emailUsed");
        }

        //Getting Email and giving Application Context
        getImei();

        getImageOnSdCard();
        logged.setText(getString(R.string.log_succes) + email);
    }

    private void getImei() {
        String imeiStr = getString(R.string.IMEI);

        //check permission on runtime


        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_PHONE_STATE}, READ_PHONE_STATE_PERMISSION);
        }else{
            TelephonyManager telephonyManager = (TelephonyManager) this.getApplicationContext().getSystemService(Context.TELEPHONY_SERVICE);

            //Check differents api version and use the correct method
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                imeiStr = telephonyManager.getImei();
            }else{
                imeiStr = telephonyManager.getDeviceId();
            }

        }

        TextView imei = findViewById(R.id.textview_imei);
        TextView logged = findViewById(R.id.textview_loggin);
        Button logout = (Button) findViewById(R.id.logout_button);
        imei.setText(imeiStr);
    }

    private void getImageOnSdCard(){
        ImageView imageView = (ImageView) findViewById(R.id.imageView);

        //request permission on runtime
        if(ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, ACCESS_SD_CARD_PERMISSION);
        }else{
            //Log.w("PATH:", Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getAbsolutePath());
            String path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getAbsolutePath() + "/vandetta.jpg";
            //Check if sd card is mounted
            if(isExternalStorageReadable()){
                imageView.setImageBitmap(BitmapFactory.decodeFile(path));
            }
        }
    }

    public boolean isExternalStorageReadable(){
        if(Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
            return true;
        }
        return false;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if(grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED){
            switch (requestCode){
                case READ_PHONE_STATE_PERMISSION: {
                    getImei();
                    break;
                }
                case ACCESS_SD_CARD_PERMISSION: {
                    getImageOnSdCard();
                    break;
                }
            }
        }
    }

    @Override
    public void onBackPressed() {
        //we do nothing here
        // we also could implement the logout of the user
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d("LoggedActivity", "onStart");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.v("LoggedActivity", "onRestart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.v("LoggedActivity", "onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.v("LoggedActivity", "onPause");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.v("LoggedActivity", "onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.v("LoggedActivity", "onDestroy");
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        savedInstanceState.putString("imei", imei.getText().toString());
        savedInstanceState.putString("logged", logged.getText().toString());
        super.onSaveInstanceState(savedInstanceState);
    }

    @Override
    public void onRestoreInstanceState(Bundle savedInstanceState) {
        imei.setText(savedInstanceState.getString("imei"));
        logged.setText(savedInstanceState.getString("logged"));
        super.onRestoreInstanceState(savedInstanceState);
    }
}
