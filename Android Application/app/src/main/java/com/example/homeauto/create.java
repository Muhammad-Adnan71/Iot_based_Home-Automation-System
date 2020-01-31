package com.example.homeauto;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class create extends AppCompatActivity {

    private EditText et_name,et_uname,et_email,et_phone,et_password,et_cpassword;
    private String name,uname,email,phone,password,cpassword;
    Button btncreate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create);
    et_name = (EditText)findViewById(R.id.editText3);
        et_uname = (EditText)findViewById(R.id.editText4);
        et_email = (EditText)findViewById(R.id.editText5);
        et_phone = (EditText)findViewById(R.id.editText6);
        et_password = (EditText)findViewById(R.id.editText7);
        et_cpassword = (EditText)findViewById(R.id.editText8);
        btncreate=(Button)findViewById(R.id.button3);
        btncreate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Create();
            }
        });

    }
    public void Create()
    {
        initialize();
        if(!validate()){
            Toast.makeText(this,"Information necessary",Toast.LENGTH_LONG).show();

        }
        else{

            onSuccess();

        }
    }
    public void onSuccess(){


    }
    public boolean validate() {

        boolean valid = true;
        if (name.isEmpty() || name.length() > 32) {
            et_name.setError("Please Enter Valid Name");
            valid = false;
        }

        if (uname.isEmpty() || uname.length() > 32) {
            et_uname.setError("Please Enter Valid Username");
            valid = false;
        }

        if (phone.isEmpty()) {
            et_phone.setError("Please Enter Valid Phone Number");
            valid = false;
        }

        if (password.isEmpty()) {
            et_password.setError("Please Enter Password");
            valid = false;
        }

        if (cpassword.isEmpty() || cpassword.length() > 32) {
            et_cpassword.setError("Please Enter Password");
            valid = false;

        }

        if (email.isEmpty() || !Patterns.EMAIL_ADDRESS.matcher(email).matches()) {
            et_email.setError("Please Enter Valid Email Adress");
            valid = false;
        }
        return valid;
    }
    public void initialize(){
        name=et_name.getText().toString().trim();
        uname=et_uname.getText().toString().trim();
        email=et_email.getText().toString().trim();
        phone=et_phone.getText().toString().trim();
        password=et_password.getText().toString().trim();
        cpassword=et_cpassword.getText().toString().trim();
    }
}
