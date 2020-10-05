/*
 * RF24TrashLogAppender.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#include "RF24TrashLogAppender.h"

RF24TrashLogAppender::RF24TrashLogAppender()
{

}

void RF24TrashLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const char *message)
{
   // do nothing, everything goes to trash
}

void RF24TrashLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message)
{
   // do nothing, everything goes to trash
}

