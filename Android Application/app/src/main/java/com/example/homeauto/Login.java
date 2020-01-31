package com.example.homeauto;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Login extends AppCompatActivity {
    Button login;
    EditText mail,password;
    private Button butn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        butn =(Button)findViewById(R.id.button2);
        mail=(EditText)findViewById(R.id.editText);
        password=(EditText)findViewById(R.id.editText2);
        login=(Button)findViewById(R.id.button2);
        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {


                String validemail = "[a-zA-Z0-9\\+\\.\\_\\%\\-\\+]{1,256}" +

                        "\\@" +

                        "[a-zA-Z0-9][a-zA-Z0-9\\-]{0,64}" +

                        "(" +

                        "\\." +

                        "[a-zA-Z0-9][a-zA-Z0-9\\-]{0,25}" +

                        ")+";
String email = mail.getText().toString();
                Matcher match = Pattern.compile(validemail).matcher(email);
                if(password.getText().toString().equals("")){
                    password.setError("Enter password");
                }
                if(match.matches()){
                    if(password.getText().toString() != null){
                    openfeature();
                }}
                else{

                    Toast.makeText(getApplicationContext(),"Enter valid email",Toast.LENGTH_LONG).show();

                }
            }
        });

    }
    public void openfeature(){
        Intent intent = new Intent(this,RoomsGrid.class);
        startActivity(intent);
    }
}
