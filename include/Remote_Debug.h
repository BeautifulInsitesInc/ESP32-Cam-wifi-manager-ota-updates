#ifndef REMOTE_DEBUG_H
#define REMOTE_DEBUG_H

#include "PapertrailLogger.h"  //https://github.com/atomic14/ESP32RemoteLogging

#define PAPERTRAIL_HOST "logs2.papertrailapp.com"
#define PAPERTRAIL_PORT 18579

PapertrailLogger *errorLog;
PapertrailLogger *warningLog;
PapertrailLogger *noticeLog;
PapertrailLogger *debugLog;
PapertrailLogger *infoLog;

void paperTrailsetup() {
  errorLog = new PapertrailLogger(PAPERTRAIL_HOST, PAPERTRAIL_PORT, LogLevel::Error, "\033[0;31m", "papertrail-test", "testing");
  warningLog = new PapertrailLogger(PAPERTRAIL_HOST, PAPERTRAIL_PORT, LogLevel::Warning, "\033[0;33m", "papertrail-test", "testing");
  noticeLog = new PapertrailLogger(PAPERTRAIL_HOST, PAPERTRAIL_PORT, LogLevel::Notice, "\033[0;36m", "papertrail-test", "testing");
  debugLog= new PapertrailLogger(PAPERTRAIL_HOST, PAPERTRAIL_PORT, LogLevel::Debug, "\033[0;32m","papertrail-test", "testing");
  infoLog = new PapertrailLogger(PAPERTRAIL_HOST, PAPERTRAIL_PORT, LogLevel::Info, "\033[0;34m", "papertrail-test", "testing");
  Serial.println("Up and running");
  debugLog->print("This is a test");
  debugLog->print("This is another test");
}


int count = 0;
void paperTrailLoop() {
  infoLog->println("Looping");
  infoLog->printf("In the loop %d\n", count);

  errorLog->printf("In the loop error %d\n", count);
  warningLog->printf("In the loop warning %d\n", count);
  noticeLog->printf("In the loop notice %d\n", count);
  debugLog->printf("In the loop debug %d\n", count);
  infoLog->printf("In the loop info %d\n", count);

  count++;
  delay(3000);
}

#endif

