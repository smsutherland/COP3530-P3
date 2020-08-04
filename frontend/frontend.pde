import controlP5.*;
import java.util.*;

ControlP5 cp5;
JSONArray arr;
String[] params = new String[7];
Group[] groups = new Group[3];

String alertMessage = "";
int alertDuration = 0;

PFont arial12;
PFont arial14;

void setup() {

    arial12 = createFont("arial", 12);
    arial14 = createFont("arial", 14);


    arr = loadJSONArray("samplejson.json");
    size(500, 500);
    cp5 = new ControlP5(this);
    List events = Arrays.asList("2x2x2", "3x3x3", "3x3x3 blindfolded", "3x3x3 one-handed", "4x4x4", "4x4x4 blindfolded", "5x5x5", "5x5x5 blindfolded", "6x6x6", "7x7x7");

    cp5.addCheckBox("Options")
        .setPosition(25, 25)
        .setSize(20, 20)
        .setFont(arial14)
        .setColorLabel(0)
        .addItem("Date Range", 1)
        .addItem("Time Range", 2)
        .addItem("Average/Single", 3)
        ;

    cp5.addButton("Go")
        .setSize(50, 50)
        .setPosition(200, 75)
        ;

    cp5.addScrollableList("Event Type")
        .setPosition(150, 25)
        .setSize(150, 100)
        .setBarHeight(25)
        .setItemHeight(20)
        .addItems(events)
        .close()
        .plugTo(this, "updateEventID")
        .setFont(arial12)
        ;
    
    groups[0] = cp5.addGroup("Date Range Group").hide();
    groups[1] = cp5.addGroup("Time Range Group").hide();
    groups[2] = cp5.addGroup("Average/Single Group").hide();

    cp5.addTextfield("Date Lower Bound")
        .setSize(200, 25)
        .setColor(color(255,255,255))
        .setAutoClear(false)
        .setFont(arial14)
        .setColorLabel(0)
        .moveTo(groups[0])
        ;

    cp5.addTextfield("Date Upper Bound")
        .setSize(200, 25)
        .setPosition(0, 50)
        .setColor(color(255,255,255))
        .setAutoClear(false)
        .setFont(arial14)
        .setColorLabel(0)
        .moveTo(groups[0])
        ;

    cp5.addTextfield("Time Lower Bound")
        .setSize(200, 25)
        .setColor(color(255,255,255))
        .setAutoClear(false)
        .setFont(arial14)
        .setColorLabel(0)
        .moveTo(groups[1])
        ;

    cp5.addTextfield("Time Upper Bound")
        .setSize(200, 25)
        .setPosition(0, 50)
        .setColor(color(255,255,255))
        .setAutoClear(false)
        .setFont(arial14)
        .setColorLabel(0)
        .moveTo(groups[1])
        ;
    
    cp5.addRadioButton("Single/Average")
        .setSize(25, 25)
        .addItem("Average", 1)
        .addItem("Single", 2)
        .setColorLabel(0)
        .setNoneSelectedAllowed(false)
        .activate(0)
        .moveTo(groups[2])
        ;

    cp5.addAccordion("acc")
        .addItem(groups[0])
        .addItem(groups[1])
        .addItem(groups[2])
        .setPosition(300, 25)
        ;
    
    cp5.addRadioButton("Tree Type")
        .setSize(25, 25)
        .setPosition(25, 100)
        .addItem("AVL Tree", 1)
        .addItem("Standard BST", 2)
        .setFont(arial14)
        .setColorLabel(0)
        .setNoneSelectedAllowed(false)
        .activate(0)
        ;

    params[0] = "-1";
}

void draw() {
    noStroke();
    background(255);
    fill(0);
    drawAlert();
    //drawHistogram(arr, 200, 200);
}

void updateEventID(int eventIndex){
    String[] eventIDs = {"222", "333", "333bf", "333oh", "444", "444bf", "555", "555bf", "666", "777"};
    println("Set eventID to", eventIDs[eventIndex]);
    params[0] = eventIDs[eventIndex];
}

void Options(float[] options){
    for(int i = 0; i < options.length; i++){
        groups[i].setVisible(options[i] == 1);
    }
}

void Go(){
    if(params[0] == "-1"){
        alert("Please select an event.");
        return;
    }

    if(groups[0].isVisible()){
        // println("taking params from group 0");
        params[1] = cp5.get(Textfield.class, "Date Lower Bound").getText();
        params[2] = cp5.get(Textfield.class, "Date Upper Bound").getText();
        if(!isViableDate(params[1]) || !isViableDate(params[2])){
            alert("Make sure your date is written in the form \"MM/DD/YYYY\".");
            return;
        }
    }
    else{
        // println("not taking params from group 0");
        params[1] = "-1";
        params[2] = "-1";
    }

    if(groups[1].isVisible()){
        // println("taking params from group 1");
        params[3] = cp5.get(Textfield.class, "Time Lower Bound").getText();
        params[4] = cp5.get(Textfield.class, "Time Upper Bound").getText();
        if(!isViableTime(params[3]) || !isViableTime(params[4])){
            alert("Make sure your time is written as a decimal number of seconds.");
            return;
        }
        params[3] = "" + (int)(float(params[3]) * 100);
        params[4] = "" + (int)(float(params[4]) * 100);
    }
    else{
        // println("not taking params from group 1");
        params[3] = "-1";
        params[4] = "-1";
    }

    if(groups[2].isVisible()){
        // println("taking params from group 2");
        params[5] = cp5.get(RadioButton.class, "Single/Average").getState(0) ? "1" : "0";
    }
    else{
        // println("not taking params from group 2");
        params[5] = "1";
    }

    params[6] = cp5.get(RadioButton.class, "Tree Type").getState(0) ? "1" : "0";
    execute();
}

boolean isViableDate(String str){
    if(str.length() != 10){
        return false;
    }
    if(str.charAt(2) != '/' || str.charAt(5) != '/'){
        return false;
    }
    String monthStr = str.substring(0, 2);
    String dayStr = str.substring(3, 5);
    String yearStr = str.substring(6, 10);

    try{
        int month = int(monthStr);
        if(month < 1 || month > 12){
            return false;
        }

        int day = int(dayStr);
        if(day < 1 || day > 31){
            return false;
        }

        int year = int(yearStr);
        if(year < 0){
            return false;
        }
    }
    catch(Exception e){
        return false;
    }
    return true;
}

boolean isViableTime(String str){
    if(str.length() == 0){
        return false;
    }
    try{
        float a = float(str);
        if(a < 0 || Float.isNaN(a)){
            return false;
        }
    }
    catch(Exception e){
        return false;
    }
    return true;
}

void drawAlert(){
    fill(0);
    textFont(arial14);
    if(alertDuration > 0){
        alertDuration--;
        text(alertMessage, 25, 175);
    }
}

void alert(String alert){
    alertMessage = alert;
    alertDuration = 300;
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

void execute(){
    String paramsStr = "";
    for(int i = 0; i < params.length; i++){
        paramsStr += " " + params[i];
    }
    println("..\\backend\\main.exe" + paramsStr);
    try{
        // Process pr = Runtime.getRuntime().exec("..\\backend\\main.exe" + params);
        Process pr = Runtime.getRuntime().exec("\"C:\\Users\\sagan\\Documents\\Actual Documents\\UF Documents\\Summer 2020\\COP3530\\Projects\\COP3530-P3\\backend\\main.exe\"" + params);
        pr.waitFor();
        print("made it!");
    }
    catch(IOException e){println("IOException");}
    catch(InterruptedException e){println("Interrupted");}
}