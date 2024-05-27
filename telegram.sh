#!/bin/bash
TELEGRAM_TOKEN="7068843655:AAFWpeIxf-gsCG-2sdAfI0IF7Gl18dXkoj4"
TELEGRAM_CHAT_ID="764346210"
MESSAGE="$CI_JOB_NAME прошел со статусом $CI_JOB_STATUS!"

curl -s -X POST https://api.telegram.org/bot$TELEGRAM_TOKEN/sendMessage -d chat_id=$TELEGRAM_CHAT_ID -d text="$MESSAGE" > /dev/null
