from logging import root
from xml.etree import ElementTree
import os
import pandas as pd
from config import Config

config = Config()
cols = ["filename", "type", "xmin", "xmax", "ymin", "ymax"]
rows = []
fatherpath= config.xml_dir
files= os.listdir(fatherpath)
for i in files:
    file= fatherpath+'/'+str(i)
    print(file)
    file= open(file, encoding= 'utf-8')
    tree = ElementTree.parse(file)

    root = tree.getroot()
    # for elem in root:
    filename = root.find('filename').text

    for obj in root.findall("object"):
        name = obj.find("name").text
        for bndbox in obj.findall("bndbox"):
            xmin = bndbox.find("xmin").text
            xmax = bndbox.find("xmax").text
            ymin = bndbox.find("ymin").text
            ymax = bndbox.find("ymax").text
            rows.append({"filename": filename,
                      "type": name,
                      "xmin": xmin,
                      "xmax": xmax,
                      "ymin": ymin,
                      "ymax": ymax})

df = pd.DataFrame(rows, columns = cols)  

# write dataframe to csv
df.to_csv(config.train_csv)