import controlP5.*;
import java.util.*;

ControlP5 cp5;
JSONArray arr;
String[] params;
void setup() {

    PFont arial12 = createFont("arial", 12);
    PFont arial14 = createFont("arial", 14);


    arr = loadJSONArray("samplejson.json");
    size(500, 500);
    cp5 = new ControlP5(this);
    List events = Arrays.asList("2x2x2", "3x3x3", "3x3x3 blindfolded", "3x3x3 one-handed", "4x4x4", "4x4x4 blindfolded", "5x5x5", "5x5x5 blindfolded", "6x6x6", "7x7x7");

    cp5.addScrollableList("Event Type")
        .setPosition(25, 25)
        .setSize(150, 100)
        .setBarHeight(25)
        .setItemHeight(20)
        .addItems(events)
        .close()
        .plugTo(this, "updateEventID")
        .setFont(arial12)
        ;

    cp5.addTextfield("Lower Bound")
        .setPosition(200, 25)
        .setSize(200, 25)
        .setColor(color(255,0,0))
        .setAutoClear(false)
        .setFont(arial14)
        ;
    
    params = new String[5];
}

void draw() {
    noStroke();
    background(255);
    fill(0);
    text("Lower Time Bound", 200, 20);
    //drawHistogram(arr, 200, 200);
}

void updateEventID(int eventIndex){
    String[] eventIDs = {"222", "333", "333bf", "333oh", "444", "444bf", "555", "555bf", "666", "777"};
    println("Set eventID to", eventIDs[eventIndex]);
    params[0] = eventIDs[eventIndex];
}

void drawHistogram(JSONArray histogramData, int x, int y){
    drawHistogram(histogramData, x, y, color(0), color(255, 0, 0));
}

void drawHistogram(JSONArray histogramData, int x, int y, color axisColor, color bucketColor){
    int bucketWidth = 10;
    int bucketMargin = 2;
    int heightScale = 10;
    int fullWidth = histogramData.size()*(bucketWidth + bucketMargin);
    int maxHeight = 0;
    fill(bucketColor);
    for(int i = 0; i < histogramData.size(); i++){
        JSONObject thisBucket = histogramData.getJSONObject(i);
        int bucketStart = x + (bucketWidth + bucketMargin)*i + bucketMargin;
        int bucketHeight = thisBucket.getInt("height");
        if(bucketHeight > maxHeight){
            maxHeight = bucketHeight;
        }
        rect(bucketStart, y, bucketWidth, -bucketHeight*heightScale);

        rotate(PI/2);
        text(str(thisBucket.getInt("bottom limit")), y + 5, -bucketStart - bucketMargin/2);
        rotate(-PI/2);
    }
    fill(axisColor);
    stroke(0);
    strokeWeight(2);
    line(x, y, x + fullWidth, y);
    line(x, y, x, y - maxHeight*heightScale);
}


//{"222", "333", "333bf", "333oh", "444", "444bf", "555", "555bf", "666", "777"}