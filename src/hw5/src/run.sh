run_xml_to_csv=0    # 1: run xml_to_csv.py
run_copy_img=1      # 1: run copy_img.py
run_annotate=1      # 1: run annotate.py

if [ $run_xml_to_csv -eq 1 ]; then python3 xml_to_csv.py; fi
if [ $run_copy_img   -eq 1 ]; then python3 copy_img.py;   fi
if [ $run_annotate   -eq 1 ]; then python3 annotate.py;   fi
