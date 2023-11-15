#!/bin/bash

# cd /home/11278041/11278041/frcnn_chicken_1
cd "/home/lab353/Documents/GitHub/PRML_Code/src/hw5/frcnn_chicken_1"

pip install --upgrade pip;
pip install pandas matplotlib pillow "keras==2.3" opencv-python scikit-learn;
apt-get update
sudo apt install -y libgl1-mesa-glx;

bash run.sh;

python train_frcnn.py;
python test_frcnn.py;
