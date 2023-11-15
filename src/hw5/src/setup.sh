#!/bin/bash

# cd /home/11278041/11278041/frcnn_chicken_1
cd "/home/lab353/Documents/GitHub/PRML_Code/src/hw5/frcnn_chicken_1"
currentPath=$(pwd)

pip install --upgrade pip;
pip install pandas matplotlib pillow "keras==2.3" opencv-python scikit-learn;
apt-get update
sudo apt install -y libgl1-mesa-glx;

bash "${currentPath}/run.sh";

python3 "${currentPath}/train_frcnn.py";
python3 "${currentPath}/test_frcnn.py";
