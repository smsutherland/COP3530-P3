JSONArray arr;
void setup() {
    arr = loadJSONArray("samplejson.json");
    size(500, 500);
}

void draw() {
    noStroke();
    background(255);
    drawHistogram(arr, 200, 200, color(0), color(255, 0, 0));
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
