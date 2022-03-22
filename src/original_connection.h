#include "wifikeys.h" //#define SSID1 "replace with your wifi ssid"    #define PWD1 "replace your wifi password"


void originalConnection() {
    // Configure the camera
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Frame parameters: pick one
    //  config.frame_size = FRAMESIZE_UXGA;
    config.frame_size = FRAMESIZE_SVGA;
    //config.frame_size = FRAMESIZE_QVGA;
    //config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 2;

    #if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
    #endif

    if (cam.init(config) != ESP_OK) {
    Serial.println("Error initializing the camera");
    delay(10000);
    ESP.restart();
    }


    //  Configure and connect to WiFi
    IPAddress ip;

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID1, PWD1);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(F("."));
    }
    ip = WiFi.localIP();
    Serial.println(F("WiFi connected"));
    Serial.println("");
    Serial.print("Stream Link: http://");
    Serial.print(ip);
    Serial.println("/mjpeg/1");


  // Start mainstreaming RTOS task
    xTaskCreatePinnedToCore(
        mjpegCB,
        "mjpeg",
        4 * 1024,
        NULL,
        2,
        &tMjpeg,
        APP_CPU);
}