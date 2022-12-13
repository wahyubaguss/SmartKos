#include"FirebaseESP8266.h" //install FirebaseESP8266

#define FIREBASE_HOST "iot-indobot-fp-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "eVhIZmFlkCTvWHCicxwgRnt8v3PSK52FFLJg1knZ"

FirebaseData firebaseData;

void smartEnvirontementFirebase() {

  //untuk memasukkan data temperature ke firebase
  if (Firebase.setFloat(firebaseData, "/project/suhu", suhu)) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  //untuk memasukkan data kelembaban ke firebase
  if (Firebase.setFloat(firebaseData, "/project/kelembaban", kelembaban)) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

}

void securityDoor() {
  if (Firebase.setFloat(firebaseData, "/project/jarak", jarak)) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();    
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();   
  }
}

void setup() {

  //menjalankan firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);


}

void loop() {
  // put your main code here, to run repeatedly:

}
