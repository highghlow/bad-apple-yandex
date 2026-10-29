import cv2
import numpy as np
import sys

cap = cv2.VideoCapture(sys.argv[1])

FRAMERATE = 30 # Must match the video

actual_fps = cap.get(cv2.CAP_PROP_FPS)
if actual_fps != FRAMERATE:
    print(f"The video should be at {FRAMERATE} FPS,")
    print(f"instead it's {actual_fps} FPS")
    exit(1)

frames = []

while True:
    ret, frame = cap.read()
    ret, frame = cap.read()
    ret, frame = cap.read()
    if not ret: break

    res = cv2.resize(frame, (2, 2), interpolation=cv2.INTER_AREA)
    tl = res[0][0][0];
    tr = res[0][1][0];
    b = int(np.average(res[1]));
    frames.append((b, tr, tl));

    cv2.imshow("frame", frame)
    cv2.waitKey(1)

with open("data.h", "w") as f:
    f.write("unsigned char frames[][3] = {\n")
    for a, b, c in frames:
        f.write(f"{{{a},{b},{c}}},\n")
    f.write("};\n")
    f.write(f"size_t frames_len = {len(frames)};\n")
