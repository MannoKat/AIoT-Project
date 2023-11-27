import time
import sys
from Adafruit_IO import MQTTClient
import requests
import time
import serial.tools.list_ports
try:
    ser = serial.Serial(port="COM3", baudrate=9600)
except:
    print("Can not open the port")

def sendCommand(cmd):
    ser.write(cmd.encode())

mess = ""
def processData(data):
    data = data.replace("!", "")
    data = data.replace("#", "")
    splitData = data.split(":")
    return splitData

def readSerial():
    bytesToRead = ser.inWaiting()
    output = ""
    if (bytesToRead > 0):
        global mess
        mess = mess + ser.read(bytesToRead).decode("UTF-8")
        while ("#" in mess) and ("!" in mess):
            start = mess.find("!")
            end = mess.find("#")
            output = list(processData(mess[start:end + 1]))
            if (end == len(mess)):
                mess = ""
            else:
                mess = mess[end+1:]
    return int(float(output[-1]))

def requestData(cmd):
    sendCommand(cmd)
    time.sleep(1)
    return readSerial()

#AI Camera

from keras.models import load_model  # TensorFlow is required for Keras to work
import cv2  # Install opencv-python
import numpy as np
import base64
from PIL import Image
import io
# Disable scientific notation for clarity
np.set_printoptions(suppress=True)

# Load the model
model = load_model("keras_Model.h5", compile=False)

# Load the labels
class_names = open("labels.txt", "r", encoding="utf-8").readlines()

# CAMERA can be 0 or 1 based on default camera of your computer
camera = cv2.VideoCapture(0)
def AI_Identifying () :
    def compress_image ( image , quality = 25 ) :
        temp_image = Image.fromarray(image)
        buffer = io.BytesIO()
        temp_image.save(buffer, format ='JPEG', quality = quality)
        compressed_image = Image.open(buffer)
        return np.array(compressed_image)

    # Grab the webcamera's image.
    ret, image = camera.read()

    image = compress_image ( image , quality = 25)
    res, frame = cv2.imencode (".jpg ", image)
    data = base64.b64encode(frame)
    # Resize the raw image into (224-height,224-width) pixels
    image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)

    # Show the image in a window
    cv2.imshow("Webcam Image", image)

    # Make the image a numpy array and reshape it to the models input shape.
    image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)

    # Normalize the image array
    image = (image / 127.5) - 1

    # Predicts the model
    prediction = model.predict(image)
    index = np.argmax(prediction)
    class_name = class_names[index]
    confidence_score = prediction[0][index]

    # Print prediction and confidence score
    return class_name [2:] , data
########################################
print("MQTT with Adafruit IO")

AIO_USERNAME = "manhpham"
AIO_KEY = "aio_hrYB11G0XR2Fj9SNPD7NYa1waLEW"

def connected(client):
    print("Server connected ...")
    client.subscribe("multi-prj.light-switch")
    client.subscribe("multi-prj.nebulizer-switch")
    client.subscribe("multi-prj.pump-switch")
    client.subscribe("multi-prj.sunshade-net-switch")

def subscribe(client , userdata , mid , granted_qos):
    print("Subscribed...")

def disconnected(client):
    print("Disconnected...")
    sys.exit (1)

def message(client , feed_id , payload):
    print("Received: " + payload)
    if(feed_id == "equation"):
        global_equation = payload
        print(global_equation)
client = MQTTClient(AIO_USERNAME , AIO_KEY)

client.on_connect = connected  #callback
client.on_disconnect = disconnected
client.on_subscribe = subscribe
client.on_message = message
client.connect()
client.loop_background()


def checkTemperature(temperature):
    if (temperature > 20):
        client.publish("multi-prj.sunshade-net-switch", "1")
        client.publish("multi-prj.notifications", "Temperature is too high!")
    elif (temperature < 10):
        client.publish("multi-prj.sunshade-net-switch", "0")
        client.publish("multi-prj.notifications", "Temperature is too low!")
    else :
        client.publish("multi-prj.sunshade-net-switch", "0")
        
def checkHumidity(humidity):
    if (humidity > 60):
        client.publish("multi-prj.nebulizer-switch", "0")
        client.publish("multi-prj.notifications", "Humidity is too high!")
    elif (humidity < 40):
        client.publish("multi-prj.nebulizer-switch", "1")
        client.publish("multi-prj.notifications", "Humidity is too low!")
    else :
        client.publish("multi-prj.nebulizer-switch", "0")
    
def checkBrightness(brightness):
    if (brightness < 800):
        client.publish("multi-prj.light-switch", "1")
        client.publish("multi-prj.notifications", "Brightness is too low!")
    elif (brightness > 1300):
        client.publish("multi-prj.light-switch", "0")
        client.publish("multi-prj.notifications", "Brightness is too high!")
    else:
        client.publish("multi-prj.light-switch", "0")
    
def checkSoilMoisture(soilmoisture):
    if (soilmoisture < 55):
        client.publish("multi-prj.pump-switch", "1")
        client.publish("multi-prj.notifications", "Soil Moisture is too low!")
    elif (soilmoisture > 70):
        client.publish("multi-prj.pump-switch", "0")
        client.publish("multi-prj.notifications", "Soil Moisture is too high!")
    else:
        client.publish("multi-prj.pump-switch", "0")
pre_ai_result =""
ai_results =""
count = 5
while True:
    count = count - 1
    if (count == 0):
        count = 5
        pre_ai_result = ai_results
        ai_results, ai_cap = AI_Identifying()
        if pre_ai_result != ai_results:
            client.publish("multi-prj.notifications", ai_results)
            client.publish("multi-prj.ai-camera",ai_cap)
        time.sleep(5)
        temperature = requestData("t")
        time.sleep(5)
        humidity = requestData("h")
        time.sleep(5)
        brightness = requestData("b")
        time.sleep(5)
        soilmoisture = requestData("s")
        time.sleep(5)
        
        # print(temperature)
        # print(humidity)
        # print(brightness)
        # print(soilmoisture)
        client.publish("multi-prj.temperature", temperature)
        client.publish("multi-prj.humidity", humidity)
        client.publish("multi-prj.light-density", brightness)
        client.publish("multi-prj.soil-moisture", soilmoisture)
        checkTemperature(temperature)
        checkHumidity(humidity)
        checkBrightness(brightness)
        checkSoilMoisture(soilmoisture)
    time.sleep(1)

    keyboard_input = cv2.waitKey(1)
        # 27 is the ASCII for the esc key on your keyboard.
    if keyboard_input == 27:
        break
      
# while True:
#     time.sleep(5)
#     temperature = requestData("t")
#     time.sleep(5)
#     humidity = requestData("h")
#     time.sleep(5)
#     brightness = requestData("b")
#     time.sleep(5)
#     soilmoisture = requestData("s")
#     time.sleep(5)
    
#     # print(temperature)
#     # print(humidity)
#     # print(brightness)
#     # print(soilmoisture)
#     client.publish("multi-prj.temperature", temperature)
#     client.publish("multi-prj.humidity", humidity)
#     client.publish("multi-prj.light-density", brightness)
#     client.publish("multi-prj.soil-moisture", soilmoisture)
#     checkTemperature(temperature)
#     checkHumidity(humidity)
#     checkBrightness(brightness)
#     checkSoilMoisture(soilmoisture)

