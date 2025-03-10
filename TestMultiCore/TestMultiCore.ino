void Task1(void *pvParameters);
void Task2(void *pvParameters);

void setup() {
  Serial.begin(115200);

  // Core0でタスクを実行
  xTaskCreatePinnedToCore(
    Task1,   // タスク関数
    "Task1", // タスク名
    2000,    // スタックサイズ（バイト単位）
    NULL,    // パラメータ
    1,       // 優先度
    NULL,    // タスクハンドル
    0        // 実行するコア
  );

  // Core1でタスクを実行
  xTaskCreatePinnedToCore(
    Task2,   // タスク関数
    "Task2", // タスク名
    2000,    // スタックサイズ（バイト単位）
    NULL,    // パラメータ
    1,       // 優先度
    NULL,    // タスクハンドル
    1        // 実行するコア
  );
}

void loop() {
  // メインループは不要 Consolas, 'Courier New', monospace
}

void Task1(void *pvParameters) {
  (void) pvParameters;
  
  for (;;) {
    Serial.println("Task1: Counting...");
    // vTaskDelay(1000 / portTICK_PERIOD_MS); // 1秒待機
    delay(1000);
  }
}

void Task2(void *pvParameters) {
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); // 0.5秒待機
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS); // 0.5秒待機
  }
}
