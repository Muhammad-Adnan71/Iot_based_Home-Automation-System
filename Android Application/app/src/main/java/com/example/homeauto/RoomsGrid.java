package com.example.homeauto;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.Toast;

public class RoomsGrid extends AppCompatActivity {

    GridLayout grid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rooms_grid);

        grid=(GridLayout)findViewById(R.id.grid);

        setSingleEvent(grid);

    }

    private void setSingleEvent(GridLayout grid) {
        //loop all child item of grid

        for(int i=0;i<grid.getChildCount();i++)
        {

            CardView cardView = (CardView)grid.getChildAt(i);
            final int finalI=i;
            cardView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    if(finalI==0){
                        open_first();
                    }
                    else if (finalI==1){
                        open_second();
                    }
                    else if (finalI==3){
                        open_third();
                    }
                    else if (finalI==4){
                        open_fourth();
                    }
                    else if (finalI==2){
                        open_sixth();
                    }
                    else if (finalI==5){
                        open_seventh();
                    }

                  //  Toast.makeText(RoomsGrid.this, "Clicked at index "+ finalI, Toast.LENGTH_SHORT).show();
                }
            });

        }

    }

    public void open_first(){
        Intent intent = new Intent(this,feature.class);
        startActivity(intent);
    }
    public void open_second(){
        Intent intent = new Intent(this,feature.class);
        startActivity(intent);
    }
    public void open_third(){
        Intent intent = new Intent(this,feature.class);
        startActivity(intent);
    }
    public void open_fourth(){
        Intent intent = new Intent(this,feature.class);
        startActivity(intent);
    }
    public void open_sixth(){
        Intent intent = new Intent(this,feature_for_kitchen.class);
        startActivity(intent);
    }
    public void open_seventh(){
        Intent intent = new Intent(this,feature_for_garden.class);
        startActivity(intent);
    }

}
