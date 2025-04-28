import pyautogui as pag
import random
import time
z = 0

while True:
    x = random.randint(0, 300)
    y = random.randint(0, 300)
    pag.move(x, y)
    time.sleep(60)
    x = x * -1
    y = y * -1
    pag.move(x, y)
    z = z + 1
    print(z)

