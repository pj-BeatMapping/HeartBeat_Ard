
int sensorPin = 4;
int ledPin = 13;
int sensorValue = 0;
int integral_plus = 0;
int integral_minus = 0;
int count = 0; //心拍の回数を格納する変数
int elapse_up = 0;
int elapse_down = 0;
int ave = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  
  Serial.println("Hello, World");

}

void loop() {
  int currentValue = analogRead(sensorPin);
  int diff = (currentValue - sensorValue);
  sensorValue = currentValue;
  
  /* 変化量が 0 に近く、この時点までの積分値が一定量であれば心拍の候補として扱う*/
  if ( diff < 10 && diff > -10 && integral_plus > 160 && integral_minus < -200 ) {
    // 立ち上がり時間とたち下がり時間を調べて、人間っぽい数値になっていれば、心拍としてみなす。
    if( elapse_up > 50 && elapse_up < 400 && elapse_down > 96 && elapse_down < 800 ) {
      count++;// ★心拍が検出されるとここに処理が移る★ 

      // デバッグ用にシリアルコンソールに出力 
    //  Serial.print(count,DEC);
    //  Serial.println();
      
      unsigned int send_data;

      send_data = count;
      
      
      Serial.write(send_data);

      
      }
      // クリア
      elapse_up = 0;
      elapse_down = 0;
      integral_plus = 0;
      integral_minus = 0;
      } else if ( diff > 20 && diff < 280 ) {
        // 波形の立ち上がりを検出
        integral_plus += diff;
        elapse_up += 20;
        } else if ( diff < -20 && diff > -200 ) {
          // 波形の立下りを検出
          integral_minus += diff;
          elapse_down += 20;
          }
          delay(20); // 20ms ごとにサンプリングするために、待つ。
}
