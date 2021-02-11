#include <Arduino.h>
#include <LittleFS.h>
#include <ESPDateTime.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait a little for Serial to connect

  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
}

void loop() {
  fs::Dir fs_p = LittleFS.openDir("/");

  Serial.print("FS creation time: ");
  Serial.println(DateTimeParts::from(fs_p.fileCreationTime(), 0).toString());

  Serial.println("Listing /");
  while(fs_p.next()){
    if(fs_p.isFile()) {
      Serial.printf("%5d\t", fs_p.fileSize());
    } else if(fs_p.isDirectory()) {
      Serial.print("<dir>\t");
    } else {
      Serial.print("???\t");
    }
  
    Serial.print(DateTimeParts::from(fs_p.fileCreationTime(), 0).toString());
    Serial.print("\t");
    Serial.println(fs_p.fileName());
  }

  Serial.println();

  delay(5000);
}