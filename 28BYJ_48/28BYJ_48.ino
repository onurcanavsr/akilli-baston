// HC-SR04 Ultrasonik Sensör Pin Bağlantıları
#define trigPin 2
#define echoPin 3
#define BUZZER_PIN 7  // Buzzer'ın bağlı olduğu pin
#define MOTOR 4       // Buzzer'ın bağlı olduğu pin

// Mesafe ölçümü için değişkenler
long mesafe;
long sure;

void setup() {
  // Seri haberleşme başlat
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);  // Buzzer pini çıkış olarak ayarlanır
  pinMode(MOTOR, OUTPUT);
  // Trig pinini çıkış yap
  pinMode(trigPin, OUTPUT);
  // Echo pinini giriş yap
  pinMode(echoPin, INPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pininden dönüş süresini ölç
  sure = pulseIn(echoPin, HIGH);

  // Mesafeyi hesapla (ses hızı 343 m/s olarak kabul edilmiştir)
  mesafe = (sure / 2) * 0.0343;

  // Mesafeyi seri monitöre yazdır
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");
  if (mesafe < 10) {
    // Buzzer'ı 1 saniye boyunca tiz bir şekilde çalıştır
    int frekans = 3200;               // Tiz bir frekansı ayarlayın (örneğin, 2000 Hz)
    tone(BUZZER_PIN, frekans, 1000);  // 1000 milisaniye (1 saniye) boyunca çal
    delay(1000);                      // 1000 milisaniye (1 saniye) beklenir
    digitalWrite(MOTOR, HIGH);   // Buzzer aktif hale getirilir
    delay(1000);                      // 1000 milisaniye (1 saniye) beklenir
    digitalWrite(MOTOR, LOW);    // Buzzer kapatılır
    delay(1000);
  }

  // 2 saniyede bir mesafe ölçümü yap
  delay(20);
}
