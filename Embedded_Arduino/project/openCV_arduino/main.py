import cv2
import mediapipe
import serial
import time

#USE serial
arduino = serial.Serial('COM5', 9600)
time.sleep(5)

#USE mediapipe
mediapipe_hands = mediapipe.solutions.hands
hands = mediapipe_hands.Hands()
mediapipe_drawing = mediapipe.solutions.drawing_utils

# 4  - thumb
# 8  - index  finger
# 12 - middle finger
# 16 - ring   finge
# 20 - little finge

def detect_fingers(image, hand_landmarks):
    finger_tips = [8,12,16,20] 
    thumb_tip = 4
    finger_states = [0, 0, 0, 0, 0]

    for idx, tip in enumerate(finger_tips):
        if hand_landmarks.landmark[tip].y < hand_landmarks.landmark[tip - 2].y:
            finger_states[idx + 1] = 1

    if hand_landmarks.landmark[thumb_tip].x < hand_landmarks.landmark[thumb_tip - 1].x:
        finger_states[0] = 1 

    return finger_states

#USE cv2
cap = cv2.VideoCapture(0)

while cap.isOpened():
    success, image = cap.read()
    if not success:
        break

    image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
    results = hands.process(image)
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mediapipe_drawing.draw_landmarks(image, hand_landmarks, mediapipe_hands.HAND_CONNECTIONS)
            fingers_state = detect_fingers(image, hand_landmarks)
            arduino.write(bytes(fingers_state)) 
            print(f"Fingers State: {fingers_state}")

    cv2.imshow('Hand Tracking', image)
    if cv2.waitKey(5) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()