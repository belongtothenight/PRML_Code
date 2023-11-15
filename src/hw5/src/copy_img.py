import pandas as pd
import os
from PIL import Image
from config import Config

config = Config()

# copy train images
train = pd.read_csv(config.train_csv)
train.head()
fatherpath= config.train_img_dst
data = pd.DataFrame()
data['format'] = train['filename']
for i in range(data.shape[0]):
    image= Image.open(fatherpath+'/'+train['filename'][i])
    image.save('./train_images/'+train['filename'][i])

# copy test images
test = pd.read_csv(config.test_csv)
test.head()
fatherpath= config.test_img_dst
data = pd.DataFrame()
data['format'] = test['filename']
for i in range(data.shape[0]):
    image= Image.open(fatherpath+'/'+test['filename'][i])
    image.save('./test_images/'+test['filename'][i])

print("Done!")
