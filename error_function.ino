// 40x error handling function
void ErrorCode40X() {
  if (code == 400 || code == 401 || code == 402 || code == 403 || code == 404 || code == 405 || code == 406 || code == 407 || code == 408 || code == 409
      || code == 410 || code == 411 || code == 412 || code == 413 || code == 414 || code == 415 || code == 416 || code == 417 || code == 418 || code == 419
      || code == 421 || code == 422 || code == 423 || code == 424 || code == 425 || code == 426 || code == 428 || code == 429
      || code == 431 || code == 449 || code == 451 || code == 499) {
    static uint32_t tmr;
    if (millis() - tmr >= 60000) {  // if a minute has passed
      conn();                       // call the function to access the station again
    }
  }
}

// 50x error handling function
void ErrorCode50X() {
  if (code == 500 || code == 501 || code == 502 || code == 503 || code == 504 || code == 505 || code == 506 || code == 507 || code == 508 || code == 509
      || code == 510 || code == 511 ||
      || code == 521 || code == 522 || code == 523 || code == 524 || code == 525 || code == 526) {
    static uint32_t tmr;

    if (millis() - tmr >= 60000) {  // if a minute has passed
      conn();                       // call the function to access the station again
    }
  }
}
