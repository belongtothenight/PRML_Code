#!/bin/bash

run_env_setup=1     # 1: run env_setup
run_xml_to_csv=0    # 1: run xml_to_csv.py
run_copy_img=1      # 1: run copy_img.py
run_annotate=1      # 1: run annotate.py
run_train=1         # 1: run train_frcnn.py
run_test=1          # 1: run test_frcnn.py

srcPath="/home/lab353/Documents/GitHub/PRML_Code/src/hw5/src"
projPath="/home/lab353/Documents/GitHub/PRML_Code/src/hw5/frcnn_chicken_1"

function env_setup () {
    sudo apt install -y libgl1-mesa-glx
    python3 -m venv venv
    source venv/bin/activate
    pip install --upgrade pip
    pip install pandas matplotlib pillow 'keras==2.4.3' opencv-python scikit-learn keras-rcnn
    python3 -m pip install 'tensorflow[and-cuda]==2.4.0'
    python3 -c "import tensorflow as tf; print(tf.config.list_physical_devices('GPU'))"
    nvidia-smi
}

if [ $run_env_setup  -eq 1 ]; then env_setup;                           fi
if [ $run_xml_to_csv -eq 1 ]; then python3 "${projPath}/xml_to_csv.py"; fi
if [ $run_copy_img   -eq 1 ]; then python3 "${projPath}/copy_img.py";    fi
if [ $run_annotate   -eq 1 ]; then python3 "${projPath}/annotate.py";    fi
if [ $run_train      -eq 1 ]; then python3 "${srcPath}/train_frcnn.py"; fi
if [ $run_test       -eq 1 ]; then python3 "${srcPath}/test_frcnn.py";  fi

